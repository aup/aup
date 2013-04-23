<?php 
	/*
	 * Page template for the Events Page
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
			            	<?php if ($messages): echo $messages; endif; ?>
	            		</div>
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
	            		</div>
                        <?php echo render($page['content']); ?>
                    </div>
                    
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