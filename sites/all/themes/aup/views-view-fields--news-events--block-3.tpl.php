<?php 
	/*
	 * Block for Home Page News Listing
	*/
	//foreach($fields as $key => $val)
	//print $key . ' ';
	//print_r($fields['field_event_date']);
?>
<li>
   <h4><a href="<?php echo $fields['path']->content; ?>"><?php echo $fields['title']->content; ?></a> <span><?php echo $fields['created']->content; ?></span></h4>
   <p><?php echo $fields['body']->content; ?></p>
</li>