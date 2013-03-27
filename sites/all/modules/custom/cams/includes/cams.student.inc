<?php
/*
 * CAMS Integration
 * Integration between CAMS and MyAUP
 *
 * @author: Pierre-Yves Vasener <pvasener@aup.edu>
 */
 
/*
 * STUDENT FUNCTIONS
 */
 
/*
 * TODO
 */
function cams_student_get($filterCriteria='status', $filterValue = 'Student', $termID = NULL) {
	if (!cams_is_available())
    return FALSE;
	
  if (!$termID)
    $termID = cams_query('term', 'get');

  if (!$termID)
    return FALSE;
  
  switch ($filterCriteria) {
    case 'status':
      $sql = "SELECT DISTINCT '$filterValue' AS status, StuStaV.StudentId AS id, StuStaV.FirstName AS firstName, StuStaV.LastName AS lastName, StuV.BoxNumber AS mailbox
		      FROM CAMS_Student_View StuV INNER JOIN CAMS_StudentStatus_View StuStaV ON StuStaV.StudentID = StuV.StudentID
			  INNER JOIN CAMS_SRAcademic_View StuRegV on StuStaV.StudentUID = StuRegV.StudentUID and StuStaV.TermCalendarID = StuRegV.TermCalendarID";
      
      switch ($filterValue) {	  
        case 'Student':
          $sql .= " WHERE StuStaV.Term = '$termID'"; // Registered in the current semester   

          break;
		  
        case 'Applicant':
          $sql = "SELECT DISTINCT '$filterValue' AS status, StudentID AS id, LastName AS lastName, FirstName AS firstName, TYPE, ProspectStatus
                      FROM CAMS_Student_View StuV 
                          WHERE (SELECT TC.Term FROM TermCalendar TC WHERE TC.TermCalendarID = StuV.ExpectedTermID) >= '$termID'
                          AND ProspectStatus IN ('Admitted', 'Conditional Admit', 'Probation Admit')
                          AND Type IN ('Confirmed', 'Defer', 'No Response')
                          AND StudentID <> '999999'";
          break;          
						  
        case 'fulltime':
          $sql .= " WHERE StuStaV.Term = '$termID'" // Registered in the current semester
				. " GROUP BY StuStaV.StudentId, StuStaV.FirstName, StuStaV.LastName, StuV.BoxNumber HAVING SUM(Credits) > 11"; //Only full-timers
          break;
          
        case 'fulltime_undergrad':
          $sql .= " WHERE StuStaV.Term = '$termID'" // Registered in the current semester
                . " AND LOWER(StuStaV.GPAGrouping) = 'undergraduate'" // Only Undergraduate Students
				. " GROUP BY StuStaV.StudentId, StuStaV.FirstName, StuStaV.LastName, StuV.BoxNumber HAVING SUM(Credits) > 11"; // Only full-timers
          break;
          
        case 'fulltime_graduate':
          $sql .= " WHERE StuStaV.Term = '$termID'" // Registered in the current semester
                . " AND LOWER(StuStaV.GPAGrouping) = 'graduate'" // Only Graduate Students
				. " GROUP BY StuStaV.StudentId, StuStaV.FirstName, StuStaV.LastName, StuV.BoxNumber HAVING SUM(Credits) > 11"; // Only full-timers
          break;
          
        case 'parttime':
          $sql .= " WHERE StuStaV.Term = '$termID'" // Registered in the current semester
				. "GROUP BY StuStaV.StudentId, StuStaV.FirstName, StuStaV.LastName, StuV.BoxNumber HAVING SUM(Credits) <= 11"; // Anything else aside from full-timers
          break;
          
        case 'parttime_undergrad':
          $sql .= " WHERE StuStaV.Term = '$termID'" // Registered in the current semester
                . " AND LOWER(StuStaV.GPAGrouping) = 'undergraduate'" // Only Undergraduate Students
				. " GROUP BY StuStaV.StudentId, StuStaV.FirstName, StuStaV.LastName, StuV.BoxNumber HAVING SUM(Credits) <= 11"; // Anything else aside from full-timers
          break;
          
        case 'parttime_graduate':
          $sql .= " WHERE StuStaV.Term = '$termID'" // Registered in the current semester
                . " AND LOWER(StuStaV.GPAGrouping) = 'graduate'" // Only Graduate Students
				. " GROUP BY StuStaV.StudentId, StuStaV.FirstName, StuStaV.LastName, StuV.BoxNumber HAVING SUM(Credits) <= 11"; // Anything else aside from full-timers
          break;          
          
        case 'graduate':
          $sql .= " WHERE StuStaV.Term = '$termID'" // Registration in the current semester
                . " AND LOWER(StuStaV.GPAGrouping) = 'graduate'"; // Only Graduate Students
          break;
          
        case 'undergrad':
            $sql .= " WHERE StuStaV.Term = '$termID'" // Registration in the current semester
            . " AND LOWER(StuStaV.GPAGrouping) = 'undergraduate'"; // Only Undergraduate Students
            break;
          
        default:
          return array();
		  
      }
      break;
      
    case 'classStanding':
      $sql = "SELECT DISTINCT StuStaV.StudentId AS id, StuStaV.FirstName AS firstName, StuStaV.LastName AS lastName, StuV.BoxNumber AS mailbox
		      FROM CAMS_Student_View StuV INNER JOIN CAMS_StudentStatus_View StuStaV ON StuStaV.StudentID = StuV.StudentID
			  INNER JOIN CAMS_SRAcademic_View StuRegV on StuStaV.StudentUID = StuRegV.StudentUID and StuStaV.TermCalendarID = StuRegV.TermCalendarID";
	  switch ($filterValue) {
        case 'freshmen':
          $classStandingCode = 'freshman';
          break;
        case 'sophomores':
          $classStandingCode = 'sophomore';
          break;
        case 'juniors':
          $classStandingCode = 'junior';
          break;
        case 'seniors':
          $classStandingCode = 'senior';
          break;
		default:
          $classStandingCode = $filterValue;
          break;		  
      }

	  if ($filterValue) {
        $sql .= " WHERE StuStaV.Term = '$termID'" //Registration in the current semester
             . "   AND LOWER(StuStaV.CollegeLevel) LIKE LOWER('$classStandingCode')+'%';"; //only the spec. class
	  } else {
		return array();
	  }
      break;

    case 'master':
	  $filterValue = preg_replace("/'/", "''", $filterValue);
      $sql = " SELECT distinct StuStaV.StudentId AS id"
			. " FROM CAMS_StudentStatus_View StuStaV"
			. " INNER JOIN CAMS_SRAcademic_View StuRegV"
			. " ON StuStaV.StudentUID = StuRegV.StudentUID AND StuStaV.TermCalendarID = StuRegV.TermCalendarID"
			. " INNER JOIN CAMS_StudentProgram_View StuProgV"
			. " ON StuStaV.StudentUID = StuProgV.StudentUID AND StuStaV.TermCalendarID = StuProgV.TermCalendarID"
			. "	WHERE StuStaV.Term ='$termID'" //Registration in the current semester
			. "	AND LOWER(StuStaV.GPAGrouping) = 'graduate'" //Only Graduate Students
            . " AND LOWER(StuProgV.MajorDegree) = '$filterValue'"; //Different master programs
      break;
      
    case 'major':
      $sql = " SELECT distinct StuStaV.StudentId AS id"
			. " FROM CAMS_StudentStatus_View StuStaV"
			. " INNER JOIN CAMS_SRAcademic_View StuRegV"
			. " ON StuStaV.StudentUID = StuRegV.StudentUID AND StuStaV.TermCalendarID = StuRegV.TermCalendarID"
			. " INNER JOIN CAMS_StudentProgram_View StuProgV"
			. " ON StuStaV.StudentUID = StuProgV.StudentUID AND StuStaV.TermCalendarID = StuProgV.TermCalendarID"
			. "	WHERE StuStaV.Term ='$termID'" //Registration in the current semester
			. "	AND LOWER(StuStaV.GPAGrouping) = 'undergraduate'" //Only undergraduate Students
            . " AND LOWER(StuProgV.MajorDegree) = '$filterValue'"; //Different majors programs
      break;

    case 'minor':
      $sql = " SELECT distinct StuStaV.StudentId AS id"
			. " FROM CAMS_StudentStatus_View StuStaV"
			. " INNER JOIN CAMS_SRAcademic_View StuRegV"
			. " ON StuStaV.StudentUID = StuRegV.StudentUID AND StuStaV.TermCalendarID = StuRegV.TermCalendarID"
			. " INNER JOIN CAMS_StudentProgram_View StuProgV"
			. " ON StuStaV.StudentUID = StuProgV.StudentUID AND StuStaV.TermCalendarID = StuProgV.TermCalendarID"
			. "	WHERE StuStaV.Term ='$termID'" //Registration in the current semester
			. "	AND LOWER(StuStaV.GPAGrouping) = 'undergraduate'" //Only undergraduate Students
            . " AND LOWER(StuProgV.MinorDegree) = '$filterValue'"; //Different minor programs
      break;

    case 'advisor':
	  // Query to retrieve advisees of a given advisor
      $sql = "SELECT distinct StuStaV.StudentID AS id" 
			  . " FROM CAMS_StudentStatus_View StuStaV INNER JOIN" 
			  . " CAMS_SRAcademic_View StuRegV ON StuStaV.StudentUID = StuRegV.StudentUID AND StuStaV.TermCalendarID = StuRegV.TermCalendarID INNER JOIN"
			  .	" CAMS_StudentProgram_View StuProgV ON StuStaV.StudentUID = StuProgV.StudentUID AND StuStaV.TermCalendarID = StuRegV.TermCalendarID INNER JOIN"
			  . " CAMS_UserList_View UserV ON StuProgV.AdvisorID = UserV.AdvisorID"
			  . " WHERE StuProgV.Term = '$termID'"
			  . " AND StuProgV.AdvisorID <> 0"
              . " AND UserV.CAMSUser = '$filterValue'"
			  . " ORDER BY StuStaV.studentID";
      break;
      
    case 'course':
	  // Query to retrieve students in a given course
      $sql = "SELECT StuCrsV.StudentID AS id"
              . " FROM CAMS_StudentScheduleRpt_View StuCrsV"
              . " WHERE StuCrsV.TermSeq = '$termID'"
              . " AND StuCrsV.Department+StuCrsV.Course =  '" .$filterValue->department.$filterValue->code . "'"
      	      . " AND StuCrsV.Section = '" .trim($filterValue->section) . "'";
      break;
      
    case 'library_privileges':
      // Query to retrieve students with special library privileges
      $sql = "SELECT StuStaV.StudentId AS id
		        FROM CAMS_StudentStatus_View StuStaV INNER JOIN CAMS_StudentStatusUserDefined_View StuSUDV on StuStaV.StudentStatusID = StuSUDV.StudentStatusID 
		        WHERE uDefBit1 = 1 AND StuStaV.Term ='$termID'";
      break;      
      
    default:
    	return array();
  
  }
  
// DEBUG drupal_set_message("SQL: $sql");
  $result = mssql_query($sql);

  $students = array();
  while ($student = mssql_fetch_object($result)) {
    $students['a'.$student->id] = $student;
  }
  
// DEBUG drupal_set_message("Result: <pre>".print_r($students, TRUE)."</pre>");
  return $students;
}

