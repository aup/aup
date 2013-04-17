<?php 
	/*
	 * View For Events listing on Events Page
	*/
?>

<li>
 	<div class="date">
 		<?php 
 			$date = $fields['field_event_date']->content; 
 			$date = strip_tags($date);
 			$pieces = explode(" ", $date);
 		?>
     </div>
     <div class="info">
    	 <h4><a href="<?php echo $fields['path']->content; ?>"><?php echo $fields['title']->content; ?></a></h4>
    	 <p><strong><?php echo $date .' - '.$fields['field_event_time']->content; ?></strong></p>
	     <p><?php echo $fields['body']->content; ?></p>
     </div>
</li>