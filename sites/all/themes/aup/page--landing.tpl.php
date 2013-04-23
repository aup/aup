<?php 
	/*
	 * Page template for Support (aka Giving or Landing)
	*/
?>

<div class="outer page-landing">
	<div class="outerBg">
    	<?php include('_includes/header.php'); ?>
        <!-- Start of wrapper -->
        <div class="wrapper">
        	<div class="breadcrumb">
            	<?php echo $breadcrumb; ?>
            </div>
            
            <!-- Start of Content -->
            <div class="page-content">            	
            	<div class="surround">
            	
            		<!-- Start Slideshow -->
            		<?php if ($page['support_slideshow']): print render($page['support_slideshow']); endif; ?>
            		<!-- End Slideshow -->	
            		
                    <div class="container">

                    	<div class="statement">
                        	<div class="text">
                            	<?php echo render($page['content']); ?>
                            </div>
                            <!-- Start Gift SPIF -->
                    		<?php if ($page['support_gift']): ?>
                    		    <div class="info">
	                    	    	<?php print render($page['support_gift']); ?>
                    		    </div>
                    		<?php else: ?>
                    			<style type="text-css">
                    		    	.statement .text { width:100%; }
                    		    </style>
                    		<?php endif; ?>
                    		<!-- End Gift SPIF -->                        
                        </div>
                    </div>
                    <div class="container">
                    	<div class="cols4">
                            <div class="col">
                            	<?php if ($page['support_spif_1']): print render($page['support_spif_1']); endif; ?>
                            </div>
                            <div class="col">
                               <?php if ($page['support_spif_2']): print render($page['support_spif_2']); endif; ?>
                            </div>
                            <div class="col">
                               <?php if ($page['support_spif_3']): print render($page['support_spif_3']); endif; ?>
                            </div>
                            <div class="col noMargin">
                            	<?php if ($page['support_spif_4']): print render($page['support_spif_4']); endif; ?>
                            </div>
                        </div>
                    </div>
                </div>
                
    			<div class="fullWidth mix">
                    <ul class="feed">
                        <li class="newsSingle">
                            <div class="feedTitle">
                                <h3>News <a href="/aup/news-feed" class="rss"><img src="<?php echo base_path().path_to_theme(); ?>/images/rss.png" alt=""/></a></h3>
                                <div class="more">
                                    <a href="/aup/news-events">View more</a>
                                </div>
                            </div>
                            <?php if ($page['giving_1']): print render($page['giving_1']); endif; ?>
                        </li>
                        <li class="eventSingle">
                            <div class="feedTitle">
                                <h3>Events <a href="/aup/events-feed" class="rss"><img src="<?php echo base_path().path_to_theme(); ?>/images/rss.png" alt=""/></a></h3>
                                <div class="more">
                                    <a href="/aup/news-events">View more</a>
                                </div>
                            </div>
                            <?php if ($page['giving_2']): print render($page['giving_2']); endif; ?>
                        </li>
                        <li class="fbSingle">
                             <h5>
                                <img src="<?php echo base_path().path_to_theme(); ?>/images/facebook32.png" alt="" />
                                <span>Facebook</span>
                                <a href="#">View more</a>
                             </h5>
                             <p>Have you seen the website dedicated to AUP's 50th anniversary? Check it out! http://50years.aup.edu/ There are two 50th anniversary celebration events in November: Alumni Event in San Francisco- 1 November, 2012 Alumni... <a href="#">Read More</a></p>
                        </li>
                    </ul>
                </div>
            </div>
            
            <!-- End of Content -->
            <!-- Start of footer -->
            <?php include('_includes/footer.php'); ?>
            <!-- End of Footer -->
        </div>
        <!-- End of wrapper -->
    </div>
</div>