<?php

/**
 * @file
 * Cron callbacks for the Course module.
 */

/**
 * Synchronizes all Course Masters with CAMS.
 */
function course_master_sync_all() {
  $start_time = REQUEST_TIME;
  $rc = WATCHDOG_INFO;
  watchdog('course_master_sync', 'Task started');

  if (!cams_is_available()) {
    $rc = WATCHDOG_ERROR;
    $report[] = '[ERROR] CAMS is not available';
  }
  else {
    $result = db_query("UPDATE {node} SET status=0 WHERE type='course_master'");
    $num_course_masters = $result->rowCount();
    $report[] = "[INFO] $num_course_masters  published course masters found in Drupal.";

    $course_masters = cams_query('course_master', 'get');
    $report[] = "[INFO] " . count($course_masters) . " active course masters found in CAMS.";

    if ($course_masters) {
      foreach ($course_masters as $course_master) {
        $report = array_merge($report, course_master_sync($course_master));
      }
    }

    $result = db_query("SELECT title FROM {node} WHERE type='course_master' AND status=0");
    $unpublished = array();
    while ($title = $result->fetchField()) {
      $unpublished[] = $title;
    }
    $report[] = t("[INFO] @count unpublished course masters:<br/>!list", array(
                  '@count' => (int) count($unpublished),
                  '!list'  => implode('<br/>', $unpublished)));
  }

  // Report e-mail.
  $id = 'course_master_sync_all_mail';
  $subject = t('Course Master Synchronization Report');
  $to = variable_get('course_master_sync_all_mail_to', '');
  $body = implode('<br/>', $report);
  if (!aup_send_report_email($id, $subject, $to, $body, $rc)) {
    $rc = WATCHDOG_ERROR;
    $report[] = t('[ERROR] Unable to send the report by e-mail');
  }
  
  $msg = t('Task finished @status:<br/>!report', array(
             '@status' => ($rc == WATCHDOG_ERROR) ? 'with error(s)' :
                          (($rc == WATCHDOG_WARNING) ? 'with warning(s)' :
                          'successfully'),
             '!report' => implode('<br/>', $report)));
  watchdog('course_master_sync', $msg, array(), $rc);
  drupal_set_message($msg);
}

/**
 * Synchronizes a Course Master with CAMS.
 * 
 * @param object $course
 *   A course master retrieved from CAMS
 */
function course_master_sync($course) {
  if (!is_object($course)) {
    return FALSE;
  }

  $report = array();
  $result = db_query('SELECT entity_id FROM {field_data_field_cams_id} 
                       WHERE field_cams_id_value = :id', array(
                         ':id' => $course->cams_id));
  if ($nid = $result->fetchField()) {
    $node = node_load($nid);
  }

  // @ignore sniffer_files_linelength_toolong
  // DEBUG watchdog('debug', '<pre>Course: ' . print_r($course, TRUE) . '</pre>');
  // DEBUG watchdog('debug', '<pre>Node: ' . print_r($node, TRUE) . '</pre>');
  $node->type = 'course_master';
  $node->uid = 0;
  $node->status = 1;
  $node->field_course_code['und'][0]['value'] = $course->code;
  $node->field_course_name['und'][0]['value'] = $course->name;
  $node->field_course_description['und'][0]['value'] = utf8_encode($course->description);
  $node->field_course_type['und'][0]['value'] = $course->type;
  $node->field_course_credits['und'][0]['value'] = $course->credits;
  $node->field_course_canrepeat['und'][0]['value'] = ($course->canrepeat == 'Yes') ? 1 : 0;
  $node->field_course_level['und'][0]['value'] = $course->level;
  $node->field_course_prerequisites['und'][0]['value'] = $course->prerequisites;
  $node->field_course_corequisites['und'][0]['value'] = $course->corequisites;
  $node->field_cams_id['und'][0]['value'] = $course->cams_id;
  $node->field_cams_last_update['und'][0]['value'] = REQUEST_TIME;
  if ($equivalencies = cams_query('course_master', 'get_equivalencies', $course->cams_id)) {
    $i = 0;
    foreach ($equivalencies as $equivalency) {
      if ($equivalent_eid = db_query('SELECT entity_id FROM {field_data_field_cams_id}
                              WHERE field_cams_id_value = :id', array(
                                ':id' => $equivalency))->fetchField()) {
        $node->field_course_equivalencies['und'][$i++]['target_id'] = $equivalent_eid;
      }
    }
  }

  if ($department_eid = db_query('SELECT entity_id FROM {field_data_field_department_code}
  		WHERE field_department_code_value = :id', array(
  				':id' => $course->department))->fetchField()) {
  				$node->field_course_department['und'][0]['target_id'] = $department_eid;
  }
  else {
  	$node_department->type = 'department';
  	$node_department->uid = 0;
  	$node_department->status = 1;
  	$node_department->field_department_name['und'][0]['value'] = $course->department;
  	$node_department->field_department_code['und'][0]['value'] = $course->department;
  	node_save($node_department);
  	$report[] = t('[INFO] Department @department created', array(
  			'@department' => $course->department));
  	$node->field_course_department['und'][0]['target_id'] = $node_department->nid;
  }
    
  node_save($node);

  if (!$nid) {
  	$report[] = t('[INFO] Course Master !course created', array(
  			'!course' => $node->title));
  }
  
  return $report;
}

