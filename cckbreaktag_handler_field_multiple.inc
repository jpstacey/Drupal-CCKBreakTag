<?php

/**
 * @file
 * The subclass includes more intelligent trimming of the field at a <!--break--> tag
 */
class cckbreaktag_handler_field_multiple extends content_handler_field_multiple {
  function option_definition() {
    $options = parent::option_definition();

    $options['alter']['contains']['cckbreaktag'] = array('default' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['alter']['cckbreaktag'] = array(
      '#title' => t('Respect &lt;!--break--> comment tag'),
      '#type' => 'checkbox',
      '#description' => t('If a &lt;!--break--> HTML comment is present, split the text there rather than at the word count'),
      '#default_value' => $this->options['alter']['cckbreaktag'],
      '#process' => array('views_process_dependency'),
      '#dependency' => array(
        'edit-options-alter-trim' => array(1)
      ),
    );
    $form['alter']['strip_tags']['#weight'] = 5;
  }

  function render_text($alter) {
    // Get our data and a handy regex
    $value = trim($this->last_render);
    $re = '/(<|&lt;)!--break-->';

    // Defer to parent method if option not set
    if (!$this->options['alter']['cckbreaktag'] || !preg_match("$re/", $value)) { return parent::render_text($alter); }

    // Not sure if setting last_render directly is safe, but it's the
    // only way to get the trimmed value into the parent method
    $this->last_render = preg_replace("$re.*/", "", $value);
    unset($alter['max_length']);

    // Call parent method to do any other tidying e.g. HTML
    return parent::render_text($alter);
  }


}
