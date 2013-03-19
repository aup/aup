<?php
/*
 * CAMS Integration
 * Integration between CAMS and MyAUP
 *
 * @author: Pierre-Yves Vasener <pvasener@aup.edu>
 */
 
/*
 * COURSE SCHEDULE FUNCTIONS
 */

/*
 * TODO
 */
function cams_course_schedule_sync($node) {
  // Get the courses of the course term
  $courses = cams_query('course', 'get', $node->field_course_term[0]['value']);
	
  if ($course = $courses[$node->field_course_name[0]['value']]) {
  	// Get the schedule of the course
  	if (!$schedules = cams_query('course', 'get_schedules', $node->field_course_name[0]['value'], $node->field_course_term[0]['value'])) {
  	  $report[] = t("[WARNING] Unable to find schedules for course @course",
  		array('@course' => $node->field_course_name[0]['value']. " in " . $node->field_course_term[0]['value']));
  	  $rc = SCHEDULED_TASKS_REPORT_WARNING;
  	}
  	else {
  	  foreach ($schedules as $schedule) {
  		// DEBUG drupal_set_message('<pre>' . print_r($schedule, TRUE) . '</pre>');
  		if ($msg = _cams_course_schedule_sync($node, $course, $schedule)) {
  		  $rc = SCHEDULED_TASKS_REPORT_WARNING;
  		  $report = array_merge((array)$report, (array)$msg);
  		}
  	  }
  	}
  } else {
	$report[] = t("Unable to get course info in CAMS for @course in @term",
		array('@course' => $node->field_course_name[0]['value'],
	           '@term'   => $node->field_course_term[0]['value']));
  }
  return $report;
}

/*
 * TODO
 */
function cams_course_schedule_sync_all()  {
  $rc = SCHEDULED_TASKS_REPORT_OK;
  $startTime = time();
  watchdog('cams_course_schedule_sync_all', "Task launched");

  if (!cams_is_available()) {
  	$report[] = t('[ERROR] CAMS is not available');
  	$rc = SCHEDULED_TASKS_REPORT_ERROR;
  }
  else {
  	db_query("UPDATE {node} SET status=0 WHERE type='course_schedule'");
  	
    // Report
    $report[] = "Report of cams_course_schedule_sync_all:";
    
    $activeTerms = variable_get('cams_active_terms', NULL);
  
    foreach ($activeTerms as $activeTerm) {
      $courses = cams_query('course', 'get', $activeTerm);

      $report[] = '';
      $report[] = count($courses) . " courses found in $activeTerm in CAMS.";
      $report[] = '';
        
      foreach ($courses as $course) {
    	if (!$nid = db_result(db_query("SELECT nid FROM {content_type_course} WHERE field_course_camsid_value = %d", $course->cams_id))) {
      	  $report[] = t("[ERROR] Unable to find the node for course @course",
      	                array('@course' => "$course->name in $course->term"));
      	  $rc = SCHEDULED_TASKS_REPORT_ERROR;
        }
        else {
          $node = node_load($nid);
    	
    	  if (!$schedules = cams_query('course', 'get_schedules', $course->name, $course->termid)) {
            $report[] = t("[WARNING] Unable to find schedules for course @course",
    		              array('@course' => "$course->name in $course->term"));
            $rc = SCHEDULED_TASKS_REPORT_WARNING;
    	  }
    	  else {
    	    foreach ($schedules as $schedule) {
     	      // DEBUG drupal_set_message('<pre>' . print_r($schedule, TRUE) . '</pre>');
    	      if ($msg = _cams_course_schedule_sync($node, $course, $schedule)) {
    	        $rc = SCHEDULED_TASKS_REPORT_WARNING;
    	        $report = array_merge((array)$report, (array)$msg);
    	      }
    	    }
    	  }
    	}
      }
    }
    
    $query = db_query("SELECT title FROM {node} WHERE type='course_schedule' AND status=0");
    $unpublished = array();
    while ($title = db_result($query)) {
    	$unpublished[] = $title;
    }
    $report[] = '';
    $report[] = t("@count unpublished course schedules:\r\n@list",
    array('@count' => (int)count($unpublished),
    	                     '@list'  => implode("\r\n", $unpublished)));
        
  }
  
  if (!scheduled_tasks_report($rc,
                                'cams_course_schedule_sync_all',
                                'Course Schedule Synchronisation with CAMS Report',
  $report,
  variable_get('scheduled_tasks_report_email', null))) {
  	watchdog('cams_course_schedule_sync_all', 'Unable to send the script report', array(), WATCHDOG_WARNING);
  	$rc = SCHEDULED_TASKS_REPORT_WARNING;
  }
    
  return $rc;
}

