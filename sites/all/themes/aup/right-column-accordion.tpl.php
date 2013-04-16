<div class="pod accordionPod">
	<div class="podWrap">

		<?php $i = 1; ?>
		<?php foreach($nodes as $node): ?>
			<div class="accordion accordion<?php echo $i; ?>">
				<div class="accTitle <?php if($i ==1):?>tabOpen<?php endif;?>"><a rel="<?php echo $i; ?>" href="<?php echo $node->field_world_spif_link[LANGUAGE_NONE][0]['value']; ?>">Students <em>of</em> The World</a></div>
			    <div class="accContent <?php if($i ==1):?>open<?php endif; ?>">
			        <a href="<?php echo $node->field_world_spif_link[LANGUAGE_NONE][0]['value']; ?>">
						<?php
		        		    $field = field_get_items('node', $node, 'field_spif_image');
		        		    print render(field_view_value('node', $node, 'field_spif_image', $field[0], array('settings' => array('image_style' => 'world_spif_right_column'))));
		        		?>
			        </a>
			        <div class="info">
			            <h4><a href="<?php echo $node->field_world_spif_link[LANGUAGE_NONE][0]['value']; ?>"><?php echo $node->field_spif_title[LANGUAGE_NONE][0]['value']; ?></a></h4>
			            <p><?php echo $node->body[LANGUAGE_NONE][0]['value']; ?></p>
			        </div>
			    </div>
			</div>
			<?php $i++; ?>
		<?php endforeach; ?>
							
	</div>
</div>			        

<?php //print_r($nodes); ?>
