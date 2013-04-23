<?php 
	/*
	 * Page template for the Featured Page
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
                    <div class="leftColumn">
                        <div class="secondaryNav">
                        	<?php if($page['left_column']): echo render($page['left_column']); endif; ?>
                        </div>
                        <?php if(!empty($node->field_related_link)): ?>
                        <div class="relatedLinks">
                            <div class="wrap">
                                <h4>Related Links</h4>
                                <ul>
    	                            <?php foreach($node->field_related_link[LANGUAGE_NONE] as $link): ?>
										<li><?php echo l($link['title'], $link['url']);?></li>
									<?php endforeach; ?>
								</ul>
                            </div>
                        </div>
                        <?php endif; ?>
                    </div>
                </div>
                
                <!-- Begin Tabs -->
                <div class="tabSection gatewayFeature">                
                	<div class="tabSurround">
                        <h4>More from</h4>
                        <ul class="gTabs doubleLineTabs">
                        	<?php if($page['tabbed_features_1']): ?>
                            	<li class="tab-1 selected">
                            	    <a href="#">Students <em>of</em> The World</a>
                            	</li>
                            <?php endif; ?>
                            <?php if($page['tabbed_features_2']): ?>
                            	<li class="tab-2">
                            	    <a href="#">STUDIES <em>for</em> The World</a>
                            	</li>
                            <?php endif; ?>
                            <?php if($page['tabbed_features_3']): ?>
                            	<li class="tab-3 last">
                            	    <a href="#">Success <em>in</em> The World</a>
                            	</li>
                            <?php endif; ?>
                        </ul>
                    </div>

                    <div class="gContent">
                    	<?php if($page['tabbed_features_1']): ?>
                        <div class="gInner1 gInner selected">
                        	<?php echo render($page['tabbed_features_2']); ?>
                        </div>
                        <?php endif; ?>
                        
                        <?php if($page['tabbed_features_2']): ?>
	                        <div class="gInner2 gInner">
    	                    	<?php echo render($page['tabbed_features_3']); ?>
        	                </div>
                        <?php endif; ?>
                        
                        <?php if($page['tabbed_features_3']): ?>
                        	<div class="gInner3 gInner">
                        		<?php echo render($page['tabbed_features_1']); ?>
                        	</div>
                        <?php endif; ?>
                    </div> 
                </div>
                <!-- End Tabs -->

                
            </div>
            <!-- End of Content -->
            <!-- Start of footer -->
            <?php include('_includes/footer.php'); ?>
            <!-- End of Footer -->
        </div>
        <!-- End of wrapper -->
    </div>
</div>