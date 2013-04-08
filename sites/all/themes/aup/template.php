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

/**
 * Implementation of hook_preprocess_page()
 */
 
function aup_preprocess_page(&$variables) {
 
    // Allow use of page--myContentType.tpl.php
	if (isset($variables['node'])) {
		$variables['theme_hook_suggestion'] = 'page__'.$variables['node']->type;
	}
  	
  if(empty($variables['tabs']['#primary']))
  	$variables['tabs'] = '';

  $link = menu_get_item();

  $result = db_query("SELECT p1 FROM menu_links WHERE link_path='" . str_replace("'", "", $link['href']) . "'");
  foreach ($result as $parent) {
    if (isset($parent->p1)) {
      $m = menu_link_load($parent->p1);
    }
  }

  $variables['primary_navigation'] =
          '    
<ul>

<li><a ' . ($m['link_path'] == 'node/4' ? ' class="active"' : '') . ' href="' . base_path() . 'about">About</a></li>

<li><a ' . ($m['link_path'] == 'node/32' ? ' class="active"' : '') . ' href="' . base_path() . 'academics">Academics</a></li>

<li><a ' . ($m['link_path'] == 'node/8' ? ' class="active"' : '') . ' href="' . base_path() . 'admissions">Admissions</a></li>

<li><a ' . ($m['link_path'] == 'node/33' ? ' class="active"' : '') . ' href="' . base_path() . 'student-life">Student Life</a></li>

<li><a ' . ($m['link_path'] == 'news-events' ? ' class="active"' : '') . ' href="' . base_path() . 'news-events">News &amp; Events</a></li>

<li><a ' . ($m['link_path'] == 'node/7' ? ' class="active"' : '') . ' href="' . base_path() . 'support">Giving</a></li>

</ul>';
}
