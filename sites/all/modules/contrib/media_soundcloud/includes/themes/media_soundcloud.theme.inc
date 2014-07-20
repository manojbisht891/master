<?php

/**
 * @file media_soundcloud/includes/themes/media_soundcloud.theme.inc
 *
 * Theme and preprocess functions for Media: SoundCloud.
 */

/**
 * Preprocess function for theme('media_soundcloud_audio').
 */
function media_soundcloud_preprocess_media_soundcloud_audio(&$variables) {
  //drupal_set_message("media_soundcloud_preprocess_media_soundcloud_audio");  
  // Build the URL for display.
  
      
  $uri = $variables['uri'];
  $wrapper = file_stream_wrapper_get_instance_by_uri($uri);
  
  $parts = $wrapper->get_parameters();
  
  //drupal_set_message(print_r($wrapper,true));
  $url = $wrapper->interpolateUrl();
  
  //drupal_set_message(print_r($url,true));
  if(isset($parts['u'])){
    $variables['user_name'] = check_plain($parts['u']);
    $variables['wrapper_id'] = 'media_soundcloud_' . $variables['user_name'] . '_' . $variables['id'];
  }
  if(isset($parts['a'])){
    $variables['audio_name'] = check_plain($parts['a']);
    $variables['wrapper_id'] = 'media_soundcloud_' . $variables['audio_name'] . '_' . $variables['id'];
  }
  if(isset($parts['g'])){
    $variables['group_name'] = check_plain($parts['g']);
    $variables['wrapper_id'] = 'media_soundcloud_' . $variables['group_name'] . '_' . $variables['id'];
  }
  if(isset($parts['s'])){
    $variables['set_name'] = check_plain($parts['s']);
    $variables['wrapper_id'] = 'media_soundcloud_' . $variables['set_name'] . '_' . $variables['id'];
  }
  
  $variables['width'] = isset($variables['width']) ? $variables['width'] : media_soundcloud_variable_get('width');
  $variables['autoplay'] = isset($variables['autoplay']) ? $variables['autoplay'] : media_soundcloud_variable_get('autoplay');
  $variables['autoplay'] = $variables['autoplay'] ? 1 : 0;
  
  //Explode the values in extra_params
  $variables['extra_params'] = isset($variables['extra_params']) ? $variables['extra_params'] : media_soundcloud_variable_get('extra_params');
  $variables['extra_params_expanded'] = array();
  if ($variables['extra_params']) {
    foreach (explode(',', $variables['extra_params']) as $key => $value) {
      $value_pair = explode(':', $value);
      if (count($value_pair) == 2) { // some degree of check, though it is largely dependent on site admin to set sensible values
        $variables['extra_params_expanded'][trim($value_pair[0])] = trim($value_pair[1]);
      }
    }
  }
  $variables['widget_options'] = array_merge(array('auto_play'=> $variables['autoplay'] ? 'true' : 'false'), $variables['extra_params_expanded']);
  $embed_data = $wrapper->getOEmbed($url, $variables['widget_options']);
  
  
  
  $variables['output'] = str_replace('width="100%"', 'width="'.$variables['width'].'"', $embed_data['html']);
}

function theme_media_soundcloud_field_formatter_styles($variables) {
  drupal_set_message("theme_media_soundcloud_field_formatter_styles");
  
  $element = $variables['element'];
  $style = $variables['style'];
  $variables['file'] = $element['#item'];
  $variables['uri'] = $variables['file']['uri'];
  $variables['style_name'] = $style['name'];
  return theme('media_soundcloud_embed', $variables);
}



