<?php

/**
 * @file
 * CAMS - Course
 * CAMS functions related to Courses
 */

/**
 * Retrieves courses.
 *
 * @param string $term
 *   TODO
 *   
 * @param bool $onlyDisplayInPortal
 *   TODO
 *   
 * @return array
 *   An array of courses indexed by course code
 */
function cams_course_get($term = NULL, $onlyDisplayInPortal = TRUE) {
  if (!cams_is_available()) {
  return FALSE;
  
  }
  if (!$term) {
    $term = cams_query('term', 'get');
  }
  
  $sql =  "
    SELECT CAMS_SROffer_View.Department+CAMS_SROffer_View.Course+CAMS_SROffer_View.Section AS code,
           CAMS_SROffer_View.SROfferID AS cams_id, 
           CAMS_SROffer_View.Department AS department,
           CAMS_SROffer_View.CourseType AS type,
           CAMS_SROffer_View.Section AS section,
           CAMS_SROffer_View.CourseName AS name,
           CAMS_SROffer_View.Credits AS credits,
           CAMS_SROffer_View.Grouping AS grouping,
           CAMS_SROffer_View.Notes AS notes,
           CONVERT(VARCHAR(10), CAMS_SROffer_View.StartDate, 126) AS StartDate,
           CONVERT(VARCHAR(10), CAMS_SROffer_View.EndDate, 126) AS EndDate,
           CAMS_SROffer_View.CanRepeat AS canrepeat,
           CAMS_SROffer_View.CourseDivision AS division,
           CAMS_SROffer_View.Status AS status,
           CAMS_SROffer_View.GPAGrouping AS level,
           CAMS_SROffer_View.Semester AS termid,
           CAMS_SROffer_View.TextTerm AS term,
           CONVERT(VARCHAR(19), CAMS_SROffer_View.ExamDate, 126) AS examdate,
           CAMS_SRMaster_View.CourseDescription AS description,
           CAMS_SROffer_View.CrossListedID AS crosslisted,
           CAMS_SROffer_View.SRMasterID AS masterID
      FROM CAMS_SROffer_View INNER JOIN CAMS_SRMaster_View ON CAMS_SROffer_View.SRMasterID = CAMS_SRMaster_View.SRMasterID
     WHERE CAMS_SROffer_View.Semester = '$term' 
       AND CAMS_SROffer_View.CourseType <> 'BIL'
       AND CAMS_SROffer_View.CourseType <> 'STACT'
       AND CAMS_SROffer_View.Status = 'Open'";

  if ($onlyDisplayInPortal) {
  	$sql .= "
       AND CAMS_SROffer_View.DisplayInPortal = 1";
  }
  $sql .= "
     ORDER BY code";
  
  $result = mssql_query($sql);
  $courses = array();
  while ($course = mssql_fetch_object($result)) {
    $courses[$course->code] = $course;
  }
  
  return $courses; 
}

/**
 * TODO
 */
function cams_course_get_schedules($courseName = NULL, $term = NULL, $onlyDisplayInPortal = TRUE) {
  if (!cams_is_available() || !$courseName) { return FALSE; }
  if (!$term) { $term = cams_query('term', 'get'); }
  
  $sql = "
    SELECT DISTINCT CAMS_SROfferFacultyTeach_View.facultyName instructor,
           lower(FacultyPortal.ActiveDirectoryIdentifier) AS netid,
           CAMS_SROfferSchedule_View.RoomName AS room,
           CAMS_SROfferSchedule_View.SROfferScheduleID AS scheduleID,
           CONVERT(VARCHAR(8), CAMS_SROfferSchedule_View.OfferTimeFrom, 108) AS OfferTimeFrom,
           CONVERT(VARCHAR(8), CAMS_SROfferSchedule_View.OfferTimeTo, 108) AS OfferTimeTo,
           CAMS_SROfferSchedule_View.OfferDays
      FROM CAMS_SROffer_View INNER JOIN CAMS_SROfferSchedule_View
           ON CAMS_SROffer_View.SROfferID = CAMS_SROfferSchedule_View.SROfferID
           INNER JOIN CAMS_SROfferFacultyTeach_View ON CAMS_SROfferFacultyTeach_View.SROfferID = CAMS_SROfferSchedule_View.SROfferID        
           INNER JOIN FacultyPortal ON FacultyPortal.FacultyID = CAMS_SROfferFacultyTeach_View.FacultyID
           AND CAMS_SROffer_View.SemesterID = CAMS_SROfferSchedule_View.TermCalendarID
     WHERE CAMS_SROffer_View.Semester = '$term'
       AND CAMS_SROffer_View.Department+CAMS_SROffer_View.Course+CAMS_SROffer_View.Section = '$courseName'";  
  
  if ($onlyDisplayInPortal) {
  	$sql .= "
  	   AND CAMS_SROffer_View.DisplayInPortal = 1";
  }
  
  $result = mssql_query($sql);
  while ($schedule = mssql_fetch_object($result)) {
    $schedules[$schedule->scheduleID][] = $schedule;
  }
  
  return $schedules;
}

