<?php //print_r($nodes); ?>
<?php $i == 0; ?>
<?php foreach($nodes as $node): ?>
	<li <?php if($i == 1):?>class="alt"<?php endif;?>>
	    <a href="<?php print $node->field_spif_link[LANGUAGE_NONE][0]['value']; ?>">
	    
	   		<?php
			    $field = field_get_items('node', $node, 'field_standard_spif_image');
			    print render(field_view_value('node', $node, 'field_standard_spif_image', $field[0], array('settings' => array('image_style' => 'admissions_spif'))));
			?>
	    
	    </a>
	    <div class="caption">
	        <h4><a href="#"><?php print $node->field_spif_headline[LANGUAGE_NONE][0]['value']; ?></a></h4>
	        <?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
	        <p class="more"><a href="<?php print $node->field_spif_link[LANGUAGE_NONE][0]['value']; ?>">
	        	<?php if($node->field_spif_link_text[LANGUAGE_NONE][0]['value']): ?>
		        	<?php print $node->field_spif_link_text[LANGUAGE_NONE][0]['value']; ?>
		        <?php else: ?>
		        	More Information
		        <?php endif; ?>
	        </a></p>
	    </div>
	</li>
	<?php $i++ ?>
<?php endforeach; ?>