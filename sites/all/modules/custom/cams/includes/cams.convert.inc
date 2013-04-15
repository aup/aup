<?php

/**
 * @file
 * CAMS - Convert
 * Conversion functions
 */

/**
 * Converts CAMS-compatible days to PHP-compatible ones.
 * 
 * @param string $value
 *   CAMS-compatible day (M/T/W/R/F/A/U)
 *    
 * @param bool $long
 *   Select the version of the PHP-compatible name (Monday/Mo)
 *    
 * @return string
 *   The PHP-compatible name (long version or not)
 */
function cams_convert_camsday2phpday($value, $long = FALSE) {
  switch ($value) {
    case 'M':
      return $long ? 'Monday' : 'Mo';

    case 'T':
      return $long ? 'Tuesday' : 'Tu';

    case 'W':
      return $long ? 'Wednesday' : 'We';

    case 'R':
      return $long ? 'Thursday' : 'Th';

    case 'F':
      return $long ? 'Friday' : 'Fr';

    case 'A':
      return $long ? 'Saturday' : 'Sa';

    case 'U':
      return $long ? 'Sunday' : 'Su';

    default:
      return '';

  }
}

/**
 * Converts CAMS-compatible days to day number.
 *
 * @param string $value
 *   CAMS-compatible day (M/T/W/R/F/A/U)
 *
 * @return string
 *   The day number (1 = Monday)
 */
function cams_convert_camsday2daynb($value) {
	switch ($value) {
		case 'M':
			return 1;

		case 'T':
			return 2;

		case 'W':
			return 3;

		case 'R':
			return 4;

		case 'F':
			return 5;

		case 'A':
			return 6;

		case 'U':
			return 7;

		default:
			return 0;

	}
}

/**
 * Converts CAMS-compatible time with Timetable values.
 *
 * @param string $value
 *   CAMS-compatible time (HH:MM)
 *
 * @return string
 *   Timetable values (Nb of minutes since midnight)
 */
function cams_convert_camstime2minutes($value) {
  if (list($hours, $minutes) = explode(':', $value)) {
    return $hours * 60 + $minutes;
  }
  return FALSE;
}
