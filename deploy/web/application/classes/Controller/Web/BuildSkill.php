<?php defined('SYSPATH') or die('No direct script access.');
//This is the builds rendering page, needs to be moved to it's own model soon.
class Controller_Web_BuildSkill extends Template_Web_Core {

	public function before() {
		parent::before();
		$this->template->site->title = "Shadow Knight Build";
		$this->template->site->description = "Shadow Knight Custom Build For RebuildEQ";
		
	}

	public function action_index() {
		$class =  strtolower($this->request->param('class'));
		$skills = array();


		$skillid = intval($this->request->param('skillid'));
		$build = Build::get_build_info($class);
		$skills = Build::get_skills($class);

		if (empty($class) || empty($build) || empty($build->styles)) {
			$this->redirect('/builds/');
			return;
		}

		if (empty($skills[$skillid])) {
			$this->redirect('/builds/');
			return;
		}
		$skill = $skills[$skillid];
		$this->template->class = $class;
		$this->template->skill = $skill;
		$this->template->monogram = $build->monogram;
		$this->template->styles = $build->styles;
		$this->template->site->image = $skill->image;
		$this->template->site->title = $skill->title." | ".ucfirst($class);
		$this->template->fullName = $build->fullName;
		$this->template->classDescription = $build->desc;
		$this->template->site->description = strip_tags($skill->title." ".$skill->desc);
	}

}

