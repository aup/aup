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
            <?php include('_includes/footer.php'); ?>
            <!-- End of Footer -->
        </div>
        <!-- End of wrapper -->
    </div>
</div>