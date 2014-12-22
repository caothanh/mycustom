/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
jQuery(document).ready(function($) 
{//start code
  //var $mean_bar = $('body.mean-container').find('.mean-bar');
  var $comic_navi = $('#comic-navi');
  $comic_navi.change(function(e) {
    var url = $(this).val();
    window.location = url;
    
  });
  
  var $mobie_nav = $('.navi-mobie');
  var $mobie_menu = $mobie_nav.find('.navbar-nav');
  var $mobbie_icon = $mobie_nav.find('.icon');
  var $search_box = $mobie_nav.find('.search_box');
  
  $search_box.click(function(e) {
    //alert('abc');
    e.stopPropagation();
    //e.preventDefault();
    $mobie_menu.show();
    $(this).show();
  })
  
  
  $mobbie_icon.on('swipedown',function(){
    $mobie_menu.slideDown(200);
    $mobie_nav.css('background', '#000');
    $search_box.show()
  })
  
  $mobie_menu.on('swipeup',function(){
    $mobie_menu.slideUp(200);
    $mobie_nav.css('background', 'rgba(0, 0, 0, 0.7)');
    $search_box.hide();
  })
  
  $mobie_nav.click(function(e) {
    //$mobie_menu.toggle();
    //alert('abc');
    if($mobie_menu.is(":visible")) {
      $mobie_menu.slideUp(100);
      $mobie_nav.css('background', 'rgba(0, 0, 0, 0.7)');
      $search_box.hide();
    }
    else {
      $mobie_menu.slideDown(100);
      $mobie_nav.css('background', '#000');
      $search_box.show();
    }
  })
  
  $('#mycustom-main-content').show();
  
  var h = document.documentElement.clientHeight;
  $('#flexslider_views_slideshow_hentai_mysql-page_8').find('li').css({'display': 'table', 'min-height' : h +'px'});
  
  var url = document.URL;
  if(url.indexOf('nozoki') !==-1) {
    var $chaps = $('#chapter');
    $chaps.find('img').each(function(e) {
      var src = $(this).attr('src');
      if (src.indexOf('imgur') !== -1) {
        src = src.replace('s.', '.');
      }
      $(this).attr('src', src);
    })
  }
  
  var $chaps = $('#block-system-main').find('.view-id-chapters');
  //$chaps.hide();
  $chaps.find('a').each(function(e) {
    var link = $(this).attr('href');
    link = 'http://adf.ly/7057492/' + encodeURIComponent('http://www.ihentai69.com' + link);
    //window.console.log(link);
    $(this).attr('href', link);
    //$(this).attr('target', '_blank');
  })
});

