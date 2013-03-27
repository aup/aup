<?php

/**
 * Implementation of hook_nodequeue_block_treatments()
 */
function nodequeue_block_nodequeue_block_treatments() {
	
	$treatments = array();
	
	$treatments['single_random_node'] = array(
		'name' => t('Single Random Node'),
		'theme_hook' => 'nodequeue_block_random_node',
	);
	
	return $treatments;
	
}

/**
 * Implementation of hook_theme().
 */
function nodequeue_block_theme($existing, $type, $theme, $path) {
	
	$theme = array();
	$path = drupal_get_path('module', 'nodequeue_block') .'/theme';
	
	$theme['nodequeue_block_random_node'] = array(
		'arguments' => array('queue' => null),
		'template' => 'nodequeue-block-random-node',
		'path' => $path,
	);
	
	return $theme;
	
}

function nodequeue_block_preprocess_nodequeue_block_random_node(&$variables) {
	
	$node = @nodequeue_load_random_node($variables['qid']);
	
	//Pass then nodequeue informatino into the node.
	@$node->{'queue'} = $variables;
	
	//Check if this is actually a node object. Or else get a warning!
	if (isset($node->nid)) {
		$view = node_view($node);
		$variables['random_node'] = drupal_render($view);
	}

}