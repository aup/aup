<?php 
	/*
	 * Page template for the:
	 * - Default Page
	 * - Contact Page
	 * - Search Page
	 * - News Story Page
	 * - Events Page
	*/
?>

<div class="outer">
	<div class="outerBg">
		<?php include('_includes/header.php'); ?>
        <!-- Start of wrapper -->
        <div class="wrapper">
        	<div class="breadcrumb <?php if(!$page['left_column']):?>full<?php endif; ?>">
            	<?php echo $breadcrumb; ?>
            </div>
            <!-- Start of Content -->
            <div class="page-content">
            	<div class="surround">
                    <div class="mainContent <?php if(!$page['left_column']):?>full<?php endif; ?> bodyCopy">
                        <div class="container inner">
                            <div class="pageTitle">
                                <?php if($title): echo '<h1>'.$title.'</h1>'; endif ?>
                                <?php if($page['add_this']): ?>
                               		<div class="share">
	                               		<?php echo render($page['add_this']);?> 
	                               	</div>
                               	<?php endif; ?>
                            </div>
                        </div>
                        <div class="container inner">
                        	<?php if ($messages): echo $messages; endif; ?>
	                        <?php if ($tabs): echo render($tabs); endif; ?>
	                        <?php if($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
                            <?php echo render($page['content']); ?>
                        </div>
                    </div>
                    <?php if($page['left_column']): ?>
					    <div class="leftColumn">
					    	<div class="secondaryNav">
					        	<?php echo render($page['left_column']); ?>   							
					        </div>         
					   </div>
					<?php endif; ?>
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

