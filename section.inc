<?php

namespace Drupal\parsely;

/**
 * Attempt to determine the "section" to which a given node belongs.
 */
use Drupal\node\Entity\Node;

/**
 * @param $node Node
 * @return string
 */
function parsely_get_section($node) {
    $section_name = 'Uncategorized';
    $section_term = NULL;
    $section_logic = \Drupal::config('parsely_settings')->get('parsely_section_logic');

    switch($section_logic) {

        case 0:
            $section_id = \Drupal::config('parsely_settings')->get('parsely_section_by_node');
            $section_by_node_type = \Drupal::config('parsely.settings')->get('parsely_nodes');
            if (\Drupal::moduleHandler()->moduleExists('node') && !is_null($section_by_node_type)) {

                $node = \Drupal::routeMatch()->getParameter('node');
                if (in_array($node->type, $section_by_node_type)) {
                    $section_name = $node->type;
                }
            }
            break;

        case 1:
            $section_id = \Drupal::config('parsely_settings')->get('parsely_section_vocabulary');
            $section_vocabulary_id = \Drupal::config('parsely.settings')->get('parsely_section_vocabulary');

            if (\Drupal::moduleHandler()->moduleExists('taxonomy') && !is_null($section_vocabulary_id)) {
                // Find the most relevant term from the designated vocab, using the
                // criterion specified in the module configuration. See
                // parsely_admin_settings() for an explanation of the supported criteria.


                // "First term" or "Last term."


                // "Highest-level ancestor."

            }

            if ($section_term && property_exists($section_term, 'name')) {
                $section_name = $section_term->name;
            }
            break;

    }

    // Allow any module to alter the section name.
    \Drupal::moduleHandler()->alter('parsely_section', $section_name, $node, $section_term);

    return $section_name;
}


