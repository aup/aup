<h3>Students <em>of</em> the World</h3>
<p><a href="<?php echo base_path().drupal_lookup_path('alias', 'node/'.$node->field_feature_reference[LANGUAGE_NONE][0]['entity']->nid); ?>">
	<?php
        $field = field_get_items('node', $node, 'field_spif_image');
        print render(field_view_value('node', $node, 'field_spif_image', $field[0], array('settings' => array('image_style' => 'world_spif'))));
    ?>
</a></p>
<h4><a href="<?php echo base_path().drupal_lookup_path('alias', 'node/'.$node->field_feature_reference[LANGUAGE_NONE][0]['entity']->nid); ?>"><?php echo $title; ?></a></h4>
<p><?php print $node->body['und'][0]['value']; ?></p>