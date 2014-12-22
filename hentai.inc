<?php
/**
 * Quick get tag
 */
function mycustom_dochentai_gettags(){
  $tags = array(
    'anh-em' => 1,
    'bac-chau' => 15,
    'ban-be' => 5,
    'chi-em' => 2,
    'choi-tap-the' => 23,
    'cuong-hiep' => 6,
    'di-chau' => 7,
    'doujinshi' => 25,
    'em-chong-chi-dau' => 14,
    'fuck' => 4,
    'gia-dinh' => 8,
    'giao-vien' => 9,
    'group' => 10,
    'hang-xom' => 11,
    'khac' => 12,
    'lesbian' => 13,
    'loan-luan' => 16,
    'lolicon' => 28,
    'me-ban' => 29,
    'me-con' => 17,
    'mom' => 19,
    'monster' => 27,
    'mother' => 18,
    'ngoai-tinh' => 20,
    'nhan-vien' => 30,
    'nu-sinh' => 22,
    'school' => 21,
    'teens' => 31,
    'tinh-yeu' => 24,
    'vo-sep' => 26,
  );
  return $tags;
}

// Get nid of truyen by nid of chuong
function mycustom_get_truyen_by_chuong($nid) {
  $query = db_select('field_data_field_chuong', 'n')
      ->fields('n', array('entity_id'))
      ->condition('field_chuong_target_id', $nid)
      //->condition('entity_type', 'node')
      ->range(0, 1)
      ->execute()
      ->fetchAssoc();
  return $query['entity_id'];
}


function mycustom_quick_get_tags($nid) {
  $query = db_select('field_data_field_tags', 'n')
    ->fields('n', array('field_tags_tid'))
    ->condition('entity_id', $nid)
    ->condition('entity_type', 'node')
    ->range(0, 1)
    ->execute()
    ->fetchAssoc();
  return $query['field_tags_tid'];
}

function mycustom_curl_google_auth() {
  $clientlogin_url = "https://www.google.com/accounts/ClientLogin";
  $clientlogin_post = array(
    "accountType" => "HOSTED_OR_GOOGLE",
    "Email" => "ihentai69@gmail.com",
    "Passwd" => "Taolatung@1501",
    "service" => "blogger",
    "source" => "your application name"
  );

// Initialize the curl object
  $curl = curl_init($clientlogin_url);

// Set some options (some for SHTTP)
  curl_setopt($curl, CURLOPT_POST, true);
  curl_setopt($curl, CURLOPT_POSTFIELDS, $clientlogin_post);
  curl_setopt($curl, CURLOPT_HTTPAUTH, CURLAUTH_ANY);
  curl_setopt($curl, CURLOPT_SSL_VERIFYPEER, false);
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);
  curl_setopt($curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt");
  curl_setopt($curl, CURLOPT_COOKIEJAR, "/tmp/cookie.txt");

// Execute
  $response = curl_exec($curl);
}


// GET hentai from dochentai.com
function mycustom_getdochentai_batch_form($form, $form_state) {
  $to = isset($_SESSION['dochentai_last_to']) ? $_SESSION['dochentai_last_to'] : 0;
  $form['from'] = array(
    '#type' => 'textfield',
    '#title' => 'From',
    '#default_value' => $to + 1
  );
  $form['to'] = array(
    '#type' => 'textfield',
    '#title' => 'To',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
    '#submit' => array('mycustom_getdochentai_batch_form_submit'),
  );
  return $form;
}




function mycustom_convert($str) {
  $unwanted_array = array(    'Š'=>'S', 'š'=>'s', 'Ž'=>'Z', 'ž'=>'z', 
    'À'=>'A', 'Á'=>'A', 'Â'=>'A', 'Ã'=>'A', 'Ä'=>'A', 'Å'=>'A', 'Æ'=>'A', 'Ç'=>'C', 'È'=>'E', 'É'=>'E',
    'ạ' => 'a', 'á' => 'a', 'à' => 'a', 'ả' => 'a', 'â' => 'a', 'ẩ' => 'a', 'ậ' => 'a','ấ' => 'a', 'ầ' => 'a',
    'ă' => 'a', 'ẳ' => 'a', 'ằ' => 'a', 'ắ' => 'a','ã' => 'a', 'ẫ' => 'a', 'ẵ' => 'a','ặ' => 'a',
    'Ê'=>'E', 'Ë'=>'E', 'ê' => 'e', 'ể' => 'e', 'ệ' => 'e', 'ề' => 'e', 'ế' => 'e','ễ' => 'e', 'ẹ' => 'e',
    'Ì'=>'I', 'Í'=>'I', 'Î'=>'I', 'Ï'=>'I', 'Ñ'=>'N', 'í' => 'i', 'ì' => 'i', 'ị' => 'i', 'ỉ' => 'i',
    'Ò'=>'O', 'Ó'=>'O', 'Ô'=>'O', 'Õ'=>'O', 'Ö'=>'O', 'Ø'=>'O','ô' => 'o','ộ' => 'o', 'Ộ' => 'o',
    'ỏ' => 'o', 'ò' => 'o', 'ọ' => 'o', 'ó' => 'o', 'ồ' => 'o', 'ổ' => 'o', 'ố' => 'o', 'ộ' => 'o','ô' => 'o',
    'ở' => 'o', 'ơ' => 'o', 'ờ' => 'o', 'ớ' => 'o', 'ợ' => 'o', 'ỗ' => 'o',
    'ú' => 'u', 'ù' => 'u', 'ụ' => 'u', 'ủ' => 'u', 'ũ' => 'u', 'ữ' => 'u',
    'ứ' => 'u', 'ử' => 'u', 'ừ' => 'u', 'ư' => 'u', 'ự' => 'ư',
    'Ù'=>'U','ư' => 'u', 'Ư' => 'u', 'ử' => 'u', 'Ử' => 'u', 'ú' => 'u', 'Ú' => 'u', 'ự' => 'u', "Ự" => 'u',
    'Ú'=>'U', 'Û'=>'U', 'Ü'=>'U', 'Ý'=>'Y', 'Þ'=>'B', 'ß'=>'Ss', 'à'=>'a', 'á'=>'a', 'â'=>'a', 'ã'=>'a', 'ä'=>'a', 'å'=>'a', 'æ'=>'a', 'ç'=>'c',
    'è'=>'e', 'é'=>'e', 'ê'=>'e', 'ë'=>'e', 'ẻ' => 'e', 'ẽ' => 'e',
    'ì'=>'i', 'í'=>'i', 'î'=>'i','ị' => 'i', 'Ị' => 'i', 'ï'=>'i', 'ỉ' => 'i','ĩ' => 'i',
    'ð'=>'o', 'ñ'=>'n', 'ò'=>'o', 'ó'=>'o', 'ô'=>'o', 'õ'=>'o',
    'ö'=>'o', 'ø'=>'o', 'ù'=>'u', 'ú'=>'u', 'û'=>'u', 'ữ' => 'u',
    'ý'=>'y', 'ý'=>'y', 'þ'=>'b', 'ÿ'=>'y', 'ỷ' => 'y', 'ỳ' => 'y','ỵ' => 'y','ỹ' => 'y',
    'đ' => 'd', 'Đ' => 'd' );
  $str = strtr( $str, $unwanted_array );
  //dsm('abc');
  return $str;
}



