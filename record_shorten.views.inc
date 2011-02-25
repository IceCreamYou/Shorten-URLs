<?php

/**
 * @file
 * Provide views data and handlers for the Record Shortened URLs module.
 */

/**
 * Implementation of hook_views_data().
 */
function record_shorten_views_data() {
  //Basic table information.
  $data['record_shorten']['table']['group']  = t('Shortened URLs');

  //Advertise this table as a possible base table.
  $data['record_shorten']['table']['base'] = array(
    'field' => 'sid',
    'title' => t('Shortened URLs'),
    'help' => t('Listings of URLs shortened by the Shorten URLs module.'),
    'weight' => 10,
  );

  $data['record_shorten']['sid'] = array(
    'title' => t('Shorten ID'),
    'help' => t('The ID of the recorded URL.'),
    'field' => array(
      'handler' => 'views_handler_field_numeric',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_numeric',
    ),
  );

  $data['record_shorten']['original'] = array(
    'title' => t('Original URL'),
    'help' => t('The original, long, unshortened URL.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['record_shorten']['short'] = array(
    'title' => t('Shortened URL'),
    'help' => t('The new, computed, shortened URL.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  $data['record_shorten']['service'] = array(
    'title' => t('Service'),
    'help' => t('The service used to shorten the URL.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
    'filter' => array(
      'handler' => 'record_shorten_views_handler_filter_string_service',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers().
 */
function record_shorten_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'record_shorten'),
    ),
    'handlers' => array(
      'record_shorten_views_handler_filter_string_service' => array(
        'parent' => 'views_handler_filter_many_to_one',
      ),
    ),
  );
}