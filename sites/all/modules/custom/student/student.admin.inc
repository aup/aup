<?php

/**
 * @file
 * Administration functions for the Student module.
 */

/**
 * Page callback: Settings for the Student module.
 * 
 * @see student_menu()
 */
function student_settings_form($form, &$form_state) {
  $form['notification'] = array(
    '#type' => 'fieldset',
    '#title' => t('Notifications'),
  );

  $form['notification']['student_sync_mail_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject of the student synchronization script notification'),
    '#default_value' => variable_get('student_sync_mail_subject', ''),
    '#required' => TRUE,
  );
  
  $form['notification']['student_sync_mail_to'] = array(
    '#type' => 'textarea',
    '#title' => t('Recipients of the student synchronization script notification'),
    '#default_value' => variable_get('student_sync_mail_to', ''),
    '#description' => t('One e-mail per line.'),
    '#required' => TRUE,
  );

  
  return system_settings_form($form);
}
