<?php defined('SYSPATH') or die ('No direct script access.');

class Controller_Rest_Builds extends Template_Rest_Core {

	public function action_update() {
		$buildIndex = $this->request->post('buildindex');
		if (empty($buildIndex) || intval($buildIndex) > 53 || intval($buildIndex) < 1) {
			$this->rest->Message = "Invalid buildIndex: ".intval($buildIndex);
			return;
		}

		$session = $this->request->post('session');

		$character = DB::select()->from('character_data')
		->where('session', '=', $session)
		->where('session_timeout', '>=', DB::expr('NOW()'))
		->limit(1)
		->as_object()->execute()->current();

		if (empty($session)) {
			$this->rest->Message = "Missing POST session";
			return;
		}
		if (empty($character)) {
			$this->rest->Message = "Invalid Session";
			return;
		}
		$build = $character->build_data;
		$build = Build::clean($build);
		if (!Build::validate($build)) {
			$this->rest->Message = "Invalid Build Before Set";
			return;
		}
		$newBuild = $build;
		$newBuild[$buildIndex] = intval($newBuild[$buildIndex]) + 1;
		$newBuild = Build::clean($newBuild);
		if ($newBuild == $build) {
			$this->rest->Message = "Changes discarded, old and new builds are same.";
			return;
		}
		if (!Build::validate($newBuild)) {
			$this->rest->Message = "Invalid build request sent";
			return;
		}

		$data = array('build_data' => $newBuild);
		$query = DB::update('character_data')->set($data)->where('session', "=", $session)->limit(1)->execute();
		$this->rest->Status = 1;
		$this->rest->oldBuild = $build;
		$this->rest->newBuild = $newBuild;
		$this->rest->Message = "Success!";
		return;
	}

	public function validate_build($character, $build) {
		if (empty($build)) {
			return false;
		}
		if (empty($character)) {
			return false;
		}
		return true;
	}
}