function cams_course_get_masters($term = NULL) {
  if (!cams_is_available()) { return FALSE; }
  if (!$term) { $term = cams_query('term', 'get'); }
  $sql = "SELECT DISTINCT MajorDegree FROM CAMS_StudentProgram_View StuProgV 
			JOIN CAMS_StudentStatus_View StuStaV
			  ON (StuProgV.StudentStatusID = STUSTAV.StudentStatusID)
			WHERE StuStaV.Term = '$term'
			AND LOWER(StuStaV.GPAGrouping) = 'graduate'
			AND MajorDegree <> ''
			ORDER BY MajorDegree";
  $result = mssql_query($sql);
  while ($line = mssql_fetch_array($result)) {
    $masters[] = $line['MajorDegree'];
  }
  
  return $masters;
}

function cams_course_get_majors($term = NULL) {
  if (!cams_is_available()) { return FALSE; }
  if (!$term) { $term = cams_query('term', 'get'); }
  $sql = "SELECT DISTINCT MajorDegree FROM CAMS_StudentProgram_View StuProgV 
			JOIN CAMS_StudentStatus_View StuStaV
			  ON (StuProgV.StudentStatusID = STUSTAV.StudentStatusID)
			WHERE StuStaV.Term = '$term'
			AND LOWER(StuStaV.GPAGrouping) = 'undergraduate'
			AND MajorDegree <> ''
			ORDER BY MajorDegree";
  $result = mssql_query($sql);
  while ($line = mssql_fetch_array($result)) {
    $majors[$line['MajorDegree']] = $line['MajorDegree'];
  }
  
  return $majors;
}

function cams_course_get_minors($term = NULL) {
  if (!cams_is_available()) { return FALSE; }
  if (!$term) { $term = cams_query('term', 'get'); }
  $sql = "SELECT DISTINCT MinorDegree FROM CAMS_StudentProgram_View StuProgV 
			JOIN CAMS_StudentStatus_View StuStaV
			  ON (StuProgV.StudentStatusID = STUSTAV.StudentStatusID)
			WHERE StuStaV.Term = '$term'
			AND LOWER(StuStaV.GPAGrouping) = 'undergraduate'
			AND MinorDegree <> ''
			ORDER BY MinorDegree";
  $result = mssql_query($sql);
  while ($line = mssql_fetch_array($result)) {
    $minors[$line['MinorDegree']] = $line['MinorDegree'];
  }
  
  return $minors;
}

/*
 * TODO
 */