/**
 * Edit Solr api search
 */
function mycustom_modify_entity_solr_search($entity) {
  //if(!$entity->field_search_field['und'][0]['value']) {
    $s_content = '';
    $s_content .= $entity->title;
    foreach($entity->field_tags['und'] as $tag) {
      $taxo = taxonomy_term_load($tag['tid']);
      $s_content .= ' '. $taxo->name;
    }
    $node = node_load($entity->nid);
    $node->field_search_field['und'][0]['value'] = mycustom_convert(strtolower($s_content));
    node_save($node);
  //}
}

/**
 * Implement submit for 'mycustom_getdochentai_batch_form' form
 */
function mycustom_getdochentai_batch_form_submit(&$form, &$form_state) {
  $from = $form_state['values']['from'];
  $to = $form_state['values']['to'];
  
  if(!file_exists('/tmp/cookie.txt')) {
    mycustom_curl_google_auth();
  }
  //dsm($form_state);
  //$batch = ();
  $_SESSION['http_request_count'] = 0;
  $_SESSION['dochentai_last_to'] = $to;
  batch_set(mycustom_getdochentai_ops($from, $to));
}

function mycustom_getdochentai_ops($from, $to) {
  $operations = array();
  for ($i = $from; $i <= $to; $i++) {
    //$operations[] = array('mycustom_getdochentai_page', array($i, t('(Operation @operation)', array('@operation' => $i))));
    $operations[] = array('mycustom_getdochentai_page', array($i, t('(Operation @operation)', array('@operation' => $i))));
  }
  $batch = array(
    'operations' => $operations,
    'finished' => 'mycustom_dochentai_batch_finished'
  );
  return $batch;
}


/**
 * 
 */
function mycustom_getfakku_page($pid, $operation_details, &$context) {
  mycustom_getfakku_page_run($pid);
}

function mycustom_getfakku_page_run($pid) {
  //$link = 'http://www.fakku.net/search/incest/page/' . $pid;
  //$link = 'http://www.fakku.net/page/' . $pid;
  $link = 'http://www.fakku.net/search/schoolgirl/page/' . $pid;
  $html = file_get_html($link);
  foreach($html->find('.content-title') as $link) {
    $url = 'http://www.fakku.net/' . $link->href;
    //dsm($url);
    mycustom_fakku_get_comic($url);
  }
}

/**
 * Get Images form chap (Dochentai and thiendia.com)
 */
function mycustom_dochentai_get_images($content, $node, $newcomicid, $class ='img') {
  //echo $content;
  //dsm($content);
  //dsm($newcomicid);
  $comic_item_id = 0;
  if ($content) {
    $body_content = "<div id='chapter'>";
    foreach ($content->find($class) as $pic) {
      $src = $pic->src;
      //dsm($src);
      if(strpos($src, 'http') !== FALSE) {
         $body_content .= "<div class='pic' ><img data-src='$src' alt='truyen sex online,anh nude,truyen hentai, truyen tranh hentai, hentai loan luan, ihentai69.com, truyen tranh online $node->title' ></div>";
      }
    }
    $body_content .= '</div>';
    $node->body['und'][0]['value'] = $body_content;
    $node->body['und'][0]['format'] = 'full_html';
    $node->book['bid'] = $newcomicid;
    node_save($node);
    $comic_item_id = $node->nid;
  }
  return $comic_item_id;
}

function mycustom_getdochentai_page($pid, $operation_details, &$context) {
  mycustom_getdochentai_page_run($pid);
}

