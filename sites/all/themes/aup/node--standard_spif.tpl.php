<?php 
	/*
	 * Node Template for the Standard SPIF
	*/
?>

<h4><?php print $node->field_spif_headline[LANGUAGE_NONE][0]['value']; ?></h4>
<a href="<?php print $node->field_spif_link[LANGUAGE_NONE][0]['value']; ?>">
	<?php
	    $field = field_get_items('node', $node, 'field_standard_spif_image');
	    print render(field_view_value('node', $node, 'field_standard_spif_image', $field[0], array('settings' => array('image_style' => 'standard_spif'))));
	?>
</a>

<div>
    <h5><a href="<?php print $node->field_spif_link[LANGUAGE_NONE][0]['value']; ?>"><?php print $node->field_spif_sub_heading[LANGUAGE_NONE][0]['value']; ?></a></h5>
	<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
</div>