function cams_course_get_by_room($room, $termID = NULL) {
  if (!cams_is_available() || !$room) { return FALSE; }
  if (!$termID) { $termID = cams_query('term', 'get'); }

  // Room names in AMIS either with or without a dash
  $rooms = "'$room', '".ereg_replace('-', '', $room)."'";
  $result = mssql_query("
    SELECT Department +  Course + ' ' + Section AS Course, CourseType, CourseName, 
           DATEDIFF(s, '19700101', StartDate) AS StartDate, 
           DATEDIFF(s, '19700101', EndDate) AS EndDate, OfferDays, 
           CONVERT(VARCHAR, OfferTimeFrom, 8)AS OfferTimeFrom, 
           CONVERT(VARCHAR, OfferTimeTo, 8)AS OfferTimeTo, RoomName, Instructor
      FROM CAMS_SROffer_View, CAMS_SROfferSchedule_View
     WHERE CAMS_SROffer_View.SROfferID = CAMS_SROfferSchedule_View.SROfferID
       AND RoomName IN ($rooms)
       AND Semester = $termID
       AND Status = 'Open'");
  $rs = array();
  
  while ($line = mssql_fetch_object($result)) {
    $rs[] = $line;
  }

  return $rs;
  
}

/*
 * TODO
 */
function cams_course_get_students($camsID = NULL) {
  if (!$camsID) {
    return FALSE;
  }

  $result = mssql_query("
      SELECT 'a'+StudentID AS netid
      FROM CAMS_StudentScheduleRpt_View
      WHERE SROfferID = $camsID");

  $rs = array();
  while ($line = mssql_fetch_object($result)) {
    $rs[] = $line->netid;
  }
  
  return $rs;
}

/*
 * TODO
 */
function cams_course_get_professors($camsID = NULL) {
  if (!$camsID) {
    return FALSE;
  }

  $result = mssql_query("
      SELECT DISTINCT fp.PortalAlias AS netid
      FROM CAMS_SROfferSchedule_Faculty_View osf INNER JOIN FacultyPortal fp ON osf.FacultyID = fp.FacultyID 
      WHERE SROfferID = $camsID");

  $rs = array();
  while ($line = mssql_fetch_object($result)) {
    $rs[] = $line->netid;
  }

  return $rs;
}

/*
* TODO
*/
function cams_course_get_book_list($camsID = NULL) {
	if (!$camsID) {
		return FALSE;
	}

	$result = mssql_query("
      SELECT ISBNNumber, Publisher, BookTitle, BookCost, Author, PublisherPhone
      FROM CAMS_SROfferingBook_View 
      WHERE SROfferID = $camsID");

	$rs = array();
	while ($line = mssql_fetch_object($result)) {
		$rs[] = $line;
	}

	return $rs;
}

/*
* TODO
*/
function cams_course_get_fees($camsID = NULL) {
	if (!$camsID) {
		return FALSE;
	}

	$result = mssql_query("
      SELECT Transdoc, Amount, RefundType, FeeType, OptionalFee
      FROM CAMS_CourseFees_View 
      WHERE SROfferID = $camsID");

	$rs = array();
	while ($line = mssql_fetch_object($result)) {
		$rs[] = $line;
	}

	return $rs;
}

/*
 * TODO
 */
function cams_course_sync($node) {
  // Get the courses of the course term
  $courses = cams_query('course', 'get', $node->field_course_term[0]['value']);

  if ($course = $courses[$node->field_course_name[0]['value']]) {
    $error = _cams_course_sync($course);
    $error = array_merge((array)$error, (array)cams_query('course_schedule', 'sync', $node));
  } else {
    drupal_set_message(t("Unable to get course info in CAMS for @course in @term",
                      array('@course' => $node->field_course_name[0]['value'],
                            '@term'   => $node->field_course_term[0]['value'])), 'error');
  }
  if (!$error) {
  	return t("Synchronisation successful.");
  }
  else {
    return implode("<br/>", $error);
  }
}

/*
 * TODO
 */
function cams_course_sync_all()  {
  $rc = SCHEDULED_TASKS_REPORT_OK;
  $startTime = time();
  watchdog('cams_course_sync_all', "Task launched");

  if (!cams_is_available()) {
  	$report[] = t('[ERROR] CAMS is not available');
  	$rc = SCHEDULED_TASKS_REPORT_ERROR;
  }
  else {
  	db_query("UPDATE {node} SET status=0 WHERE type='course'");
  	
    // Report
    $report[] = "Report of cams_course_sync_all:";
    
    $activeTerms = variable_get('cams_active_terms', NULL);
    
    foreach ($activeTerms as $activeTerm) {
      $courses = cams_query('course', 'get', $activeTerm);

      $report[] = '';
      $report[] = count($courses) . " courses found in $activeTerm in CAMS.";
      $report[] = '';
        
      foreach ($courses as $course) {
        if ($msg = _cams_course_sync($course)) {
          $rc = SCHEDULED_TASKS_REPORT_WARNING;
          $report = array_merge($report, (array)$msg);
        }
      }
    }
    
    $query = db_query("SELECT title FROM {node} WHERE type='course' AND status=0");
    $unpublished = array();
    while ($title = db_result($query)) {
    	$unpublished[] = $title;
    }
    $report[] = '';
    $report[] = t("@count unpublished courses:\r\n@list",
    array('@count' => (int)count($unpublished),
    	                     '@list'  => implode("\r\n", $unpublished)));
        
  }
  
  if (!scheduled_tasks_report($rc,
                                'cams_course_sync_all',
                                'Course Synchronisation with CAMS Report',
  $report,
  variable_get('scheduled_tasks_report_email', null))) {
  	watchdog('cams_course_sync_all', 'Unable to send the script report', array(), WATCHDOG_WARNING);
  	$rc = SCHEDULED_TASKS_REPORT_WARNING;
  }
    
  return $rc;
}

/*
 * TODO
*/
function _cams_course_sync($course) {
  $nid = db_result(db_query("SELECT nid FROM {content_type_course} WHERE field_course_camsid_value = %d", $course->cams_id));
  if ($nid) {
    $node = node_load($nid);
  }
  
  $currentTerm = cams_query('term', 'get');
  $inCurrentTerm = ($currentTerm == $course->termid) ? TRUE : FALSE;
  
  // DEBUG drupal_set_message('<pre>Course: ' . print_r($course, TRUE) . '</pre>');
  // DEBUG drupal_set_message('<pre>Node: ' . print_r($node, TRUE) . '</pre>');
  //$node->title = "$course->name ($course->title) in $course->term";
  $node->body = $course->description;
  $node->type = 'course';
  $node->uid = 1;
  $node->status = 1;
  if ($inCurrentTerm) {
    $node->og_selective = 3;
  }
  $node->field_course_camsid[0]['value'] = $course->cams_id;
  $node->field_misc_cams_last_update[0]['value'] = time();
  $node->field_course_name[0]['value'] = $course->name;
  $node->field_course_department[0]['value'] = $course->department;
  $node->field_course_code[0]['value'] = $course->code;
  $node->field_course_type[0]['value'] = $course->type;
  $node->field_course_section[0]['value'] = $course->section;
  $node->field_course_title[0]['value'] = utf8_encode($course->title);
  $node->field_course_credits[0]['value'] = $course->credits;
  $node->field_course_grouping[0]['value'] = $course->grouping;
  $node->field_course_notes[0]['value'] = $course->notes;
  $node->field_course_canrepeat[0]['value'] = $course->canrepeat;
  $node->field_course_division[0]['value'] = htmlentities($course->division);
  $node->field_course_status[0]['value'] = $course->status;
  $node->field_course_gpagrouping[0]['value'] = $course->gpagrouping;
  $node->field_course_term[0]['value'] = $course->termid;
  $node->field_course_examdate[0]['value'] = $course->examdate;

  if ($course->crosslisted) {
    $crosslisted = db_result(db_query("SELECT nid FROM {content_type_course} WHERE field_course_camsid_value = %d", $course->crosslisted));
    $node->field_course_crosslisted[0]['nid'] = $crosslisted;	
    // DEBUG     drupal_set_message("Crosslisted: $course->name ($node->nid) with $crosslisted");
    //break;
  }

  $courseMasterNid = db_result(db_query("SELECT nid FROM {content_type_course_master} WHERE field_course_master_camsid_value = %d", $course->masterID));
  if ($courseMasterNid) {
    $node->field_course_course_master[0]['nid'] = $courseMasterNid;
  }
  else {
    $msg[] =  t('[Warning] @course: Course Master @coursemaster not found',
        array('@course' => "$course->name in $course->term", '@coursemaster' => $course->masterID));
  }

  drupal_set_message('<pre>' . print_r($node, TRUE) . '</pre>');
  node_save($node);
  
  /*
   * Group Members
   */
  // Professor(s)
  db_query('DELETE FROM {og_uid} WHERE nid = %d AND is_admin = 1', $node->nid);
  $professors = cams_query('course', 'get_professors', $course->cams_id);
  foreach ($professors as $professor) {
    if (!$user = user_load(array('name' => strtolower($professor)))) {
      $msg[] = t('[Warning] @course: Professor @netid not found',
               array('@course' => "$course->name in $course->term", '@netid' => strtolower($professor)));
    }
    else {
      db_query("INSERT INTO {og_uid} (`nid`, `og_role`, `is_active`, `is_admin`, `uid`, `created`, `changed`)
                VALUES ('%d',  '0',  '1',  '1',  '%d', NOW() , NOW());",
               $node->nid, $user->uid);
    }
  }
    
  // Students
  if ($inCurrentTerm) {
    db_query('DELETE FROM {og_uid} WHERE nid = %d AND is_admin = 0', $node->nid);
    $students = cams_query('course', 'get_students', $course->cams_id);
    foreach ($students as $student) {
      if (!$user = user_load(array('name' => $student))) {
        $msg[] = t('[Warning] @course: Student @netid not found',
                 array('@course' => "$course->name in $course->term", '@netid' => $student));
      }
      else {
        db_query("INSERT INTO {og_uid} (`nid`, `og_role`, `is_active`, `is_admin`, `uid`, `created`, `changed`)
                  VALUES ('%d',  '0',  '1',  '0',  '%d', NOW() , NOW());",
                 $node->nid, $user->uid);
      }
    }  
  }
	
  // DEBUG     drupal_set_message('<pre>Debug: ' . print_r($node, TRUE) . '</pre>');
	
  /*$msg[] = t('Course !course @action', 
                     array('!course' => $node->title, 
                           '@action' => $nid ? 'updated' : 'created'));*/
  
  return $msg;
}

function cams_course_delete() {
  $rs = db_query("SELECT nid FROM {node} WHERE type IN ('course', 'course_schedule')");
  while ($nid = db_result($rs)) {
    node_delete($nid);
  }
  return 'OK';
}
  