function mycustom_getdochentai_page_run($pid) {
  //function mycustom_getdochentai_page($pid) {
  $link = 'http://dochentai.com/?p=' . $pid;

  $cache_comic = cache_get('dochentai', 'cache_mycustom');
  $cache_data = array();

  $chaps = array();
  $html = file_get_html($link);
  // Preparing tags
  $tags = mycustom_dochentai_gettags();

  // Preparing Node

  $node = new stdClass();
  $node->type = 'commic';
  // get #detail div 
  if ($html) {
    $detail = $html->find('#details', 0);
    if ($detail) {
      // Title
      $title = $html->find('#main', 0)->find('.entry-title', 0)->plaintext;
      $title = preg_replace("/\[[^)]+\]/", "", $title);
      $node->title = $title;
      $node->status = 1;
      $node->uid = 1;
      // Get Image Logo

      if (!is_null($detail->find('.alignnone', 0))) {
        $img_logo = $detail->find('.alignnone', 0);
      }
      else {
        $img_logo = $detail->find('.separator', 0)->find('img', 0);
      }

      //dsm($img_logo);
      $img_logo = $img_logo->attr['src'];
      //$node->field_image_link['und'][0]['value'] = $img_logo;
      //->field_image_logo['und'][0]['fid']
      
      $file_img_name = mycustom_convert(trim($node->title));
      $logofile = file_save_data(file_get_contents($img_logo), 'public://comiclogo/comic-' . $file_img_name . '.png');
      $node->field_image_logo['und'][0]['fid'] = $logofile->fid;

      // Creating tags to post; 
      foreach ($detail->find('a') as $element) {
        //dsm($element->href);
        if (strpos($element->href, 'tag') !== FALSE) {
          $vars = explode('/', $element->href);
          $tag = $vars[4];
          if(isset($tags[$tag])) {
            $node->field_tags['und'][] = array('tid' => $tags[$tag]);
          }
        }
        else
        if (strpos($element->href, '.dochentai') !== FALSE) {
          $chaps[$element->plaintext] = $element->href;
        }
      }
      //dsm($chaps);

      // Set node as new book
      

      // Get new node id
      
      if(!empty($chaps)) {
        $node->book['bid'] = 'new';
        node_save($node);

        // Store data to caching.
        $cache_data['pid'] = $pid;
        $cache_data['type'] = 'clone';
        $cache_data['chaps'] = array();
        $cache_data['chapnids'] = array();
        $newcomicid = $node->nid;
        // Creating Chapters
        foreach ($chaps as $key => $chap) {
          //dsm($chap);
          //$shotr_chap = str_replace(array('http://read.dochentai.com/', '/'), array('', ''), $chap);
          $cache_data['chaps'][] = $chap;
          //dsm($shotr_chap . ' ---- ' . $chap);
          $nodei = new stdClass();
          $nodei->type = 'commic_item';
          $nodei->title = $key . '-' . $title;
          

          $htmlcontent = file_get_html($chap);
          if ($htmlcontent && strpos($chap, 'read.') !== FALSE) {
            
            $content = $htmlcontent->find('#content', 0);
            if($content) {
              $cache_data['chapnids'][] = mycustom_dochentai_get_images($content, $nodei, $newcomicid);
            }
          }
          else
          if ($htmlcontent && strpos($chap, 'readonline.') !== FALSE) {
            //dsm($chap);
            
            $content = $htmlcontent->find('#Blog1', 0);
            if($content) {
              mycustom_dochentai_get_images($content, $nodei, $newcomicid);
            } else {
              $link_al = $htmlcontent->find('.maia-button-primary', 0)->attr['href'];
              $htmlcontent = mycustom_dochentai_readonline($link_al);
              //dsm($link_al);
              $content = $htmlcontent->find('#Blog1', 0);
              if ($content) {
                $cache_data['chapnids'][] = mycustom_dochentai_get_images($content, $nodei, $newcomicid);
              } else {dsm($htmlcontent->plaintext);}
              //dsm($link_al);
            }
          }
          else {
            $node = node_load($newcomicid);
            $node->status = 0;
            node_save($node);
          }
        }
        
        
      } else {
        
      }

      if (isset($cache_comic->data) && is_array($cache_comic->data)) {
        if($newcomicid) {
          if (!isset($cache_comic->data[$newcomicid])) {
            $cache_comic->data[$newcomicid] = $cache_data;
            cache_set('dochentai', $cache_comic->data, 'cache_mycustom');
          }
        }
      } else {
        $cache_comic_data = array();
        $cache_comic_data[$newcomicid] = $cache_data;
        cache_set('dochentai', $cache_comic_data, 'cache_mycustom');
      }
    }
    _mycustom_dochentai_batch_update_http_requests();
  }
}

function _mycustom_dochentai_batch_update_http_requests() {
  $_SESSION['http_request_count']++;
}

/**
 * Finish of butch. Messagess
 */
function mycustom_dochentai_batch_finished($success, $results, $operations) {
  if ($success) {
    drupal_set_message(t('@count products added.', array('@count' => isset($results['added']) ? count($results['added']) : 0)));
  }
  else {
    $error_operation = reset($operations);
    drupal_set_message(t('An error occurred while processing @operation with arguments : @args', array('@operation' => $error_operation[0], '@args' => print_r($error_operation[0], TRUE))));
  }
  watchdog('import', 'import finished');
}

function mycustom_dochentai_readonline($url) {
  $curl = curl_init();
// Make the request
  curl_setopt($curl, CURLOPT_URL, $url);
//curl_setopt($curl, CURLOPT_HTTPHEADER, $headers);
  curl_setopt($curl, CURLOPT_POST, false);
  curl_setopt($curl, CURLOPT_FOLLOWLOCATION, 1);
  curl_setopt($curl, CURLOPT_COOKIEFILE, "/tmp/cookie.txt");
  curl_setopt($curl, CURLOPT_RETURNTRANSFER, 1);

  $response = curl_exec($curl);
  curl_close($curl);

  $html = new simple_html_dom(); // Create new parser instance
  $html->load($response);
  return $html;
}

/**
 * Get Hentai from thiendia.com
 */
