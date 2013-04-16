<?php 
	/*
	 * Node Template for Events
	*/
?>
        
<div class="container inner">
	<h4><?php echo date("F d, Y", strtotime($node->field_event_date[LANGUAGE_NONE][0]['value'])); ?> - <?php print $node->field_event_time[LANGUAGE_NONE][0]['value']; ?></h4>
	<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
</div>