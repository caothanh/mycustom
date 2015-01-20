<?php

define('TRUYENDAM', 'truyensex');

// handle submit form "add truyen sex"
function mycustom_truyensex_submit(&$form, &$form_state) {
  //dsm($form_state['values']);
  $link = $form_state['values']['field_link']['und'][0]['value'];
  $from = $form_state['values']['field_from']['und'][0]['value'];
  $to = $form_state['values']['field_to']['und'][0]['value'];
  for($i= $from ; $i <= $to ; $i++) {
    mycustom_truyensex_parse_page($link, $i);
  }
}

// creating truyensex node 
function mycustom_truyensex_createnode($content) {
    $node = new stdClass();
    $node->type = TRUYENDAM;
    node_object_prepare($node);

    $node->uid = 1;
    $node->status = 1;
    $node->title = 'test' . time();
    $node->language = LANGUAGE_NONE;
    $node->body[$node->language][0]['value'] = $content;
    $node->body[$node->language][0]['summary'] = text_summary($content);
    $node->body[$node->language][0]['format'] = 'full_html';

    node_save($node);
}

// Parse each page in thread and create new node
function mycustom_truyensex_parse_page($link, $page) {
  $linkpage = $link . '&page=' . $page;
  //dsm($linkpage);
  $html = file_get_html($linkpage);
  $ownmem = 'member.php?u=1096784';
  $posts = $html->find('#posts', 0);
  
  $content = '';
  foreach($posts->find('table.tborder') as $table) {
      //dsm("abc");
    $a_link = $table->find('a.bigusername', 0);
    $mem = $table->find('a.bigusername', 0)->href;
    //dsm($mem);
    if($mem == $ownmem) {
      $cont = $table->find('td.alt1', 0) . '';
      if (strlen($cont) > 2000) {
        //mycustom_truyensex_createnode($content);
        $content .= $cont;
      }
    }
  }
  
  if (strlen($content) > 4000) {
    mycustom_truyensex_createnode($content);
  }
}