/**
 * Synchronizes all Courses with CAMS.
 */
function course_sync_all() {
  $start_time = REQUEST_TIME;
  $rc = WATCHDOG_INFO;
  watchdog('course_sync', 'Task started');

  if (!cams_is_available()) {
    $rc = WATCHDOG_ERROR;
    $report[] = t('[ERROR] CAMS is not available');
  }
  elseif (!$active_terms = cams_query('term', 'get', 'active')) {
    $rc = WATCHDOG_ERROR;
    $report[] = t('[ERROR] No active term found in CAMS');
  }
  else {
    $terms = array();
    foreach ($active_terms as $term) {
      $terms[] = $term->name;
    }
    $report[] = t('[INFO] Active terms in CAMS: @terms', array(
                    '@terms' => implode(', ', $terms)));

    $result = db_query("UPDATE {node} SET status=0 WHERE type='course'");
    $num_courses = $result->rowCount();
    $report[] = "[INFO] $num_courses published courses found in Drupal.";
    
    foreach ($active_terms as $term) {
      $courses = cams_query('course', 'get', $term->id);
      $report[] = t("[INFO] @count active courses for @term found in CAMS.", array(
                      '@count' => count($courses),
                      '@term'  => $term->name));
      if ($courses) {
        foreach ($courses as $course) {
          $report = array_merge($report, course_sync($course));
          break;
        }
      }
    }

    $result = db_query("SELECT title FROM {node} WHERE type='course' AND status=0");
    $unpublished = array();
    while ($title = $result->fetchField()) {
      $unpublished[] = $title;
    }
    $report[] = t("[INFO] @count unpublished courses:<br/>!list", array(
                  '@count' => (int) count($unpublished),
                  '!list'  => implode('<br/>', $unpublished)));
  }

  // Report e-mail.
  $id = 'course_sync_all_mail';
  $subject = t('Course Synchronization Report');
  $to = variable_get('course_sync_all_mail_to', '');
  $body = implode('<br/>', $report);
  if (!aup_send_report_email($id, $subject, $to, $body, $rc)) {
    $rc = WATCHDOG_ERROR;
    $report[] = t('[ERROR] Unable to send the report by e-mail');
  }

  $msg = t('Task finished @status:<br/>!report', array(
             '@status' => ($rc == WATCHDOG_ERROR) ? 'with error(s)' :
                          (($rc == WATCHDOG_WARNING) ? 'with warning(s)' :
                          'successfully'),
                          '!report' => implode('<br/>', $report)));
  watchdog('course_sync', $msg, array(), $rc);
  drupal_set_message($msg);
}

