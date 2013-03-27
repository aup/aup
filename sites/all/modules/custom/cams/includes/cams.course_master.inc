<?php

/**
 * @file
 * CAMS - Course Master
 * CAMS functions related to Course masters
 */

/**
 * TODO
 */
function cams_course_master_get() {
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

	$result = mssql_query($sql);
	while ($course = mssql_fetch_object($result)) {
		$courses[$course->code] = $course;
	}

	return $courses;
}

/**
 * TODO
 * @param unknown_type $id
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