/**
/*
* TODO
*/
function cams_student_get_info($netID = NULL) {
	if (!cams_is_available())
	return FALSE;

	if (!$netID)
	return FALSE;

	$stuID = substr($netID, 1);
	$sql = "SELECT 
	       S.FirstName, S.MiddleName, S.LastName, SD.Veteran,
	       CAST(BirthDate AS DATE) AS BirthDate
      FROM CAMS_Student_View S 
           LEFT JOIN CAMS_StudentDemographics_View SD ON S.StudentUID = SD.StudentUID
      WHERE StudentID = '$stuID'";
	$query = mssql_query($sql);

  if (mssql_num_rows($query) == 1) {
    return mssql_fetch_object($query);
  }
  
  return FALSE;
}

/**
 /*
 * TODO
 */
function cams_student_get_classstanding($netID = NULL) {
  if (!cams_is_available())
    return FALSE;

  if (!$termID)
    $termID = cams_query('term', 'get');

  if (!$termID || !$netID)
    return FALSE;

  $stuID = substr($netID, 1);
  $sql = "SELECT CollegeLevel
  FROM CAMS_StudentStatus_View
  WHERE StudentID = '$stuID' AND Term = $termID";
  $query = mssql_query($sql);

  if (mssql_num_rows($query) == 1) {
    return mssql_result($query, 0, 'CollegeLevel');
  }
  return '';
}

