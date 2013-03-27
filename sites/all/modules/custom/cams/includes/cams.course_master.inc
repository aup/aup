<?php

/**
 * @file
 * CAMS - Course Master
 * CAMS functions related to Course masters
 */

/**
 * Retrieves all active course masters.
 *    
 * @return array
 *   An array of course masters indexed by course code
 */
function cams_course_master_get() {
  if (!cams_is_available()) {
    return FALSE;
  }

  $sql = "
    SELECT Department+CourseNumber AS code,
    SRM.SRMasterID AS cams_id,
    Department AS department,
    CourseType AS type,
    CourseName AS name,
    Credits AS credits,
    CanRepeat AS canrepeat,
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
 * Retrieves equivalencies of a given course master.
 *
 * @param string $id
 *   Course Master ID
 *   
 * @return array
 *   An array of ID of equivalent courses
 */
function cams_course_master_get_equivalencies($id = '') {
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
