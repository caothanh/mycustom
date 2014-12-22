<?php
define('PHOTO_DIR', '/var/www/HT/');

/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
function mycustom_exclude_img() {
  $arr[] = 'http://img.thiendia.com/server5/images/23535331075350883682.png';
  $arr[] ='http://i.imgbox.com/acq2TcUJ.jpg';
  $arr[] = 'http://thiendia.com/diendan/blak_ice/buttons/post_thanks.gif';
  $arr[] = 'http://upload69.net/images/kpgut0uk6xdsf1zeg5zf.gif';
  $arr[] = 'http://s5.postimg.org/mgvwc9r47/image.jpg';
  return $arr;
}

// image standard
function mycustom_imgalt($src, $title = '') {
  $alt = $title .' Ảnh sex, ảnh khỏa thân, ảnh chụp lén, ảnh nude, truyện sex loạn luân,'
      . ' anh sex, anh khoa than, anh nude, anh chup len, truyen loan luan';
  return "<img src ='' data-src='$src' alt='$alt'>";
}

// function 

// Page analystic
function mycustom_page_ana($link, $title, $content, $img = 'img', $attr ='src', $ex = '') {
  $html = file_get_html($link);
  $title = $html->find($title, 0)->plaintext;
  $content = $html->find($content, 0);
  $logo = '';
  
  $body = array();
  //$dem == 0;
  foreach($content->find($img) as $img) {
//    if($dem == 0) {
//      $logo = $img->{$attr};
//    }
//    $src = $ex . $img->{$attr};
//    if(strpos($src, '.') !== false) {
//      $body .= "<div class='pic'><a class='colorbox-load' href='$src' rel='test'>" 
//        . mycustom_imgalt($src, $title) . "</a></div>";
//    }
//    
//    ++$dem;
    if(strpos($img->{$attr}, '.') !== false)
    $body[] = $img->{$attr};
  }
  
  $arr['title'] = $title;
  $arr['logo'] = $logo;
  $arr['body'] = $body;
  return $arr;
}




// Create new box_anh post
function mycustom_create_box_anh($content, $title, $logo) {
  $node = new stdClass();
  $node->type = 'box_anh';
  $body = "<div id='pics'>" . $content . '</div>';
  
  $file_img_name = str_replace(' ', '-', $title);
  //$logofile = file_save_data(file_get_contents($logo), 'public://anh-sex-' . $file_img_name . '.png', );
  $node->field_image_box['und'][0]['fid'] = $logofile->fid;
  
  $node->body['und'][0]['value'] = $body;
  $node->body['und'][0]['format'] = 'full_html';
  $node->title = $title;
  $node->status = 1;
  node_save($node);
}



// Get images from blogspot
function mycustom_box_anh_blogger($link, $title='.post-title', $content='.posts p', $img = 'img', $attr ='src',$ex = '') {
  $arr = mycustom_page_ana($link, $title, $content, $img, $attr);
  //mycustom_create_box_anh($arr['body'], $arr['title'], $arr['logo']);
  
  $dir = PHOTO_DIR . $arr['title'];
  
  $find = array(
      'small',
      't10.',
      't7.'
  );

  $rep = array(
      'big',
      'i10.',
      'i7.'
  );
  mkdir($dir);
  $dem = 0;
  foreach($arr['body'] as $img) {
      ++$dem;
    $img = $ex.'/'. $img;
    $img = str_replace($find, $rep, $img);
    $img = preg_replace('/\?.*/', '', $img);
    $img = trim($img, '/');
    mycustom_save_img($img, $dir, $dem);
  }
  //chmod(file,mode);
}


function mycustom_box_anh_pururin_page($link) {
  $html = file_get_html($link);
  $img = $html->find('a.image-next', 0)->find('img', 0)->src;
  return "http://pururin.com" . $img;
}

function mycustom_box_anh_pururin($link, $title='.post-title', $content='.posts p', $find='', $re='', $ex='') {
  $arr = mycustom_page_ana($link, $title, $content, 'a', 'href');
  //mycustom_create_box_anh($arr['body'], $arr['title'], $arr['logo']);
  
  $dir = PHOTO_DIR . time();

  mkdir($dir);
  foreach($arr['body'] as $img) {
    $img = $ex.'/'. $img;
    //$img = str_replace($find, $re, $img);
    //$img = preg_replace('/\?.*/', '', $img);
    //$img = trim($img, '/');
    $img = mycustom_box_anh_pururin_page($link);
    mycustom_save_img($img, $dir);
  }
  //chmod(file,mode);
}



