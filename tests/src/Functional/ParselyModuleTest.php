<?php

namespace Drupal\Tests\parsely\Functional;

use Drupal\Tests\BrowserTestBase;

/**
 * Check if our user field works.
 *
 * @group test_example
 * @runTestsInSeparateProcesses
 * @preserveGlobalState disabled
 */
class ParselyModuleTest extends BrowserTestBase {

	/**
	 * @var \Drupal\user\Entity\User.
	 */
	protected $user;



	/**
	 * Enabled modules
	 */
	public static $modules = ['parsely'];

	/**
	 * {@inheritdoc}
	 */
	function setUp() {
		parent::setUp();

		$this->user = $this->drupalCreateUser();
		$this->node = $this->createNode(array(
			'title' => 'hello, world!',
			'type' => 'article'
		));
		$this->config = \Drupal::service('config.factory')->getEditable('parsely.settings');


	}

	/**
	 * Test that the user has a test_status field.
	 */
	public function testUserHasTestStatusField() {
		$this->assertTrue(in_array('test_status', array_keys($this->user->getFieldDefinitions())));
	}

}