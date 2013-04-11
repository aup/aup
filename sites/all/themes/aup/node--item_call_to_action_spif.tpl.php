<?php 
	/*
	 * Node Template for Call To Action Widget
	*/
?>

<div class="button">
	<a href="<?php echo $node->field_action_spif_link[LANGUAGE_NONE][0]['value']; ?>"><?php echo $node->field_action_text[LANGUAGE_NONE][0]['value']; ?></a>
</div>
<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>