function mycustom_gethentai_thiendia($form, $form_state) {
  $tags = array_flip(mycustom_dochentai_gettags());
  $form['tags'] = array(
    '#type' => 'select',
    '#options' => $tags,
    '#title' => 'Select Tag',
    '#multiple' => TRUE
  ); 
  $form['comic_type'] = array(
    '#type' => 'select',
    '#options' => array('commic' => "Create new comic", 'commic_item' => "Comic item")
  );
  
  $form['comic_select'] = array(
    '#type' => 'entityreference',
    '#title' => t('Select comic for this item'),
    '#cardinality' => FIELD_CARDINALITY_UNLIMITED,
    '#settings' => array(
      'target_type' => 'node',
      'target_bundles' => array('commic'),
    ),
  );

  $form['submit'] = array(
    '#value' => 'Submit',
    '#type' => 'submit'
  );
  return $form;
}


/**
 * Count chapter for special comic
 */
function mycustom_count_chaper($nid) {
  $count = db_select('book', 'n')
      ->fields('n', array('mlid'))
      ->condition('bid', $nid)
      ->execute()->rowCount();
  return $count;
}


function mycustom_get_hentai_new_comic($link, $div_content, $div_title, $div_img = '', $tags) {
  $node = new stdClass();
  $html = file_get_html($link);
  if($html) {
  $lxtheard = $html->find($div_content, 0);
    if($lxtheard) {
      $node->type = 'commic';
      $title = $lxtheard->find($div_title, 0)->plaintext;
      $node->title = $title;
      $node->status = 1;
      $node->uid = 1;
      $node->field_english['und'][0]['value'] = 1;
      // Search content
      $s_content = '';
      $s_content .= $node->title;

      foreach ($tags as $tag) {
        $node->field_tags['und'][] = array('tid' => $tag['tid']);
        $taxo = taxonomy_term_load($tag['tid']);
        $s_content .= ' '. $taxo->name;
      }
      $node->field_search_field['und'][0]['value'] = mycustom_convert(strtolower($s_content));
    

      //$img_logo = $lxtheard->find('img', 1)->src;
      if ($div_img == '') {
        $dem = 0;
        foreach ($lxtheard->find('img') as $img) {
          if($dem == 2) {
            break;
          }
          //dsm($img->src);
          if (strpos($img->src, 'http:') !== FALSE) {
            //dsm($img->src);
            $img_logo = $img->src;
            ++$dem;
            //break;
          }
        }
      }
      else {
        $img_logo = $lxtheard->find($div_img, 0)->src;
        //dsm($img_logo);
      }
      //dsm($img_logo);
      //$node->field_image_link['und'][0]['value'] = $img_logo;
      //->field_image_logo['und'][0]['fid']
      $logofile = file_save_data(file_get_contents($img_logo), 'public://comiclogo/comic-' . $node->title . '.jpg');
      $node->field_image_logo['und'][0]['fid'] = $logofile->fid;
      $node->field_image_logo['und'][0]['alt'] = $title . ', Truyện tranh loạn luân, loạn luân mẹ con, ihentai69.com'; 
      $node->book['bid'] = 'new';
      
      
      
      foreach($entity->field_tags['und'] as $tag) {
        
      }
      //$node = node_load($entity->nid);
      
      node_save($node);
      return $node->nid;
    }
  }
  //else {dsm('fail');}
  return -1;
}

/**
 * generating new chap
 */
