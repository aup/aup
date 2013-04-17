
<!-- Start Non Mobile -->
<ul class="feed bxslider mobileHide">
	<li>
		<div class="columns3">
		<?php echo 'count: ' . count($nodes); ?>
		<?php foreach($nodes as $node): ?>
			<div class="col">
			
				<?php /* if($node->type == 'world_spif'): ?>
					<!-- World SPIF ============= -->
					world
					 <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
			    	<h4><a href="#">Success in the World 01</a></h4>
			    	<p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
				<?php else: ?>		
					<!-- Standard SPIF ============== -->
					standard
					 <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
			    	<h4><a href="#">Success in the World 01</a></h4>
			    	<p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
				<?php endif; */?>
				
			   ++++ <?php echo $node->title; ?> ++++
			    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
			    	<h4><a href="#">Success in the World 01</a></h4>
			    	<p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
			    
			    
			    
			</div>
		<?php endforeach; ?>
		</div>
	</li>
</ul>
<!-- End Non Mobile -->

<!-- Start Mobile -->
<ul class="feed mobileShow">
	<?php foreach($nodes as $node): ?>
		<li>
		
			<?php if($node->type == 'world_spif'): ?>
				<!-- World SPIF ============= -->
			
			<?php else: ?>		
			    <!-- Standard SPIF ============== -->
			<?php endif; ?>
		
		
		
		    <p><a href="#"><img alt="" src="<?php echo base_path().path_to_theme(); ?>/images/promo1.jpg"></a></p>
		    <h4><a href="#">Success in the World 01</a></h4>
		    <p>Morbi dignissim hendrerit dui a tristique. Cras dictum magna vitae velit facilisis rutrum. Aliquam sollicitudin dignissim metus, nec consequat tellus bibendum id.</p>
		    
		    
		    
		    
		</li>
	<?php endforeach; ?>
</ul>
<!-- End Mobile -->

<?php //print_r($nodes); ?>



 <?php /* <ul class="feed bxslider mobileHide">
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
                            </ul> */ ?>