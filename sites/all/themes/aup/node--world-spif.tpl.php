<?php if(!empty($node->field_spif_title)):?>
	<h3><?php print $node->field_spif_title[LANGUAGE_NONE][0]['value']; ?></h3>
<?php endif; ?>
<p><a href="<?php echo base_path().drupal_lookup_path('alias', 'node/'.$node->field_feature_reference[LANGUAGE_NONE][0]['entity']->nid); ?>">
	<?php
        $field = field_get_items('node', $node, 'field_spif_image');
        print render(field_view_value('node', $node, 'field_spif_image', $field[0], array('settings' => array('image_style' => 'world_spif'))));
    ?>
</a></p>
<h4>
	<?php if(!empty($node->field_feature_reference)):?>
		<a href="<?php echo base_path().drupal_lookup_path('alias', 'node/'.$node->field_feature_reference[LANGUAGE_NONE][0]['entity']->nid); ?>">
	<?php endif; ?>
		<?php echo $title; ?>
	<?php if(!empty($node->field_feature_reference)):?>
		</a>
	<?php endif; ?>
</h4>
<?php if(!empty($node->body)):?>
	<p><?php print $node->body[LANGUAGE_NONE][0]['value']; ?></p>
<?php endif; ?>