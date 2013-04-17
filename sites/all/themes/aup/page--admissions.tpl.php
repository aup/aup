<?php 
	/*
	 * Page template for the Admissions Page
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
                    <div class="container">
                    	<div class="admissionLead">
                        	<div class="text">
                            	<?php if ($tabs): echo render($tabs); endif; ?>
	                    		<?php if($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
		                        <?php echo render($page['content']); ?>
                            </div>
                            <div class="info">
                            	<?php if ($page['admissions_menu']): print render($page['admissions_menu']); endif; ?>
                            </div>
                        </div>
                    </div>
                    <ul class="admissionPods">
                    	<?php if ($page['admissions_features_1']): print render($page['admissions_features_1']); endif; ?>
                    	<?php if ($page['admissions_features_2']): print render($page['admissions_features_2']); endif; ?>
                    	<?php if ($page['admissions_features_3']): print render($page['admissions_features_3']); endif; ?>
                    </ul>
                </div>
                <div class="admissions-bar-destination">
                	<!-- JS puts info here -->
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