/*
 * TODO
*/
function _cams_course_schedule_sync($courseNode, $course, $schedule) {
  $nid = db_result(db_query("SELECT nid FROM {content_type_course_schedule} WHERE field_course_schedule_camsid_value = %d", $schedule[0]->scheduleID));
  if ($nid) {
    $node = node_load($nid);
  }
  
  $offerDays = array();
  if (in_array(trim($schedule[0]->OfferDays), array('', 'N\A'))) {
    $msg[] = t("[WARNING] '@days' are not valid days for a schedule for @course.", 
          array('@days'   => $schedule[0]->OfferDays,
                 '@course' => "$course->name in $course->term"));
    return $msg;
  }
  else {
    $i = 0;
    foreach(str_split($schedule[0]->OfferDays) as $offerDay) {
      if ($offerDay = strtoupper(cams_query('convert', 'camsday2phpday', $offerDay, FALSE))) {
        $node->field_course_schedule_days[$i++]['value'] = $offerDay;
        $offerDays[] = $offerDay;
      }
    }
  }

  $details = implode('/', array(
      $course->term,
      implode('-',  $offerDays),
      substr($schedule[0]->OfferTimeFrom, 0, 5),
      substr($schedule[0]->OfferTimeTo, 0, 5),
    )
  );
  $node->title = "$course->name in " . $schedule[0]->room . ' (' . $details . ')';
  $node->type = 'course_schedule';
  $node->uid = 1;
  $node->status = 1;
  $node->field_course_schedule_camsid[0]['value'] = $schedule[0]->scheduleID;
  $node->field_misc_cams_last_update[0]['value'] = time();
  if (!$roomNid = db_result(db_query("SELECT nid FROM {node} WHERE type = 'room' and title = '%s'", $schedule[0]->room))) {
  	$msg[] = t("[WARNING] '@room' room does not exist in MyAUP for @course.",
  	           array('@room'   => $schedule[0]->room,
  	                 '@course' => "$course->name in $course->term"));
  } 
  $node->field_course_schedule_course[0]['nid'] = $courseNode->nid;
  $node->field_course_schedule_room[0]['nid'] = $roomNid;
  // TODO TEMP drupal_set_message(print_r($schedule[0]->OfferDays, TRUE));
  $node->field_course_schedule_startdate[0] = array(
    'value' => $course->StartDate,
    'timezone' => 'Europe/Paris',
    'timezone_db' => 'Europe/Paris',
    'date_type' => 'date',
  );
  $node->field_course_schedule_enddate[0] = array(
      'value' => $course->EndDate,
      'timezone' => 'Europe/Paris',
      'timezone_db' => 'Europe/Paris',
      'date_type' => 'date',
  );

  $startDate = $course->StartDate . ' ' . $schedule[0]->OfferTimeFrom;
  $endDate = $course->EndDate . ' ' . $schedule[0]->OfferTimeTo;

  //drupal_set_message($startDate);
  $startDate = date_make_date($startDate);
  //drupal_set_message(cams_query('convert', 'camsday2phpday', $schedule[0]->OfferDays[0], TRUE));
  date_modify($startDate, '+1 ' . cams_query('convert', 'camsday2phpday', $schedule[0]->OfferDays[0], TRUE));
  $startDate = date_convert($startDate, DATE_OBJECT, DATE_DATETIME);  
  //drupal_set_message("$startDate -> $endDate");
  $course->RealStartDate = substr($startDate, 0, 10);
  
  $until = str_replace('-', '', $course->EndDate);
  $rrule = 'RRULE:FREQ=WEEKLY;INTERVAL=1;BYDAY='.implode(',', $offerDays).';UNTIL='.$until.'T215959Z;WKST=MO';
  
  //drupal_set_message('<pre>' . print_r(date_repeat_calc($rrule, $startDate, $endDate), TRUE) . '</pre>');return TRUE;
  $repeats = array();
  $repeats = array(
    'start' => date_repeat_calc($rrule, $course->RealStartDate.' '.$schedule[0]->OfferTimeFrom, $course->EndDate.' '.$schedule[0]->OfferTimeFrom),
    'end' => date_repeat_calc($rrule, $course->RealStartDate.' '.$schedule[0]->OfferTimeTo, $course->EndDate.' '.$schedule[0]->OfferTimeTo),
  );
  for ($i = 0 ; $i < count($repeats['start']) ; $i++) {
    $node->field_course_schedule[$i] = array(
      'value' => $repeats['start'][$i],
      'value2' => $repeats['end'][$i],
      'rrule' => $rrule,
      'timezone' => 'Europe/Paris',
      'timezone_db' => 'Europe/Paris',
      'date_type' => 'date',
    );
  }
  //drupal_set_message('<pre>' . print_r($node->field_course_schedule, TRUE) . '</pre>');
  
  $i = 0;
  foreach ($schedule as $item) {
    $instructor = db_result(db_query("SELECT uid FROM {users} WHERE name = '%s'", $item->netid));
    $node->field_course_schedule_instructor[$i]['uid'] = $instructor;
    $i++;
  }
  // DEBUG   drupal_set_message('<pre>' . print_r($schedule, TRUE) . '</pre>');
  // DEBUG   drupal_set_message('<pre>' . print_r($node, TRUE) . '</pre>');
  
  node_save($node);

  // TODO Add the course schedule in the course OG
  if (!db_result(db_query("SELECT * FROM {og_ancestry} WHERE nid = %d AND group_nid = %d", $node->nid, $courseNode->nid))) {
    db_query("INSERT INTO {og_ancestry} (nid, group_nid) VALUES ('%d', '%d');", $node->nid, $courseNode->nid);
  }
  
  /*$msg = t('Course Schedule !course_schedule @action',
      array('!course_schedule' => l($node->title, "node/$node->nid"),
          '@action' => $nid ? 'updated' : 'created'));*/
  
  return $msg;
}  