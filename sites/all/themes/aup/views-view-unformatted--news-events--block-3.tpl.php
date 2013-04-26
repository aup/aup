<?php 
	/*
	 * Block Wrapper for Home Page News Listing
	*/
?>

<div class="fullWidth news">
	<div class="feedTitle">
	    <h3>News</h3>
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