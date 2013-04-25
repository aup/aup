<?php

/**
 * @file
 * CAMS - Course
 * CAMS functions related to Courses
 */

/**
 * TODO.
 */
function cams_course_get() {
  if (!cams_is_available()) {
    return FALSE;
  }

  $sql = "
  SELECT Department+CourseNumber AS code,
  SRM.SRMasterID AS camsID,
  Department AS discipline,
  CourseType AS type,
  CourseName AS name,
  Credits AS credits,
  Grouping AS grouping,
  CanRepeat AS canRepeat,
  CourseDivision AS division,
  GPAGrouping AS level,
  CourseDescription AS description,
  SRP.FormulaText AS prerequisites,
  SRC.FormulaText AS corequisites
  FROM CAMS_SRMaster_View SRM
  LEFT JOIN AUP_SRPrerequisite_View SRP ON SRM.SRMasterID = SRP.SRMasterID
  LEFT JOIN AUP_SRCorequisite_View SRC ON SRM.SRMasterID = SRC.SRMasterID
  WHERE ActiveFlag = 1 AND DisplayInPortal = 1
  AND CourseType <> 'BIL'
  AND CourseType <> 'STACT'
  ORDER BY code";

  // @ignore sniffer_semantics_functioncall_functionalias
  $result = mssql_query($sql);
  // @ignore sniffer_semantics_functioncall_functionalias
  while ($course = mssql_fetch_object($result)) {
    $courses[$course->code] = $course;
  }

  return $courses;
}

/**
 * TODO.
 * 
 * @param int $id
 *   Course CAMS ID
 */
function cams_course_get_equivalencies($id = '') {
  if (!cams_is_available() || !$id) {
    return FALSE;
  }

  $sql = "
  SELECT EquivSRMasterID
  FROM CAMS_SREquivalent_View
  WHERE SRMasterID = $id";

  // @ignore sniffer_semantics_functioncall_functionalias
  $result = mssql_query($sql);

  $equivalencies = array();
  // @ignore sniffer_semantics_functioncall_functionalias
  while ($equivalency = mssql_fetch_object($result)) {
    $equivalencies[] = $equivalency->EquivSRMasterID;
  }

  return $equivalencies;
}

/**
 * Retrieves course offerings of a give term.
 *
 * @param string $term_id
 *   Term ID of the courses (Format: YYYYMM)
 *   
 * @param bool $only_display_in_portal
 *   Only retrieves the courses meant to be displayed on the CAMS portal
 *   
 * @return array
 *   An array of courses indexed by course code
 */
function cams_course_get_offerings($term_id = NULL, $only_display_in_portal = TRUE) {
  if (!cams_is_available()) {
    return FALSE;
  }
  if (!$term_id) {
    $term = cams_query('term', 'get');
    $term_id = $term->id;
  }

  $sql = "
    SELECT CAMS_SROffer_View.Department+CAMS_SROffer_View.Course+CAMS_SROffer_View.Section AS code,
           CAMS_SROffer_View.SROfferID AS camsID, 
           CAMS_SROffer_View.Department AS discipline,
           CAMS_SROffer_View.CourseType AS type,
           CAMS_SROffer_View.Section AS section,
           CAMS_SROffer_View.CourseName AS name,
           CAMS_SROffer_View.Credits AS credits,
           CAMS_SROffer_View.Grouping AS grouping,
           CAMS_SROffer_View.Notes AS notes,
           CONVERT(VARCHAR(10), CAMS_SROffer_View.StartDate, 120) AS startDate,
           CONVERT(VARCHAR(10), CAMS_SROffer_View.EndDate, 120) AS endDate,
           CAMS_SROffer_View.CanRepeat AS canRepeat,
           CAMS_SROffer_View.CourseDivision AS division,
           CAMS_SROffer_View.Status AS status,
           CAMS_SROffer_View.GPAGrouping AS level,
           CAMS_SROffer_View.Semester AS termID,
           CAMS_SROffer_View.TextTerm AS term,
           CONVERT(VARCHAR(19), CAMS_SROffer_View.ExamDate, 120) AS examDate,
           CAMS_SRMaster_View.CourseDescription AS description,
           CAMS_SROffer_View.CrossListedID AS crosslisted,
           CAMS_SROffer_View.SRMasterID AS masterID
      FROM CAMS_SROffer_View INNER JOIN CAMS_SRMaster_View ON CAMS_SROffer_View.SRMasterID = CAMS_SRMaster_View.SRMasterID
     WHERE CAMS_SROffer_View.Semester = '$term_id' 
       AND CAMS_SROffer_View.CourseType <> 'BIL'
       AND CAMS_SROffer_View.CourseType <> 'STACT'
       AND CAMS_SROffer_View.Status = 'Open'";

  if ($only_display_in_portal) {
    $sql .= "
       AND CAMS_SROffer_View.DisplayInPortal = 1";
  }
  $sql .= "
     ORDER BY code";

  // @ignore sniffer_semantics_functioncall_functionalias
  $result = mssql_query($sql);
  $courses = array();
  // @ignore sniffer_semantics_functioncall_functionalias
  while ($course = mssql_fetch_object($result)) {
    $courses[$course->code] = $course;
  }

  return $courses;
}

