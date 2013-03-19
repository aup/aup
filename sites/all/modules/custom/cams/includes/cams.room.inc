<?php
/*
 * CAMS Integration
 * Integration between CAMS and MyAUP
 *
 * @author: Pierre-Yves Vasener <pvasener@aup.edu>
 */
 
/*
 * ROOM FUNCTIONS
 */



/**
 * TODO
 */
function cams_room_get_day_name($dayCode = NULL, $format = 'short') {
  switch ($dayCode) {
    case 'M':
	  return $format == 'short' ? 'Mon':'Monday';

    case 'T':
	  return $format == 'short' ? 'Tue':'Tuesday';

    case 'W':
	  return $format == 'short' ? 'Wed':'Wednesday';

    case 'R':
	  return $format == 'short' ? 'Thu':'Thursday';

    case 'F':
	  return $format == 'short' ? 'Fri':'Friday';

    case 'S':
	  return $format == 'short' ? 'Sat':'Saturday';

	default:
      return NULL;
  }
}

function cams_room_sync($node) {
  return "OK for the $node->type named $node->title";
}

/*
 * TODO
 */
function cams_room_sync_all() {
  return "OK for sync all rooms";
}