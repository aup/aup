<?php 
	/*
	 * Node Template for Featured Story
	*/
?>

<div class="container inner">
	
	<?php $field = field_get_items('node', $node, 'field_inline_image'); ?>
	<?php if($field): ?>
		<div class="inline mobileHide">
			<?php print render(field_view_value('node', $node, 'field_inline_image', $field[0], array('settings' => array('image_style' => 'feature_page')))); ?>
			<?php if(!empty($node->field_inline_image_caption)): ?>
				<?php print $node->field_inline_image_caption[LANGUAGE_NONE][0]['value']; ?>
			<?php endif; ?>
		</div>
	<?php endif; ?>
	
	<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
	
	<?php if($field): ?>
		<div class="inline mobileShow">
			<?php print render(field_view_value('node', $node, 'field_inline_image', $field[0], array('settings' => array('image_style' => 'feature_page')))); ?>
			<?php if(!empty($node->field_inline_image_caption)): ?>
				<?php print $node->field_inline_image_caption[LANGUAGE_NONE][0]['value']; ?>
			<?php endif; ?>
		</div>
	<?php endif; ?>
	
</div>

<?php if(!empty($node->field_you_tube_video)): ?>
	<div class="container">
 		<div class="feature">
     		<div class="media">
     			<?php if(!empty($node->field_you_tube_video)):?>
	         		<?php print $node->field_you_tube_video[LANGUAGE_NONE][0]['value']; ?>
	         	<?php endif; ?>
         	</div>
         	<div class="caption">
         		<?php if(!empty($node->field_you_tube_video_caption)):?>
	         		<?php print $node->field_you_tube_video_caption[LANGUAGE_NONE][0]['value']; ?>
				<?php endif; ?>
	         </div>
    	 </div>
	</div>
<?php endif; ?>