/**
 * Retrieves schedules of a course offering.
 *
 * @param string $course_code
 *   Course Code (Example: AB1000C)
 *
 * @param string $term_id
 *   Term ID of the courses (Format: YYYYMM)
 *   
 * @return array
 *   An array of schedules
 */
function cams_course_get_schedules($course_code = NULL, $term_id = NULL) {
  if (!cams_is_available() || !$course_code) {
    return FALSE;
  }
  if (!$term_id) {
    $term = cams_query('term', 'get');
    $term_id = $term->id;
  }

  $sql = "
  SELECT DISTINCT
  CAMS_SROfferSchedule_View.RoomName AS room,
  --CAMS_SROfferSchedule_View.SROfferScheduleID AS scheduleID,
  CONVERT(VARCHAR(8), CAMS_SROfferSchedule_View.OfferTimeFrom, 108) AS offerTimeFrom,
  CONVERT(VARCHAR(8), CAMS_SROfferSchedule_View.OfferTimeTo, 108) AS offerTimeTo,
  CAMS_SROfferSchedule_View.OfferDays AS offerDays
  FROM CAMS_SROffer_View INNER JOIN CAMS_SROfferSchedule_View
  ON CAMS_SROffer_View.SROfferID = CAMS_SROfferSchedule_View.SROfferID
  AND CAMS_SROffer_View.SemesterID = CAMS_SROfferSchedule_View.TermCalendarID
  WHERE CAMS_SROffer_View.Semester = '$term_id'
  AND CAMS_SROffer_View.Department+CAMS_SROffer_View.Course+CAMS_SROffer_View.Section = '$course_code'";

  // @ignore sniffer_semantics_functioncall_functionalias
  $query = mssql_query($sql);

  $rs = array();
  // @ignore sniffer_semantics_functioncall_functionalias
  while ($line = mssql_fetch_object($query)) {
    if (!in_array($line->offerDays, array('NULL', 'N\A', ''))) {
      $rs[$line->offerDays] = $line;
    }
  }

  // DEBUG watchdog('debug', '<pre>SCHEDULES'.print_r($rs, TRUE).'</pre>');
  return $rs;
}

/**
 * Retrieves the roster of a course offering.
 *
 * @param string $course_code
 *   Course Code (Example: AB1000C)
 *
 * @param string $term_id
 *   Term ID of the courses (Format: YYYYMM)
 *
 * @return array
 *   An array of Student NetIDs
 */