function mycustom_save_img($file, $dir, $dem = '') {
  //$url = 'http://example.com/image.php';
  //$img = '/my/folder/flower.gif';
  $dir = $dir .'/' . $dem . '.jpg';
  file_put_contents($dir, file_get_contents($file));
  //mycustom_addtext_img($dir, $dir);
  //chmod($dir,'777');
  //
}


// Get image from moonhug.com
function mycustom_getmonhug($link) {
  $link = $link;
//  $node = new stdClass();
//  $node->type = 'box_anh';
//  $body = "<div id='pics'>";
  
  $html = file_get_html($link);
  $title = $html->find('.entry-title',0)->plaintext;
   
  $title = substr($string, 0,10);
  
  $dir = '/srv/www/htdocs/Photos/Anh-dep - ' . $title . ' - '. time();
  
  mkdir($dir);
  
  
  
//  $img = $html->find('.post-content',0)->find('img',0);
//  
//  
//  $file_img_name = str_replace(' ', '-', $title);
//  $logofile = file_save_data(file_get_contents($img->src), 'public://anh-sex-' . $file_img_name . '.png');
//  $node->field_image_box['und'][0]['fid'] = $logofile->fid;
  
  foreach ($html->find('.post-content', 0)->find('img') as $img) {
    if (strpos($img->src, '.gif') == false) {
      mycustom_save_img($img->src, $dir);
      
    }
      //$body .= "<div class='pic'><a class='colorbox-load' href='$img->src' rel='test'>" . mycustom_imgalt($img->src, $title) . "</a></div>";
  }

  $page_link = $html->find('.page-links',0);
  $dem = 0;
  
  $links = $page_link->find('a');
  $num = count($links);
  
  for($i=2; $i<=$num +1; $i++) {
    $href = $link . '/' .$i;
    //dsm($href);
    $page_html = file_get_html($href);
    if ($page_html) {
      foreach ($page_html->find('.post-content', 0)->find('img') as $img) {
        if (strpos($img->src, '.gif') == false) {
          mycustom_save_img($img->src, $dir);
        }
          //$body .= "<div class='pic'><a class='colorbox-load' href='$img->src' rel='test'>" . mycustom_imgalt($img->src, $title) . "</a></div>";
      }
    }
  }
  
  
//  $body .= '</div>';
//  $node->body['und'][0]['value'] = $body;
//  $node->body['und'][0]['format'] = 'full_html';
//  $node->title = $title;
//  $node->status = 1;
//  node_save($node);
}


//// Get image form thiendia's thread
//function mycustom_get_thiendia_tid($tid) {
//   $node = new stdClass();
//   $node->type = 'box_anh';
//   
//   // Init body content
//   $body = "<div id='pics'>";
//   
//   $link = 'http://thiendia.com/diendan/showthread.php?t=' . $tid;
//   
//   $html = file_get_html($link);
//   
//   $wrap_posts = $posts = $html->find('#posts', 0);
//   
//   $step = 0;
//   
//   foreach($wrap_posts->find('table.tborder') as $postss) {
//    ++$step;
//    
//    $posts = $postss->find('td.alt1', 0);
//    if($step == 1) {
//      $title = $posts->find('h2', 0)->plaintext;
//      $title = str_replace(array('&quot;', '&amp;'), '', $title);
//    }
//    
//    //$dem = 0;
//    foreach ($posts->find('img') as $img) {
//      if (strpos($img->src, "http") !== false && (strpos($img->src, "gif") == false && strpos($img->src, "thiendia") == false)  && !in_array($img->src, mycustom_exclude_img())) {
//        ++$dem;
//        //$img_info = getimagesize($img->src);
//        //if($img_info[0] > 600) {
//         // $w = $img_info[0];
//          $body .= "<div class='pic'><a class='colorbox-load' href='$img->src' rel='test'>" . mycustom_imgalt($img->src, $title) . "</a></div>";
//        //}
//        
//        if ($dem == 2 && $step == 1) {
//          $file_img_name = str_replace(' ', '-', $title);
//          $logofile = file_save_data(file_get_contents($img->src), 'public://anh-sex-' . $file_img_name . '.png');
//          $node->field_image_box['und'][0]['fid'] = $logofile->fid;
//        }
//      }
//    }
//    //break;
//  }
//   
//   
//   //$body .= '</div>';
//   $node->body['und'][0]['value'] = $body;
//   $node->body['und'][0]['format'] = 'full_html';
//   $node->title = $title;
//   $node->status = 1;
//   node_save($node);
//}


