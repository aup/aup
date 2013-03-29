<?php 
	/*
	 * Block Wrapper for News Page Events Column
	*/
?>

<ul class="feed">
	<?php foreach ($rows as $id => $row): ?>
    	<?php print $row; ?>
	<?php endforeach; ?>
</ul>