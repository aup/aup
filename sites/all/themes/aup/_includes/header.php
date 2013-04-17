<div class="header">
    <div class="banner">
    	<?php if ($page['banner']): print render($page['banner']); endif; ?>
    </div>
    <div class="audience">
		<?php print render($page['top_links']);?>
    </div>
    <div class="title">
    	<p>At home <em>in</em> the world</p>
    </div>
    <div class="main">
        <div class="mobileShow">
            <div class="mobileSiteSearch">
                <form method="post" action="#">
                    <fieldset>
                        <legend>Search</legend>
                        <label for="txtSiteSearch">Search</label>
                        <input type="text" class="txtSiteSearch" id="txtSiteSearch" value="Search" />
                        <input type="submit" class="btnSiteSubmit" value="" />
                    </fieldset>
                </form>
            </div>
        </div>
        <div class="logo">
            <a href="<?php echo base_path(); ?>"><img src="<?php echo base_path().path_to_theme(); ?>/images/logo.png" alt="" /></a>
            <div class="mobileShow mobileSearchButton"><a href="#"><span>Search</span></a></div>
        </div>
    	<div class="topic">
	    	<?php if($primary_navigation): echo $primary_navigation; endif; ?>
        </div>
        <div class="utility">
        	<?php if ($page['search_menu']): print render($page['search_menu']); endif; ?>
            <div class="siteSearch">
				<?php if ($page['header_search']): print render($page['header_search']); endif; ?>
            </div>
        </div>
        <div class="section">
        	<?php if($title): echo '<p>'.$title.'</p>'; endif ?>
        </div>
    </div>
    <div class="mobileShow mobileHeader">
        <div class="tabs blockBg">
        	<div class="menu">
            	<a href="#">Menu</a>
            </div>
        	<div class="infomenu">
            	<a href="#">This section</a>
            </div>
        	<div class="search">
            	<a href="#">Info for</a>
            </div>
        </div>
        <div class="ddContainer">
            <div class="topic">
                <?php if($primary_navigation): echo $primary_navigation; endif; ?>
            </div>
            <div class="infomenulist">
            	
            </div>
            <div class="siteSearch">
            
            </div>
        </div>
    </div>
</div>