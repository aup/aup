<div class="footer">
	<h6>&copy; 2013 THE AMERICAN UNIVERSITY OF PARIS</h6>
    <!--<ul>
    	<li><a href="#">Maps &amp; Directories</a></li>
    	<li><a href="#">Site A to Z</a></li>
    	<li><a href="#">MyAUP</a></li>
    	<li class="last"><a href="#">Employment Opportunities</a></li>
    </ul>-->
    <?php if ($page['footer_links']): print render($page['footer_links']); endif; ?>
    <ul class="icons">
    	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/facebook20.png" alt=""/></a></li>
    	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/twitter20.png" alt=""/></a></li>
    	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/youtube20.png" alt=""/></a></li>
    	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/rss20.png" alt=""/></a></li>
    </ul>
</div>