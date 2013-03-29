<?php 
	/*
	 * Block Wrapper for Home Page Events Listing
	*/
?>
<ul class="feed">
	<?php foreach ($rows as $id => $row): ?>
    	<?php print $row; ?>
	<?php endforeach; ?>
</ul>