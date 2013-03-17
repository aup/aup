<div class="outer">
	<div class="outerBg">
    	<div class="header">
            <div class="banner">
                <img src="<?php echo base_path().path_to_theme(); ?>/images/banner1.jpg" alt=""/>
            </div>
            <div class="audience">
                <ul>
                    <li><a href="#">Prospective students</a></li>
                    <li><a href="#">Current Students</a></li><li><a href="#">Faculty &amp; Staff</a></li><li><a href="#">Parents &amp; Families</a></li><li><a href="#">Alumni</a></li><li><a href="#">Employers</a></li>
                </ul>
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
                    <a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/logo.png" alt="" /></a>
                    <div class="mobileShow mobileSearchButton"><a href="#"><span>Search</span></a></div>
                </div>
            	<div class="topic">
                	<ul>
                    	<li><a href="#">About</a></li>
                    	<li class="selected"><a href="#">Academics</a></li>
                    	<li><a href="#">Admissions</a></li>
                    	<li><a href="#">Student Life</a></li>
                    	<li><a href="#">News &amp; Events</a></li>
                    	<li><a href="#">Support AUP</a></li>
                    </ul>
                </div>
                <div class="utility">
                	<ul>
                    	<li><a href="#">Contact Us</a></li>
                        <li class="last"><a href="#">Visit AUP</a></li>
                    </ul>
                    <div class="siteSearch">
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
        <!-- Start of wrapper -->
        <div class="wrapper">
        	<div class="breadcrumb full">
            	<?php echo $breadcrumb; ?>
            </div>
            <!-- Start of Content -->
            <div class="page-content">
            	<div class="surround">
                    <div class="mainContent full bodyCopy">
                        <div class="container inner">
                            <div class="pageTitle">
                                <?php if($title): echo '<h1>'.$title.'</h1>'; endif ?>
                                <div class="share">
                                    <a href="#">Share This</a>
                                </div>
                            </div>
                        </div>
                        <div class="container inner">
			            	<?php if ($messages): echo $messages; endif; ?>
	            		</div>
                        <div class="container inner">
	                        <?php if ($tabs): echo render($tabs); endif; ?>
	                        <?php if($action_links): ?><ul class="action-links"><?php print render($action_links); ?></ul><?php endif; ?>
                            <?php echo render($page['content']); ?>
                        </div>

                    </div>
            	</div>
            </div>
            <!-- End of Content -->
            <!-- Start of footer -->
            <div class="footer">
    			<h6>&copy; 2013 THE AMERICAN UNIVERSITY OF PARIS</h6>
                <ul>
                	<li><a href="#">Maps &amp; Directories</a></li>
                	<li><a href="#">Site A to Z</a></li>
                	<li><a href="#">MyAUP</a></li>
                	<li class="last"><a href="#">Employment Opportunities</a></li>
                </ul>
                <ul class="icons">
                	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/facebook20.png" alt=""/></a></li>
                	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/twitter20.png" alt=""/></a></li>
                	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/youtube20.png" alt=""/></a></li>
                	<li><a href="#"><img src="<?php echo base_path().path_to_theme(); ?>/images/rss20.png" alt=""/></a></li>
                </ul>
            </div>
            <!-- End of Footer -->
        </div>
        <!-- End of wrapper -->
    </div>
</div>

