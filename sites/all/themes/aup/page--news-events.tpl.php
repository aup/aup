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
                    <div class="mainContent bodyCopy noPad">
                    
                    	
                    	
                    	<!-- Begin Title -->
                        <div class="container inner">
                            <div class="pageTitle">
                                <?php if($title): echo '<h1>'.$title.'</h1>'; endif ?>
                            </div>
                        </div>
                        <!-- End Title -->
                        
                        <div class="container inner">
			            	<?php if ($messages): echo $messages; endif; ?>
	            		</div>
                        
                        <!-- Begin Slider -->
                        <div class="container inner">
                            <div class="contentCarousel">
                            	<ul class="bxslider">
                                	<li>
                                    	<div class="media">
                                        	<a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/news1.jpg" alt="" /></a>
                                        </div>
                                        <div class="text">
                                        	<h3>Vestibulum ipsum fringilla</h3>
                                            <p>Nullam risus turpis, tincidunt fringilla aliquam quis, semper sit amet lorem. Donec nec arcu adipiscing libero mattis vehicula ornare eu tellus. Quisque cursus iaculis ultrices.</p>
                                            <div class="more">
                                            	<a href="#">Read more</a>
                                            </div>
                                        </div>
                                    </li>
                                	<li>
                                    	<div class="media">
                                        	<a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/news1.jpg" alt="" /></a>
                                        </div>
                                        <div class="text">
                                        	<h3>Vestibulum ipsum fringilla</h3>
                                            <p>Nullam risus turpis, tincidunt fringilla aliquam quis, semper sit amet lorem. Donec nec arcu adipiscing libero mattis vehicula ornare eu tellus. Quisque cursus iaculis ultrices.</p>
                                            <div class="more">
                                            	<a href="#">Read more</a>
                                            </div>
                                        </div>
                                    </li>
                                </ul>
                            </div>
                        </div>
                        <!-- End Slider -->
                        
                        <!-- Begin News Column -->
                        <div class="newsevents">
                            <div class="newseventsWrap">
                                <div class="newsColumn">
                                    <div class="feedTitle">
                                        <h3>News <a href="#" class="rss"><img src="<?php echo base_path().path_to_theme(); ?>/images/rss.png" alt=""/></a></h3>
                                    </div>
                                    
                                    <?php if ($tabs): echo render($tabs); endif; ?>
	                       	 		<?php if($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
                            		<?php echo render($page['content']); ?>
                            		
                            		<?php /*
                                    <ul class="feed">
                                        <li>
                                            <h4><a href="#">A Variety of Fellow Students</a> <span>October 25</span></h4>
                                            <p>Join Celeste Schenck, President of The American University of Paris, for a thought-provoking discussion about the increasing fit between women's...</p>
                                        </li>
                                        <li>
                                            <h4><a href="#">A Variety of Fellow Students</a> <span>October 25</span></h4>
                                            <p>Join Celeste Schenck, President of The American University of Paris, for a thought-provoking discussion about the increasing fit between women's...</p>
                                        </li>
                                        <li>
                                            <h4><a href="#">A Variety of Fellow Students</a> <span>October 25</span></h4>
                                            <p>Join Celeste Schenck, President of The American University of Paris, for a thought-provoking discussion about the increasing fit between women's...</p>
                                        </li>
                                        <li>
                                            <h4><a href="#">A Variety of Fellow Students</a> <span>October 25</span></h4>
                                            <p>Join Celeste Schenck, President of The American University of Paris, for a thought-provoking discussion about the increasing fit between women's...</p>
                                        </li>
                                        <li>
                                            <h4><a href="#">A Variety of Fellow Students</a> <span>October 25</span></h4>
                                            <p>Join Celeste Schenck, President of The American University of Paris, for a thought-provoking discussion about the increasing fit between women's...</p>
                                        </li>
                                    </ul> */ ?>
                                    <div class="more">
                                    	<a href="#">View more news stories</a>
                                    </div>
                                </div>
                                <div class="eventsColumn">
                                    <div class="feedTitle">
                                        <h3>Events <a href="#" class="rss"><img src="<?php echo base_path().path_to_theme(); ?>/images/rss.png" alt=""/></a></h3>
                                    </div>
                                    <?php echo render($page['news_events_col']); ?>
                                    <?php /*
                                    <ul class="feed">
                                        <li>
                                        	<div class="date">
                                                <span>October</span>
                                                <em>22</em>
                                            </div>
                                            <div class="info">
                                            	<h4><a href="#">Women's Leadership for the 21st Century</a> <span>6.30 - 8.30 PM</span></h4>
                            					<p>Join Celeste Schenck, President of The American University of Paris, for a thought-provoking discussion about the increasing fit between women's...</p>
                                            </div>
                                        </li>
                                        <li>
                                        	<div class="date">
                                                <span>October</span>
                                                <em>22</em>
                                            </div>
                                            <div class="info">
                                            	<h4><a href="#">Women's Leadership for the 21st Century</a> <span>6.30 - 8.30 PM</span></h4>
                            					<p>Join Celeste Schenck, President of The American University of Paris, for a thought-provoking discussion about the increasing fit between women's...</p>
                                            </div>
                                        </li>
                                        <li>
                                        	<div class="date">
                                                <span>October</span>
                                                <em>22</em>
                                            </div>
                                            <div class="info">
                                            	<h4><a href="#">Women's Leadership for the 21st Century</a> <span>6.30 - 8.30 PM</span></h4>
                            					<p>Join Celeste Schenck, President of The American University of Paris, for a thought-provoking discussion about the increasing fit between women's...</p>
                                            </div>
                                        </li>
                                    </ul> */ ?>
                                    <div class="more">
                                    	<a href="#">View full calendar</a>
                                    </div>
                                </div>
                            </div>
                        </div>
                    </div>
                    <!-- End News Column -->   

                    <!-- Begin Left Column -->
                    <div class="leftColumn">
                        <div class="secondaryNav">
                            <ul>
                                <li><a href="#">Link Number 01</a></li>
                                <li><a href="#">Link Number 02</a></li>
                                <li>
                                    <a href="#">Link Number 03</a>
                                    <ul>
                                        <li>
                                            <a class="selected" href="#">Sub Link Long Number 01</a>
                                            <ul>
                                                <li><a href="#">Child Link 01</a></li>
                                                <li><a href="#">Child Link 02</a></li>
                                                <li><a href="#">Child Link 03</a></li>
                                                <li><a href="#">Child Link 04</a></li>
                                            </ul>
                                        </li>
                                        <li><a href="#">Sub Link 03</a></li>
                                        <li><a href="#">Sub Link 03</a></li>
                                    </ul>
                                </li>
                                <li><a href="#">Link Number 04</a></li>
                                <li><a href="#">Link Number 05</a></li>
                                <li><a href="#">Link Number 06</a></li>
                            </ul>
                        </div>
                        <div class="relatedLinks">
                            <div class="wrap">
                                <h4>Related Links</h4>
                                <ul>
                                    <li><a href="#">Link Number One</a></li>
                                    <li><a href="#">Link Number Two</a></li>
                                    <li><a href="#">Link Number Three</a></li>
                                </ul>
                            </div>
                        </div>
                    </div>
                    <!-- Begin Left Column -->
                    
            	</div>
            </div>
            <!-- End of Content -->
            <!-- Start of footer -->
            <div class="footer">
    			<h6>&copy; 2013 THE AMERICAN UNIVERSITY OF PARIS</h6>
                <ul>
                	<li><a href="#">Maps &amp; Directories</a></li>
                	<li><a href="#">Site A to Z</a></li>
                	<li><a href="#">MyAUP</a></li>
                	<li class="last"><a href="#">Employment Opportunities</a></li>
                </ul>
                <ul class="icons">
                	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/facebook20.png" alt=""/></a></li>
                	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/twitter20.png" alt=""/></a></li>
                	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/youtube20.png" alt=""/></a></li>
                	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/rss20.png" alt=""/></a></li>
                </ul>
            </div>
            <!-- End of Footer -->
        </div>
        <!-- End of wrapper -->
    </div>
</div>
