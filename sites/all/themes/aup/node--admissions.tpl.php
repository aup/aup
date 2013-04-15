<?php 
	/*
	 * Node Template for Admissions
	*/
?>

<?php print $node->body[LANGUAGE_NONE][0]['value']; ?>

<?php if($node->field_bottom_bar_text[LANGUAGE_NONE][0]['value']): ?>
	<script type="text/javascript">
	//<![CDATA[
		jQuery(document).ready(function(){
			jQuery('.admissions-bottom-source .studentInfo').appendTo('.admissions-bar-destination');
		});
	//]]>
	</script>
						
	<div class="admissions-bottom-source">
		 <div class="studentInfo">            
			<a href="<?php print $node->field_bottom_bar_link[LANGUAGE_NONE][0]['value']; ?>"><?php print $node->field_bottom_bar_text[LANGUAGE_NONE][0]['value']; ?></a>          	
		</div>
	</div>
<?php endif; ?>