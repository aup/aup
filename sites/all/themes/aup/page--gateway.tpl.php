<div class="outer">
	<div class="outerBg">
    	<?php include('_includes/header.php'); ?>
    	<!-- Start of wrapper -->
        <div class="wrapper">
        	<div class="breadcrumb">
            	<?php echo $breadcrumb; ?>
            </div>
            <!-- Start of Content -->
            <div class="content">
                <!--<div class="pageTitle leftMargin">
                    <h1>Page Title Header</h1>
                </div>-->
                <div class="gateway">
                	<?php if ($tabs): echo render($tabs); endif; ?>
	                <?php if($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
	                <?php echo render($page['content']); ?>
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