/**
 /*
 * TODO
 */
function cams_student_get_gpagrouping($netID = NULL) {
  if (!cams_is_available())
    return FALSE;

  if (!$termID)
    $termID = cams_query('term', 'get');

  if (!$termID || !$netID)
    return FALSE;

  $stuID = substr($netID, 1);
  $sql = "SELECT GPAGrouping
  FROM CAMS_StudentStatus_View
  WHERE StudentID = '$stuID' AND Term = $termID";
  $query = mssql_query($sql);

  if (mssql_num_rows($query) == 1) {
    return mssql_result($query, 0, 'GPAGrouping');
  }
  return '';
}

/**
 /*
 * TODO
 */
function cams_student_get_degrees($netID = NULL, $type = 'major') {
  if (!cams_is_available())
    return FALSE;

  if (!$termID)
    $termID = cams_query('term', 'get');

  if (!$termID || !$netID)
    return FALSE;

  $stuID = substr($netID, 1);
  $column = ($type == major) ? 'MajorDegree' : 'MinorDegree';
  $sql = "SELECT $column AS Degree
  FROM CAMS_StudentProgram_View
  WHERE StudentUID in (SELECT StudentUID FROM CAMS_Student_View WHERE StudentID = '$stuID')
  AND Term = $termID";
  $query = mssql_query($sql);

  $degrees = array();
  while ($degree = mssql_fetch_object($query)) {
    if (trim($degree->Degree))
      $degrees[] = trim($degree->Degree);
  }

  return $degrees;
}

