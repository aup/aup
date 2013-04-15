<?php

/**
 * @file
 * Cron callbacks for the Course module.
 */

/**
 * Synchronizes all Courses with CAMS.
 */
function course_sync() {
  $rc = WATCHDOG_INFO;
  aup_custom_task_start();

  if (!cams_is_available()) {
    $report[] = t('[ERROR] CAMS is not available');
    return aup_custom_task_end($report, WATCHDOG_ERROR);
  }
  
  if (!$active_terms = cams_query('term', 'get', 'future')) {
    $report[] = t('[ERROR] No active term found in CAMS');
    return aup_custom_task_end($report, WATCHDOG_ERROR);
  }

  $terms = array();
  foreach ($active_terms as $term) {
    $terms[] = $term->name;
  }
  $report[] = t('[INFO] Active terms in CAMS: @terms', array(
                  '@terms' => implode(', ', $terms)));
  
  /*
   * Course Master Synchronization
   */
  $report[] = '';
  $report[] = '[INFO] COURSE MASTERS SYNCHRONIZATION';

  // Unpublish all course masters
  $count = db_query("UPDATE {node} SET status=0 WHERE type='course_master'")->rowCount();
  $report[] = "[INFO] $count published course masters found in Drupal.";
  
  // Update active course masters in CAMS
  if (!$course_masters = cams_query('course_master', 'get')) {
    $report[] = t('[ERROR] No active course master found in CAMS');
    return aup_custom_task_end($report, WATCHDOG_ERROR);
  }
  else {
    $report[] = "[INFO] " . count($course_masters) . " active course masters found in CAMS.";
    foreach ($course_masters as $course_master) {
    _course_master_sync($course_master, $report, $rc);
    }
  }
  
  // Report remaining unpublished course masters
  $query = db_query("SELECT title FROM {node} WHERE type='course_master' AND status=0");
  $unpublished = array();
  while ($title = $query->fetchField()) {
  	$unpublished[] = $title;
  }
  $report[] = t("[INFO] @count unpublished course masters:<br/>!list", array(
    '@count' => (int) count($unpublished),
    '!list'  => implode('<br/>', $unpublished)));

  /*
   * Course Synchronization
   */
  $report[] = '';
  $report[] = '[INFO] COURSE OFFERS SYNCHRONIZATION';
  
  // Unpublish all course offers
  $count = db_query("UPDATE {node} SET status=0 WHERE type='course'")->rowCount();
  $report[] = "[INFO] $count published course offers found in Drupal.";
  
  // Update active course offers in CAMS
  foreach ($active_terms as $term) {
    $courses = cams_query('course', 'get_offers', $term->id);
    $report[] = t("[INFO] @count active courses for @term found in CAMS.", array(
                    '@count' => count($courses),
                    '@term'  => $term->name));
    if ($courses) {
      foreach ($courses as $course) {
        _course_offer_sync($course, $report, $rc);
        //break;
      }
    }
  }

  // Report remaining unpublished course offers
  $query = db_query("SELECT title FROM {node} WHERE type='course' AND status=0");
  $unpublished = array();
  while ($title = $query->fetchField()) {
    $unpublished[] = $title;
  }
  $report[] = t("[INFO] @count unpublished courses:<br/>!list", array(
                '@count' => (int) count($unpublished),
                '!list'  => implode('<br/>', $unpublished)));

  return aup_custom_task_end($report, $rc);
}

/**
 * Synchronizes a Course Master with CAMS.
 *
 * @param object $course
 *   A course master retrieved from CAMS
 *   
 * @param array $report
 *   Synchronization report
 *   
 * @param int $rc
 *   WATCHDOG_* status      
 */
