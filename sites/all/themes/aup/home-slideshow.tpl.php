<?php if(!empty($nodes)): ?>
	<div class="homeCarousel">
		<ul class="bxslider">
			<?php foreach($nodes as $node): ?>
				<li>
					<?php
					    $field = field_get_items('node', $node, 'field_slide_image');
					    print render(field_view_value('node', $node, 'field_slide_image', $field[0], array('settings' => array('image_style' => 'home_slide'))));
					?>
				   <div class="caption">
				   	<?php if(!empty($node->field_slide_caption_text_mobile)): ?>
				   		<div class="text mobileHide">
				   		<?php
					    	$field = field_get_items('node', $node, 'field_slide_caption_image');
					   		print render(field_view_value('node', $node, 'field_slide_caption_image', $field[0], array('settings' => array('image_style' => 'home_slide_caption'))));
						?>
						</div>
				   	<?php endif; ?>
				   	<?php if(!empty($node->field_slide_caption_text_mobile)): ?>
					   	<div class="text mobileShow"><?php echo $node->field_slide_caption_text_mobile[LANGUAGE_NONE][0]['value']; ?></div>
				   	<?php endif; ?>
				       <h2><?php echo $node->field_slide_text[LANGUAGE_NONE][0]['value']; ?></h2>
				       <div class="more"><a href="<?php echo $node->field_button_url[LANGUAGE_NONE][0]['value']; ?>"><?php echo $node->field_button_text[LANGUAGE_NONE][0]['value']; ?></a></div>
				   </div>
				</li>
			<?php endforeach; ?>
		</ul>
	</div>
<?php endif; ?>	    


	

    
  
   
    
    

	
