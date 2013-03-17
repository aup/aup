<?php 

/**
 * Template override for theme_breadcrumb().
 */

function aup_breadcrumb($breadcrumb) {
	
	if (!empty($breadcrumb)) {
	
		$lastitem = sizeof($breadcrumb['breadcrumb']);
		$crumbs = '<ul>';
		$a=1;

		foreach ($breadcrumb['breadcrumb'] as $value) {
			
			if ($a == 1) {
				
				if ($a == sizeof($breadcrumb['breadcrumb']))
					$crumbs .= '<li class="first last">'.$value.'</li>';
				else
					$crumbs .= '<li class="first">'.$value.'</li>';
				
				$a++;

			} elseif ($a == $lastitem) {

				$crumbs .= '<li class="last">'.$value.'</li>';

			} else {

				$crumbs .= '<li>'.$value.'</li>';
				$a++;	

			}	

		}

		$crumbs .= '</ul>';

	}
	
	return $crumbs;
}