function _course_master_sync($course, &$report, &$rc) {
	if (!is_object($course)) {
		$rc = WATCHDOG_ERROR;
		return FALSE;
	}

	// Load the node if it already exists
	$query = db_query("SELECT entity_id FROM {field_data_field_cams_id}
                      WHERE bundle='course_master'
                        AND field_cams_id_value = :id", array(
                    ':id' => $course->camsID));
	if ($nid = $query->fetchField()) {
    $node = node_load($nid);
  }

	// @ignore sniffer_files_linelength_toolong
	// DEBUG watchdog('debug', '<pre>Course: ' . print_r($course, TRUE) . '</pre>');
	// DEBUG watchdog('debug', '<pre>Node: ' . print_r($node, TRUE) . '</pre>');
	$node->type = 'course_master';
	$node->uid = 0;
	$node->status = 1;
	$node->field_course_code[LANGUAGE_NONE][0]['value'] = $course->code;
	$node->field_course_name[LANGUAGE_NONE][0]['value'] = $course->name;
	$node->field_course_description[LANGUAGE_NONE][0]['value'] = utf8_encode($course->description);
	$node->field_course_discipline[LANGUAGE_NONE][0]['value'] = $course->discipline;
	$node->field_course_type[LANGUAGE_NONE][0]['value'] = $course->type;
	$node->field_course_credits[LANGUAGE_NONE][0]['value'] = $course->credits;
	$node->field_course_canrepeat[LANGUAGE_NONE][0]['value'] = ($course->canRepeat == 'Yes') ? 1 : 0;
	$node->field_course_level[LANGUAGE_NONE][0]['value'] = $course->level;
	$node->field_course_prerequisites[LANGUAGE_NONE][0]['value'] = $course->prerequisites;
	$node->field_course_corequisites[LANGUAGE_NONE][0]['value'] = $course->corequisites;
	$node->field_cams_id[LANGUAGE_NONE][0]['value'] = $course->camsID;
	$node->field_cams_last_update[LANGUAGE_NONE][0]['value'] = REQUEST_TIME;
	if ($equivalencies = cams_query('course_master', 'get_equivalencies', $course->camsID)) {
		$i = 0;
		foreach ($equivalencies as $equivalency) {
      if ($equivalent_eid = db_query("
            SELECT entity_id FROM {field_data_field_cams_id}
             WHERE bundle='course_master'
               AND field_cams_id_value = :id", array(
            ':id' => $equivalency))->fetchField()) {
        $node->field_course_equivalencies[LANGUAGE_NONE][$i++]['target_id'] = $equivalent_eid;
      }
		}
	}

  node_save($node);

  if (!$nid) {
  			$report[] = t('[INFO] Course Master !course created', array(
  					'!course' => $node->title));
  }
  return TRUE;
}

/**
 * Synchronizes a Course Offer with CAMS.
 *
 * @param object $course
 *   A course offer retrieved from CAMS
 *   
  * @param array $report
 *   Synchronization report
 *   
 * @param int $rc
 *   WATCHDOG_* status
 */
