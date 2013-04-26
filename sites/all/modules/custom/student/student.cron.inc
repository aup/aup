<?php

/**
 * @file
 * Cron callbacks for the Student module.
 */

/**
 * Synchronizes Student accounts with CAMS.
 */
function student_sync() {
  global $user;

  // Need to masquerade as an admin user (uid = 1) to be able to properly create new user accounts
  $previousUser = $user;
  $user = user_load(1);

  $rc = WATCHDOG_INFO;
  aup_custom_task_start();

  if (!cams_is_available()) {
    $report[] = t('[ERROR] CAMS is not available');
    return aup_custom_task_end($report, WATCHDOG_ERROR);
  }

  if (!active_directory_is_available()) {
    $report[] = t('[ERROR] Active Directory is not available');
    return aup_custom_task_end($report, WATCHDOG_ERROR);
  }

  /*
   * Retrieves Students from CAMS.
   */
  $applicants = cams_query('student', 'get', 'type', 'Applicant');
  $currentStudents = cams_query('student', 'get', 'type', 'Current Student');
  $report[] = "[INFO] " . count($applicants) . " applicants in CAMS.";
  $report[] = "[INFO] " . count($currentStudents) . " current students in CAMS.";
  
  /*
   * Create or modify the accounts for each student in CAMS
   */
  $stop = FALSE;
  $invalid = array();
  $students = array_merge($applicants, $currentStudents);
  foreach($students as $student) {
    // Check the validity of the student information in CAMS
    $student->netid = 'a' . $student->id;
    $student->email = cams_query('student', 'get_email', $student->netid);
    if (!valid_email_address($student->email)) {
      $invalid[$student->type][] = $student;
      $report[] = t('[WARNING] @name has an invalid e-mail (@email)',
          array('@name'  => $student->netid,
                '@email' => $student->email));
      $rc = WATCHDOG_WARNING;
      continue;
    }

    // Create a new account if non-existent
    if (!$account = user_load_by_name($student->netid)) {
      // Account Creation
      $account = new StdClass();
      $account->is_new = TRUE;
      $account->status = TRUE;
      $account->name = $student->netid;
      $account->mail = $student->netid.'@aup.edu';
      $account->init = $student->netid.'@aup.edu';
      $account->field_user_type[LANGUAGE_NONE][0]['value'] = $student->type;
      $account->field_firstname[LANGUAGE_NONE][0]['value'] = trim(ucwords(strtolower($student->firstName)));
      $account->field_lastname[LANGUAGE_NONE][0]['value'] = trim(ucwords(strtolower($student->lastName)));
      $account->field_personal_email[LANGUAGE_NONE][0]['value'] = $student->email;
      user_save($account);
      if (!$account->uid) {
        $report[] = t('[ERROR] Unable to create a Drupal account for @netid',
            array('@netid' => $student->netid));
        $rc = WATCHDOG_ERROR;
        continue;
      }
      else {
        $report[] = t('[INFO] New @role account created for @netid',
          array('@role'  => $student->type,
                '@netid' => $student->netid));
      }
      //$stop = TRUE;
    }

    // The account already exists
    else {
      // Activate it if needed
      if (!$account->status) {
        $account->status = TRUE;
        $report[] = t('[INFO] Account @netid reactivated' ,
          array('@netid' => $account->name));
        // DEBUG break;
      }

      // Profile
      unset($account->field_user_type);
      $account->field_user_type[LANGUAGE_NONE][0]['value'] = $student->type;
      $account->field_firstname[LANGUAGE_NONE][0]['value'] = trim(ucwords(strtolower($student->firstName)));
      $account->field_lastname[LANGUAGE_NONE][0]['value'] = trim(ucwords(strtolower($student->lastName)));
      $account->field_personal_email[LANGUAGE_NONE][0]['value'] = $student->email;

      user_save($account);
      /*$report[] = t('[DEBUG] @role account updated for @netid',
      		array('@role'  => $student->type,
      				'@netid' => $student->netid));*/
      //$stop = TRUE;
    }

    // Profiles
    $profiles = profile2_load_by_user($account);

    // Contact
    if (array_key_exists('contact', $profiles)) {
      $profile = $profiles['contact'];
    }
    else {
      $profile = new Profile(array('uid' => $account->uid, 'type' => 'contact'));
    }
    $profile->field_email[LANGUAGE_NONE][0]['email'] = $student->email;
    profile2_save($profile);
    if (!$profile->pid) {
      $report[] = t('[ERROR] Unable to save the Contact profile of @netid',
        array('@netid' => $student->netid));
      $rc = WATCHDOG_ERROR;
      continue;
    }
    if ($stop) break;
  }

  /*
   * Set previously 'Student' as 'Alum' if no longer in CAMS
  */
  /*$user_type_id['Student'] = db_result(db_query("SELECT user_type_id FROM {user_types_type} WHERE name = '%s'", 'Student'));
  $myaup_students = db_query("SELECT u.uid, u.name FROM {user_types_user} utu, {users} u WHERE u.uid = utu.uid AND utu.user_type_id = %d", $user_type_id['Student']);
  while ($myaup_student = db_fetch_object($myaup_students)) {
  	if (!array_key_exists($myaup_student->name, $students)) {
  		$newAlumni[] = $myaup_student->name;
  		$account = user_load($myaup_student->uid);
  		if (!aup_user_type_edit($account, 'Alum')) {
  			$report[] = t('[ERROR] Unable to set @netid as an Alum',
  					array('@netid' => $myaup_student->name));
  			$rc = SCHEDULED_TASKS_REPORT_ERROR;
  		}
  		else {
  			$report[] = t('[INFO] Set @netid from Student to Alum',
  					array('@netid'   => $myaup_student->name));
  			// DEBUG   	    break;
  		}
  	}
  }*/

  /*
   * Deactivate no longer applicants
  */
  /*$user_type_id['Applicant'] = db_result(db_query("SELECT user_type_id FROM {user_types_type} WHERE name = '%s'", 'Applicant'));
  $myaup_applicants = db_query("SELECT u.uid, u.name FROM {user_types_user} utu, {users} u WHERE u.status = 1 AND u.uid = utu.uid AND utu.user_type_id = %d", $user_type_id['Applicant']);
  while ($myaup_applicant = db_fetch_object($myaup_applicants)) {
  	if (!array_key_exists($myaup_applicant->name, $students)) {
  		$noLongerApplicant[] = $myaup_applicant->name;
  		$account = user_load($myaup_applicant->uid);
  		if (!aup_user_deactivate($account)) {
  			$report[] = t('[ERROR] Unable to deactivate @netid account',
  					array('@netid' => $myaup_applicant->name));
  			$rc = SCHEDULED_TASKS_REPORT_ERROR;
  		}
  		else {
  			$report[] = t('[INFO] No longer applicant @netid deactivated',
  					array('@netid'   => $myaup_applicant->name));
  			// DEBUG    		  break;
  		}
  	}
  }*/
  
  // Grant CAMS portal access to students
  /*if (!cams_query('student', 'enable_portal_access')) {
  	$report[] = t('[ERROR] Unable to grant CAMS portal access to students');
  	$rc = SCHEDULED_TASKS_REPORT_ERROR;
  }*/

  return aup_custom_task_end($report, $rc);
}
