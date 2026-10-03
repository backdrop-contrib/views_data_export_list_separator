<?php

/**
 * @file
 * CSV export style plugin with list-separator support.
 */

/**
 * Adds list conversion options to the Views Data Export CSV style plugin.
 */
class views_data_export_list_separator_plugin_style_export_csv extends views_data_export_plugin_style_export_csv {

  /**
   * {@inheritdoc}
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['convert_lists'] = array(
      'default' => FALSE,
      'translatable' => FALSE,
    );
    $options['list_separator'] = array(
      'default' => ',',
      'translatable' => FALSE,
    );
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['convert_lists'] = array(
      '#type' => 'checkbox',
      '#title' => t('Convert ordered and unordered lists to simple separated values.'),
      '#default_value' => !empty($this->options['convert_lists']),
      '#description' => t('Only list markup (eg, &lt;ol&gt;&lt;ul&gt;&lt;li&gt;) in the CSV export is changed. Other field settings in attached displays are not modified.'),
    );
    $form['list_separator'] = array(
      '#type' => 'textfield',
      '#title' => t('List-item separator character or characters'),
      '#default_value' => isset($this->options['list_separator']) ? $this->options['list_separator'] : ',',
      '#size' => 12,
      '#maxlength' => 255,
      '#description' => t('Examples: , ; - ~ etc. Enter "\n" for a line break. You may enter multiple characters. Make sure to enable "Quote values" setting above.'),
      '#states' => array(
        'visible' => array(
          ':input[name="style_options[convert_lists]"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  /**
   * {@inheritdoc}
   *
   * Converts list markup before Views Data Export runs its normal CSV
   * preprocessing, which strips HTML tags from rendered field values.
   */
  function render_body() {
    if (empty($this->options['convert_lists'])) {
      return parent::render_body();
    }

    // The parent normally does this in render_grouping(), after this method
    // starts. Populate the cache first so it can be transformed for CSV only.
    $this->render_fields($this->view->result);
    if (empty($this->rendered_fields)) {
      return parent::render_body();
    }

    $original_rendered_fields = $this->rendered_fields;
    foreach ($this->rendered_fields as $row => $fields) {
      foreach ($fields as $field => $value) {
        $this->rendered_fields[$row][$field] = views_data_export_list_separator_convert_lists($value, $this->options['list_separator']);
      }
    }

    try {
      $output = parent::render_body();
    }
    catch (Exception $exception) {
      $this->rendered_fields = $original_rendered_fields;
      throw $exception;
    }

    $this->rendered_fields = $original_rendered_fields;
    return $output;
  }
}

/**
 * Converts UL and OL elements in an HTML fragment to separated item values.
 *
 * @param string $html
 *   A rendered Views field value.
 * @param string $separator
 *   Text placed between list items.
 *
 * @return string
 *   The rendered value, with list elements replaced by their item contents.
 */
function views_data_export_list_separator_convert_lists($html, $separator) {
  if (!is_string($html) || (stripos($html, '<ul') === FALSE && stripos($html, '<ol') === FALSE)) {
    return $html;
  }

  // A textfield cannot contain a literal newline, so accept its familiar
  // escaped representation in the display setting.
  $separator = str_replace('\\n', "\n", $separator);

  if (!class_exists('DOMDocument')) {
    return $html;
  }

  $document = new DOMDocument();
  $previous = libxml_use_internal_errors(TRUE);
  $fragment = '<div id="views-data-export-list-separator-root">' . $html . '</div>';
  $loaded = $document->loadHTML('<?xml encoding="UTF-8">' . $fragment);
  libxml_clear_errors();
  libxml_use_internal_errors($previous);

  if (!$loaded) {
    return $html;
  }

  $xpath = new DOMXPath($document);
  $lists = $xpath->query('//ul | //ol');
  for ($index = $lists->length - 1; $index >= 0; $index--) {
    $list = $lists->item($index);
    $items = array();
    foreach ($list->childNodes as $child) {
      if ($child instanceof DOMElement && strtolower($child->tagName) === 'li') {
        $items[] = views_data_export_list_separator_inner_html($child);
      }
    }
    $list->parentNode->replaceChild($document->createTextNode(implode($separator, $items)), $list);
  }

  $root = $document->getElementById('views-data-export-list-separator-root');
  return $root ? views_data_export_list_separator_inner_html($root) : $html;
}

/**
 * Returns the inner HTML of a DOM node.
 */
function views_data_export_list_separator_inner_html(DOMNode $domnode) {
  $html = '';
  foreach ($domnode->childNodes as $child) {
    $html .= $domnode->ownerDocument->saveHTML($child);
  }
  return $html;
}
