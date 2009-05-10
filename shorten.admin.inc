<?php
// $Id$

/**
 * @file
 *   Settings for the Shorten module.
 */

/**
 * Settings page.
 */
function shorten_admin() {
  $form['shorten_http'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use "www." instead of "http://"'),
    '#description' => t('"www." is shorter, but "http://" is automatically link-ified by more services.'),
    '#default_value' => variable_get('shorten_www', TRUE),
  );
  $methods = array();
  if (function_exists('file_get_contents')) {
    $methods['php'] = t('PHP');
  }
  if (function_exists('curl_exec')) {
    $methods['curl'] = t('cURL');
  }
  if (empty($methods)) {
    if (variable_get('shorten_method', 'curl') != 'none') {
      variable_set('shorten_method', 'none');
    }
    $form['shorten_method'] = array(
      '#type' => 'radios',
      '#title' => t('Method'),
      '#description' => '<p>'. t('The method to use to retrieve the abbreviated URL.') .'</p>'.
        '<p><strong>'. t('Your PHP installation does not support the URL abbreviation feature of the Shorten module.') .'</strong> '.
        t('You must compile PHP with either the cURL library or the file_get_contents() function to use this option.') .'</p>',
      '#default_value' => 'none',
      '#options' => array('none' => t('None')),
      '#disabled' => TRUE,
    );
    $form['shorten_service'] = array(
      '#type' => 'radios',
      '#title' => t('Service'),
      '#description' => t('The service to use to create the abbreviated URL.'),
      '#default_value' => 'none',
      '#options' => array('none' => t('None')),
    );
    $form['shorten_service_backup'] = array(
      '#type' => 'radios',
      '#title' => t('Backup Service'),
      '#description' => t('The service to use to create the abbreviated URL if the primary service is down.'),
      '#default_value' => 'none',
      '#options' => array('none' => t('None')),
    );
  }
  else {
    $form['shorten_method'] = array(
      '#type' => 'radios',
      '#title' => t('Method'),
      '#description' => t('The method to use to retrieve the abbreviated URL.'),
      '#default_value' => variable_get('shorten_method', 'curl'),
      '#options' => $methods,
    );
    $all_services = module_invoke_all('shorten_service', $original);
    $services = array();
    foreach ($all_services as $key => $value) {
      $services[$key] = $key;
    }
    $services['none'] = t('None');
    $form['shorten_service'] = array(
      '#type' => 'select',
      '#title' => t('Service'),
      '#description' => t('The default service to use to create the abbreviated URL.'),
      '#default_value' => variable_get('shorten_service', 'is.gd'),
      '#options' => $services,
    );
    $form['shorten_service_backup'] = array(
      '#type' => 'select',
      '#title' => t('Backup Service'),
      '#description' => t('The service to use to create the abbreviated URL if the primary or requested service is down.'),
      '#default_value' => variable_get('shorten_service_backup', 'TinyURL'),
      '#options' => $services,
    );
  }
  return system_settings_form($form);
}

/**
 * Validation handler for shorten_admin().
 */
function shorten_admin_validate($form, &$form_state) {
  if ($form_state['values']['shorten_service'] == $form_state['values']['shorten_service_backup'] && $form_state['values']['shorten_service_backup'] != 'none') {
    form_set_error('shorten_service_backup', t('You must select a backup abbreviation service that is different than your primary service.'));
  }
  if ($form_state['values']['shorten_service'] == 'none' && $form_state['values']['shorten_service_backup'] != 'none') {
    drupal_set_message(t('You have selected a backup URL abbreviation service, but no primary service.  Your URLs will not be abbreviated with these settings.'));
  }
}

/**
 * Submit handler for shorten_admin().
 */
function shorten_admin_submit($form, &$form_state) {
  variable_set('shorten_method', $form_state['values']['shorten_method']);
  variable_set('shorten_service', $form_state['values']['shorten_service']);
  variable_set('shorten_service_backup', $form_state['values']['shorten_service_backup']);
  variable_set('shorten_www', $form_state['values']['shorten_www']);
  //Clear the general cache because changed settings may mean that different URLs should be used.
  cache_clear_all('*', 'cache', TRUE);
  drupal_set_message(t('The configuration options have been saved.'));
}