function mycustom_get_hentai_new_chap($link, $comic_id, $div_content, $div_title) {
  //$comic_id = $form_state['values']['field_comic']['und'][0]['nid'];
  $nodei = new stdClass();
  $nodei->type = 'commic_item';

  $chap = mycustom_count_chaper($comic_id);
  //dsm($chap);
  $html = file_get_html($link);
  //dsm($html);
  if($html) {
    if(strpos($link,'yeuhentai') !==FALSE || strpos($link,'truyen18') !== FALSE) {
      //dsm($link);
      $title = $html->find($div_title, 0)->plaintext;
      $nodei->title = "Chap $chap - " . $title;
      //$html = file_get_html($l);
      $imgs = $html->find('#truyen18-eedit', 0);
      $imgs_str = $imgs->plaintext;
      if(strpos($imgs_str, '[IMG]') !== FALSE) {
        //$imgs_str = $imgs->plaintext;
      //dsm($imgs);
        $img_prefix = "<div class='pic' ><img src='";
        $img_suffix = "?imgmax=1600' alt='anh sex,anh nude,truyen hentai,truyen loan luan, truyen tranh loan luan, incest hentai
              truyen tranh hentai, hentai manga, ihentai69.com, truyen tranh online' ></div>";
        $imgs_str = str_replace('[IMG]', $img_prefix, $imgs_str);
        $imgs_str = str_replace('[/IMG]', $img_suffix, $imgs_str);
        $imgs_str = str_replace('s250', 's1600', $imgs_str);
        $imgs_str = str_replace('http://s2.truyen18.org/css/imgcss/hoantat.jpg?imgmax=1600', '', $imgs_str);
        $imgs_str = str_replace('http://thumb.truyen18.org/Store2/f2091640347ad82adff4f5452bc9850b.jpg?imgmax=1600', '', $imgs_str);
        //http://thumb.truyen18.org/Store2/f2091640347ad82adff4f5452bc9850b.jpg?imgmax=1600
        if(strpos('imgur.com', $img_str) !== false) {
          $imgs_str = str_replace('s.jpg', '.jpg', $imgs_str);
        }
        
      }
      else {
        $imgs_str = '';
        foreach($imgs->find('img') as $img) {
          //dsm($img->src);
          $src = $img->src . '?imgmax=1600';
          $src = str_replace('s250', 's1600', $src);
          $imgs_str .= "<div class='pic' ><img data-src='$src' alt='anh sex,anh nude,truyen hentai,truyen loan luan, truyen tranh loan luan, incest hentai
              truyen tranh hentai, hentai manga, ihentai69.com, truyen tranh online' ></div>";
          $imgs_str = str_replace('http://s2.truyen18.org/css/imgcss/hoantat.jpg?imgmax=1600', '', $imgs_str);
          $imgs_str = str_replace('http://thumb.truyen18.org/Store2/f2091640347ad82adff4f5452bc9850b.jpg?imgmax=1600', '', $imgs_str);
          if(strpos('imgur.com', $img_str) !== false) {
          
          $imgs_str = str_replace('s.jpg', '.jpg', $imgs_str);
          }
        }
        //$imgs_str = t$imgs->plaintext, '"');
        //dsm($imgs_str);
//        $img_prefix = "<div class='pic' ><img ";
//        $img_suffix = " alt='anh sex,anh nude,truyen hentai,truyen loan luan, truyen tranh loan luan, incest hentai
//              truyen tranh hentai, hentai manga, ihentai69.com, truyen tranh online, ihentai' ></div>";
//        $imgs_str = str_replace('<img', $img_prefix, $imgs_str);
//        $imgs_str = str_replace('/></br>', $img_suffix, $imgs_str);
        //foreach ($imgs->find('img') as )
      }
      
      $body_content = "<div id='chapter'>";
      $body_content .= $imgs_str;
      $body_content .= '</div>';
      $nodei->body['und'][0]['value'] = $body_content;
      $nodei->body['und'][0]['format'] = 'full_html';
      $nodei->book['bid'] = $comic_id;
      node_save($nodei);
      $body_content = "<div id='chapter'>";
      $body_content .= $imgs_str;
      $body_content .= '</div>';
      $nodei->body['und'][0]['value'] = $body_content;
      $nodei->body['und'][0]['format'] = 'full_html';
      $nodei->book['bid'] = $comic_id;
      node_save($nodei);
    }
    else {
      $lxtheard = $html->find($div_content, 0);
      if ($lxtheard) {
        $title = $lxtheard->find($div_title, 0)->plaintext;
        $nodei->title = "Chap $chap - " . $title;
        mycustom_dochentai_get_images($lxtheard, $nodei, $comic_id);
      }
      else {
        $link_al = $html->find('.maia-button-primary', 0)->attr['href'];
        $htmlcontent = mycustom_dochentai_readonline($link_al);
        //dsm($link_al);
        $content = $htmlcontent->find('#Blog1', 0);
        if ($content) {
          mycustom_dochentai_get_images($content, $nodei, $comic_id);
        }
        else {
          //dsm($htmlcontent->plaintext);
        }
      }
    }
    
  }

  
}

/**
 * Get link chap from single page
 */
function mycustom_get_links_chap($link, $div_chap) {
  $html = file_get_html($link);
  $links = array();
  if($html) {
    
    foreach($html->find($div_chap) as $link) {
      $links[] = $link->href;
    }
  }
  return $links;
}


/**
 * Handle submit for mycustom_get_hentai_thiendia
 */
