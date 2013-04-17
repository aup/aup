<?php 
	/*
	 * Page template for the Universal Page
	*/
?>

<div class="outer">
	<div class="outerBg">
    	<?php include('_includes/header.php'); ?>
        <!-- Start of wrapper -->
        <div class="wrapper">
        	<div class="breadcrumb">
            	<?php echo $breadcrumb; ?>
            </div>
            <!-- Start of Content -->
            <div class="page-content">
            
            	<div class="surround">
                    <div class="mainContent bodyCopy">
                        <div class="container inner">
                            <div class="pageTitle">
                                <?php if($title): echo '<h1>'.$title.'</h1>'; endif ?>
                                <div class="share">
                                    <a href="#">Share This</a>
                                </div>
                            </div>
                        </div>
                        <div class="container inner">
			            	<?php if ($messages): echo $messages; endif; ?>
			            	<?php if ($tabs): echo render($tabs); endif; ?>
	                        <?php if($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
	            		</div>

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

										<!-- Start SPIF Region -->
										<?php if($page['universal_spif_1']): echo render($page['universal_spif_1']); endif; ?>
										<?php if($page['universal_spif_2']): echo render($page['universal_spif_2']); endif; ?>
										<?php if($page['universal_spif_3']): echo render($page['universal_spif_3']); endif; ?>
										<!-- End SPIF Region -->

										
										
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

                    </div>
                    <div class="leftColumn">
                        <div class="secondaryNav">
                        	<?php if($page['left_column']): echo render($page['left_column']); endif; ?>
                        </div>
                        
                        <?php if(!empty($node->field_related_links[LANGUAGE_NONE])): ?>
                        <div class="relatedLinks">
                            <div class="wrap">
                                <h4>Related Links</h4>
                                <ul>
    	                            <?php foreach($node->field_related_links[LANGUAGE_NONE] as $link): ?>
										<li><?php echo l($link['title'], $link['url']);?></li>
									<?php endforeach; ?>
								</ul>
                            </div>
                        </div>
                        <?php endif; ?>
                        
                    </div>
            	</div>
            	
            	<div class="fullWidth news">
                	<div class="feedTitle">
                    	<h3>News</h3>
                        <div class="more">
                        	<a href="#">View more</a>
                        </div>
                    </div>
                    <?php echo views_embed_view('news_events', 'block_3'); ?>
                </div>
    			<div class="fullWidth events">
                	<div class="feedTitle">
                    	<h3>Events</h3>
                        <div class="more">
                        	<a href="#">View more</a>
                        </div>
                    </div>
                    <?php echo views_embed_view('news_events', 'block_2'); ?>
                </div>
            	
            </div>
            <!-- End of Content -->
            <!-- Start of footer -->
            <?php include('_includes/footer.php'); ?>
            <!-- End of Footer -->
        </div>
        <!-- End of wrapper -->
    </div>
</div>

