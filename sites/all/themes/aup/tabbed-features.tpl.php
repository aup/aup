<?php 
	/*
	 * Template for the Featured Tabs
	*/
?>

<?php 
// Check node count for display
$node_count = count($nodes); 

if($node_count >= 4) {
	$bxslider = true;
}
else {
	$bxslider = false;
}
?>

<!-- BXSLIDER (more than 3 nodes) ================ -->
<?php if($bxslider == true): ?>
    
    <!-- Start Non Mobile -->
	<ul class="feed mobileHide bxslider">
		<?php $i = 1; ?>
		<?php foreach($nodes as $node): ?>
		
			<?php if($i == 1) :?>
				<li>
					<div class="columns3">
			<?php endif; ?>

						
						<!-- World SPIF ============= -->
						<?php if($node->type == 'world_spif'): ?>
						    <div class="col">
						    	<p>
						    		<?php if(!empty($node->field_world_spif_link)): ?>
						    	    	<a href="<?php echo $node->field_world_spif_link[$node->language][0]['value']; ?>">
						    	    <?php endif; ?>
						    	    	<?php
						    	    	    $field = field_get_items('node', $node, 'field_spif_image');
						    	    	    print render(field_view_value('node', $node, 'field_spif_image', $field[0], array('settings' => array('image_style' => 'feature_tab'))));
						    	    	?>
						    	    <?php if(!empty($node->field_world_spif_link)): ?>
						    		    </a>
						    		<?php endif; ?>
						    	</p>
						    	<h4>
						    		<?php if(!empty($node->field_world_spif_link)): ?>
						    			<a href="<?php echo $node->field_world_spif_link[$node->language][0]['value']; ?>">	
						    		<?php endif; ?>
						    	    	<?php if(!empty($node->field_spif_title)):?>
						    	    		<?php echo $node->field_spif_title[$node->language][0]['value']; ?>
						    		    <?php endif; ?>
						    		<?php if(!empty($node->field_world_spif_link)): ?>
						    			</a>
						    		<?php endif; ?>
						    	</h4>
						    	<?php echo $node->body[LANGUAGE_NONE][0]['value']; ?>
						    </div>
						<!-- Standard SPIF ============== -->
						<?php else: ?>
							<div class="col">		
						 		<p>
						 			<a href="<?php if(isset($node->field_spif_link[$node->language][0]['value'])) { echo $node->field_spif_link[$node->language][0]['value']; } ?>">
						 				<?php
						 				    $field = field_get_items('node', $node, 'field_standard_spif_image');
						 				    print render(field_view_value('node', $node, 'field_standard_spif_image', $field[0], array('settings' => array('image_style' => 'feature_tab'))));
						 				?>
						 			</a>
						 		</p>
						    	<h4><a href="<?php if(isset($node->field_spif_link[$node->language][0]['value'])) { echo $node->field_spif_link[$node->language][0]['value']; } ?>">	
						    		<?php if(isset($node->field_spif_headline[$node->language][0]['value'])):?>
						    			<?php echo $node->field_spif_headline[$node->language][0]['value']; ?>
						    		<?php endif; ?>
						    	</a></h4>
						    	<?php echo $node->body[LANGUAGE_NONE][0]['value']; ?>
						    </div>
						<?php endif; ?>
						
						
			<?php if($i == 3 || $i == 6 || $i == 9 || $i == 12 || $i == 15 && $i != $node_count):?>
					</div>
				</li>
				<li>
					<div class="columns3">
			<?php endif; ?>
						
			<?php if($i == $node_count) :?>
					</div>
				</li>
			<?php endif;?>
			
			<?php $i++; ?>
		<?php endforeach; ?>
	</ul>
	<!-- End Non Mobile -->
	
