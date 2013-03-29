<?php 

/**
 * Implementation of hook_preprocess_page
 */
function aup_implemenation_preprocess_page(&$variables) {
	
	if (arg(0) == 'news-events') {
		
		
		$slideshow_nodes = new NodequeueNodes(variable_get('news_events_slideshow_qid', 0));
		
		if(count($slideshow_nodes->getNodes()) >= 2)
			$variables['show_arrows'] = 1;
		else
			$variables['show_arrows'] = 0;
			
		$variables['news_events_slideshow'] = theme('news_events_slideshow', array('nodes' => $slideshow_nodes->getNodes()));

	}
	
}