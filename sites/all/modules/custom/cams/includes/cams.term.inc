<?php

/**
 * @file
 * CAMS - Term
 * CAMS functions related to Terms
 */

/**
 * Get Terms upon various parameters
 *
 * @param string $type
 *   Criteria which defines which term ID to return. See @return for more details.
 *
 * @return string
 *  Returns the current term ID if $type is 'current'
 *
 * @return array of objects
 *  Returns all known terms if $type is 'all'
 *          all active terms if $type is 'active'
 *         string
 *   Attributes:
 *    - ID Term ID
 *    - Name Term Name
 */
function cams_term_get($type = 'current') {
  if (!cams_is_available()){
    return FALSE;
  }

  switch ($type) {
    case 'all':
      $sql = mssql_query("
               SELECT Term AS id, TextTerm AS name FROM TermCalendar
               ORDER BY Term");
      $result = array();
      while ($line = mssql_fetch_object($sql)) {
        $result[] = $line;
      }
      break;

    case 'active':
      $sql = mssql_query("
                SELECT Term AS id, TextTerm AS name FROM TermCalendar
                 WHERE ActiveFlag = 1
              ORDER BY Term");
      $result = array();
      while ($line = mssql_fetch_object($sql)) {
      	if ($line->id) {
          $result[] = $line;
      	}
      }
      break;

	case 'current':
	  $result = variable_get('cams_current_term', NULL);
	  break;

    case 'past':
  	  $currentTerm = variable_get('cams_current_term', NULL);
  	  $sql = mssql_query("
  	    SELECT Term AS id, TextTerm AS name FROM TermCalendar
  	    WHERE Term < $currentTerm AND ActiveFlag = 1
  	    ORDER BY Term");
  	  $result = array();
  	  while ($line = mssql_fetch_object($sql)) {
  		$result[] = $line;
  	  }
      break;
	  		  
	case 'future':
	  $currentTerm = variable_get('cams_current_term', NULL);
	  $sql = mssql_query("
	    SELECT Term AS id, TextTerm AS name FROM TermCalendar
	    WHERE Term >= $currentTerm AND ActiveFlag = 1
              AND DisplayInStudentPortal = 1 and DisplayInFacultyPortal = 1
	    ORDER BY Term");
	  $result = array();
	    while ($line = mssql_fetch_object($sql)) {
	      $result[] = $line;
	    }
	    break;	 

    case 'future_summer':
    	$currentTerm = variable_get('cams_current_term', NULL);
    	$sql = mssql_query("
    	    SELECT Term AS id, TextTerm AS name FROM TermCalendar
    	    WHERE Term >= $currentTerm AND ActiveFlag = 1 AND Term LIKE '%06'
    	    ORDER BY Term");
    	$result = array();
    	while ($line = mssql_fetch_object($sql)) {
    		$result[] = $line;
    	}
    	break;
    	 
  }
  
  return $result;
}

/**
 * TODO
 */
function cams_term_get_name($termID = NULL) {
  if (!cams_is_available()){
    return FALSE;
  }
  if (!$termID) {
    $termID = cams_query('term', 'get');
  }
  if ($result = mssql_result(mssql_query("SELECT TextTerm FROM TermCalendar WHERE Term = '$termID'"), 0, 'TextTerm')) {
   return $result;
  }
  else {
  	return '';
  }
}

/**
 * TODO
 */
function cams_term_get_id($term = NULL) {
	if (!cams_is_available()){
		return FALSE;
	}
	if (!$term) {
		return cams_query('term', 'get');
	}
	if ($result = mssql_result(mssql_query("SELECT Term FROM TermCalendar WHERE TextTerm = '$term'"), 0, 'Term')) {
		return $result;
	}
	else {
		return '';
	}
}

/**
 * TODO
 */
function cams_term_get_dates($termID = NULL) {
  if (!cams_is_available()){
    return FALSE;
  }  
  if (!$termID) {
    $termID = cams_query('term', 'get');
  }
  $result = mssql_query("
    SELECT convert(varchar, TermStartDate, 101) AS TermStartDate, -- mm/dd/yyyy
           convert(varchar, TermEndDate, 101) AS TermEndDate      -- mm/dd/yyyy
      FROM TermCalendar
     WHERE Term = $termID");

  while ($dates = mssql_fetch_object($result)) {
    return $dates;
  }
  return FALSE;  
}

/**
 * TODO
 */
function cams_term_get_majors($term = NULL) {
  if (!cams_is_available()){
    return FALSE;
  }
  if (!$term) { $term = cams_query('term', 'get'); }
  $sql = "SELECT DISTINCT stufields.field_code
            FROM stureg, stufields
           WHERE stureg.stu_id = stufields.stu_id 
             AND stufields.field_type = 'MAJ'
             AND stureg.Term = $term ORDER BY field_code";
  $result = mssql_query($sql);
  while ($line = mssql_fetch_array($result)) {
    $majors[] = $line['field_code'];
  }
  
  return $majors; 
}

/**
 * TODO
 */
function cams_term_get_minors($term = NULL) {
  if (!cams_is_available()){
    return FALSE;
  }
  if (!$term) { $term = cams_query('term', 'get'); }
  $sql = "SELECT DISTINCT stufields.field_code
            FROM stureg, stufields
           WHERE stureg.stu_id = stufields.stu_id 
             AND stufields.field_type = 'MIN'
             AND stureg.Term = $term ORDER BY field_code";
  $result = mssql_query($sql);
  while ($line = mssql_fetch_array($result)) {
    $minors[] = $line['field_code'];
  }
  
  return $minors; 
}

/**
 * TODO
 */
function cams_term_get_graduate_programs($term = NULL) {
  if (!cams_is_available()){
    return FALSE;
  }
  if (!$test) { $test = cams_query('term', 'get'); }
  $sql = "SELECT DISTINCT program_code
            FROM stureg
           WHERE Term = $Term
             AND curriculum = 'GMP' ORDER BY program_code";
  $result = mssql_query($sql);
  while ($line = mssql_fetch_array($result)) {
    $masters[] = $line['program_code'];
  }
  
  return $masters; 
}
