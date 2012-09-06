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

  $links = dibs_menu();
  $helptxt = '<p><strong>This is a list of links to the resources created by the Dibs module.</strong></p>';
  
  foreach ($links as $link => $v) {
    $helptxt .= '<p>' . l($v['title'] . ' - ' . $v['description'],$link) . '</p>';
  }
  
  
  $form['help'] = array(
      '#type' => 'markup',
      '#preface' => '<div>',
      '#markup' => $helptxt,
      '#suffix' => '</div>',
   );


  return system_settings_form($form);
}