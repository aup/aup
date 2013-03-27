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

  $form['notification']['course_master_sync_all_mail_to'] = array(
    '#type' => 'textarea',
    '#title' => t('Notifications recipients for course master synchronization scripts'),
    '#default_value' => variable_get('course_master_sync_all_mail_to', ''),
    '#description' => t('One e-mail per line.'),
    '#required' => TRUE,
  );

  $form['notification']['course_sync_all_mail_to'] = array(
  		'#type' => 'textarea',
  		'#title' => t('Notifications recipients for course synchronization scripts'),
  		'#default_value' => variable_get('course_sync_all_mail_to', ''),
  		'#description' => t('One e-mail per line.'),
  		'#required' => TRUE,
  );
  
  return system_settings_form($form);
}