<!-- STANDARD (less than 3 nodes) ================ -->
<?php else: ?>
    
    <!-- Start Non Mobile -->
	<ul class="feed mobileHide">
		<?php foreach($nodes as $node): ?>
			<li>
				<!-- World SPIF ============= -->
				<?php if($node->type == 'world_spif'): ?>
					<p>
					    <a href="<?php if(isset($node->field_world_spif_link[$node->language][0]['value'])) { echo $node->field_world_spif_link[$node->language][0]['value']; } ?>">
					    	<?php
					    	    $field = field_get_items('node', $node, 'field_spif_image');
					    	    print render(field_view_value('node', $node, 'field_spif_image', $field[0], array('settings' => array('image_style' => 'feature_tab'))));
					    	?>
					    </a>
					</p>
					<h4><a href="<?php if(isset($node->field_world_spif_link[$node->language][0]['value'])) { echo $node->field_world_spif_link[$node->language][0]['value']; } ?>">	
					    <?php if(isset($node->field_spif_title[$node->language][0]['value'])):?>
					    	<?php echo $node->field_spif_title[$node->language][0]['value']; ?>
					    <?php endif; ?>
					</a></h4>
					<?php echo $node->body[LANGUAGE_NONE][0]['value']; ?>
				<!-- Standard SPIF ============== -->
				<?php else: ?>		
				 	<p>
				 		<a href="<?php if(isset($node->field_spif_link[$node->language][0]['value'])) { echo $node->field_spif_link[$node->language][0]['value']; } ?>">
				 			<?php
				 			    $field = field_get_items('node', $node, 'field_standard_spif_image');
				 			    print render(field_view_value('node', $node, 'field_standard_spif_image', $field[0], array('settings' => array('image_style' => 'feature_tab'))));
				 			?>
				 		</a>
				 	</p>
				    <h4><a href="<?php if(isset($node->field_spif_link[$node->language][0]['value'])) { echo $node->field_spif_link[$node->language][0]['value']; } ?>">	
				    	<?php if(isset($node->field_spif_headline[$node->language][0]['value'])):?>
				    		<?php echo $node->field_spif_headline[$node->language][0]['value']; ?>
				    	<?php endif; ?>
				    </a></h4>
				    <?php echo $node->body[LANGUAGE_NONE][0]['value']; ?>
				<?php endif; ?>
				</li>
		<?php endforeach; ?>
    </ul>
	<!-- End Non Mobile -->
<?php endif; ?>

























<!-- Start Mobile -->

<?php /*
<ul class="feed mobileShow">
	<?php foreach($nodes as $node): ?>
		<li>
			<?php if($node->type == 'world_spif'): ?>
				<!-- World SPIF ============= -->
				<p>
				    <a href="<?php if(isset($node->field_world_spif_link[$node->language][0]['value'])) { echo $node->field_world_spif_link[$node->language][0]['value']; } ?>">
				    	<?php
				    	    $field = field_get_items('node', $node, 'field_spif_image');
				    	    print render(field_view_value('node', $node, 'field_spif_image', $field[0], array('settings' => array('image_style' => 'feature_tab'))));
				    	?>
				    </a>
				</p>
				<h4><a href="<?php if(isset($node->field_world_spif_link[$node->language][0]['value'])) { echo $node->field_world_spif_link[$node->language][0]['value']; } ?>">	
				    <?php if(isset($node->field_spif_title[$node->language][0]['value'])):?>
				    	<?php echo $node->field_spif_title[$node->language][0]['value']; ?>
				    <?php endif; ?>
				</a></h4>
				<?php echo $node->body[LANGUAGE_NONE][0]['value']; ?>
			<?php else: ?>		
			    <!-- Standard SPIF ============== -->
				<p>
				    <a href="<?php if(isset($node->field_spif_link[$node->language][0]['value'])) { echo $node->field_spif_link[$node->language][0]['value']; } ?>">
				    	<?php
				    	    $field = field_get_items('node', $node, 'field_standard_spif_image');
				    	    print render(field_view_value('node', $node, 'field_standard_spif_image', $field[0], array('settings' => array('image_style' => 'feature_tab'))));
				    	?>
				    </a>
				</p>
				<h4><a href="<?php if(isset($node->field_spif_link[$node->language][0]['value'])) { echo $node->field_spif_link[$node->language][0]['value']; } ?>">	
				    <?php if(isset($node->field_spif_headline[$node->language][0]['value'])):?>
				    	<?php echo $node->field_spif_headline[$node->language][0]['value']; ?>
				    <?php endif; ?>
				</a></h4>
				<?php echo $node->body[LANGUAGE_NONE][0]['value']; ?>
			<?php endif; ?>
		</li>
	<?php endforeach; ?>
</ul>
<!-- End Mobile --> */ ?>



