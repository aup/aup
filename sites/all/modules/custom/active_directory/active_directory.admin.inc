<?php

/**
 * @file
 * Administration functions for the Active Directory module.
 */

/**
 * Page callback: Settings for the Active Directory module.
 * 
 * @see active_directory_menu()
 */
function active_directory_settings_form($form, &$form_state) {
  $form['connection'] = array(
    '#type' => 'fieldset',
    '#title' => t('Connection parameters'),
  );

  $form['connection']['active_directory_dc'] =  array(
    '#type' => 'textarea',
    '#title' => t('Domain Controller(s)'),
    '#default_value' => variable_get('active_directory_dc', NULL),
    '#description' => t('Enter the name or the IP of the AD. One per line.'),
  );
  $form['connection']['active_directory_basedn'] =  array(
    '#type' => 'textfield',
    '#title' => t('Base DN'),
    '#default_value' => variable_get('active_directory_basedn', NULL),
  );
  $form['connection']['active_directory_account_suffix'] =  array(
    '#type' => 'textfield',
    '#title' => t('Account Suffix'),
    '#default_value' => variable_get('active_directory_account_suffix', NULL),
  );
  $form['connection']['active_directory_bind_user'] =  array(
    '#type' => 'textfield',
    '#title' => t('Username of the account to bind the AD'),
    '#default_value' => variable_get('active_directory_bind_user', NULL),
    '#required' => TRUE,
  );
  $form['connection']['active_directory_bind_password'] =  array(
    '#type' => 'password',
    '#title' => t('Password of the account to bind the AD'),
    '#default_value' => variable_get('active_directory_bind_password', NULL),
  );
  
  $form = system_settings_form($form);

  // Add custom submit handler so that password will not be overwritten
  // if saved with no value.
  array_unshift($form['#submit'], 'active_directory_settings_form_submit');

  return $form;
}

/**
 * TODO.
 */
function active_directory_settings_form_submit($form, &$form_state) {
  if ($form_state['values']['active_directory_bind_password'] == '') {
    unset($form_state['values']['active_directory_bind_password']);
  }
}
