<?php

namespace Drupal\parsely;

/**
 * Attempt to determine the "section" to which a given node belongs.
 */
/**
 * @param $node
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
                $selection_criterion = \Drupal::config('parsely.settings')->get('parsely_section_term_criterion');

                $section_term_query = \Drupal::database()->select('taxonomy_index', 'ti');
                $section_term_query->join('taxonomy_term_data', 'ttd', 'ti.tid=ttd.tid');
                $section_term_query->fields('ttd', array('tid'))
                    ->condition('ti.nid', $node->get('nid'))
                    ->condition('ttd.vid', $section_vocabulary_id);

                // "First term" or "Last term."
                if ($selection_criterion == 'first' || $selection_criterion == 'last') {
                    $sort_direction = ($selection_criterion == 'first') ? 'ASC' : 'DESC';
                    $section_term_query->orderBy('ttd.tid', $sort_direction)
                        ->range(0, 1);
                    $section_term_result = $section_term_query->execute();

                    if ($section_term_result->rowCount() > 0) {
                        $section_tid = $section_term_result->fetchField();
                        $section_term = \Drupal::entityTypeManager()->getStorage("taxonomy_term")->load($section_tid);
                    }
                }

                // "Highest-level ancestor."
                elseif ($selection_criterion == 'ancestor') {
                    $first_term_result = $section_term_query->orderBy('ti.created')
                        ->range(0, 1)
                        ->execute();

                    if ($first_term_result->rowCount() > 0) {
                        $first_term_tid = $first_term_result->fetchField();
                        $storage = \Drupal::EntityTypeManager()->getStorage('taxonomy_term');
                        $parents = $storage->loadAllParents($first_term_tid);
                        $section_term = array_pop($lineage);
                    }
                }
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


