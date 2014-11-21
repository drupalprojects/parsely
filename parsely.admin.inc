<?php
/**
 * @file
 * The admin file containing the menu callback function.
 */

/**
 * Menu callback for the String Overrides module to display administration
 */

function parsely_admin_settings($form, &$form_state) {
    // Required settings
    $form['parsely_apikey'] = array(
        '#type' => 'textfield',
        '#title' => t('Parse.ly Site ID'),
        '#description' => t('You can find your Site ID on your your <a target="_blank" href="@parsely_settings">API settings page</a>.',
                            array('@parsely_settings' => 'http://dash.parsely.com/to/settings/api?highlight=apikey')),
        '#default_value' => variable_get('parsely_apikey'),
    );

    if (module_exists('taxonomy')) {
        $form['parsely_tag_vocabularies'] = array(
            '#type' => 'checkboxes',
            '#title' => t('Tag Vocabularies'),
            '#options' => _parsely_vocab_array_format(taxonomy_get_vocabularies()),
            '#description' => t('Select which taxonomy vocabularies will be tracked as tags.'),
            '#default_value' => variable_get('parsely_tag_vocabularies', array()),
        );

        $form['parsely_section_vocabulary'] = array(
            '#type' => 'radios',
            '#title' => t('Section Vocabulary'),
            '#options' => _parsely_vocab_array_format(taxonomy_get_vocabularies()),
            '#description' => t('Select the taxonomy to use for Parse.ly sections. The first term in this vocabulary is used to populate the Parse.ly section variable.'),
            '#default_value' => variable_get('parsely_section_vocabulary', ''),
        );
    }
    // TODO: Should display warning if taxonomy module isn't available

    // Optional settings
    $form['parsely_optional_settings'] = array(
        '#type' => 'fieldset',
        '#title' => t('Optional Settings'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
    );
    $form['parsely_optional_settings']['parsely_content_id_prefix'] = array(
        '#type' => 'textfield',
        '#title' => t('Content ID Prefix'),
        '#description' => t('If you use more than one content management system (e.g. Drupal and WordPress), you may end up with duplicate content IDs. Adding a Content ID Prefix will ensure the content IDs from Drupal will not conflict with other content management systems.'),
        '#default_value' => variable_get('parsely_content_id_prefix', ''),
    );
    $form['parsely_optional_settings']['parsely_track_authenticated_users'] = array(
        '#type' => 'radios',
        '#title' => t('Track Authenticated Users'),
        '#description' => t('By default, the Parse.ly module will track the activity of users that are logged into this site. You can change this setting to only track the activity of anonymous visitors. Note: You will no longer see the Parse.ly tracking code on your site if you browse while logged in.'),
        '#options' => array(0 => t('No'), 1 => t('Yes')),
        '#default_value' => variable_get('parsely_track_authenticated_users', 1),
    );


    return system_settings_form($form);
}


function _parsely_vocab_array_format($vocabularies = NULL) {
    $vocab_array = array();
    foreach ($vocabularies as $vocab) {
        $vocab_array[$vocab->vid] = $vocab->name;
    }

    return $vocab_array;
}