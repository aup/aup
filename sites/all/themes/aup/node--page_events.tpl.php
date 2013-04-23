<?php 
	/*
	 * Node Template for Events
	*/
?>
        
<div class="container inner">
	<h4>
		<?php if(!empty($node->field_event_date)) :?>
			<?php echo date("F d, Y", strtotime($node->field_event_date[LANGUAGE_NONE][0]['value'])); ?> 
		<?php endif; ?>
		- 
		<?php if(!empty($node->field_event_time)) :?>
			<?php print $node->field_event_time[LANGUAGE_NONE][0]['value']; ?>
		<?php endif; ?>
	</h4>
	<?php if(!empty($node->body)) :?>
		<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
	<?php endif; ?>
</div>