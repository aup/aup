<?php 
	/*
	 * Page template for the News Page
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
                <div class="tabSection gatewayFeature">
                	<div class="tabSurround">
                        <h4>More from</h4>
                        <ul class="gTabs doubleLineTabs">
                            <li class="tab-1 selected">
                                <a href="#">Students <em>of</em> The World</a>
                            </li>
                            <li class="tab-2">
                                <a href="#">STUDIES <em>for</em> The World</a>
                            </li>
                            <li class="tab-3 last">
                                <a href="#">Success <em>in</em> The World</a>
                            </li>
                        </ul>
                    </div>
                    <div class="gContent">
                        <div class="gInner1 gInner selected">
                            <ul class="feed bxslider mobileHide">
                                <li>
                                	<div class="columns3">
                                        <div class="col">
                                            <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
                                            <h4><a href="#">Success in the World 01</a></h4>
                                            <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                        </div>
                                        <div class="col">
                                            <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
                                            <h4><a href="#">Success in the World 02</a></h4>
                                            <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                        </div>
                                        <div class="col">
                                            <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo3.jpg"></a></p>
                                            <h4><a href="#">Success in the World 03</a></h4>
                                            <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                        </div>
                                    </div>
                                </li>
                                <li>
                                	<div class="columns3">
                                        <div class="col">
                                            <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo3.jpg"></a></p>
                                            <h4><a href="#">Success in the World 04</a></h4>
                                            <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                        </div>
                                        <div class="col">
                                            <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo3.jpg"></a></p>
                                            <h4><a href="#">Success in the World 05</a></h4>
                                            <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                        </div>
                                        <div class="col">
                                            <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo3.jpg"></a></p>
                                            <h4><a href="#">Success in the World 06</a></h4>
                                            <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                        </div>
                                    </div>
                                </li>
                            </ul>
                            <ul class="feed mobileShow">
                                <li>
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
                                    <h4><a href="#">Success in the World 01</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                                <li class="wideCol">
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
                                    <h4><a href="#">Success in the World 02</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                                <li>
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo3.jpg"></a></p>
                                    <h4><a href="#">Success in the World 03</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                                <li>
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
                                    <h4><a href="#">Success in the World 04</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                                <li>
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
                                    <h4><a href="#">Success in the World 05</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                                <li>
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo3.jpg"></a></p>
                                    <h4><a href="#">Success in the World 06</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                            </ul>
                        </div>
                        <div class="gInner2 gInner">
                            <ul class="feed">
                                <li>
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
                                    <h4><a href="#">Success in the World 01</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                                <li class="wideCol">
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo2.jpg"></a></p>
                                    <h4><a href="#">Success in the World 02</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                                <li>
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
                                    <h4><a href="#">Success in the World 03</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                            </ul>
                        </div>
                        <div class="gInner3 gInner">
                            <ul class="feed">
                                <li>
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo3.jpg"></a></p>
                                    <h4><a href="#">Success in the World 01</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                                <li class="wideCol">
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo2.jpg"></a></p>
                                    <h4><a href="#">Success in the World 02</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                                <li>
                                    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo3.jpg"></a></p>
                                    <h4><a href="#">Success in the World 03</a></h4>
                                    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
                                </li>
                            </ul>
                        </div>
                    </div>
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