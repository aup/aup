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
      $result = $long ? 'Wednesday' : 'We';

    case 'R':
      $result = $long ? 'Thursday' : 'Th';

    case 'F':
      $result = $long ? 'Friday' : 'Fr';

    case 'A':
      $result = $long ? 'Saturday' : 'Sa';

    case 'U':
      $result = $long ? 'Sunday' : 'Su';

    default:
      return '';

  }
}
