<?php

/**
 * @file
 * Administration functions for the CAMS module.
 */

/**
 * Page callback: Settings for the CAMS module.
 * 
 * @see cams_menu()
 */
function cams_settings_form($form, &$form_state) {
  $terms = cams_query('term', 'get', 'all');
  foreach ($terms as $term) {
    $term_options[$term->id] = "$term->id ($term->name)";
  }

  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('General Settings'),
  );
  $form['settings']['cams_current_term'] = array(
    '#type' => 'select',
    '#title' => t('Current Term'),
    '#default_value' => variable_get('cams_current_term', NULL),
    '#options' => $term_options,
    '#description' => t('Select the current term. This value is used by MyAUP to retrieve data from CAMS in the proper term for mailing lists, role assignments...'),
  );

  $form['connection'] = array(
    '#type' => 'fieldset',
    '#title' => t('Connection parameters'),
  );

  $form['connection']['cams_server'] = array(
    '#type' => 'textfield',
    '#title' => t('CAMS Server'),
    '#default_value' => variable_get('cams_server', ''),
    '#description' => t('Name or IP of the CAMS server.'),
    '#required' => TRUE,
  );

  $form['connection']['cams_database'] = array(
    '#type' => 'textfield',
    '#title' => t('Database Name'),
    '#default_value' => variable_get('cams_database', NULL),
    '#required' => TRUE,
  );

  $form['connection']['cams_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Connection Username'),
    '#default_value' => variable_get('cams_username', NULL),
    '#required' => TRUE,
  );

  $form['connection']['cams_password'] = array(
    '#type' => 'password',
    '#title' => t('Connection Password'),
    '#description' => t('Leave empty to keep the password unchanged.'),
  );

  $form = system_settings_form($form);

  // Add custom submit handler so that password will not be overwritten
  // if saved with no value.
  array_unshift($form['#submit'], 'cams_settings_form_submit');

  return $form;
}

/**
 * TODO.
 */
function cams_settings_form_submit($form, &$form_state) {
  if ($form_state['values']['cams_password'] == '') {
    unset($form_state['values']['cams_password']);
  }
}
