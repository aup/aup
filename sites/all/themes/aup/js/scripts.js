(function ($) {
$(document).ready(function() {
	 var temp =  $(".main .siteSearch").html();
	 $(".mobileHeader .siteSearch").html(temp);
	 //temp =  $(".main .topic").html();
	 //$(".mobileHeader .topic").html(temp);
	 temp =  $(".audience").html();
	 $(".mobileHeader .siteSearch").html(temp);
	 temp =  $(".secondaryNav").html();
	 $(".mobileHeader .infomenulist").html(temp);
	 
	 
	 
});

$(document).ready(function() {
	function setInputAction(cssClass, val){
  		$(cssClass).focus(function() {if(this.value == val){this.value =""}});
  		$(cssClass).blur(function() {if(this.value == ""){this.value = val}});
	}
	setInputAction('.txtSiteSearch', 'Search');
});

$(document).ready(function() {
	var selected = 0;
	var anim = 600;

	$(".mobileHeader .menu a").click(function(){
		if(selected == 1){
			$(".mobileHeader .topic").slideUp(anim, 0);
			selected = 0;
		}
		else{
			$(".mobileHeader .infomenulist").slideUp(anim, 0);
			$(".mobileHeader .siteSearch").slideUp(anim, 0);
			$(".mobileHeader .topic").slideDown(anim, 0);
			selected = 1;
		}
		return false;
	});
	
	$(".mobileHeader .infomenu a").click(function(){
		if(selected == 2){
			$(".mobileHeader .infomenulist").slideUp(anim, 0);
			selected = 0;
		}
		else{
			$(".mobileHeader .topic").slideUp(anim, 0);
			$(".mobileHeader .siteSearch").slideUp(anim, 0);
			$(".mobileHeader .infomenulist").slideDown(anim, 0);
			selected = 2;
		}
		return false;
	});
	
	$(".mobileHeader .search a").click(function(){
		if(selected == 3){
			$(".mobileHeader .siteSearch").slideUp(anim, 0);
			selected = 0;
		}
		else{
			$(".mobileHeader .infomenulist").slideUp(anim, 0);
			$(".mobileHeader .topic").slideUp(anim, 0);
			$(".mobileHeader .siteSearch").slideDown(anim, 0);
			selected = 3;
		}
		return false;
	});
	
	var mobileSearchDisplay = false;
	$(".mobileSearchButton a").click(function(){
		if(mobileSearchDisplay){
			$(this).removeClass("btnOn");
			mobileSearchDisplay = false;
			$(".mobileSiteSearch").slideUp(300);	
		}
		else{
			$(this).addClass("btnOn");
			mobileSearchDisplay = true;	
			$(".mobileSiteSearch").slideDown(300);
		}
		
	});
	
});


$(document).ready(function() {
	var gcount = 1;
	$(".gTabs").children().each(function() {
		addGatewayClickEvent($(this), gcount);
		gcount++;
   	 });
	 function addGatewayClickEvent(listitem, counter){
		 $(listitem.children()).click(function() {toggleGateway(counter); return false;});
	 }
	function toggleGateway(id){
		$(".gTabs li").removeClass("selected");
		$(".gInner").removeClass("selected");
		var contentClass = ".gInner" + id;
		var menuClass = ".gTabs .tab-" + id;
		$(contentClass).addClass("selected");
		$(menuClass).addClass("selected");	
	}
	if ($(".gatewayFeature").html() != null){
		var gatewaySections = $('.gatewayFeature .gTabs').children().length;
		//alert(gatewaySections);
		if(gatewaySections > 0){
			var sb = "";
			for(var i = 1; i <= gatewaySections; i++){
				sb += '<div class="accordion accordion' + i + '">';
				sb += '<div class="accTitle"><a href="#" rel="' + i + '">' + $('.gTabs .tab-' + i + ' a').html() + '</a></div>';
				sb += '<div class="accContent">' + $('.gContent .gInner' + i).html() + '</div>';
				sb += '</div>';
			}
			$('.gatewayFeature').after('<div class="mobileGatewayFeature">' + sb + '</div>');
			$('.accordion1 .accContent').show();
			$('.accordion1 .accContent').addClass("open");
			$('.accordion .accTitle a').click(function() { accordionSwitch($(this).attr("rel"));return false;});
		}
	}
	
	
	if ($(".accordionPod").html() != null){
		$('.accordionPod .accTitle a').click(function() { accordionSwitch($(this).attr("rel"));return false;});
	}
	function accordionSwitch(id){
		if($('.accordion' + id + ' .open').html() == null){
			$('.accordion .open').removeClass("open");
			$('.accordion .tabOpen').removeClass("tabOpen");
			$('.accordion' + id + ' .accContent').addClass("open");
			$('.accordion' + id + ' .accTitle').addClass("tabOpen");
			$('.accordion .accContent').slideUp(300);
			$('.accordion' + id + ' .accContent').slideDown(300);
		}
	}
	
});



/** social pod tabs **/
$(document).ready(function() {
	var gcount = 1;
	$(".podSocial .gTabs").children().each(function() {
		addSocialEvent($(this), gcount);
		gcount++;
   	 });
	 function addSocialEvent(listitem, counter){
		 $(listitem.children()).click(function() {toggleSocial(counter); return false;});
	 }
	function toggleSocial(id){
		$(".podSocial .gTabs li").removeClass("selected");
		$(".podSocial .gInner").removeClass("selected");
		var contentClass = ".podSocial .gInner" + id;
		var menuClass = ".podSocial .gTabs .tab-" + id;
		$(contentClass).addClass("selected");
		$(menuClass).addClass("selected");	
	}
});
})(jQuery);