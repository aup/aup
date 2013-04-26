<?php 
	/*
	 * Block Wrapper for Home Page Events Listing
	*/
?>

<div class="fullWidth events">
    <div class="feedTitle">
    	<h3>Events</h3>
        <div class="more">
        	<a href="/aup/news-events">View more</a>
        </div>
    </div>
	<ul class="feed">
		<?php foreach ($rows as $id => $row): ?>
	    	<?php print $row; ?>
		<?php endforeach; ?>
	</ul>
</div>