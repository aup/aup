<?php 
	/*
	 * View for News & Events Page
	*/
?>

<ul class="feed">
	<?php if($rows): ?>
		<?php print $rows; ?>
	<?php endif; ?>
</ul>

<div class="clear"></div>
<div class="post-pager">
	<?php if ($pager): ?>
		<?php print $pager; ?>
	<?php endif; ?>
</div>