function mycustom_get_hentai_thiendia(&$form, &$form_state) {
  //dsm($form_state['values']);
  $tags = $form_state['values']['field_tags']['und'];
  $comic_or_item = $form_state['values']['field_comic_or_item']['und'][0]['value'];
  
  
  switch ($comic_or_item) {
    case 1 :
      $comic_id = $form_state['values']['field_comic']['und'][0]['nid'];
//      $nodei = new stdClass();
//      $nodei->type = 'commic_item';
//
//      $chap = mycustom_count_chaper($comic_id);
//      //dsm($chap);
//      $html = file_get_html("http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]");
//      $lxtheard = $html->find('#lxthread', 0);
//      $title = $lxtheard->find('h2', 0)->plaintext;
//      $nodei->title = "Chap $chap - " . $title;
//
//      mycustom_dochentai_get_images($lxtheard, $nodei, $comic_id);
      //dsm("http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]");
      
      mycustom_get_hentai_new_chap("http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]", $comic_id,'#lxthread', 'h2' );
      break;
    case 0 :
//      $node = new stdClass();
//      $html = file_get_html("http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]");
//      $lxtheard = $html->find('#lxthread', 0);
//      $node->type = 'commic';
//      $title = $lxtheard->find('h2', 0)->plaintext;
//      $node->title = $title;
//      $node->status = 1;
//      $node->uid = 1;
//
//      foreach ($tags as $tag) {
//        $node->field_tags['und'][] = array('tid' => $tag['tid']);
//      }
//
//
//      //$img_logo = $lxtheard->find('img', 1)->src;
//      foreach ($lxtheard->find('img') as $img) {
//        //dsm($img->src);
//        if (strpos($img->src, 'http:') !== FALSE) {
//          //dsm($img->src);
//          $img_logo = $img->src;
//          break;
//        }
//      }
//      //dsm($img_logo);
//      //$node->field_image_link['und'][0]['value'] = $img_logo;
//      //->field_image_logo['und'][0]['fid']
//      $logofile = file_save_data(file_get_contents($img_logo), 'public://comiclogo/comic-' . $node->title . '.jpg');
//      $node->field_image_logo['und'][0]['fid'] = $logofile->fid;
//      $node->book['bid'] = 'new';
//      node_save($node);
      //dsm($link);
      //$t = $_GET['t'];
      //$link = "http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
      $link = "http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
      //dsm($link);
      $nid = mycustom_get_hentai_new_comic($link, '#lxthread', 'h2','',$tags);
      
      // Saving comic item

//      $nodei = new stdClass();
//      $nodei->type = 'commic_item';
//      $nodei->title = 'Chap 1 - ' . $title;
//      mycustom_dochentai_get_images($lxtheard, $nodei, $node->nid);
      mycustom_get_hentai_new_chap($link, $nid, '#lxthread', 'h2');
      break;
    case 2 :
      //dsm($form_state['values']);
      $link = $form_state['values']['field_url']['und'][0]['value'];
      $nid = mycustom_get_hentai_new_comic($link, '#Blog1', '.post-title', '.post-body img', $tags);
      mycustom_get_hentai_new_chap($link, $nid, '#Blog1', '.post-title');
      break;
    case 3 :
      //dsm($form_state['values']);
      $link = $form_state['values']['field_url']['und'][0]['value'];
      $link_chap = $form_state['values']['field_url_chap']['und'][0]['value'];
      $num_chap = $link1 = $form_state['values']['field_num_chap']['und'][0]['value'];
      
      $nid = mycustom_get_hentai_new_comic($link, '#main', '.entry-title', '#details img', $tags);
      if($num_chap > 0) {
        for ($i = 1; $i <= $num_chap; $i++) {
          $link = $link_chap . '-' . $i;
          //dsm($link);
          mycustom_get_hentai_new_chap($link, $nid, '#content', '.post-title');
        }
      }
      else {
        //mycustom_get_hentai_new_chap($link_chap, $nid, '#content', '.post-title');
      }
      break;
      
    case 4 :
      $link = $form_state['values']['field_url']['und'][0]['value'];
      $nid = mycustom_get_hentai_new_comic($link, '.barContent', 'a', 'img', $tags);
      //mycustom_get_hentai_new_chap($link, $nid, '#Blog1', '.post-title');
      $links = mycustom_get_links_chap($link, '.bigBarContainer a.title2');
      $links =array_reverse($links);
      foreach($links as $link) {
        //dsm($link);
        mycustom_get_hentai_new_chap($link, $nid, '.entry', '.singletitle span');
        //dsm($link);
      }
      break;
    case 5 :
      $link = $form_state['values']['field_url']['und'][0]['value'];
      $div_content = $form_state['values']['field_custom_div_content']['und'][0]['value'];
      $div_title = $form_state['values']['field_custom_div_title']['und'][0]['value'];
      $div_logo = $form_state['values']['field_custom_div_logo']['und'][0]['value'];
      $nid = mycustom_get_hentai_new_comic($link, $div_content, $div_title, $div_logo, $tags);
      mycustom_get_hentai_new_chap($link, $nid, $div_content, $div_title);
      
    case 6:
      $link = $form_state['values']['field_url']['und'][0]['value'];
      $nid = mycustom_get_hentai_new_comic($link, '.DetailItem', '.title_truyen h1', '#anhto', $tags);
      $links = mycustom_get_links_chap($link, '#List_Chapters a');
      $links = array_reverse($links);
      foreach($links as $key=>$l) {
        $l = 'http://yeuhentai.com' . $l;
        mycustom_get_hentai_new_chap($l, $nid, '.entry', '.singletitle a');
        
        //<div class='pic' ><img src='$src' 
      }
      break;
    case 7 :
      $comic_id = $form_state['values']['field_comic']['und'][0]['nid'];
      $link = $form_state['values']['field_url']['und'][0]['value'];
      mycustom_get_hentai_new_chap($link, $comic_id, '#content', '.post-title');
      break;
    case 8:
      $link = "http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]";
      $tags = $form_state['values']['field_pic_tags']['und'];
      $html = file_get_html($link);
      $node = new stdClass();
      $content = $html->find('#lxthread', 0);
      $body_content = "<div id='flexslider'><ul class='slides'>";
      $title = $html->find('#lxthread h2', 0)->plaintext;
      $node->title = $title;
      $dem = 0;
      foreach ($content->find('img') as $pic) {
        $src = $pic->src;
        
        
        //dsm($src);
        if (strpos($src, 'http') !== FALSE) {
          if ($dem == 1) {
            if (!is_404($src)) {
              $logofile = file_save_data(file_get_contents($src), 'public://comiclogo/comic-' . $node->title . '.jpg');
              $node->field_image['und'][0]['fid'] = $logofile->fid;
            }
          }
          ++$dem;
          $body_content .= "<li class='pic' ><img src='$src' alt='anh sex,anh nude,truyen hentai, truyen tranh hentai, hentai manga, ihentai69.com, truyen tranh online $node->title' ></li>";
        }
      }
      
      foreach ($tags as $tag) {
        $node->field_tags['und'][] = array('tid' => $tag['tid']);
        //$taxo = taxonomy_term_load($tag['tid']);
        //$s_content .= ' ' . $taxo->name;
      }
      $body_content .= '</ul></div>';
      
      $node->type = 'article';
      $node->uid = 1;
      
      $node->body['und'][0]['value'] = $body_content;
      $node->body['und'][0]['format'] = 'full_html';
      $node->book['bid'] = $newcomicid;
      node_save($node);
      $comic_item_id = $node->nid;
      break;
    case 9 :
      $link = $form_state['values']['field_url']['und'][0]['value'];
      $nid = mycustom_get_hentai_new_comic($link, '#content', '.post-title', '.post-entry img', $tags);
      mycustom_get_hentai_new_chap($link, $nid, '#content', '.post-title');
      break;
    case 10 : // get comic from blogger.com
      $comic_id = $form_state['values']['field_comic']['und'][0]['nid'];
      $link = $form_state['values']['field_url']['und'][0]['value'];
      mycustom_get_hentai_new_chap($link, $comic_id, '#Blog1', '.post-title');
      break;
    // Get Chap from hentailx.
    case 11: // Get new comic and chap 1 blogger.com
      //$comic_id = $form_state['values']['field_comic']['und'][0]['nid'];
      //$link = $form_state['values']['field_url']['und'][0]['value'];
      //mycustom_get_hentai_new_chap($link, $comic_id, '#Blog1', '.post-title');
      $link = $form_state['values']['field_url']['und'][0]['value'];
      $nid = mycustom_get_hentai_new_comic($link, '#Blog1', '.post-title', '.post-body img', $tags);
      mycustom_get_hentai_new_chap($link, $nid, '#Blog1', '.post-title');
      break;
    // Get lx comic and chaps
    case 12 : 
      $chaps = $form_state['values']['field_url']['und'][0]['value'];
      //dsm();
      $chaps = preg_replace('/\s+/', '',$chaps);
      
      // Get chap delimiter by comma
      $chaps = explode(',', $chaps);
      //dsm($chaps);
//      
      // Create comic
      $link = "http://www.ihentai69.com/getlx/getlx?t=" . $chaps[0];
      $nid = mycustom_get_hentai_new_comic($link, '#lxthread', 'h2','',$tags);
      
      foreach($chaps as $chap) {
        $link = "http://www.ihentai69.com/getlx/getlx?t=" . $chap;
        mycustom_get_hentai_new_chap($link, $nid, '#lxthread', 'h2');
      }
    break;
    // add chaps from lx to exist comics
    case 13 :
      $nid = $form_state['values']['field_comic']['und'][0]['nid'];
      $chaps = $form_state['values']['field_url']['und'][0]['value'];
      //dsm($chap);
      $chaps = preg_replace('/\s+/', '', $chaps);

      // Get chap delimiter by comma
      $chaps = explode(',', $chaps);
      foreach ($chaps as $chap) {
        $link = "http://www.ihentai69.com/getlx/getlx?t=" . $chap;
        //dsm($link);
        mycustom_get_hentai_new_chap($link, $nid, '#lxthread', 'h2');
      }
  }
}

