<?php 
	/*
	 * Node Template for Admissions
	*/
?>

<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>

<?php if(!empty($node->field_bottom_bar_text)): ?>
	<script type="text/javascript">
	//<![CDATA[
		jQuery(document).ready(function(){
			jQuery('.admissions-bottom-source .studentInfo').appendTo('.admissions-bar-destination');
		});
	//]]>
	</script>
						
	<div class="admissions-bottom-source">
		 <div class="studentInfo">
		 	<?php if(!empty($node->field_bottom_bar_link)): ?>            
				<a href="<?php print $node->field_bottom_bar_link[LANGUAGE_NONE][0]['value']; ?>">
			<?php endif; ?>
				<?php if(!empty($node->field_bottom_bar_text)): ?>
					<?php print $node->field_bottom_bar_text[LANGUAGE_NONE][0]['value']; ?>
				<?php endif; ?>
			<?php if(!empty($node->field_bottom_bar_link)): ?> 
				</a>     
		    <?php endif; ?> 	
		</div>
	</div>
<?php endif; ?>