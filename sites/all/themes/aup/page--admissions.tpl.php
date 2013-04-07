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
            	<div class="surround">
                    <div class="container">
                    	<div class="admissionLead">
                        	<div class="text">
                            	<?php if ($tabs): echo render($tabs); endif; ?>
	                    		<?php if($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
		                        <?php echo render($page['content']); ?>
                            </div>
                            <div class="info">
                            	<ul>
                                	<li><a href="#">Apply Now</a></li>
                                    <li><a href="#">Visit</a></li>
                                    <li><a href="#">Tuition &amp; Financial Aid</a></li>
                                    <li class="last"><a href="#">Admissions Blog</a></li>
                                </ul>
                            </div>
                        </div>
                    </div>
                    <ul class="admissionPods">
                        <li>
                            <a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/ad1.jpg" alt="" /></a>
                            <div class="caption">
                                <h4><a href="#">Undergraduate Admissions</a></h4>
                                <p>Aenean lacinia bibendum nulla sed consectetur. Nulla vitae elit libero, a pharetra augue. Nullam quis risus eget urna mollis ornare..</p>
                                <p class="more"><a href="#">More Information</a></p>
                            </div>
                        </li>
                        <li class="alt">
                            <a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/ad1.jpg" alt="" /></a>
                            <div class="caption">
                                <h4><a href="#">Undergraduate Admissions</a></h4>
                                <p>Aenean lacinia bibendum nulla sed consectetur. Nulla vitae elit libero, a pharetra augue. Nullam quis risus eget urna mollis ornare..</p>
                                <p class="more"><a href="#">More Information</a></p>
                            </div>
                        </li>
                        <li>
                            <a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/ad1.jpg" alt="" /></a>
                            <div class="caption">
                                <h4><a href="#">Undergraduate Admissions</a></h4>
                                <p>Aenean lacinia bibendum nulla sed consectetur. Nulla vitae elit libero, a pharetra augue. Nullam quis risus eget urna mollis ornare..</p>
                                <p class="more"><a href="#">More Information</a></p>
                            </div>
                        </li>
                        <li class="alt">
                            <a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/ad1.jpg" alt="" /></a>
                            <div class="caption">
                                <h4><a href="#">Undergraduate Admissions</a></h4>
                                <p>Aenean lacinia bibendum nulla sed consectetur. Nulla vitae elit libero, a pharetra augue. Nullam quis risus eget urna mollis ornare..</p>
                                <p class="more"><a href="#">More Information</a></p>
                            </div>
                        </li>
                    </ul>
                </div>
                <div class="studentInfo">
                	<a href="#">Admitted Student Information</a>
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