<?php  
// Hide Scroller arrows if needed
$count = count($nodes);
if ($count <= 1):
?>
	<style type="text/css">
		.bx-controls { display: none; }
	</style>
<?php endif; ?>


<!-- Begin Slider -->
<div class="container inner">
    <div class="contentCarousel">
    	<ul class="bxslider">
    		<?php foreach($nodes as $node): ?>
        	<li>
            	<div class="media">
                	<a href="<?php echo $node->field_news_slide_read_more[LANGUAGE_NONE][0]['value']; ?>">
                		<?php
		        		    $field = field_get_items('node', $node, 'field_news_slide_image');
		        		    print render(field_view_value('node', $node, 'field_news_slide_image', $field[0], array('settings' => array('image_style' => 'news_slideshow'))));
		        		?>
                	</a>
                </div>
                <div class="text">
                	<h3><?php echo $node->field_news_slide_title[LANGUAGE_NONE][0]['value']; ?></h3>
                    <p><?php echo $node->field_news_slide_text[LANGUAGE_NONE][0]['value']; ?></p>
                    <div class="more">
                    	<a href="<?php echo $node->field_news_slide_read_more[LANGUAGE_NONE][0]['value']; ?>">Read More</a>
                    </div>
                </div>
            </li>
            <?php endforeach; ?>
        </ul>
    </div>
</div>
<!-- End Slider -->
<?php //print_r($nodes); ?>