// Get image form thiendia's thread
function mycustom_get_thiendia_tid($tid) {
  
   $offset = variable_get('mycustom_box_offset', 0);
   $node = new stdClass();
   $node->type = 'box_anh';
   
   // Init body content
   $body = "<div id='pics'>";
   
   $link = 'http://thiendia.com/diendan/showthread.php?t=' . $tid;
   
   $html = file_get_html($link);
   $posts = $html->find('#posts', 0)->find('table.tborder', 0)->find('td.alt1', 0);
   $title = $posts->find('h2', 0)->plaintext;
   $dem = 0;
   foreach($posts->find('img') as $img) {
     //if(strpos($img->src, "http") !== false && strpos($img->src, "gif") == false) {
     if (strpos($img->src, "http") !== false && (strpos($img->src, "gif") == false && strpos($img->src, "thiendia") == false)  && !in_array($img->src, mycustom_exclude_img())) {
       ++$dem;
       if($dem > $offset) {
         $body .= "<div class='pic'><a class='colorbox-load' href='$img->src' rel='test'>" . mycustom_imgalt($img->src, $title) . "</a></div>";
       }
       
       if($dem == 4) {
        //dsm($img);
         //dsm(getimagesize($img->src)[0] .' - '. getimagesize($img->src)[1] );
        $file_img_name = str_replace(' ', '-', $title);
        $logofile = file_save_data(file_get_contents($img->src), 'public://anh-sex-' . $file_img_name . '.png');
        $node->field_image_box['und'][0]['fid'] = $logofile->fid;
      }
       
       
     }
   }
   $body .= '</div>';
   $node->body['und'][0]['value'] = $body;
   $node->body['und'][0]['format'] = 'full_html';
   $node->title = str_replace('&quot;', '', $title);
   $node->status = 1;
   node_save($node);
   variable_set('mycustom_box_offset', 0);
}

function mycustom_get_tid_page($page) {
  $tids = array();
  $link = 'http://thiendia.com/diendan/forumdisplay.php?f=30?&order=desc&page=' . $page;
  $html = file_get_html($link);
  $ths = $html->find('#threadbits_forum_30', 0);
  
  if($page == 1) {
    $break = 5;
  }
  else {
    $break = 0;
  }
  $dem = 0;
  foreach ($ths->find('tr') as $tr) {
    ++$dem;
    if($dem < $break) {
      continue;
    }
    else {
      $td = $tr->find('td', 0);
      $tid = $td->id;
      $tid = explode('_', $tid);
      $tid = $tid[2];
      $tids[] = $tid;
    }
    
  }
  return $tids;
}

// Get boxanh thiendia form
function mycustom_boxanh_thiendia($form, $form_state) {
  
  $options = array(
    'monhug' => 'MoonHug.com',
    'blogspot' => 'Blogspot.com',
    'jj' => 'jjgirls.com',
    'gravure_idol' => "gravure-idols.com",
    'gravure_idol_href' => "gravure-idols.com Link",
    'milftoon' => "Milftoon",
    'pornxxx' => 'pornxxxcomics.com',
    'hentai2read' => 'Hentai2Read',
    'dochentai' => 'Doc hentai',
    'pururin' => 'pururin.com'
  );
  
  $form['select'] = array(
    '#type' => 'select',
    '#options' => $options
  );
  
  $offset = variable_get('mycustom_box_offset', 0);
  
  $form['link'] = array(
    '#type' => 'textfield',
    '#title' => 'Link',
    '#maxlength' => 500, 
  );
  
  $form['offset'] = array(
    '#type' => 'textfield',
    '#title' => 'Offset',
    '#default_value' => $offset
      //'#maxlength' => 400, 
  );
  
  $form['to'] = array(
    '#type' => 'textfield',
    '#title' => 'To',
    //'#default_value' => $offset
      //'#maxlength' => 400, 
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
    '#submit' => array('mycustom_boxanh_update')
  );

  return $form;
}

