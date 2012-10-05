<?php
// $Id$
/**
 * @file
 * Dibs page for the dibs module.
 */

// dibs_page function
function dibs_offers_page() {
  // DIBS on my nodes
  global $user;
  $build = array();
  
  $query = db_select('node', 'n');
  $query
    ->fields('n')
    ->orderby('n.nid')
    ->condition('n.uid', $user->uid, '=');
  $query
    ->innerjoin('votingapi_vote', 'v', 'n.nid = v.entity_id');
  $query
    ->fields('v');
  $result = $query->execute();
  
 


  // Loop through each of our node_example nodes and instruct node_view
  // to use our custom "example_node_list" view.
  // http://api.drupal.org/api/function/node_load/7
  // http://api.drupal.org/api/function/node_view/7
  foreach ($result as $row) {
    $offer = '';
    $color = drupal_substr(MD5($row->nid), 0, 6);
    $vote_node = node_load($row->nid);
    $vote_user = user_load($row->uid);
    
    $offered = 'no';
    $offerlink =  l($offered, 'dibs/' . $row->nid . '/' . $row->vote_id . '/' . $row->uid);
    
    $subquery = db_select('dibs', 'd')
      ->fields('d')
      ->condition('d.nid', $vote_node->nid, '=');
    $subresult = $subquery->execute();

      foreach ($subresult as $subrow) {
        $offer = $subrow->uid;
      }
    
    
    if ($offer != '') {
      if ($offer == $vote_user->uid) {
        $offered = 'YES';
        $offerlink =  l($offered, 'dibs/' . $row->nid . '/0/0');
      }
    }



    $rows[] = array(
          '<div style="width:20px;height:20px;float:left;margin-right:10px;background:#' . $color . '"></div>' .  $vote_node->nid,
          l($vote_node->title, 'node/' . $vote_node->nid),
          l($vote_user->name, 'user/' . $vote_user->uid . '/contact'),
          $vote_user->field_address['und']['0']['postal_code'],
          format_date($row->timestamp),
          $offerlink
    );
    
  
  }
  if (empty($rows)) {
    $rows[] = array(
          '<div style="width:20px;height:20px;float:left;margin-right:10px;background:#666666"></div>',
          'No one has requested dibs, or you have no active items.',
          '',
          '',
          '',
          '',
    );
  }
    $header = array('Item ID', 'Title', 'Voter', 'Voter Zip', 'Date Voted', 'Offered?');
    // Format output.
    $output = "<h4>To select a person that will receive your hand-me-down items, click in the offer column to make an offer.</h4>";
    $output .= theme('table', array('header' => $header, 'rows' => $rows)) . theme('pager');
  return $output;
}

// my_saleitem_page function
function mydibs_page() {
  global $user;
  $build = array();
  
  
  $query = db_select('votingapi_vote', 'v');
  $query
    ->fields('v')
    ->condition('v.uid', $user->uid, '=');
  $query
    ->leftjoin('dibs', 'd', 'v.vote_id = d.vid');
  $query->addField('d', 'uid', 'dibs_uid');
  $query->addField('d', 'nid', 'dibs_nid');
  $query->addField('d', 'vid', 'dibs_vid');
  $result = $query->execute();



  // Loop through each of our node_example nodes and instruct node_view
  // to use our custom "example_node_list" view.
  // http://api.drupal.org/api/function/node_load/7
  // http://api.drupal.org/api/function/node_view/7
  foreach ($result as $row) {
    $offered = '';
    $color = drupal_substr(MD5($row->entity_id), 0, 6);
    if ($row->entity_type != "node") {
      continue;
    }
    if ($row->dibs_vid == $row->vote_id) {
      $offered = 'Offered, contact the owner.';
    }
    else {
      $subquery = db_select('dibs', 'd')
        ->fields('d')
        ->condition('d.nid', $row->entity_id, '=');
      $subresult = $subquery->execute();
  
        foreach ($subresult as $subrow) {
          $offeree = $subrow->uid;
					if (($offeree != '') && ($offeree > '0')) {
							$offered = 'Closed';
					}
        }
      
      
    
    }
    
    
    
    if (($row->dibs_vid != $row->vote_id) && ($row->dibs_vid != '')) {
      $offered = '';
    }
   // drupal_set_message('<pre>' . print_r($row, true) . '</pre>');
    
    $vote_node = node_load($row->entity_id);
    $node_user = user_load($row->uid);
    $rows[] = array(
          '<div style="width:20px;height:20px;float:left;margin-right:10px;background:#' . $color . '"></div>' .           $vote_node->nid,
          l($vote_node->title, 'node/' . $vote_node->nid),
          l($node_user->name, 'user/' . $node_user->uid . '/contact'),
          $node_user->field_address['und']['0']['postal_code'],
          format_date($vote_node->created),
          $offered
    );
    
  
  }
  if (empty($rows)) {
    $rows[] = array(
          '<div style="width:20px;height:20px;float:left;margin-right:10px;background:#666666"></div>',
          'You have no requests open on active items.',
          '',
          '',
          '',
          '',
    );
  }
    $header = array('Item ID', 'Title', 'Item Owner', 'Owner Zip', 'Date Created', 'Status');
    // Format output.
    $output = "<h4>If you have been offered something, you will need to contact the owner to arrange pickup or delivery.  Click to owners name to contact them.</h4>";
    $output .= theme('table', array('header' => $header, 'rows' => $rows)) . theme('pager');

  return $output;
 
}





function dibs_make_offer($nid = '', $voteid = '', $userid = '') {
  global $user;
  $output = "";
  
  if ($nid != '') {
    $this_node = node_load($nid);

    if ($this_node->uid != $user->uid){
      drupal_goto('user/' . $user->uid . '/dibs');
      return;
    }
  }
    
  if ($voteid == '0') {
      db_delete('dibs')
      ->condition('nid', $nid)
      ->execute();
      drupal_goto('user/' . $user->uid . '/dibs');
      return;

  }
  elseif (($voteid != '') && ($userid != '')) {
    
      db_delete('dibs')
      ->condition('nid', $nid)
      ->execute();
  
      db_insert('dibs')
      ->fields(array(
        'nid' => $nid,
        'vid' => $voteid,
        'uid' => $userid,
      ))
      ->execute();
    
  }
  

  if (user_access('administer content')) {
      
    $subquery = db_select('dibs', 'd')
      ->fields('d');
    $subresult = $subquery->execute();

      foreach ($subresult as $subrow) {
        $offer = $subrow->uid;
         $rows[] = array(
                l($subrow->nid, 'node/' . $subrow->nid),
                l($subrow->uid, 'user/' . $subrow->uid . '/contact'),
                $subrow->vid
          );
      }
    
    $header = array('Node ID', 'User ID', 'Vote ID');
    // Format output.
    $output = theme('table', array('header' => $header, 'rows' => $rows)) . theme('pager');
    $output .=       l('My Dibs', 'user/' . $user->uid . '/dibs');

  }
  else {
    drupal_goto('user/' . $user->uid . '/dibs');
  }
      drupal_goto('user/' . $user->uid . '/dibs');
  return $output;
  
}

