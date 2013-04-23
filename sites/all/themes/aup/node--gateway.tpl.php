<?php 
	/*
	 * Node Template for Gateway
	*/
?>

<div class="main">
	<?php if(!empty($node->body)): ?>
	    <?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
	   <?php endif; ?>					
</div>
<div class="side">
	<?php if(!empty($node->field_announcement)): ?>
		<?php print $node->field_announcement[LANGUAGE_NONE][0]['value']; ?>          	
	<?php endif; ?>
</div>
