<?php
/**
 * TODO
 * @return TODO
 */
function cams_sync($node) {
  require_once(drupal_get_path('module', 'cams') . '/includes/cams.' . $node->type . '.inc');
  $function = 'cams_' . $node->type . '_sync';
  return call_user_func($function, $node);
}

/**
 * TODO
 * @return TODO
 */
function cams_sync_all($type) {
  require_once(drupal_get_path('module', 'cams') . '/includes/cams.' . $type . '.inc');
  $function = 'cams_' . $type . '_sync_all';
  return call_user_func($function);
}
