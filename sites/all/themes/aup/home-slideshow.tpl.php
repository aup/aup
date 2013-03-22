I am the home template file
<?php if(!empty($nodes)): ?>


		
			<?php foreach($nodes as $node): ?>
			
	    		I am in the featured node loop
				<h2><?php echo $node->field_slideshow_heading[LANGUAGE_NONE][0]['value']; ?></h2>
	            
	       
	        <?php endforeach; ?>

	
<?php endif; ?>