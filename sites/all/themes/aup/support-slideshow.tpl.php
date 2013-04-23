<?php 
	/*
	 * Template for Support Template Slideshow
	*/
?>

<?php  
// Hide Scroller arrows if needed
$count = count($nodes);
if ($count <= 1):
?>
	<style type="text/css">
		.bx-controls { display: none; }
	</style>
<?php endif; ?>

<div class="supportCarousel container">
	<ul class="bxslider">
		<?php foreach($nodes as $node): ?>
	    <li>
	        <div class="media">
	        	<?php if(!empty($node->field_news_slide_read_more)):?>
	            	<a href="<?php echo $node->field_news_slide_read_more[LANGUAGE_NONE][0]['value']; ?>">
	            <?php endif; ?>
					<?php
		        	    $field = field_get_items('node', $node, 'field_news_slide_image');
		        	    print render(field_view_value('node', $node, 'field_news_slide_image', $field[0], array('settings' => array('image_style' => 'support_slideshow'))));
		        	?>
		        <?php if(!empty($node->field_news_slide_read_more)):?>
		            </a>
		        <?php endif; ?>
	        </div>
	        <div class="text">
	        	<?php if(!empty($node->field_news_slide_title)):?>
		            <h3><?php echo $node->field_news_slide_title[LANGUAGE_NONE][0]['value']; ?></h3>
	            <?php endif; ?>
	            <?php if(!empty($node->field_news_slide_text)): ?>
					<p><?php echo $node->field_news_slide_text[LANGUAGE_NONE][0]['value']; ?></p>
				<?php endif; ?>
				<?php if(!empty($node->field_news_slide_read_more)):?>
					<div class="more">
						<a href="<?php echo $node->field_news_slide_read_more[LANGUAGE_NONE][0]['value']; ?>">Read More</a>
					</div>
				<?php endif; ?>
	        </div>
	    </li>
	    <?php endforeach; ?>
	</ul>
</div>
<?php //print_r($nodes); ?>