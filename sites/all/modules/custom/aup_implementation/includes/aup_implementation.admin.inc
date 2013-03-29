<?php

/**
 * Helper: Home administration page callback
 */
function news_events_administration($form_state) {

	$nqr = new NodequeueQueues();
	
	/*$form['titles'] = array(
		'#type' => 'fieldset',
		'#title' => t('Home page Titles'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);

	$form['titles']['description'] = array(
	    '#markup'=> t('<p>Here you can set the two title regions on the home page.</p>'),
	);
	
	$form['titles']['title1'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Title 1'),
	    '#default_value' => variable_get('home_title1', ''),
	    '#description' => 'The first title will be wrapped in an h2 tag.',
	);
	
	$form['titles']['title2'] = array(
	    '#type' => 'textfield',
	    '#title' => t('Title 2'),
	    '#default_value' => variable_get('home_title2', ''),
	    '#description' => 'The second title will be wrapped in an h3 tag.'
	); */

		
	$form['nodequeues'] = array(
		'#type' => 'fieldset',
		'#title' => t('Nodequeue Settings'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	$form['nodequeues']['slideshow_description'] = array(
	    '#markup'=> t('<p>Select a nodequeue that the background will retrieve their nodes from.</p>'),
	);
	
	$form['nodequeues']['slideshow_qid'] = array(
	    '#type' => 'select',
	    '#title' => t('Slideshow Nodequeue Reference'),
	    '#default_value' => variable_get('news_events_slideshow_qid', 0),
	    '#options' => $nqr->getQueues(),
	    '#description' => t('To rearrange the nodes within a queue, go to Structure &rarr; Nodequeue.')
	);
	
	/*
	
	$form['nodequeues']['spif_description'] = array(
	    '#markup'=> t('<p>Select a nodequeue that the SPIF region will retrieve their nodes from.</p>'),
	);
	
	$form['nodequeues']['spif_qid'] = array(
	    '#type' => 'select',
	    '#title' => t('SPIF Region Nodequeue Reference'),
	    '#default_value' => variable_get('home_spif_qid', 0),
	    '#options' => $nqr->getQueues(),
	    '#description' => t('To rearrange the nodes within a queue, go to Structure &rarr; Nodequeue.')
	);
	
	*/
	
	/*
	
	$form['link_buttons'] = array(
		'#type' => 'fieldset',
		'#title' => t('Not Sure Where To Start Block'),
		'#collapsible' => TRUE,
		'#collapsed' => FALSE,
	);
	
	$form['link_buttons']['description'] = array(
	    '#markup'=> t('<p>Enter the title and url for each of the four buttons that will display in the <em>"Not Sure Where to Start"</em> block</p>'),
	);
	
	$form['link_buttons']['button1_title'] = array(
		'#type' => 'textfield',
		'#title' => t('Button 1 Title'),
		'#default_value' => variable_get('home_button1_title', ''),
		'#size' => 60,
		'#required' => TRUE,
	);
	
	$form['link_buttons']['button1_url'] = array(
		'#type' => 'textfield',
		'#title' => t('Button 1 Url'),
		'#default_value' => variable_get('home_button1_url', ''),
		'#size' => 60,
		'#required' => TRUE,
	);

	$form['link_buttons']['button1_open'] = array(
		'#type' => 'checkbox',
		'#title' => t('Open in a new window?'),
		'#default_value' => variable_get('home_button1_open', ''),
		'#required' => FALSE,
	);
	
	$form['link_buttons']['button2_title'] = array(
		'#type' => 'textfield',
		'#title' => t('Button 2 Title'),
		'#default_value' => variable_get('home_button2_title', ''),
		'#size' => 60,
		'#required' => TRUE,
	);
	
	$form['link_buttons']['button2_url'] = array(
		'#type' => 'textfield',
		'#title' => t('Button 2 Url'),
		'#default_value' => variable_get('home_button2_url', ''),
		'#size' => 60,
		'#required' => TRUE,
	);

	$form['link_buttons']['button2_open'] = array(
		'#type' => 'checkbox',
		'#title' => t('Open in a new window?'),
		'#default_value' => variable_get('home_button2_open', ''),
		'#required' => FALSE,
	);
	
	$form['link_buttons']['button3_title'] = array(
		'#type' => 'textfield',
		'#title' => t('Button 3 Title'),
		'#default_value' => variable_get('home_button3_title', ''),
		'#size' => 60,
		'#required' => TRUE,
	);
	
	$form['link_buttons']['button3_url'] = array(
		'#type' => 'textfield',
		'#title' => t('Button 3 Url'),
		'#default_value' => variable_get('home_button3_url', ''),
		'#size' => 60,
		'#required' => TRUE,
	);

	$form['link_buttons']['button3_open'] = array(
		'#type' => 'checkbox',
		'#title' => t('Open in a new window?'),
		'#default_value' => variable_get('home_button3_open', ''),
		'#required' => FALSE,
	);
	
	$form['link_buttons']['button4_title'] = array(
		'#type' => 'textfield',
		'#title' => t('Button 4 Title'),
		'#default_value' => variable_get('home_button4_title', ''),
		'#size' => 60,
		'#required' => TRUE,
	);
	
	$form['link_buttons']['button4_url'] = array(
		'#type' => 'textfield',
		'#title' => t('Button 4 Url'),
		'#default_value' => variable_get('home_button4_url', ''),
		'#size' => 60,
		'#required' => TRUE,
	);

	$form['link_buttons']['button4_open'] = array(
		'#type' => 'checkbox',
		'#title' => t('Open in a new window?'),
		'#default_value' => variable_get('home_button4_open', ''),
		'#required' => FALSE,
	);
	
	*/
	
	$form['submit'] = array('#type' => 'submit', '#value' => t('Save'));
	
	return $form;
	
}

function news_events_administration_submit($form, &$form_state) {

	$slideshow_qid = variable_get('news_events_slideshow_qid', 0);

	if ($slideshow_qid != $form_state['values']['slideshow_qid'])
		variable_set('news_events_slideshow_qid', $form_state['values']['slideshow_qid']);

	drupal_set_message(t('Saved.'), 'status');
		
}