<div class="pod accordionPod">
	<div class="podWrap">

		<?php $i = 1; ?>
		<?php foreach($nodes as $node): ?>
		
			<?php if($node->type == 'world_spif'): ?>
				<!-- World SPIF ============= -->
				<div class="accordion accordion<?php echo $i; ?>">
					<div class="accTitle <?php if($i ==1):?>tabOpen<?php endif;?>">
						<a rel="<?php echo $i; ?>" href="#>">
							<?php if(!empty($node->field_spif_title)): ?>
								<?php echo $node->field_spif_title[LANGUAGE_NONE][0]['value']; ?>
							<?php endif; ?>
						</a>
					</div>
				    <div class="accContent <?php if($i ==1):?>open<?php endif; ?>">
				    	<?php if(!empty($node->field_world_spif_link)): ?>
					        <a href="<?php echo $node->field_world_spif_link[LANGUAGE_NONE][0]['value']; ?>">
				        <?php endif; ?>
							<?php
		    	    		    $field = field_get_items('node', $node, 'field_spif_image');
		    	    		    print render(field_view_value('node', $node, 'field_spif_image', $field[0], array('settings' => array('image_style' => 'world_spif_right_column'))));
		    	    		?>
		    	    	<?php if(!empty($node->field_world_spif_link)): ?>
					        </a>
					    <?php endif; ?>
				        <div class="info">
				        	<?php if(!empty($node->field_spif_title)): ?>
					            <h4>
					            	<?php if(!empty($node->field_world_spif_link)): ?>
					            	<a href="<?php echo $node->field_world_spif_link[LANGUAGE_NONE][0]['value']; ?>"><?php echo $node->field_spif_title[LANGUAGE_NONE][0]['value']; ?></a>
					            	<?php endif; ?>
					            </h4>
							<?php endif; ?>
							<?php if(!empty($node->body)):?>
				            	<?php echo $node->body[LANGUAGE_NONE][0]['value']; ?>
				            <?php endif; ?>
				        </div>
				    </div>
				</div>
			<?php else: ?>
				<!-- Standard SPIF ============= -->
				<div class="accordion accordion<?php echo $i; ?>">
					<div class="accTitle <?php if($i ==1):?>tabOpen<?php endif;?>">
						<a rel="<?php echo $i; ?>" href="#">
							<?php if(!empty($node->field_spif_headline)):?>
								<?php echo $node->field_spif_headline[LANGUAGE_NONE][0]['value']; ?>
							<?php endif; ?>
						</a>
					</div>
				    <div class="accContent <?php if($i ==1):?>open<?php endif; ?>">
				    	<?php if(!empty($node->field_spif_link)):?>
					        <a href="<?php echo $node->field_spif_link[LANGUAGE_NONE][0]['value']; ?>">
					    <?php endif; ?>
							<?php
		    	    		    $field = field_get_items('node', $node, 'field_standard_spif_image');
		    	    		    print render(field_view_value('node', $node, 'field_standard_spif_image', $field[0], array('settings' => array('image_style' => 'world_spif_right_column'))));
		    	    		?>
		    	    	<?php if(!empty($node->field_spif_link)):?>
				       		</a>
				       	<?php endif; ?>
				        <div class="info">
				            <h4>
				            	<?php if(!empty($node->field_spif_link)):?>
					            	<a href="<?php echo $node->field_spif_link[LANGUAGE_NONE][0]['value']; ?>">
				            	<?php endif; ?>
				            		<?php if(!empty($node->field_spif_sub_heading)):?>
					            		<?php echo $node->field_spif_sub_heading[LANGUAGE_NONE][0]['value']; ?>
				            		<?php endif; ?>
				            	<?php if(!empty($node->field_spif_link)):?>
					            	</a>
				            	<?php endif; ?>
				            </h4>
				            <?php if(!empty($node->body)):?>
				            	<?php echo $node->body[LANGUAGE_NONE][0]['value']; ?>
				            <?php endif; ?>
				        </div>
				    </div>
				</div>
			<?php endif; ?>
			<?php $i++; ?>
		<?php endforeach; ?>
							
	</div>
</div>			        

<?php //print_r($nodes); ?>
