<?php 
	/*
	 * Block for News Page Events Column
	*/
	//foreach($fields as $key => $val)
	//print $key . ' ';
	//print_r($fields['field_event_date']);
?>
<li>
 	<div class="date">
 		<?php 
 			$date = $fields['field_event_date']->content; 
 			$date = strip_tags($date);
 			$pieces = explode(" ", $date);
 		?>
     	<span><?php echo $pieces[0]; ?></span>
        <em><?php echo $pieces[1]; ?></em>
     </div>
     <div class="info">
    	 <h4><a href="<?php echo $fields['path']->content; ?>"><?php echo $fields['title']->content; ?></a> <span><?php echo $fields['field_event_time']->content; ?></span></h4>
	     <p><?php echo $fields['body']->content; ?></p>
     </div>
</li>