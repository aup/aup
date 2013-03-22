<div class="header">
    <div class="banner">
        <img src="<?php echo base_path().path_to_theme(); ?>/images/banner1.jpg" alt=""/>
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
        	<ul>
            	<li><a href="/aup/about">About</a></li>
            	<li><a href="#">Academics</a></li>
            	<li><a href="/aup/admissions">Admissions</a></li>
            	<li><a href="#">Student Life</a></li>
            	<li><a href="/aup/news">News &amp; Events</a></li>
            	<li><a href="/aup/support">Support AUP</a></li>
            </ul>
        </div>
        <div class="utility">
        	<ul>
            	<li><a href="#">Contact Us</a></li>
                <li class="last"><a href="#">Visit AUP</a></li>
            </ul>
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
                <ul>
                    <li><a href="#">About</a></li>
                    <li><a href="#">Academics</a></li>
                    <li><a href="#">Admissions</a></li>
                    <li><a href="#">Student Life</a></li>
                    <li><a href="#">News &amp; Events</a></li>
                    <li><a href="#">Support AUP</a></li>
                    <li><a href="#">Contact Us</a></li>
                    <li><a href="#">Visit AUP</a></li>
                </ul>
            </div>
            <div class="infomenulist">
            	
            </div>
            <div class="siteSearch">
            
            </div>
        </div>
    </div>
</div>