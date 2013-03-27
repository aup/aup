<?php

function nodequeue_block_invoke_custom_treatments() {
	
	$treatments = module_invoke_all('nodequeue_block_treatments');
	
	return $treatments;
	
}

function nodequeue_block_enabled_blocks() {
	
	$result = db_query("select * from {nodequeue_block} where `enabled` = :enabled", 
					array(':enabled' => 1),
					array('fetch' => 'PDO::FETCH_OBJ')
				);
				
	$blocks = new stdClass();
	
	while ($block = $result->fetchObject()) {
		
		nodequeue_block_build_block_object($block);
		
		if (isset($block->{'#queue'}))
			$blocks->{'#blocks'}[] = $block;
	
	}
	
	return $blocks;
	
}

function nodequeue_block_get_block($qbid) {
	
	if (!$qbid)
		throw new Exception('No queue block ID.');
	
	$result = db_query("select * from {nodequeue_block} where `qbid` = :qbid", 
					array(':qbid' => $qbid),
					array('fetch' => 'PDO::FETCH_OBJ')
				);
	$block = $result->fetchObject();
	nodequeue_block_build_block_object($block);
	
	return $block;
	
}

function nodequeue_block_build_block_object(&$block) {
	
	$treatments = nodequeue_block_invoke_custom_treatments();
	//$count = db_result(db_query("select COUNT(*) as count from nodequeue_nodes where `qid` = %d;", $block->qid));
	
	$nodequeue = nodequeue_load($block->qid);
	
	if ($nodequeue)
		$block->{'#queue'} = nodequeue_load($block->qid);
	
	$block->{'#theme_hook'} = $treatments[$block->block_treatment]['theme_hook'];
	$block->{'#block'} = nodequeue_block_get_saved_block($block->qbid);
	
}

function nodequeue_block_get_saved_block($delta) {
	
	//@todo figure out how to use the core API to do this.
	$db_block = db_query("select * from block where `module` = 'nodequeue_block' and `delta` = ':delta'", 
					array(':delta' => $delta),
					array('fetch' => 'PDO::FETCH_OBJ')
				);
	
	return $db_block->fetchObject();
	
}