function mycustom_bulk_update_chap($entity) {
  $entity->field_last_chap['und'][0]['value'] = mycustom_count_chaper($entity->nid);
  node_save($entity);
  
}




/**
 * function update chap entity
 */
function mycustom_gethentai_update($nid) {
  $cache_docht = cache_get('dochentai', 'cache_mycustom');
  $docdentai = $cache_docht->data;
  $comic = $docdentai[$nid];
  
  $url = 'http://dochentai.com/' + '?p=' + $comic['pid'];
  $html = file_get_html($url);
  
  $chaps = array();
  
  $detail = $html->find('#details', 0);
  // Creating tags to post; 
  foreach ($detail->find('a') as $element) {
    if (strpos($element->href, '.dochentai') !== FALSE) {
      if(!in_array($element->plaintext, $comic['chaps'])) {
        $chaps[$element->plaintext] = $element->href;
      }
    }
  }
  
  foreach ($chaps as $key => $chap) {
    //dsm($chap);
    //$shotr_chap = str_replace(array('http://read.dochentai.com/', '/'), array('', ''), $chap);
    $comic['chaps'][] = $chap;
    //dsm($shotr_chap . ' ---- ' . $chap);
    $nodei = new stdClass();
    $nodei->type = 'commic_item';
    $nodei->title = $key . '-' . $title;


    $htmlcontent = file_get_html($chap);
    if ($htmlcontent && strpos($chap, 'read.') !== FALSE) {

      $content = $htmlcontent->find('#content', 0);
      if ($content) {
        $comic['chapnids'][] = mycustom_dochentai_get_images($content, $nodei, $nid);
      }
    }
    else
    if ($htmlcontent && strpos($chap, 'readonline.') !== FALSE) {
      //dsm($chap);

      $content = $htmlcontent->find('#Blog1', 0);
      if ($content) {
        mycustom_dochentai_get_images($content, $nodei, $nid);
      }
      else {
        $link_al = $htmlcontent->find('.maia-button-primary', 0)->attr['href'];
        $htmlcontent = mycustom_dochentai_readonline($link_al);
        //dsm($link_al);
        $content = $htmlcontent->find('#Blog1', 0);
        if ($content) {
          $comic['chapnids'][] = mycustom_dochentai_get_images($content, $nodei, $nid);
        }
        else {
          //dsm($htmlcontent->plaintext);
        }
        //dsm($link_al);
      }
    }
  }
  
  $docdentai[$nid] = $comic;
  //$cache_docht->data = $docdentai;
  cache_set('dochentai', $docdentai, 'cache_mycustom');
  //if(isset($docdentai))
  //foreach($d)
}


function mycustom_getdochentai_single_form() {
  $form['text'] = array(
    '#type' => 'textfield',
    '#title' => 'Link'
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#submit' => array('mycustom_getdochentai_single_form_submit'),
    '#value' => 'Submit'
  );
  return $form;
}


function mycustom_getdochentai_single_form_submit(&$form, &$form_state) {
  $chap = $form_state['values']['text'];
  $htmlcontent = file_get_html($chap);
  
  
  
  $content = $htmlcontent->find('#Blog1', 0);
  if ($content) {
    
    $node = new stdClass();
    //$html = file_get_html("http://$_SERVER[HTTP_HOST]$_SERVER[REQUEST_URI]");
    //$lxtheard = $html->find('#lxthread', 0);
    $node->type = 'commic';
    $title = $content->find('.post-title', 0)->plaintext;
    
    $post_body = $content->find('.post-body', 0);
    $img_logo = $post_body->find('img', 0)->src;
    
    $node->title = $title;
    $node->status = 1;
    $node->uid = 1;
    $logofile = file_save_data(file_get_contents($img_logo), 'public://comiclogo/comic-' . $node->title . '.jpg');
    $node->field_image_logo['und'][0]['fid'] = $logofile->fid;
    $node->book['bid'] = 'new';
    node_save($node);
    
    // Saving comic item
    
    $nodei = new stdClass();
    $nodei->type = 'commic_item';
    $nodei->title =  'Chap 1 - ' . $title;
    mycustom_dochentai_get_images($content, $nodei, $node->nid);
    dsm($node->nid);
  }
}


