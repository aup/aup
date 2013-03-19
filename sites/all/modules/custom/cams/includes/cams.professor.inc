<?php
/*
 * AMIS Integration
 * Integration between AMIS and MyAUP
 *
 * @author: Pierre-Yves Vasener <pvasener@aup.edu>
 */
 
/*
 * PROFESSOR FUNCTIONS
 */

/**
 * Get the AMIS professor ID from his/her NetID
 *
 * @param string $netid Professor's NetID
 * @return string Professor's AMIS ID or null
 */
/*function amis_professor_get_id($netid){
  if (!cams_is_available() || !$netid) { return FALSE; }
  
  $sql = "SELECT prof_id FROM prof where netid = '".strtoupper($netid)."'";
  $prof_id = amis_result(amis_query($sql));
  if (!$prof_id) {
    $subject = 'AMIS - professor\'s netid not found';
    $body = "AMIS :  netid $netid was not found in prof table.";
    $site_mail = variable_get('site_mail', null);
    $to = 'mpaille@aup.edu';
    if (!drupal_mail('amis_professor_get_id',$to, $subject, $body, $site_mail)) {
      watchdog('amis', t('Error mailing prof netid retrieval failure to %email', array('%email'=>$to)));
    }
  }
  return $prof_id;
}

function amis_professor_get($term = NULL) {
  if (!cams_is_available()) { return FALSE; }
  if (!$term) { $term = amis_semester_get_id(); }

  $sql = "select distinct lastname, firstname, netid, p.prof_id from prof p, crsprof cp, crssem cs, courses c
where p.prof_id = cp.prof_id
and cp.crssem_id = cs.crssem_id
and sem_id = $term
and cs.course_code = c.course_code
and course_curriculum in ('AUP', 'GMP')";

  $result = amis_query($sql);

  $faculty = array();
  while ($line = amis_fetch_object($result)) {
    $faculty[$line->netid] = $line;
  }

  return $faculty;
}

function amis_professor_get_office_hours(){
  if (!cams_is_available()) { return FALSE; }
  if (!$term) { $term = amis_semester_get_id(); }

  $sql = "SELECT p.firstname, p.lastname, p.netid, p.office_hours,
                 p.office_location AS office, p.mailbox_location AS mailbox,
                 p.tel_aup_ext AS phone
            FROM prof p
           WHERE p.active_semester = $term
        ORDER BY p.lastname";
  $result = amis_query($sql);

  if ($result) {
    while($line = amis_fetch_array($result)){
      $rows[] = $line;	
    }
    return $rows;
  }

  return FALSE;
}*/

/**
 * Retrieve the Professor's academic schedule
 *
 * @param string $netid
 * @param number $term
 * @return array
 */
/*function amis_professor_get_schedule($netid, $term) { 
  if (!cams_is_available() || !$netid) { return FALSE; }
  if (!$term) { $term = amis_semester_get_id(); }
  
  $prof_id = amis_professor_get_id($netid);
  if ($prof_id) { 
    $result = amis_query("SELECT course_code, course_section, ac.course_no, ac.course_title, prof_name,
                                                                class_period as period,
                                                                weekday_code, classroom, weekday_order
                                                        FROM rv_academic_schedule ac, crssem cs
                                                        WHERE prof_id = $prof_id
                                                        AND ac.sem_id = $term
                                                        AND ac.crssem_id = cs.crssem_id
                                                        ORDER BY weekday_order, ac.course_no");
    $rs = array();

    while ($line = amis_fetch_array($result)) {
      $courseCode = theme('amis_course_code', $line['course_code'], $line['course_section']);
      $line['courseCode'] = $courseCode;
      $rs[] = $line;
    }
  }
  return $rs;
}*/

/**
 * Retrieve the Professor's student list
 *
 * @param string $netid NetID of the professor
 * @param number $term
 * @return array
 */
function cams_professor_get_students($netid, $term = NULL) { 
  if (!cams_is_available() || !$netid) { return FALSE; }
  if (!$term) { $term = cams_query('term', 'get'); }

  $result = mssql_query("SELECT  DISTINCT CAMS_SRAcademic_View.StudentID stu_id,  
                         CAMS_SRAcademic_View.Department +' '+ CAMS_SRAcademic_View.Course course_code,
                         CAMS_SRAcademic_View.Section course_section,
                         CAMS_SRAcademic_View.CourseName course_name
                        FROM   CAMS_SRAcademic_View JOIN
                        CAMS_SROfferFacultyTeach_View ON CAMS_SRAcademic_View.SROfferID = CAMS_SROfferFacultyTeach_View.SROfferID
                        JOIN FacultyPortal ON CAMS_SROfferFacultyTeach_View.FacultyID = FacultyPortal.FacultyID
						WHERE     UPPER(FacultyPortal.ActiveDirectoryIdentifier) = UPPER('$netid') 
						AND CAMS_SRAcademic_View.TermSeq = '$term'
						ORDER BY course_code");
  
  $rs = array();

  while ($line = mssql_fetch_object($result)) {
    $rs['a'.$line->stu_id][] = $line;
  }
  
  return $rs;
}

/**
 * Retrieve the Professor's advisee list
 *
 * @param number $netid NetID of the professor
 * @param number $term Concerned Term
 * @return array An array of advisees
 */
function cams_professor_get_advisees($netid, $term = NULL) {
  if (!cams_is_available() || !$netid) { return FALSE; }
  if (!$term) { $term = cams_query('term', 'get'); }
  
  $result = mssql_query("SELECT DISTINCT CAMS_Student_View.StudentID stu_id
                           FROM CAMS_Student_View INNER JOIN CAMS_StudentProgram_View ON CAMS_Student_View.StudentUID = CAMS_StudentProgram_View.StudentUID LEFT OUTER JOIN
                                CAMS_UserList_View INNER JOIN FacultyPortal ON CAMS_UserList_View.FacultyID = FacultyPortal.FacultyID ON
                                CAMS_StudentProgram_View.AdvisorID = CAMS_UserList_View.AdvisorID
                          WHERE FacultyPortal.ActiveDirectoryIdentifier = UPPER('$netid') 
                          AND CAMS_StudentProgram_View.Term = '$term'");
  
  $rs = array();

  while ($line = mssql_fetch_object($result)) {
    $rs[] = 'a' . $line->stu_id;
  }
  
  return $rs;
  
}

/**
 * TODO
 */
function cams_professor_get_advisors($term = NULL) {
  if (!cams_is_available()) { return FALSE; }
  if (!$term) { $term = cams_query('term', 'get'); }
  //get advisors for a given semester
  //This query used to return the netid, the prof last name and prof first name
  //Modified to only return netid and recup other info from MyAUP profile
  $sql = "SELECT DISTINCT CAMSUser netid FROM CAMS_UserList_View UsersV 
			JOIN CAMS_StudentProgram_View StuProgV ON (UsersV.Advisor = StuProgV.Advisor)
			WHERE STUprogv.Term = '". $term ."' 
			  AND StuProgV.AdvisorID <> 0
			ORDER BY netid";
  $result = mssql_query($sql);
  $advisors = array();
  while ($line = mssql_fetch_object($result)) {	
  	  $advisors[] = $line->netid;	
  }
  return $advisors; 
}