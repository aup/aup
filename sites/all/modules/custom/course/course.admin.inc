<?php

/**
 * @file
 * Administration functions for the Course module.
 */

/**
 * Page callback: Settings for the Course module.
 * 
 * @see course_menu()
 */
function course_settings_form($form, &$form_state) {
  $form['notification'] = array(
    '#type' => 'fieldset',
    '#title' => t('Notifications'),
  );

  $form['notification']['course_sync_mail_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject of the course synchronization script notification'),
    '#default_value' => variable_get('course_sync_mail_subject', ''),
    '#required' => TRUE,
  );
  
  $form['notification']['course_sync_mail_to'] = array(
    '#type' => 'textarea',
    '#title' => t('Recipients of the course synchronization script notification'),
    '#default_value' => variable_get('course_sync_mail_to', ''),
    '#description' => t('One e-mail per line.'),
    '#required' => TRUE,
  );

  
  return system_settings_form($form);
}