/*
 * TODO
 */
function cams_student_get_email($netID = NULL, $type = 'Current', $offset = 1) {
  if (!cams_is_available())
    return FALSE;

  if (!$netID)
    return FALSE;
    
  $stuID = substr($netID, 1);
  $type = strtolower($type);
  $sql = "SELECT email$offset AS email 
		  FROM CAMS_StudentAddressList_View
		  WHERE StudentID = '$stuID' AND LOWER(AddressType) = '$type' AND ActiveFlag='Yes'";
  $query = mssql_query($sql);
  
  if (mssql_num_rows($query) == 1) {
    return mssql_result($query, 0, 'email');
  }
    
  return NULL;
}

/*
 * TODO
*/
function cams_student_get_address($netID = NULL, $type = 'Current') {
  if (!cams_is_available())
    return FALSE;

  if (!$netID)
    return FALSE;

  $stuID = substr($netID, 1);
  $type = strtolower($type);
  $sql = "SELECT TOP 1 *
  FROM CAMS_StudentAddressList_View
  WHERE StudentID = '$stuID' AND LOWER(AddressType) = '$type' AND ActiveFlag='Yes' ORDER BY AddressID DESC";
  $query = mssql_query($sql);

  if (mssql_num_rows($query) == 1) {
    $address = mssql_fetch_object($query);
    foreach($address as &$prop) {
      $prop = trim($prop);
    }
    return $address;
  }
  
  return NULL;
}

/**
 * TODO
 *
 * @param unknown_type $netID
 * @param unknown_type $termID
 * @return unknown
 */
