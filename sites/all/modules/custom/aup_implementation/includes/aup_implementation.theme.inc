<?php 

/**
 * Implementation of hook_preprocess_page
 */
function aup_implementation_preprocess_page(&$variables) {

	if (arg(0) == 'news-events') {
		
		
		$slideshow_nodes = new NodequeueNodes(variable_get('news_events_slideshow_qid', 0));

		if(count($slideshow_nodes->getNodes()) >= 2)
			$variables['show_arrows'] = 1;
		else
			$variables['show_arrows'] = 0;

		$variables['news_events_slideshow'] = theme('news_events_slideshow', array('nodes' => $slideshow_nodes->getNodes()));

	}
	
}

function aup_implementation_preprocess_aup_support_slideshow_treatment(&$variables) {

	$slideshow_nodes = new NodequeueNodes($variables['qid']);
	
	$variables['slideshow'] = theme('support_slideshow', array('nodes' => $slideshow_nodes->getNodes()));
}

function aup_implementation_preprocess_aup_admissions_features_treatment(&$variables) {

	$features_nodes = new NodequeueNodes($variables['qid']);
	
	$variables['features'] = theme('admissions_features', array('nodes' => $features_nodes->getNodes()));
}

function aup_implementation_preprocess_aup_right_column_accordion_treatment(&$variables) {

	$nodes = new NodequeueNodes($variables['qid']);
	
	$variables['accordion'] = theme('right_column_accordion', array('nodes' => $nodes->getNodes()));
}

function aup_implementation_preprocess_aup_tabbed_feature_treatment(&$variables) {

	$nodes = new NodequeueNodes($variables['qid']);
	
	$variables['features'] = theme('tabbed_features', array('nodes' => $nodes->getNodes()));
}