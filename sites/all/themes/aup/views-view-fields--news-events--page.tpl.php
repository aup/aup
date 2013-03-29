<?php 
	/*
	 * View For News on News & Events Page
	*/
	//foreach($fields as $key => $val)
	//print $key . ' ';
?>

<li>
   <h4><a href="<?php echo $fields['path']->content; ?>"><?php echo $fields['title']->content; ?></a> <span><?php echo $fields['created']->content; ?></span></h4>
   <p><?php echo $fields['body']->content; ?></p>
</li>