function cams_student_get_advisors($netID = NULL, $termID = NULL) {
  if (!cams_is_available())
    return FALSE;
	
  if (!$termID)
    $termID = cams_query('term', 'get');

  if (!$termID || !$netID)
    return FALSE;
    
  $stuID = substr($netID, 1);
  
  $result = mssql_query("SELECT FacultyPortal.ActiveDirectoryIdentifier AS netid, CAMS_Student_View.StudentUID
					       FROM CAMS_Student_View INNER JOIN CAMS_StudentProgram_View ON CAMS_Student_View.StudentUID = CAMS_StudentProgram_View.StudentUID LEFT OUTER JOIN
                                CAMS_UserList_View INNER JOIN FacultyPortal ON CAMS_UserList_View.FacultyID = FacultyPortal.FacultyID ON 
                                CAMS_StudentProgram_View.AdvisorID = CAMS_UserList_View.AdvisorID
						  WHERE CAMS_Student_View.StudentID = '$stuID'
                            AND CAMS_StudentProgram_View.Term = '$termID'
                            AND CAMS_StudentProgram_View.AdvisorID <> 0");
	
  $advisors = array();
  while ($line = mssql_fetch_array($result)) {
    $advisors[] = strtolower($line['netid']);
  }
  
  return $advisors;
}

/**
 * TODO
 *
 * @param unknown_type $netID
 * @param unknown_type $termID
 * @return unknown
 */
function cams_student_get_schedule($netID = NULL, $termID = NULL){
  if (!cams_is_available())
    return FALSE;
	
  if (!$termID)
    $termID = cams_query('term', 'get');

  if (!$termID || !$netID)
    return FALSE;
    
  $stuID = substr($netID, 1);

  $result = mssql_query("SELECT s.Department+' '+s.Course+s.Section as name, 
                                os.OfferDays as offerDays, 
                                os.RoomName as roomName, 
                                osf.FacultyName as facultyName, 
                                fp.PortalAlias as netID,
                                datename(hh, os.OfferTimeFrom)+':'+datename(mi, os.OfferTimeFrom) as startTime, 
                                datename(hh, os.OfferTimeTo)+':'+datename(mi, os.OfferTimeTo) as endTime
					       FROM CAMS_StudentScheduleRpt_View s, CAMS_SROfferSchedule_View os, CAMS_SROfferSchedule_Faculty_View osf, FacultyPortal fp
						  WHERE s.StudentID = '$stuID'
                            AND s.TermSeq = '$termID'
							AND s.SROfferID = os.SROfferID
							AND os.SROfferScheduleID = osf.SROfferScheduleID
							AND osf.FacultyID = fp.FacultyID");
							
  $rs = array();

  while ($line = mssql_fetch_object($result)) {
    $rs[] = $line;
  }

  return $rs;
}

/**
 * TODO
 *
 * @param unknown_type $netID
 * @return unknown
 */
function cams_student_get_ferpa($netID = NULL){
  if (!cams_is_available())
    return FALSE;

  if (!$termID)
    $termID = cams_query('term', 'get');

  if (!$termID || !$netID)
    return FALSE;

  $stuID = substr($netID, 1);

  $ferpaItems = array(
    'directory' => 2493,
    'address'   => 1530,
    'grade'     => 2494,
  );
  
  $rs = array();
  foreach ($ferpaItems as $key => $value) {
  	$result = mssql_query("
  	  SELECT AllowDisplay FROM StudentFerpa 
  	    WHERE FERPAItemID = $value
  	      AND StudentUID = (SELECT StudentUID FROM CAMS_Student_View WHERE StudentID = '$stuID')");
  	$line = mssql_fetch_object($result);
  	$rs[$key] = trim($line->AllowDisplay);
  }
  
  return $rs;
}

/**
 * TODO
 *
 * @param unknown_type $netID
 * @return unknown
 */
function cams_student_get_application_info($netID = NULL){
  if (!cams_is_available())
    return FALSE;

  $termID = cams_query('term', 'get');

  if (!$termID || !$netID)
    return FALSE;

  $stuID = substr($netID, 1);

  $result = mssql_query("
    SELECT StuV.ExpectedTerm expectedTermName, 
           TermCalendar.Term expectedTerm, 
           StuV.ProspectStatus status, 
           StuV.Type response, 
           StuV.enrollmentStatus initialStatus,
           StuV.RecruiterName counselor
      FROM CAMS_Student_View StuV 
           INNER JOIN TermCalendar ON StuV.expectedTermID = TermCalendar.TermCalendarID
           -- INNER JOIN CAMS_RecruiterSignature_View RecV ON StuV.RecruiterID = RecV.RecruiterID
     WHERE StudentID = '$stuID'");
  $rs = array();

  return mssql_fetch_object($result);
}

/**
* TODO
*
* @param unknown_type $netID
* @return unknown
*/
function cams_student_get_checkin_info($netID = NULL){
	if (!cams_is_available())
	return FALSE;

	$termID = variable_get('cams_prearrival_term', NULL);
	
	if (!$termID || !$netID)
	return FALSE;

	$stuID = substr($netID, 1);

	$query = mssql_query("
	SELECT StudentRegistered 
	  FROM CAMS_StudentStatus_View 
	 WHERE StudentID = $stuID
	   AND Term = $termID");
	$rs = mssql_fetch_object($query);
	$registrationStatus = $rs->StudentRegistered;

	$query = mssql_query("
	SELECT CAST(uDefDate1 AS date) AS checkinDate
	  FROM CAMS_StudentStatusUserDefined_View 
	 WHERE StudentStatusID in
             (SELECT StudentStatusID 
                FROM CAMS_StudentStatus_View
               WHERE StudentID = $stuID
                 AND Term = $termID)");
	$rs = mssql_fetch_object($query);
	$checkinDate = $rs->checkinDate;
	
	return array(
	  'registrationStatus' => $registrationStatus,
	  'checkinDate'        => $checkinDate);
}

/**
* TODO
*
* @param unknown_type $netID
* @return unknown
*/
function cams_student_get_holds($netID = NULL){
  if (!cams_is_available())
	return FALSE;

  if (!$netID)
	return FALSE;

  $stuID = substr($netID, 1);

  $result = mssql_query("
      SELECT HoldCategoryID, HoldCategory, CAST(HoldDate AS date) AS HoldDate, HoldDescription, StopGradeCard, StopOnLineRegistration, StopStatement, StopTranscript
        FROM CAMS_StudentHolds_View
       WHERE StudentUID in (SELECT StudentUID FROM CAMS_Student_View WHERE StudentID = '$stuID')
         AND HoldStatus = 'Hold'
  ");
  $rs = array();

  while ($line = mssql_fetch_object($result)) {
    $rs[] = $line;
  }

  return $rs;
}

/**
* TODO
*
* @param unknown_type $netID
* @return unknown
*/
function cams_student_get_sis_info($netID = NULL){
	if (!cams_is_available())
	return FALSE;

	if (!$netID)
	return FALSE;

	$stuID = substr($netID, 1);

	$result = mssql_query("
	  SELECT UserDefFreeFormat2 AS Status, CAST(UserDefDate1 AS Date) AS Date 
	    FROM CAMSUserDefined 
	   WHERE SystemUID in (SELECT StudentUID FROM Student WHERE StudentID = '$stuID')
    ");
    $result = mssql_fetch_object($result);
    return $result ? $result : 'TEST';
}

/**
* TODO
*
* @param string $netID
* @param string $date (YYYY-MM-DD) New Check-in Date
* @return boolean
*/
function cams_student_set_checkin_date($netID = NULL, $date = NULL) {
	if (!cams_is_available() || !$netID || !$date)
	return FALSE;

	$stuID = substr($netID, 1);
    $term = variable_get('cams_prearrival_term', NULL);

    if (mssql_num_rows(mssql_query("
      SELECT 1 FROM StudentStatusUDef
       WHERE StudentStatusID in (SELECT StudentStatusID from StudentStatus where StudentUID = (SELECT StudentUID FROM Student WHERE StudentID ='$stuID')
         AND TermCalendarID = (SELECT TermCalendarID from TermCalendar WHERE term = '$term'))
    ")) > 0) {
	  return mssql_query("
        UPDATE StudentStatusUDef
           SET uDefDate1 = CAST('$date' AS DATETIME)
         WHERE StudentStatusID in (SELECT StudentStatusID from StudentStatus where StudentUID = (SELECT StudentUID FROM Student WHERE StudentID ='$stuID')
           AND TermCalendarID = (SELECT TermCalendarID from TermCalendar WHERE term = '$term'))
      ");
    }
    else {
      $query = mssql_query("
    	SELECT StudentStatusID
    	  FROM StudentStatus
    	 WHERE StudentUID = (SELECT StudentUID FROM Student WHERE StudentID ='$stuID')
    	   AND TermCalendarID = (SELECT TermCalendarID from TermCalendar WHERE term = '$term')
      ");
/*drupal_set_message("SELECT StudentStatusID
    	  FROM StudentStatus
    	 WHERE StudentUID = (SELECT StudentUID FROM Student WHERE StudentID ='$stuID')
    	   AND TermCalendarID = (SELECT TermCalendarID from TermCalendar WHERE term = '$term')
      ");
drupal_set_message('Debug: ' . $result->StudentStatusID);*/ 
      $result = mssql_fetch_object($query);
      $studentStatusID = $result->StudentStatusID;
      return mssql_query("
    	INSERT INTO StudentStatusUDef(StudentStatusID, uDefDate1)
    	VALUES ($studentStatusID, CAST('$date' AS DATETIME))
      ");
    }
}

/**
* TODO
*
* @param string $netID
* @param string $date (YYYY-MM-DD) New Birth Date
* @return boolean
*/
function cams_student_set_birthdate($netID = NULL, $date = NULL) {
	if (!cams_is_available() || !$netID || !$date)
	  return FALSE;

	$stuID = substr($netID, 1);

	return mssql_query("
	  UPDATE Student
         SET BirthDate = '$date'
	   WHERE StudentUID = (SELECT StudentUID FROM CAMS_Student_View WHERE StudentID = '$stuID')
	");	
}

/**
 * TODO
 *
 * @param string $netID
 * @param object $address
 * @return boolean
 */
function cams_student_set_address($netID = NULL, $address = NULL) {
  if (!cams_is_available())
    return FALSE;

  if (!$netID || !is_object($address))
    return FALSE;

  $stuID = substr($netID, 1);

  $formerAddress = cams_query('student', 'get_address', $netID, $address->AddressType);
  
  /*
   * Check if the address was modified
   */
  if (!$formerAddress->AddressID
    || $address->Address1 != $formerAddress->Address1
    || $address->Address2 != $formerAddress->Address2
    || $address->Address3 != $formerAddress->Address3
    || $address->City != $formerAddress->City
    || $address->StateID != $formerAddress->StateID
    || $address->CountryID != $formerAddress->CountryID
    || $address->ZipCode != $formerAddress->ZipCode
    || $address->Phone1 != $formerAddress->Phone1
    || $address->Email1 != $formerAddress->Email1
    || $address->ResponsibleParty != $formerAddress->ResponsibleParty
    || $address->MobilePhone != $formerAddress->MobilePhone
    ) {
    /*
     * Create a new address
     */ 

    // Retrieve the StudentID
    $sql = "SELECT StudentUID id FROM Student WHERE StudentID=$stuID";
    $query = mssql_query($sql);
    $result = mssql_fetch_object($query);
    if (!$address->StudentUID = $result->id) {
      $msg = t('Unable to retrieve StudentUID from CAMS for @netID',
               array('@netID' => $netID));
      drupal_set_message($msg, 'error');
      watchdog('cams', $msg, array(), WATCHDOG_ERROR);
      return FALSE;
    }
    // DEBUG drupal_set_message("StudentUID = $address->StudentUID");

    // Retrieve the AddressTypeID
    $sql = "SELECT UniqueID id FROM Glossary WHERE Category=14 AND lower(DisplayText) = '" . strtolower($address->AddressType) . "'";
    $query = mssql_query($sql);
    $result = mssql_fetch_object($query);
    if (!$address->AddressTypeID = $result->id) {
      $msg = t('Unable to retrieve addressTypeID from CAMS for @addressType address Type',
               array('@addressType' => $address->AddressType));
      drupal_set_message($msg, 'error');
      watchdog('cams', $msg, array(), WATCHDOG_ERROR);
      return FALSE;
    }
    // DEBUG drupal_set_message("addressTypeID = $address->AddressTypeID");

    // Deactivate the former address
    if ($formerAddress->AddressID) {
      $sql = "UPDATE Address SET ActiveFlag = 'No' WHERE AddressID=" . $formerAddress->AddressID;
      // DEBUG drupal_set_message($sql);
      if (!$query = mssql_query($sql)) {
        $msg = t('Unable deactivate the @addressID address to @netID (@studentUID)',
                 array('@addressID' => $address->AddressID,
                       '@netID' => $netID,
                       '@studentUID' => $address->StudentUID,
                      )
                );
        drupal_set_message($msg, 'error');
        watchdog('cams', $msg, array(), WATCHDOG_ERROR);
        return FALSE;
      }
    }
        
    // Insert the new Address
    $sql = "
    INSERT INTO Address
         (AddressTypeID
         ,Address1
         ,Address2
         ,Address3
         ,City
         ,County
         ,StateID
         ,CountryID
         ,ZipCode
         ,Phone1
         ,Phone2
         ,WorkPhone1
         ,Fax1
         ,Email1
         ,Email2
         ,Email3
         ,ActiveFlag
         ,ResponsibleParty
         ,PhoneOfficeCode
         ,PhoneExtension
         ,BoxNumber
         ,InsertUserID
         ,InsertTime
         ,UpdateUserID
         --,Updatetime
         ,MobilePhone
         ,InternationalFlag
         --,AddressValidationDate
         ,Town
         )
   VALUES
         ($address->AddressTypeID
         ,'" . str_replace("'", "''", $address->Address1) . "'
         ,'" . str_replace("'", "''", $address->Address2) . "'
         ,'" . str_replace("'", "''", $address->Address3) . "'
         ,'" . str_replace("'", "''", $address->City) . "'
         ,''
         ,$address->StateID
         ,$address->CountryID
         ,'" . str_replace("'", "''", $address->ZipCode) . "'
         ,'" . str_replace("'", "''", $address->Phone1) . "'
         ,''
         ,''
         ,''
         ,'" . str_replace("'", "''", $address->Email1) . "'
         ,''
         ,''
         ,'Yes'
         ,'" . str_replace("'", "''", $address->ResponsibleParty) . "'
         ,''
         ,''
         ,''
         ,'MYAUP'
         ,SYSDATETIME()
         ,''
         --,
         ,'" . str_replace("'", "''", $address->MobilePhone) . "'
         ,''
         --,
         ,''
         );
         SELECT SCOPE_IDENTITY();
    ";
    // DEBUG drupal_set_message($sql);
    $query = mssql_query($sql);
    $result = mssql_fetch_array($query);
    if (!$address->AddressID = $result[0]) {
      $msg = t('Unable to retrieve addressID from CAMS');
      drupal_set_message($msg, 'error');
      watchdog('cams', $msg, array(), WATCHDOG_ERROR);
      return FALSE;
    }
    // DEBUG drupal_set_message("addressID = $address->AddressID");
   
    // Insert the Student-Address relationship
    $sql = "
   INSERT INTO Student_Address
   (StudentID
   ,AddressID
   ,PrimaryMailingAddress
   ,SeasonalID
   ,MailStatementTo
   ,MailGradeCardTo
   ,MailTranscriptTo
   )
   VALUES
   ($address->StudentUID
   ,$address->AddressID
   ,'" . ($address->AddressTypeID == 287 ? 'Yes' : 'No') . "'
   ,0
   ,'" . ($address->AddressTypeID == 283 || $address->AddressTypeID == 287 ? 'Yes' : 'No') . "'
   ,'" . ($address->AddressTypeID == 287 ? 'Yes' : 'No') . "'
   ,'" . ($address->AddressTypeID == 287 ? 'Yes' : 'No') . "'
   )
    ";
    // DEBUG drupal_set_message($sql);
    if (!$query = mssql_query($sql)) {
      $msg = t('Unable to link the @addressID address to @netID (@studentUID)',
               array('@addressID' => $address->AddressID,
                     '@netID' => $netID,
                     '@studentUID' => $address->StudentUID,
                    )
              );
      drupal_set_message($msg, 'error');
      watchdog('cams', $msg, array(), WATCHDOG_ERROR);
      return FALSE;
    }
    $msg = t('@addressType address @addressID modified for @netID (@studentUID)',
        array('@addressType' => $address->AddressType,
              '@addressID' => $address->AddressID,
              '@netID' => $netID,
              '@studentUID' => $address->StudentUID,
        )
    );
    watchdog('cams', $msg, array(), WATCHDOG_NOTICE);
  }

  return TRUE;
}

/**
* TODO
*
* @param string $netID
* @param array $netID
* @return boolean
*/
function cams_student_set_ferpa($netID = NULL, $item = NULL, $value = NULL) {
  if (!cams_is_available())
	return FALSE;
	
  if (!$netID || !$item  || !$value )
	return FALSE;
	
  $stuID = substr($netID, 1);
  
  switch ($item) {
  	case 'directory':
  	  $ferpaItemID = 2493;
  	  break;  
  	case 'address':
  	  $ferpaItemID = 1530;
  	  break;  
  	case 'grade':
  	  $ferpaItemID = 2494;
  	  break;  
  	default:
  	  return FALSE;
  }
  
  $query = mssql_query("
    SELECT * FROM StudentFerpa 
     WHERE FERPAItemID = $ferpaItemID
  	   AND StudentUID = (SELECT StudentUID FROM CAMS_Student_View WHERE StudentID = '$stuID')");
  if (mssql_fetch_object($query)) {
  	mssql_query("
  	  UPDATE StudentFerpa
         SET AllowDisplay = '$value', UpdateUserID = 'MyAUP'
          WHERE FERPAItemID = $ferpaItemID
  	        AND StudentUID = (SELECT StudentUID FROM CAMS_Student_View WHERE StudentID = '$stuID')
  	");
  }
  else {
  	mssql_query("
  	  INSERT INTO StudentFerpa
  	    (StudentUID, FERPAItemID, AllowDisplay, InsertUserID, InsertTime, UpdateUserID, RelationCanRecv)
      VALUES 
        ((SELECT StudentUID FROM CAMS_Student_View WHERE StudentID = '$stuID'), $ferpaItemID, '$value', 'MyAUP', SYSDATETIME(),'', '' )
    ");
  }
  
  return TRUE;
}

/**
 * TODO
 *
 * @param string $netID
 * @param array $netID
 * @return boolean
 */
function cams_student_set_application_status($netID = NULL, $status = NULL) {
  if (!cams_is_available())
    return FALSE;

  if (!$netID || !$status)
    return FALSE;

  $stuID = substr($netID, 1);

  switch ($status) {
    case 'declined':
      mssql_query("UPDATE Student
          SET TypeID = 2740, WithdrawnDate = SYSDATETIME()
          WHERE StudentID = '$stuID'"); // 2740 : Declined admission
      break;
      
    case 'deferred':
      mssql_query("UPDATE Student
          SET TypeID = 2742
          WHERE StudentID = '$stuID'"); // 2742 : Defer
      break;
      
    case 'confirmed':
      mssql_query("UPDATE Student
          SET TypeID = 2176, RoomDepositAmt = 350, RoomDepositDate = SYSDATETIME()
          WHERE StudentID = '$stuID'"); // 2176 : Confirmed
      break;

    case 'noresponse':
      mssql_query("UPDATE Student
      	SET TypeID = 2741, RoomDepositAmt = '', RoomDepositDate = ''
      	WHERE StudentID = '$stuID'"); // 2741 : No Response
      break;      
            
    default:
      return FALSE;
  }
  
  return TRUE;
}

/**
 * TODO
 *
 * @return unknown
 */
function cams_student_enable_portal_access(){
  if (!cams_is_available())
    return FALSE;

  return mssql_query("UPDATE StudentPortal
						 SET PortalHandle='a'+(SELECT s.StudentID FROM Student s WHERE s.StudentUID=StudentPortal.StudentUID),
						     ActiveDirectoryIdentifier='a'+(SELECT s.StudentID FROM Student s WHERE s.StudentUID=StudentPortal.StudentUID)  
					   WHERE StudentPortal.StudentUID IS NOT NULL");
}

function cams_student_get_last_semester($netID) {
  if (!cams_is_available())
    return FALSE;

  if (!$netID)
    return FALSE;

  $stuID = substr($netID, 1);
  
  $query = mssql_query("
    SELECT MAX(Term) AS Term
      FROM CAMS_SRAcademic_View
     WHERE StudentID = $stuID");
      
  $item = mssql_fetch_object($query);
  $name = $item->Term;
  
  $query = mssql_query("
      SELECT TermEndDate
        FROM TermCalendar
       WHERE TextTerm = '$name'");
  
  $item = mssql_fetch_object($query);
  $endDate = $item-> TermEndDate;

  return array('name' => $name, 'endDate' => $endDate);
}

function cams_student_is_returning($netID) {
  if (!cams_is_available())
	return FALSE;

  if (!$netID)
	return FALSE;

  $stuID = substr($netID, 1);
  $term = cams_query('term', 'get');
  
  $rs = mssql_query("
    SELECT TOP 1 1 AS Var 
    FROM CAMS_SRAcademic_View 
    WHERE StudentID = $stuID AND TermSeq < $term and TermSeq <> ''");
  
  return (mssql_num_rows($rs) == 1 ? 'Yes' : 'No');
}
