<?php

namespace Drupal\parsely\Plugin\Block;

use Drupal\Core\Block\BlockBase;
use Drupal\Core\Block\BlockPluginInterface;
use Drupal\Core\Form\FormStateInterface;

/**
 * Provides a 'Hello' Block.
 *
 * @Block(
 *   id = "parsely_recommended_widget",
 *   admin_label = @Translation("Parsely Recommended Widget"),
 *   category = @Translation("Content Blocks"),
 * )
 */
class ParselyRecommendedBlock extends BlockBase implements BlockPluginInterface {

	/**
	 * {@inheritdoc}
	 */
	public function build() {
		return array(
			'#markup' => $this->t('Hello, World!'),
		);
	}

	public function blockForm($form, FormStateInterface $form_state) {
		$form = parent::blockForm($form, $form_state);

		$config = $this->getConfiguration();

		$form['parsely_recommended_block_title'] = array(
			'#type' => 'textfield',
			'#title' => $this->t('Block Title'),
			'#description' => $this->t('What is the block called?'),
			'#default_value' => isset($config['parsely_recommended_block_title']) ? $config['parsely_recommended_block_title'] : 'Replace Me!'
		);

		$form['parsely_recommended_block_published_within'] = array(
			'#type' => 'number',
			'#title' => $this->t('Published Within'),
			'#description' => $this->t('Only return articles published within the last X days (leave blank for no limit)'),
			'#default_value' => isset($config['parsely_recommended_block_published_within']) ? $config['parsely_recommended_block_published_within'] : 10
		);

		$form['parsely_recommended_block_published_within'] = array(
			'#type' => 'number',
			'#title' => $this->t('Published Within'),
			'#description' => $this->t('Only return articles published within the last X days (leave blank for no limit)'),
			'#default_value' => isset($config['parsely_recommended_block_published_within']) ? $config['parsely_recommended_block_published_within'] : 10
		);

		$form['parsely_recommended_block_sort_by'] = array(
			'#type' => 'select',
			'#title' => $this->t('Sort By'),
			'#description' => 'Sort by score (relevance) or recency (when it was published)',
			'#options' => [
				'score' => $this->t('score'),
				'recency' => $this->t('recency'),
			],
			'#multiple' => false,
			'#default_value' => 'score'
		);



		return $form;
	}

}