function _course_offer_sync($course, &$report, &$rc) {
	if (!is_object($course)) {
		$rc = WATCHDOG_ERROR;
		return FALSE;
	}

  // Load the node if it already exists
  $query = db_query("
    SELECT entity_id
  		FROM {field_data_field_cams_id}
     WHERE bundle='course'
       AND field_cams_id_value = :id", array(
    ':id' => $course->camsID)
  );
  if ($nid = $query->fetchField()) {
    $node = node_load($nid);
  }

	// @ignore sniffer_files_linelength_toolong
	// DEBUG watchdog('debug', '<pre>Course: ' . print_r($course, TRUE) . '</pre>');
	// DEBUG watchdog('debug', '<pre>Node: ' . print_r($node, TRUE) . '</pre>');
	$node->type = 'course';
	$node->uid = 0;
	$node->status = 1;
	$node->field_course_term[LANGUAGE_NONE][0]['value'] = $course->term;
	$node->field_course_code[LANGUAGE_NONE][0]['value'] = $course->code;
	$node->field_course_name[LANGUAGE_NONE][0]['value'] = $course->name;
	$node->field_course_section[LANGUAGE_NONE][0]['value'] = $course->section;
	$node->field_course_description[LANGUAGE_NONE][0]['value'] = utf8_encode($course->description);
	$node->field_course_discipline[LANGUAGE_NONE][0]['value'] = $course->discipline;
	$node->field_course_type[LANGUAGE_NONE][0]['value'] = $course->type;
	$node->field_course_credits[LANGUAGE_NONE][0]['value'] = $course->credits;
	$node->field_course_canrepeat[LANGUAGE_NONE][0]['value'] = ($course->canRepeat == 'Yes') ? 1 : 0;
	$node->field_course_level[LANGUAGE_NONE][0]['value'] = $course->level;
	$node->field_course_notes[LANGUAGE_NONE][0]['value'] = $course->notes;
	$node->field_course_startdate[LANGUAGE_NONE][0]['value'] = $course->startDate;
	$node->field_course_enddate[LANGUAGE_NONE][0]['value'] = $course->endDate;
	$node->field_course_examdate[LANGUAGE_NONE][0]['value'] = $course->examDate;
	$node->field_cams_id[LANGUAGE_NONE][0]['value'] = $course->camsID;
	$node->field_cams_last_update[LANGUAGE_NONE][0]['value'] = REQUEST_TIME;

  // Course Master
  $query = db_query("SELECT entity_id
                       FROM {field_data_field_cams_id}
                      WHERE bundle = 'course_master'
                        AND field_cams_id_value = :id", array(
                    ':id' => $course->masterID));
  if ($eid = $query->fetchField()) {
    $node->field_course_course_master[LANGUAGE_NONE][0]['target_id'] = $eid;
  }
  else {
    $rc = WATCHDOG_WARNING;
    $report[] = t('[WARNING] Course Master @course_master not found', array(
      '@course_master' => $course->masterID));
  }

  // Cross listed courses
  $query = db_query("SELECT entity_id
                       FROM {field_data_field_cams_id}
                      WHERE bundle = 'course'
                        AND field_cams_id_value = :id", array(
                    ':id' => $course->crosslisted));
  if ($eid = $query->fetchField()) {
    $node->field_course_crosslisted[LANGUAGE_NONE][0]['target_id'] = $eid;
  }

  // Professors
  unset($node->field_course_professors);
  if ($professors = cams_query('course', 'get_professors', $course->code, $course->termID)) {
    $i = 0;
    foreach ($professors as $professor) {
      $query = db_query("SELECT uid FROM {users}
                          WHERE name = :netid", array(
                        ':netid' => $professor->netID));
      if ($uid = $query->fetchField()) {
        $node->field_course_professors[LANGUAGE_NONE][$i++]['target_id'] = $uid;
      }
      else {
        $rc = WATCHDOG_WARNING;
        $report[] = t('[WARNING] Professor @professor not found', array(
          '@professor' => "$professor->firstName $professor->lastName ($professor->netID)"));
      }
    }
  }

  // Students
  unset($node->field_course_students);
  if ($students = cams_query('course', 'get_students', $course->code, $course->termID)) {
    $i = 0;
    foreach ($students as $netID) {
      $query = db_query("SELECT uid FROM {users}
                          WHERE name = :netid", array(
                        ':netid' => $netID));
      if ($uid = $query->fetchField()) {
        $node->field_course_students[LANGUAGE_NONE][$i++]['target_id'] = $uid;
      }
      else {
        $rc = WATCHDOG_WARNING;
        $report[] = t('[WARNING] Student @netID not found', array(
          '@netID' => $netID));
      }
    }
  }

  // Book List
  //watchdog('debug', '<pre>'.print_r($node->field_course_books, true).'</pre>');
  unset($node->field_course_books);
  if ($books = cams_query('course', 'get_book_list', $course->code, $course->termID)) {
    foreach ($books as $book) {
      $values = array(
        'field_name' => 'field_course_books',
        'field_course_book_title' => array(
          LANGUAGE_NONE => array(array('value' => $book->title)),
        ),
        'field_course_book_author' => array(
          LANGUAGE_NONE => array(array('value' => $book->author)),
        ),
        'field_course_book_publisher' => array(
          LANGUAGE_NONE => array(array('value' => $book->publisher)),
        ),
        'field_course_book_isbn' => array(
          LANGUAGE_NONE => array(array('value' => $book->ISBN)),
        ),
      );
      $entity = entity_create('field_collection_item', $values);
      $entity->setHostEntity('node', $node);
      $entity->save();
    }
  }

  // Schedules
  unset($node->field_timetable);
  unset($node->field_course_schedule);
  $i = 0;
  if ($schedules = cams_query('course', 'get_schedules', $course->code, $course->termID)) {
    // DEBUG watchdog('debug', $course->code . ' Schedules:<pre>' . print_r($schedules, TRUE) . '</pre>');
    foreach ($schedules as $schedule) {
      foreach(str_split($schedule->offerDays) as $camsDay) {
        if (!$day = strtoupper(cams_query('convert', 'camsday2phpday', $camsDay, FALSE))) {
          $rc = WATCHDOG_WARNING;
          $report[] = t('[WARNING] Day (@day) unknown for @course', array(
                        '@day'    => $camsDay,
                        '@course' => "$course->name ($course->code)"));
          $day = 'UN';
        }
        $query = db_query('SELECT entity_id FROM {field_data_field_room_code}
                            WHERE field_room_code_value = :id', array(
                          ':id' => $schedule->room));
        if (!$room_eid = $query->fetchField()) {
          $node_room = new stdClass();
          $node_room->type = 'room';
          $node_room->uid = 0;
          $node_room->status = 1;
          $node_room->field_room_code[LANGUAGE_NONE][0]['value'] = $schedule->room;
          node_save($node_room);
          $report[] = t('[INFO] Room @room created', array(
                        '@room' => $schedule->room));
          $room_eid = $node_room->nid;
        }

        // Timetable.
        $start_time = substr($schedule->offerTimeFrom, 0, 5);
        $end_time = substr($schedule->offerTimeTo, 0, 5);
//watchdog('debug', "$i day = $camsDay -> " . cams_query('convert', 'camsday2daynb', $camsDay));
        if ($day != 'UN') {
          $node->field_timetable[LANGUAGE_NONE][$i++] = array(
            'day'          => cams_query('convert', 'camsday2daynb', $camsDay),
            'start_minute' => cams_query('convert', 'camstime2minutes', $start_time),
            'end_minute'   => cams_query('convert', 'camstime2minutes', $end_time),
            'description'  => $schedule->room,
          );
        }

        // Course Schedule Field Collection.
        $values = array();
        $values['field_name'] = 'field_course_schedule';

        // Room.
        $values['field_course_schedule_room'][LANGUAGE_NONE][0]['target_id'] = $room_eid;

        // Days.
        $days = array();
        $values['field_course_schedule_day'][LANGUAGE_NONE][0]['value'] = $day;
        $days[] = $day;

        // Start and End Offer Times.
        $values['field_course_schedule_starttime'][LANGUAGE_NONE][0]['value'] = $start_time;
        $values['field_course_schedule_endtime'][LANGUAGE_NONE][0]['value'] = $end_time;

	      /*// Repeating date.
	      $startDate = $course->startDate . ' ' . $schedule->offerTimeFrom;
	      $endDate = $course->endDate . ' ' . $schedule->offerTimeTo;
	
	      // Compute the real start day.
	      // DEBUG drupal_set_message($startDate);
	      $startDate = new DateObject($startDate);
	      // DEBUG drupal_set_message(cams_query('convert', 'camsday2phpday', $schedule->offerDays[0], TRUE));
	      $startDate->modify('+1 ' . cams_query('convert', 'camsday2phpday', $schedule->offerDays[0], TRUE));
	      // DEBUG drupal_set_message("$startDate -> $endDate");
	      $course->realStartDate = $startDate->format('Y-m-d'); //substr($startDate, 0, 10);
	
	      $until = str_replace('-', '', $course->endDate);
	      $rrule = 'RRULE:FREQ=WEEKLY;INTERVAL=1;BYDAY='.implode(',', $days).';UNTIL='.$until.'T215959Z;WKST=MO';
	  
	      // DEBUG drupal_set_message('<pre>' . print_r(date_repeat_calc($rrule, $startDate, $endDate), TRUE) . '</pre>');return TRUE;
	      $repeats = array(
	        'start' => date_repeat_calc($rrule, $course->realStartDate.' '.$schedule->offerTimeFrom, $course->endDate.' '.$schedule->offerTimeFrom),
	        'end' => date_repeat_calc($rrule, $course->realStartDate.' '.$schedule->offerTimeTo, $course->endDate.' '.$schedule->offerTimeTo),
	      );
	
	      for ($i = 0 ; $i < count($repeats['start']) ; $i++) {
	        $values['field_date'][LANGUAGE_NONE][$i] = array(
	          'value' => $repeats['start'][$i],
	          'value2' => $repeats['end'][$i],
	          'rrule' => $rrule,
	        );
	      }*/
        
        // DEBUG watchdog('debug', 'Values:<pre>' . print_r($values, TRUE) . '</pre>');
        $entity = entity_create('field_collection_item', $values);
        $entity->setHostEntity('node', $node);
        $entity->save();
      }
    }
  }

  // DEBUG watchdog('debug', 'timetable:<pre>' . print_r($node->field_timetable[LANGUAGE_NONE], TRUE) . '</pre>');
  
  // DEBUG  watchdog('debug', 'Scheduling:<pre>' . print_r($node->field_date[LANGUAGE_NONE], TRUE) . '</pre>');
  
	node_save($node);

	if (!$nid) {
	  $report[] = t('[INFO] Course !course created', array(
			'!course' => $node->title));
	}
	return TRUE;
}

/**
 * TEMP.
 */
function course_master_delete() {
  $query = db_query("SELECT nid FROM {node} WHERE type IN ('course_master')");
  while ($nid = $query->fetchField()) {
    node_delete($nid);
  }
  return 'OK';
}

/**
 * TEMP.
 */
function course_delete() {
	$query = db_query("SELECT nid FROM {node} WHERE type IN ('course')");
	while ($nid = $query->fetchField()) {
		node_delete($nid);
	}
	return 'OK';
}