function cams_course_get_students($course_code = NULL, $term_id = NULL) {
  if (!cams_is_available() || !$course_code) {
    return FALSE;
  }
  if (!$term_id) {
    $term = cams_query('term', 'get'); $term_id = $term->id;
  }

  // @ignore sniffer_semantics_functioncall_functionalias
  $result = mssql_query("
      SELECT 'a'+StudentID AS netID
      FROM CAMS_StudentScheduleRpt_View ssr
      INNER JOIN CAMS_SROffer_View o ON ssr.SROfferID = o.SROfferID
      WHERE o.Semester = '$term_id'
      AND o.Department+o.Course+o.Section = '$course_code'");

  $rs = array();
  // @ignore sniffer_semantics_functioncall_functionalias
  while ($line = mssql_fetch_object($result)) {
    $rs[] = $line->netID;
  }

  return $rs;
}

/**
 * Retrieves the professors of a course offering.
 *
 * @param string $course_code
 *   Course Code (Example: AB1000C)
 *
 * @param string $term_id
 *   Term ID of the courses (Format: YYYYMM)
 *
 * @return array
 *   An array of professors
 */
function cams_course_get_professors($course_code = NULL, $term_id = NULL) {
  if (!cams_is_available() || !$course_code) {
    return FALSE;
  }
  if (!$term_id) {
    $term = cams_query('term', 'get'); $term_id = $term->id;
  }

  // @ignore sniffer_semantics_functioncall_functionalias
  $query = mssql_query("
      SELECT DISTINCT LOWER(fp.PortalAlias) AS netID, LOWER(osf.FirstName) AS firstName, LOWER(osf.LastName) AS lastName
      FROM CAMS_SROfferSchedule_Faculty_View osf 
           INNER JOIN FacultyPortal fp ON osf.FacultyID = fp.FacultyID
           INNER JOIN CAMS_SROffer_View o ON osf.SROfferID = o.SROfferID
      WHERE o.Semester = '$term_id'
      AND o.Department+o.Course+o.Section = '$course_code'");

  $rs = array();
  // @ignore sniffer_semantics_functioncall_functionalias
  while ($line = mssql_fetch_object($query)) {
    $line->firstName = ucwords($line->firstName);
    $line->lastName = ucwords($line->lastName);
    $rs[] = $line;
  }

  return $rs;
}

/**
 * Retrieves the book list of a course offering.
 *
 * @param string $course_code
 *   Course Code (Example: AB1000C)
 *
 * @param string $term_id
 *   Term ID of the courses (Format: YYYYMM)
 *
 * @return array
 *   An array of books
 */
function cams_course_get_book_list($course_code = NULL, $term_id = NULL) {
  if (!cams_is_available() || !$course_code) {
    return FALSE;
  }
  if (!$term_id) {
    $term = cams_query('term', 'get'); $term_id = $term->id;
  }

  // @ignore sniffer_semantics_functioncall_functionalias
  $result = mssql_query("
    SELECT ISBNNumber AS ISBN,
           Publisher AS publisher,
           BookTitle AS title,
           BookCost AS cost,
           Author AS author,
           PublisherPhone AS phone
      FROM CAMS_SROfferingBook_View ob
           INNER JOIN CAMS_SROFFER_View o ON ob.SROfferID = o.SROfferID
     WHERE o.Semester = '$term_id'
       AND o.Department+o.Course+o.Section = '$course_code'");

  $rs = array();
  // @ignore sniffer_semantics_functioncall_functionalias
  while ($line = mssql_fetch_object($result)) {
    $rs[] = $line;
  }

  return $rs;
}

/**
 * Retrieves the fees of a course offering.
 *
 * @param string $course_code
 *   Course Code (Example: AB1000C)
 *
 * @param string $term_id
 *   Term ID of the courses (Format: YYYYMM)
 *
 * @return array
 *   An array of fees
 */
function cams_course_get_fees($course_code = NULL, $term_id = NULL) {
  if (!cams_is_available() || !$course_code) {
    return FALSE;
  }
  if (!$term_id) {
    $term = cams_query('term', 'get'); $term_id = $term->id;
  }

  // @ignore sniffer_semantics_functioncall_functionalias
  $result = mssql_query("
    SELECT CourseFeesID AS ID, Transdoc, Amount, RefundType, FeeType, OptionalFee
      FROM CAMS_CourseFees_View cf
           INNER JOIN CAMS_SROFFER_View o ON cf.SROfferID = o.SROfferID
     WHERE o.Semester = '$term_id'
       AND o.Department+o.Course+o.Section = '$course_code'");

  $rs = array();
  // @ignore sniffer_semantics_functioncall_functionalias
  while ($line = mssql_fetch_object($result)) {
    $rs[] = $line;
  }

  return $rs;
}

/*function cams_course_get_masters($term = NULL) {
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
}*/

/*function cams_course_get_majors($term = NULL) {
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
}*/

/*function cams_course_get_minors($term = NULL) {
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
}*/

/*
 * TODO
 */
/*function cams_course_get_by_room($room, $term_id = NULL) {
  if (!cams_is_available() || !$room) { return FALSE; }
  if (!$term_id) { $term_id = cams_query('term', 'get'); }

  // Room names in AMIS either with or without a dash
  $rooms = "'$room', '".ereg_replace('-', '', $room)."'";
  $result = mssql_query("
    SELECT Department +  Course + ' ' + Section AS Course,
           CourseType, CourseName,
           DATEDIFF(s, '19700101', StartDate) AS StartDate,
           DATEDIFF(s, '19700101', EndDate) AS EndDate, OfferDays,
           CONVERT(VARCHAR, OfferTimeFrom, 8)AS OfferTimeFrom,
           CONVERT(VARCHAR, OfferTimeTo, 8)AS OfferTimeTo, RoomName, Instructor
      FROM CAMS_SROffer_View, CAMS_SROfferSchedule_View
     WHERE CAMS_SROffer_View.SROfferID = CAMS_SROfferSchedule_View.SROfferID
       AND RoomName IN ($rooms)
       AND Semester = $term_id
       AND Status = 'Open'");
  $rs = array();

  while ($line = mssql_fetch_object($result)) {
    $rs[] = $line;
  }

  return $rs;
}*/
