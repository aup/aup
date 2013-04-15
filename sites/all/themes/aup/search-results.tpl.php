<?php 
	/*
	 * Search Results Template
	*/
?>

<div class="newsevents">
<?php if ($search_results): ?>

	<ul class="feed">
		
		<?php for ($i = 0; $i < sizeof($results); $i++): ?>
			
 			<?php if( $results[$i]['node']->type != 'standard_spif' && $results[$i]['node']->type != 'world_spif' && $results[$i]['node']->type != 'banner' && $results[$i]['node']->type != 'item_call_to_action_spif' &&  $results[$i]['node']->type != 'rich_text_widget'): ?>
				
				<li><?php print theme('search_result', array('result' => $results[$i], 'module' => $variables['module'])); ?></li>
				
			<?php endif; ?>
			
		<?php endfor; ?>
	</ul>

    <div class="col"></div>
    
	<div class="post-pager">
	    <?php print $pager; ?>
    </div>

<?php else : ?>
  <h2><?php print t('Your search yielded no results');?></h2>
  <?php print search_help('search#noresults', drupal_help_arg()); ?>
<?php endif; ?>
</div>