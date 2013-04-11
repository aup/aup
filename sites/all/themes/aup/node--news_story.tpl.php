<?php 
	/*
	 * Node Template for News Story
	*/
?>


   <div class="date-in-parts">
       <span class="day"><?php  echo date("j", $node->created); ?></span>
       <span class="month"><?php echo date("M", $node->created); ?></span>
       <span class="year"><?php echo date("Y", $node->created); ?></span>
    </div><!--//date-in-parts -->
        


<div class="container inner">
	
	<?php $field = field_get_items('node', $node, 'field_news_inline_image'); ?>
	<?php if($field): ?>
		<div class="inline mobileHide">
			<?php print render(field_view_value('node', $node, 'field_news_inline_image', $field[0], array('settings' => array('image_style' => 'feature_page')))); ?>
			<?php print $node->field_news_inline_image_caption[LANGUAGE_NONE][0]['value']; ?>
		</div>
	<?php endif; ?>
	
	<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
	
	<?php if($field): ?>
		<div class="inline mobileShow">
			<?php print render(field_view_value('node', $node, 'field_news_inline_image', $field[0], array('settings' => array('image_style' => 'feature_page')))); ?>
			<?php print $node->field_news_inline_image_caption[LANGUAGE_NONE][0]['value']; ?>
		</div>
	<?php endif; ?>
	
</div>

<?php if($node->field_news_you_tube_video[LANGUAGE_NONE][0]['value']): ?>
	<div class="container">
 		<div class="feature">
     		<div class="media">
         		<?php print $node->field_news_you_tube_video[LANGUAGE_NONE][0]['value']; ?>
         	</div>
         	<div class="caption">
         		<?php print $node->field_news_you_tube_video_captio[LANGUAGE_NONE][0]['value']; ?>
	         </div>
    	 </div>
	</div>
<?php endif; ?>
