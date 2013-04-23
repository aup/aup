<?php 
	/*
	 * Page for News Archive
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
                    <div class="mainContent bodyCopy noPad">
						
                        <!-- Begin News Column -->
                        <div class="newsevents">
                            <div class="newseventsWrap">
                                <div class="newsColumn">
                                    <div class="feedTitle">
                                        <h3>News Archive<a href="#" class="rss"><img src="<?php echo base_path().path_to_theme(); ?>/images/rss.png" alt=""/></a></h3>
                                    </div>
                                    
                                    <?php if ($messages): echo $messages; endif; ?>
                                    <?php if ($tabs): echo render($tabs); endif; ?>
	                       	 		<?php if($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
                            		<?php echo render($page['content']); ?>
                            		
                                </div>
                                
                                <div class="eventsColumn">
                                    <div class="feedTitle">
                                        <h3>Archives By Year</h3>
                                    </div>
                                    <?php echo views_embed_view('news_events', 'block_4'); ?>
                                   
                                </div>

                            </div>
                        </div>
                    </div>
                    <!-- End News Column -->   

                    <!-- Begin Left Column -->
                    <div class="leftColumn">
                        <div class="secondaryNav">
                        	<?php if($page['left_column']): echo render($page['left_column']); endif; ?>
	                    </div>
	                </div>
                    <!-- Begin Left Column -->
                    
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

