<h4><a href="<?php print $url; ?>"><?php echo $title; ?></a></h4>
<h6>
	<div class="date-in-parts">
	   <span class="day"><?php  echo date("j", $result['node']->created); ?></span>
	   <span class="month"><?php echo date("M", $result['node']->created); ?></span>
	   <span class="year"><?php echo date("Y", $result['node']->created); ?></span>
	</div>
</h6>