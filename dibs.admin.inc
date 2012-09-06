<?php
// $Id$

/**
 * @file
 * Admin page callback for the scaffolding module.
 */

/**
 * Builds and returns the scaffolding settings form.
 */
function dibs_admin_settings() {
  $form['dibs_max'] = array(
    '#type' => 'select',
    '#title' => t('Maximum number of dibs visible.'),
    '#options' => drupal_map_assoc(range(1, 20)),
    '#default_value' => variable_get('dibs_max', ''),
    '#description' => t('This will set the maximum visible dibs'),
    '#required' => TRUE,
  );


  return system_settings_form($form);
}