function mycustom_boxanh_update($form, $form_state) {
  $select = $form_state['values']['select'];
  $submit = 'mycustom_boxanh_' . $select . '_update';
  $submit($form, $form_state);
}

function mycustom_boxanh_pornxxx_update($form, $form_state) {
  $link = $form_state['values']['link'];
  mycustom_box_anh_blogger($link,'h2.post-title', '.single-post');
}

// Get image from hentai2read
function mycustom_get_hentai2read($link, $num, $title) {
  $dir = PHOTO_DIR . $title;
  mkdir($dir);
  for($i = 1; $i <= $num ; $i++) {
    if($i < 10) {
      $dem = '00' . $i;
    }
    else 
        if($i < 100 && $i >=10) {
            $dem = '0' . $i;
        }
        else 
            if ($i>= 100) {
                $dem = $i;
            }
    $img = $link . '/' . $dem . '.jpg';
    file_put_contents($dir . $dem .'.jpg', file_get_contents($img));
  }
}

// Pull hentai 2 read 
function mycustom_boxanh_hentai2read_update($form, $form_state) {
  $link = $form_state['values']['link'];
  $num = $form_state['values']['offset'];
  $title = $form_state['values']['to'];
  mycustom_get_hentai2read($link, $num, $title);
}
// Pull from dochentai

function mycustom_boxanh_dochentai_update(&$form, &$form_state) {
  $link = $form_state['values']['link'];
  mycustom_box_anh_blogger($link,'h1.post-title', '.post-entry');
}

function mycustom_boxanh_pururin_update(&$form, &$form_state) {
  $link = $form_state['values']['link'];
  $find = $form_state['values']['offset'];
  $re = $form_state['values']['to'];
  mycustom_box_anh_pururin($link, 'h1', '.thumblist',$find, $re,  'http://pururin.com');
}

// Pull image from jjgirls
function mycustom_boxanh_jj_update(&$form, &$form_state) {
  $link = $form_state['values']['link'];
  $form = $form_state['values']['offset'];
  $num = $form_state['values']['to'];
  
  for($i=$form; $i<= $num ; $i++) {
    $al_link = $link.'/'. $i;
    mycustom_box_anh_blogger($al_link, '.L996 h2 b', '.L664', 'a','href', 'http://www.jjgirls.com');
  }
  
}

// get Milftoon comic
// Pull image from gravure-idol
function mycustom_boxanh_milftoon_update(&$form, &$form_state) {
  $link = $form_state['values']['link'];
  mycustom_box_anh_blogger($link,'h2.post-title', '.single-post');
}


// Pull image from gravure-idol
function mycustom_boxanh_gravure_idol_update(&$form, &$form_state) {
  $link = $form_state['values']['link'];
  //$arr = mycustom_page_ana($link, '.L996 h2 b', '.L664', 'a','href', 'http://www.jjgirls.com');
  //mycustom_create_box_anh($arr['body'], $arr['title'], $arr['logo']);
  //mycustom_box_anh_blogger($link);
  mycustom_box_anh_blogger($link,'h1.entry-title', '#gallery-1');
}

// Pull image from gravure-idol
function mycustom_boxanh_gravure_idol_href_update(&$form, &$form_state) {
  $link = $form_state['values']['link'];
  //$arr = mycustom_page_ana($link, '.L996 h2 b', '.L664', 'a','href', 'http://www.jjgirls.com');
  //mycustom_create_box_anh($arr['body'], $arr['title'], $arr['logo']);
  //mycustom_box_anh_blogger($link);
  mycustom_box_anh_blogger($link,'h1.entry-title', '.ngg-galleryoverview', 'a', 'href');
}

// pull image from blog
function mycustom_boxanh_blogspot_update(&$form, &$form_state) {
  $link = $form_state['values']['link'];
  mycustom_box_anh_blogger($link);
}
function mycustom_boxanh_monhug_update(&$form, &$form_state) {
  $link = $form_state['values']['link'];
  mycustom_getmonhug($link);
}

