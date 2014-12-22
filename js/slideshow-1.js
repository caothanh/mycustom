/* 
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

jQuery(document).ready(function($) 
{//start code
    //alert("ass");
    //var html_slideshow = $(".view-footer").html();
    //$(".views-slideshow-controls-bottom").html(html_slideshow);
    
    $("#widget_pager_bottom_slideshow_1-page ul li").click(function(e)
    {
        var index = $(this).index();
        Drupal.viewsSlideshow.action({ "action": 'goToSlide', "slideshowID": "slideshow_1-page", "slideNum": index });
    })
    
//end code
})
 
