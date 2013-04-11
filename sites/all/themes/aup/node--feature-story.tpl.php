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
			<?php print $node->field_inline_image_caption[LANGUAGE_NONE][0]['value']; ?>
		</div>
	<?php endif; ?>
	
	<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
	
	<?php if($field): ?>
		<div class="inline mobileShow">
			<?php print render(field_view_value('node', $node, 'field_inline_image', $field[0], array('settings' => array('image_style' => 'feature_page')))); ?>
			<?php print $node->field_inline_image_caption[LANGUAGE_NONE][0]['value']; ?>
		</div>
	<?php endif; ?>
	
</div>

<?php if($node->field_you_tube_video[LANGUAGE_NONE][0]['value']): ?>
	<div class="container">
 		<div class="feature">
     		<div class="media">
         		<?php print $node->field_you_tube_video[LANGUAGE_NONE][0]['value']; ?>
         	</div>
         	<div class="caption">
         		<?php print $node->field_you_tube_video_caption[LANGUAGE_NONE][0]['value']; ?>
	         </div>
    	 </div>
	</div>
<?php endif; ?>
 
<?php if($node->field_related_link[LANGUAGE_NONE]): ?>

   <script type="text/javascript">
   //<![CDATA[
   	jQuery(document).ready(function(){
   		jQuery('.relatedLinks').show();
   		jQuery('.related-links-source').appendTo('.move-related-links');
   	});
   //]]>
   </script>
   
   <div style="display:none;">
   	<ul class="related-links-source">
   		<?php foreach($node->field_related_link[LANGUAGE_NONE] as $link): ?>
   			<li><?php echo l($link['title'], $link['url']);?></li>
		<?php endforeach; ?>
	</ul>
</div>

<?php endif; ?>