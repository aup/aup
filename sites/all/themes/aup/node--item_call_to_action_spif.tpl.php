<?php 
	/*
	 * Node Template for Call To Action Widget
	*/
?>

<div class="button">
	<?php if(!empty($node->field_action_spif_link)) :?>
		<a href="<?php echo $node->field_action_spif_link[LANGUAGE_NONE][0]['value']; ?>">
	<?php endif; ?>
		<?php if(!empty($node->field_action_text)) :?>
			<?php echo $node->field_action_text[LANGUAGE_NONE][0]['value']; ?>
		<?php endif; ?>
	<?php if(!empty($node->field_action_spif_link)) :?>
		</a>
	<?php endif; ?>
</div>
<?php if(!empty($node->body)) :?>
	<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
<?php endif; ?>