/**
 * Synchronizes a Course with CAMS.
 *
 * @param object $course
 *   A course retrieved from CAMS
 */
function course_sync($course) {
	if (!is_object($course)) {
		return FALSE;
	}

	$report = array();
	
	$result = db_query('SELECT entity_id FROM {field_data_field_cams_id}
			WHERE field_cams_id_value = :id', array(
					':id' => $course->cams_id));
	if ($nid = $result->fetchField()) {
		$node = node_load($nid);
	}

	// @ignore sniffer_files_linelength_toolong
	// DEBUG watchdog('debug', '<pre>Course: ' . print_r($course, TRUE) . '</pre>');
	// DEBUG watchdog('debug', '<pre>Node: ' . print_r($node, TRUE) . '</pre>');
	$node->type = 'course';
	$node->uid = 0;
	$node->status = 1;
	$node->field_course_description['und'][0]['value'] = utf8_encode($course->description);
	$node->field_course_code['und'][0]['value'] = $course->code;
	$node->field_course_name['und'][0]['value'] = $course->name;
	$node->field_course_section['und'][0]['value'] = $course->section;
	$node->field_course_credits['und'][0]['value'] = $course->credits;
	$node->field_course_type['und'][0]['value'] = $course->type;
	$node->field_course_level['und'][0]['value'] = $course->level;
	// TODO $node->field_course_term['und'][0]['value'] = $course->term;
	$node->field_course_canrepeat['und'][0]['value'] = ($course->canrepeat == 'Yes') ? 1 : 0;
	$node->field_course_notes['und'][0]['value'] = $course->notes;
	$node->field_cams_id['und'][0]['value'] = $course->cams_id;
	$node->field_cams_last_update['und'][0]['value'] = REQUEST_TIME;

	if ($department_eid = db_query('SELECT entity_id FROM {field_data_field_department_code}
			WHERE field_department_code_value = :id', array(
					':id' => $course->department))->fetchField()) {
					$node->field_course_department['und'][0]['target_id'] = $department_eid;
	}
	else {
  	$node_department->type = 'department';
  	$node_department->uid = 0;
  	$node_department->status = 1;
  	$node_department->field_department_name['und'][0]['value'] = $course->department;
  	$node_department->field_department_code['und'][0]['value'] = $course->department;
  	node_save($node_department);
  	$report[] = t('[INFO] Department @department created', array(
  			'@department' => $course->department));
  	$node->field_course_department['und'][0]['target_id'] = $node_department->nid;
	}
	
	// TODO
	$node->field_course_examdate['und'][0]['value'] = $course->examdate;

	if ($crosslisted_eid = db_query('SELECT entity_id FROM {field_data_field_cams_id}
			WHERE field_cams_id_value = :id', array(
					':id' => $course->crosslisted))->fetchField()) {
    $node->field_course_crosslisted['und'][0]['target_id'] = $crosslisted_eid;
	}


	if ($master_eid = db_query('SELECT entity_id FROM {field_data_field_cams_id}
			WHERE field_cams_id_value = :id', array(
					':id' => $course->masterID))->fetchField()) {
    $node->field_course_course_master['und'][0]['target_id'] = $master_eid;
	}
	else {
		$report[] = t('[WARNING] Course Master @course_master not found', array(
				'@course_master' => $course->masterID));
	}
	
	node_save($node);

	if (!$nid) {
	  $report[] = t('[INFO] Course !course created', array(
			'!course' => $node->title));
	}
	
	return $report;
}

/**
 * TEMP.
 */
function course_master_delete() {
  $result = db_query("SELECT nid FROM {node} WHERE type IN ('course_master')");
  while ($nid = $result->fetchField()) {
    node_delete($nid);
  }
  return 'OK';
}

/**
 * TEMP.
 */
function course_delete() {
	$result = db_query("SELECT nid FROM {node} WHERE type IN ('course')");
	while ($nid = $result->fetchField()) {
		node_delete($nid);
	}
	return 'OK';
}
