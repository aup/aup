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
   * Course Synchronization
   */
  $report[] = '';
  $report[] = '[INFO] COURSE SYNCHRONIZATION';

  // Unpublish all courses
  $count = db_query("UPDATE {node} SET status=0 WHERE type='course'")->rowCount();
  $report[] = "[INFO] $count published courses found in Drupal.";
  
  // Update active courses in CAMS
  if (!$courses = cams_query('course', 'get')) {
    $report[] = t('[ERROR] No active course found in CAMS');
    return aup_custom_task_end($report, WATCHDOG_ERROR);
  }
  else {
    $report[] = "[INFO] " . count($courses) . " active courses found in CAMS.";
    foreach ($courses as $course) {
    _course_sync($course, $report, $rc);
    }
  }
  
  // Report remaining unpublished courses
  $query = db_query("SELECT title FROM {node} WHERE type='course' AND status=0");
  $unpublished = array();
  while ($title = $query->fetchField()) {
    $unpublished[] = $title;
  }
  $report[] = t("[INFO] @count unpublished courses:<br/>!list", array(
    '@count' => (int) count($unpublished),
    '!list'  => implode('<br/>', $unpublished)));

  /*
   * Course Offering Synchronization
   */
  $report[] = '';
  $report[] = '[INFO] COURSE OFFERING SYNCHRONIZATION';
  
  // Unpublish all course offerings
  $count = db_query("UPDATE {node} SET status=0 WHERE type='course_offering'")->rowCount();
  $report[] = "[INFO] $count published course offerings found in Drupal.";
  
  // Update active course offerings in CAMS
  foreach ($active_terms as $term) {
    $courses = cams_query('course', 'get_offerings', $term->id);
    $report[] = t("[INFO] @count active courses for @term found in CAMS.", array(
                    '@count' => count($courses),
                    '@term'  => $term->name));
    if ($courses) {
      foreach ($courses as $course) {
        _course_offering_sync($course, $report, $rc);
        // break;
      }
    }
  }

  // Report remaining unpublished course offerings
  $query = db_query("SELECT title FROM {node} WHERE type='course_offering' AND status=0");
  $unpublished = array();
  while ($title = $query->fetchField()) {
    $unpublished[] = $title;
  }
  $report[] = t("[INFO] @count unpublished course offerings:<br/>!list", array(
                '@count' => (int) count($unpublished),
                '!list'  => implode('<br/>', $unpublished)));

  return aup_custom_task_end($report, $rc);
}

/**
 * Synchronizes a Course with CAMS.
 *
 * @param object $course
 *   A course retrieved from CAMS
 *   
 * @param array $report
 *   Synchronization report
 *   
 * @param int $rc
 *   WATCHDOG_* status
 */
function _course_sync($course, &$report, &$rc) {
  if (!is_object($course)) {
    $rc = WATCHDOG_ERROR;
    return FALSE;
  }

  // Load the node if it already exists
  $query = db_query("SELECT entity_id FROM {field_data_field_cams_id}
                      WHERE bundle='course'
                        AND field_cams_id_value = :id", array(
                    ':id' => $course->camsID));
  if ($nid = $query->fetchField()) {
    $node = node_load($nid);
  }

  // @ignore sniffer_files_linelength_toolong
  // DEBUG watchdog('debug', '<pre>Course: ' . print_r($course, TRUE) . '</pre>');
  // DEBUG watchdog('debug', '<pre>Node: ' . print_r($node, TRUE) . '</pre>');
  $node->type = 'course';
  $node->uid = 0;
  $node->status = 1;
  $node->language = LANGUAGE_NONE;
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
  if ($equivalencies = cams_query('course', 'get_equivalencies', $course->camsID)) {
    $i = 0;
    foreach ($equivalencies as $equivalency) {
      if ($equivalent_eid = db_query("
            SELECT entity_id FROM {field_data_field_cams_id}
             WHERE bundle='course'
               AND field_cams_id_value = :id", array(
            ':id' => $equivalency))->fetchField()) {
        $node->field_course_equivalencies[LANGUAGE_NONE][$i++]['target_id'] = $equivalent_eid;
      }
    }
  }

  node_save($node);

  if (!$nid) {
        $report[] = t('[INFO] Course !course created', array(
            '!course' => $node->title));
  }
  return TRUE;
}

/**
 * Synchronizes a Course Offering with CAMS.
 *
 * @param object $course
 *   A course offering retrieved from CAMS
 *   
  * @param array $report
 *   Synchronization report
 *   
 * @param int $rc
 *   WATCHDOG_* status
 */
function _course_offering_sync($course, &$report, &$rc) {
  if (!is_object($course)) {
    $rc = WATCHDOG_ERROR;
    return FALSE;
  }

  // Load the node if it already exists
  $query = db_query("
    SELECT entity_id
      FROM {field_data_field_cams_id}
     WHERE bundle='course_offering'
       AND field_cams_id_value = :id", array(
    ':id' => $course->camsID)
  );
  if ($nid = $query->fetchField()) {
    $node = node_load($nid);
  }

  // @ignore sniffer_files_linelength_toolong
  // DEBUG watchdog('debug', '<pre>Course: ' . print_r($course, TRUE) . '</pre>');
  // DEBUG watchdog('debug', '<pre>Node: ' . print_r($node, TRUE) . '</pre>');
  $node->type = 'course_offering';
  $node->uid = 0;
  $node->status = 1;
  $node->language = LANGUAGE_NONE;
  $node->field_course_term[LANGUAGE_NONE][0]['value'] = $course->termID;
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
                      WHERE bundle = 'course'
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
                      WHERE bundle = 'course_offering'
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
  if ($schedules = cams_query('course', 'get_schedules', $course->code, $course->termID)) {
    // DEBUG watchdog('debug', $course->code . ' Schedules:<pre>' . print_r($schedules, TRUE) . '</pre>');
    $i = 0;
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
          $node_room->language = LANGUAGE_NONE;
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

        // Timetable.
        //watchdog('debug', "$i day = $camsDay -> " . cams_query('convert', 'camsday2daynb', $camsDay));
        /*if ($day != 'UN') {
          $values['field_timetable'][LANGUAGE_NONE][0] = array(
              'day'          => cams_query('convert', 'camsday2daynb', $camsDay),
              'start_minute' => cams_query('convert', 'camstime2minutes', $start_time),
              'end_minute'   => cams_query('convert', 'camstime2minutes', $end_time),
              'description'  => $schedule->room,
          );
        }*/
        
        // DEBUG watchdog('debug', 'Values:<pre>' . print_r($values, TRUE) . '</pre>');
        $entity = entity_create('field_collection_item', $values);
        $entity->setHostEntity('node', $node);
        $entity->save();
      }
    }
  }

  // DEBUG  watchdog('debug', 'timetable:<pre>' . print_r($node->field_timetable[LANGUAGE_NONE], TRUE) . '</pre>');
  
  // DEBUG  watchdog('debug', 'Scheduling:<pre>' . print_r($node->field_date[LANGUAGE_NONE], TRUE) . '</pre>');
  
  node_save($node);

  if (!$nid) {
    $report[] = t('[INFO] Course Offering !course created', array(
      '!course' => $node->title));
  }
  return TRUE;
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

/**
 * TEMP.
 */
function course_offering_delete() {
  $query = db_query("SELECT nid FROM {node} WHERE type IN ('course_offering')");
  while ($nid = $query->fetchField()) {
    node_delete($nid);
  }
  return 'OK';
}
