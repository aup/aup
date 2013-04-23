<?php 
	/*
	 * Node Template for the Standard SPIF
	*/
?>

<?php if(!empty($node->field_spif_headline)): ?>
	<h4><?php print $node->field_spif_headline[LANGUAGE_NONE][0]['value']; ?></h4>
<?php endif; ?>
<?php if(!empty($node->field_spif_link)):?>
	<a href="<?php print $node->field_spif_link[LANGUAGE_NONE][0]['value']; ?>">
<?php endif; ?>
	<?php
	    $field = field_get_items('node', $node, 'field_standard_spif_image');
	    print render(field_view_value('node', $node, 'field_standard_spif_image', $field[0], array('settings' => array('image_style' => 'standard_spif'))));
	?>
<?php if(!empty($node->field_spif_link)):?>
	</a>
<?php endif; ?>

<div>
	<?php if(!empty($node->field_spif_sub_heading)):?>
    	<h5>
    		<?php if(!empty($node->field_spif_link)):?>
		    	<a href="<?php print $node->field_spif_link[LANGUAGE_NONE][0]['value']; ?>">
    		<?php endif; ?>	
    			<?php print $node->field_spif_sub_heading[LANGUAGE_NONE][0]['value']; ?>
    		<?php if(!empty($node->field_spif_link)):?>
    			</a>
    		<?php endif; ?>
    	</h5>
    <?php endif; ?>
    <?php if(!empty($node->body)):?>
		<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
	<?php endif; ?>
</div>