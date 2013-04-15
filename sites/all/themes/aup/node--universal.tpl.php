<?php 
	/*
	 * Node Template for the Universal Page
	*/
?>

<?php if ($node->field_display_news_feed[LANGUAGE_NONE][0]['value'] == 1): ?>
	<style type="text/css">
		.news { display:none; }
	</style>
<?php endif; ?>

<?php if ($node->field_display_events_feed[LANGUAGE_NONE][0]['value'] == 1): ?>
	<style type="text/css">
		.events { display:none; }
	</style>
<?php endif; ?>

<?php if ($node->field_page_layout[LANGUAGE_NONE][0]['value'] == 0): ?>

	<!-- Two Columns ======= -->
	<div class="container sideBar">
         
         	<!-- Start Main Col -->
         	<div class="mainContent">
	         	<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
         	</div>
         	<!-- End Main Col -->
         	
         	<!-- Start Right Sidebar -->
         	<div class="side">
				<div class="pod accordionPod">
					<div class="podWrap">
				    	<div class="accordion accordion1">
				        	<div class="accTitle tabOpen"><a rel="1" href="#">Students <em>of</em> The World</a></div>
				            <div class="accContent open">
				                <a href="#"><img src="images/promo1.jpg" alt=""/></a>
				                <div class="info">
				                    <h4><a href="#">A Variety of Fellow Students1</a></h4>
				                    <p>The training I received in and out of the classroom has been useful in countless ways...</p>
				                </div>
				            </div>
				        </div>
				        <div class="accordion accordion2">
				        	<div class="accTitle"><a rel="2" href="#">STUDIES <em>for</em> The World</a></div>
				            <div class="accContent">
				                <a href="#"><img src="images/promo1.jpg" alt=""/></a>
				                <div class="info">
				                    <h4><a href="#">A Variety of Fellow Students1</a></h4>
				                    <p>The training I received in and out of the classroom has been useful in countless ways...</p>
				                </div>
				            </div>
				        </div>
				        <div class="accordion accordion3">
				        	<div class="accTitle"><a rel="3" href="#">Success <em>in</em> The World</a></div>
				            <div class="accContent">
				                <a href="#"><img src="images/promo1.jpg" alt=""/></a>
				                <div class="info">
				                    <h4><a href="#">A Variety of Fellow Students1</a></h4>
				                    <p>The training I received in and out of the classroom has been useful in countless ways...</p>
				                </div>
				            </div>
				        </div>
				    </div>
				</div>
				<div class="pod podRichtext">
					<div class="podWrap">
				    	<img src="images/inlineImage.jpg" alt="" />
						<p><strong>Inline Image Caption:</strong> Proin blandit sollicitudin tempus. In turpis augue, tempus non mollis ac, feugiat sed quam. Tincidunt consectetur.  <a href="#">read more</a></p>
				    </div>
				</div>
				<div class="pod last">
					<div class="podWrap">
				   	<div class="podSocial">
				            <div class="tabSurround">
				                <ul class="gTabs">
				                    <li class="tab-1 selected">
				                        <a href="#"><em>Twitter</em></a>
				                        <span></span>
				                    </li>
				                    <li class="tab-2">
				                        <a href="#"><em>Facebook</em></a>
				                        <span></span>
				                    </li>
				                </ul>
				            </div>
				            <div class="gContent">
				                <div class="gInner1 gInner selected">
				                    <ul class="feed">
				                        <li>
				                            <p>Tonight at #TheAUP "Ou va l'Amerique?", roundtable with incredible guests. RSVP now for last minutes spots <a href="#">http://t.co/JC16asP8</a> <a href="#">#aupevents</a></p>
				                        </li>
				                        <li>
				                            <p>Tonight at #TheAUP "Ou va l'Amerique?", roundtable with incredible guests. RSVP now for last minutes spots <a href="#">http://t.co/JC16asP8</a> <a href="#">#aupevents</a></p>
				                        </li>
				                        <li>
				                            <p>Tonight at #TheAUP "Ou va l'Amerique?", roundtable with incredible guests. RSVP now for last minutes spots <a href="#">http://t.co/JC16asP8</a> <a href="#">#aupevents</a></p>
				                        </li>
				                    </ul>
				                    <div class="more">
				                    	<a href="#">View more</a>
				                    </div>
				                </div>
				                <div class="gInner2 gInner">
				                    <ul class="feed">
				                        <li>
				   						<p>Have you seen the website dedicated to AUP's 50th anniversary? Check it out! http://50years.aup.edu/ There are two 50th anniversary celebration events in November: Alumni Event in San Francisco- 1 November, 2012 Alumni... <a href="#">Read More</a></p>
				                        </li>
				                        <li>
				   						<p>Have you seen the website dedicated to AUP's 50th anniversary? Check it out! http://50years.aup.edu/ There are two 50th anniversary celebration events in November: Alumni Event in San Francisco- 1 November, 2012 Alumni... <a href="#">Read More</a></p>
				                        </li>
				                        <li>
				   						<p>Have you seen the website dedicated to AUP's 50th anniversary? Check it out! http://50years.aup.edu/ There are two 50th anniversary celebration events in November: Alumni Event in San Francisco- 1 November, 2012 Alumni... <a href="#">Read More</a></p>
				                        </li>
				                    </ul>
				                    <div class="more">
				                    	<a href="#">View more</a>
				                    </div>
				                </div>
				            </div>
				        </div>
				    </div>
				</div>
				
         	<!-- End Right Sidebar -->
         	
         </div>
	</div>
	
<?php else: ?>

	<!-- One Columns ======= -->
	<div class="container inner">
		<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>
	</div>
	
<?php endif; ?>

<?php if($node->field_related_links[LANGUAGE_NONE][0]['value']): ?>

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
			<?php foreach($node->field_related_links[LANGUAGE_NONE] as $link): ?>
				<li><?php echo l($link['title'], $link['url']);?></li>
			<?php endforeach; ?>
		</ul>
	</div>

<?php endif; ?>