function mycustom_boxanh_thiendia_update(&$form, &$form_state) {
  $tids = $form_state['values']['link'];
  $tids = explode(',', $tids);
  $offset = $form_state['values']['offset'];
  variable_set('mycustom_box_offset', $offset);
  batch_set(mycustom_boxanh_batch_ops($tids));
  //mycustom_get_thiendia_tid($tid);
}
// Clear cache 
function mycustom_boxanh_thiendia_clear_cache(&$form, &$form_state) {
  $data = array();
  cache_set('image_thiendia', null, 'cache_mycustom');
}

// Pull image when submit 
function mycustom_boxanh_thiendia_pull(&$form, &$form_state) {
  //dsm($form_state);
  $from = $form_state['values']['page_from'];
  $to = $form_state['values']['page_to'];
  
  $links = array();
  for($i= $from ; $i< $to ; $i++) {
    $tids = mycustom_get_tid_page($i);
    $links = array_merge($links, $tids);
  }
  
  $pulled = cache_get('image_thiendia','cache_mycustom');
  $new_pulled = array();
  //dsm($links);
  $exclude = trim($form_state['values']['not_pull']);
  $exclude = explode(',', $exclude);
  //dsm($exclude);
  //$giao = array_intersect($links, $exclude);
  if(!$pulled->data) {
    $diff = array_diff($links, $exclude);
    $new_pulled = $diff;
  } else {
    $exclude = array_merge($exclude, $pulled->data);
    $diff = array_diff($diff, $exclude);
    $new_pulled = array_merge($pulled, $diff);
  }
  $new_pulled = array_unique($new_pulled);
  //dsm($diff);
  cache_set('image_thiendia',$new_pulled, 'cache_mycustom');
  batch_set(mycustom_boxanh_batch_ops($diff));
}

// Preparing batch
function mycustom_boxanh_batch_ops($diff) {
  $operations = array();
  foreach ($diff as $tid) {
    $operations[] = array('mycustom_batch_getpage_anh', array($tid, t('(Operation @operation)', array('@operation' => $tid))));
  }
  $batch = array(
    'operations' => $operations,
    'finished' => 'mycustom_dochentai_batch_finished'
  );
  return $batch;
}

// Run batch
function mycustom_batch_getpage_anh($tid, $operation_details, &$context) {
  mycustom_get_thiendia_tid($tid);
}


///////////////////// ----------------------------- //////////////////////////////
// Tryen dam - thiendia
function mycustom_truyendam_create_chap($title, $body) {
  $node = new stdClass();
  $node->type = 'article';
  //$node->uid = 1;
  $node->body['und'][0]['value'] = $body;
  $node->body['und'][0]['format'] = 'full_html';
  $node->title = $title;
  $node->status = 1;
  node_save($node);
}

function mycustom_truyendam_gettruyen_content($html, $uname) {
  $content = '';
  
  $posts = $html->find('#posts', 0);
  foreach($posts->find('div') as $post) {
    if(isset($post->id) && strpos($post->id, 'edit') !== false) {
      $un = $post->find('.bigusername', 0)->href;
      $pid = $post->id;
      if ($un == $uname) {
        //dsm('anc');
        $message_pid = str_replace('edit', 'post_message_', $pid);
        $message_content = $post->find('#' . $message_pid, 0);
        //dsm($message_content .' ');
        //$message_content = $message_content . '';
        $message_content_text = $message_content->plaintext;
        $message_content = $message_content . '';
        if (strlen($message_content_text) > 1000) {
          $content .= $message_content;
        }
      }
    }
    
  }
  return $content;
}
/**
 * $tid : thiendia thread id
 * $from : start page
 * $to : end page
 */
function mycustom_truyendam_create($tid, $from, $to) {
  $link = 'http://thiendia.com/diendan/showthread.php?t=' . $tid;
  // Parse html
  $html = file_get_html($link);
  $uname = $html->find('.bigusername', 0)->href;
  $title = $html->find('#posts', 0)->find('h2', 0)->plaintext;
  
  
  for($i=$from; $i <= $to; $i++) {
    $linkpage = $link .'&page=' . $i;
    //dsm($linkpage);
    if($i!=1) {
      $html_page = file_get_html($linkpage);
    }
    else {
      $html_page = $html;
    }
    $content = mycustom_truyendam_gettruyen_content($html_page, $uname);
    
    if($content != '')  {
      //dsm($content);
      mycustom_truyendam_create_chap($title, $content);
    }
  }
  
}