/////////////////// FAKKU.NET ////////////////////////

function mycustom_fakku_change_path($name) {
  $name = str_replace(array('-', 'english'), array('', ''), $name);
  $name = strtolower($name);
  $name = $name . '_e';
  return $name;
}

//require_once("simple_html_dom.php");
//$link = 'http://www.fakku.net/doujinshi/cinderella-girls-love-2-english';

function mycustom_fakku_get_num_pages($link) {
  
  $html = file_get_html($link);
  if($html) {
    //if($html->find('#right', 0)->find('.small', 0)->find('b', 0))
    $right = $html->find('#right', 0);
    if($right) {
      $num = $right->find('.small', 0)->find('b', 0)->plaintext;
      $title = $html->find('#right', 0)->find('h1', 0)->plaintext;
    } else {
      //$num = 20;
      return -1;
    }
    
    
    //$num = $html->find('#right', 0)->find('.small', 0)->find('b', 0)->plaintext;
    
    return array('num' => $num, 'title' => $title);
  }
  return -1;
  


  //$num = $html->find('#right', 0)->plaintext;
  
}

function mycustom_fakku_get_root_image_link($link) {
  $parts = explode('/', $link);

  $name = $parts[5];
  $name = mycustom_fakku_change_path($name);
//echo change_path($name) .'----------' . $name[0];

  $root_img = 'https://t.fakku.net/images/manga/' . $name[0] . '/' . $name . '/images/';
  return $root_img;
}

function mycustom_fakku_get_images($link, $num_pic) {
  $root_img = mycustom_fakku_get_root_image_link($link);

  $link_imgs = array();



  for ($i = 1; $i <= $num_pic; $i++) {
    if ($i < 10) {
      $num = '00' . $i;
    }
    else {
      $num = '0' . $i;
    }
    $num .= '.jpg';
    $src = $root_img . $num;
    $link_imgs[] = $src;
  }
  //dsm($link_imgs);
  return $link_imgs;
}

function mycustom_fakku_get_comic($link) {
  $info = mycustom_fakku_get_num_pages($link);
  if(!$info) {
    return;
  }
  $title = $info['title'];
  $num_pic = $info['num'];
  $link_imgs = mycustom_fakku_get_images($link, $num_pic);

  // Generate Comic
  $node = new stdClass();
  $node->type = 'commic';
  ///$title = $lxtheard->find($div_title, 0)->plaintext;
  $node->title = $title;
  $node->status = 1;
  $node->uid = 1;
  $node->field_search_field['und'][0]['value'] = $title . ' incest, mom';
  if(!is_404($link_imgs[0])) {
    
  
    //$logofile = file_save_data(file_get_contents($img_logo), 'public://comiclogo/comic-' . $file_img_name . '.png');
    $logofile = file_save_data(file_get_contents($link_imgs[0]), 'public://comiclogo/comic-' . $title . '.png');
    $node->field_image_logo['und'][0]['fid'] = $logofile->fid;
    $node->book['bid'] = 'new';
    // Tags
    $node->field_tags['und'][] = array('tid' => 16);
    $node->field_tags['und'][] = array('tid' => 18);
    $node->field_tags['und'][] = array('tid' => 19);
    $node->field_tags['und'][] = array('tid' => 42);
    $node->field_english['und'][0]['value'] = 0;
    node_save($node);

    $nid = $node->nid;


    // Generating chap
    $nodei = new stdClass();
    $nodei->type = 'commic_item';
    $nodei->title = 'One shot - '. $title;
    $body_content = "<div id='chapter'>";
    $imgs_str = '';

    foreach ($link_imgs as $src) {
      $imgs_str .= "<div class='pic' ><img src='$src' alt='ihentai69.com, anh sex,anh nude,truyen hentai,truyen loan luan, truyen tranh loan luan, incest hentai
                truyen tranh hentai, hentai manga, , truyen tranh online' ></div>";
    }
    $body_content .= $imgs_str;
    $body_content .= '</div>';
    $nodei->body['und'][0]['value'] = $body_content;
    $nodei->body['und'][0]['format'] = 'full_html';
    $nodei->book['bid'] = $nid;
    node_save($nodei);
  }
  // Generating chap
}

function is_404($url) {
    $handle = curl_init($url);
    curl_setopt($handle,  CURLOPT_RETURNTRANSFER, TRUE);

    /* Get the HTML or whatever is linked in $url. */
    $response = curl_exec($handle);

    /* Check for 404 (file not found). */
    $httpCode = curl_getinfo($handle, CURLINFO_HTTP_CODE);
    curl_close($handle);

    /* If the document has loaded successfully without any redirection or error */
    if ($httpCode >= 200 && $httpCode < 300) {
        return false;
    } else {
        return true;
    }
}


function mycustom_delete_file($fid) {
  $file = file_load($fid);
  file_delete($file, TRUE);
}

// Detect php
function isMobile() {
    return preg_match("/(android|avantgo|blackberry|bolt|boost|cricket|docomo|fone|hiptop|mini|mobi|palm|phone|pie|tablet|up\.browser|up\.link|webos|wos)/i", $_SERVER["HTTP_USER_AGENT"]);
}

