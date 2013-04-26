<?php 
	/*
	 * Page template for Gateway
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
                <div class="gateway bodyCopy">
                	<?php if ($tabs): echo render($tabs); endif; ?>
	                <?php if($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
	                <?php echo render($page['content']); ?>
    			</div>
    			
    			<!-- BEGIN NEWS FEED -->
	    		<?php if ($page['horizontal_news_feed']): print render($page['horizontal_news_feed']); endif; ?>
	    		<!-- END NEWS FEED -->
	    		<!-- BEGIN EVENTS FEED -->
    			<?php if ($page['horizontal_events_feed']): print render($page['horizontal_events_feed']); endif; ?>
    			<!-- END EVENTS FEED -->
    			
            </div>
            <!-- End of Content -->
            <!-- Start of footer -->
            <?php include('_includes/footer.php'); ?>
            <!-- End of Footer -->
        </div>
        <!-- End of wrapper -->
    </div>
</div>