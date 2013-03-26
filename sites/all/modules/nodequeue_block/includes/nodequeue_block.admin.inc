<?php

function nodequeue_block_admin_form($form, &$form_state, $queue) {
	
	$treatments = nodequeue_block_invoke_custom_treatments();
	$form_treatments = array();
	
	foreach ($treatments as $key => $treatment)
		$form_treatments[$key] = t($treatment['name']);
	
	//Right now there is a one-to-one relationship between queues and blocks, this will get that one row.
	$result = db_query("SELECT * FROM {nodequeue_block} WHERE qid = :qid", 
					array(':qid' => $queue->qid), 
					array('fetch' => 'PDO::FETCH_OBJ')
				);
	
	$record = $result->fetchObject();
	
	//Set the title of the page!
	drupal_set_title(t("Nodequeue '@title' Block", array('@title' => $queue->title)));
	
	if ($record) { 
		
		//Notify the user that their treatment is outdated.
		if (!array_key_exists($record->block_treatment, $form_treatments))
			drupal_set_message(t('If the block is enabled and not showing it\'s possibly due to an outdated or missing treatment being applied. Please select a new treatment then submit.'), 'warning', true);
			
		$form['qbid'] = array('#type' => 'value', '#value' => $record->qbid);
	
	}
	
	$form['qid'] = array('#type' => 'value', '#value' => $queue->qid);
	
	$form['description'] = array(
		'#type' => 'fieldset',
		'#title' => t('Nodequeue Block'),
		'#description' => t('A nodequeue may be turned into a "nodequeue block" that is easily themable and completely independent of views.'),
	);
	
	$form['enable_block'] = array(
		'#type' => 'radios',
		'#title' => t('Enable block'),
		'#default_value' => ($record && $record->enabled ? $record->enabled : 0),
		'#options' => array(t('Disabled'), t('Enabled')),
	);
	
	$form['block_treatment'] = array(
		'#type' => 'select',
		'#title' => t('Block treatment'),
		'#default_value' => ($record && $record->block_treatment ? $record->block_treatment : 0),
		'#options' => $form_treatments,
		'#description' => t('(You may provide your own treatments with the hook_nodequeue_block_treatments api)'),
	);
	
	$form['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Submit'),
		'#submit' => array('nodequeue_block_admin_form_submit'),
	);
	
	return $form;
	
}

function nodequeue_block_admin_form_submit($form, &$form_state) {
	
	$qbid = isset($form_state['values']['qbid']) ? $form_state['values']['qbid'] : null;
	$qid = $form_state['values']['qid'];
	$enable_block = $form_state['values']['enable_block'];
	$block_treatment = $form_state['values']['block_treatment'];
	
	if (empty($qbid)) {
		db_insert('nodequeue_block')
  		    ->fields(array('qid', 'enabled', 'block_treatment'))
  		    ->values(array(
    	    	'qid' => $qid,
    	    	'enabled' => $enable_block,
    	    	'block_treatment' => $block_treatment,
  		    )
  		)->execute();
	}
	else {
		db_update('nodequeue_block')
  			->fields(array('enabled' => $enable_block, 'block_treatment' => $block_treatment))
  			->condition('qbid', $qbid, '=')
  			->execute();
	
	}
	
	//Make sure we refresh the blocks table!
	_block_rehash();
	
	//Set a friendly message :)
    drupal_set_message(t('The queue has been updated.'), 'status', true);
	
}

?>