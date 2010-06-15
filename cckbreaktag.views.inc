<?php

/**
 * @file Views CCK Break Tag - views library
 */

/**
 * Implementation of hook_views_data_alter
 */
function cckbreaktag_views_data_alter(&$cache) {
  if (!$cache['node_data_field_body']) { return; }
  $cache['node_data_field_body']['field_body_value']['field']['handler'] = 'cckbreaktag_handler_field_multiple';
}

/**
 * Implementation of hook_views_handlers
 */
function cckbreaktag_views_handlers() {
  return array(
    'handlers' => array(
      'cckbreaktag_handler_field_multiple' => array(
        'parent' => 'content_handler_field_multiple',
      ),
    ),
  );
}
