<?php defined('SYSPATH') or die('No direct script access.');

class Controller_Web_Builds extends Template_Web_Core {


	public function before() {

		parent::before();
		$this->template->site->title = "Shadow Knight Build";
		$this->template->site->description = "Shadow Knight Custom Build For RebuildEQ";
		
	}

	public function action_index() {

		$class =  strtolower($this->request->param('class'));
		$skills = array();		

		//Validate Session
		$session = $this->request->param('session');

		if (!empty($session)) {
			//First see if session exists
			$sessionObject = DB::select('session')->from('character_data')->where('session', '=', $session)->as_object()->execute()->current();
			if (empty($sessionObject)) {
				$this->template->errorMessage = "Invalid Session Provided. Go in game and type #builds to create a new session.";
			}

			$tmpChar = DB::select('name, last_name, class, level, build_data')->from('character_data')->where('session', '=', $session)->where('session_timeout', '>=', DB::expr('NOW()'))->limit(1)->as_object()->execute()->current();
			if (empty($tmpChar)) {
				$this->template->errorMessage = "Expired Session provided. Go in game and type #builds to create a new session.";
			} else {
				$character = new stdClass();
				$character->name = $tmpChar->name;
				if (!empty($tmpChar->last_name)) {
					$character->name .= " ".$tmpChar->last_name;
				}
				$character->level = $tmpChar->level;
				$class = $this->convert_class($tmpChar->class);
				if (!empty($tmpChar->build_data)) {
					$build = Build::clean($tmpChar->build_data);
					if (!Build::validate($build, $tmpChar->level)) {
						$oldBuild = $build;						
						$build = "00000000000000000000000000000000000000000000000000000";
						$build = Build::clean($build);
						//mail("rebuildeq@gmail.com", "Invalid Build for ".$tmpChar->name, "The build raw:".$tmpChar->build_data."\nOld Build: $oldBuild\nResetting it to:".$build);
						$data = array('build_data' => $build);
						DB::update('character_data')->set($data)->where('session', "=", $session)->limit(1)->execute();
					}
					$this->template->hash = $build;
				}
				//guildname invalid
				$this->template->character = $character;
				$this->template->session = $session;
			}
		}

		//Validate Build
		$buildHash = $this->request->query('build');
		if (empty($character) && !empty($buildHash)) {
			//ValidateHash
			if (!Build::validate($buildHash)) {
				die("Invalid build");
			}
			$this->template->hash = $buildHash;
		}

		$build = $this->get_build_info($class);
		$skills = $this->get_skills($class);

		$this->template->skills = $skills;
		$this->template->monogram = $build->monogram;
		$this->template->styles = $build->styles;
		$this->template->site->image = "http://rebuildeq.com/images/monograms/".$build->monogram.".gif";
		$this->template->site->title = $build->fullName;
		$this->template->fullName = $build->fullName;
		$this->template->classDescription = $build->desc;
		$this->template->site->description = $build->desc;
	}

	private function convert_class($class) {
		if ($class == 1) return "warrior";
		if ($class == 2) return "cleric";
		if ($class == 3) return "paladin";
		if ($class == 4) return "ranger";
		if ($class == 5) return "shadowknight";
		if ($class == 6) return "druid";
		if ($class == 7) return "monk";
		if ($class == 8) return "bard";
		if ($class == 9) return "rogue";
		if ($class == 10) return "shaman";
		if ($class == 11) return "necromancer";
		if ($class == 12) return "wizard";
		if ($class == 13) return "magician";
		if ($class == 14) return "enchanter";
		return "shadowknight";
	}

	private function get_build_info($class) {
		$build = new stdClass();
		$build->styles = array();
		switch ($class) {
			//==================BARD======================
			case "bard":
			$build->fullName = "Bard";
			$build->monogram = 8;
			$build->desc = "Bards sing songs to aid allies in battle.<br> Their 3 styles focus on group, melee, or solo.";
			$build->styles[0] = "Virtuoso";
			$build->styles[1] = "Swordsinger";
			$build->styles[2] = "Maestro";
			break;
			//==================CLERIC======================
			case "cleric":
			$build->fullName = "Cleric";
			$build->monogram = 2;
			$build->desc = "Clerics are classically known as the best healers in the game.<br> Their 3 styles focus on melee, healing, or protection.";
			$build->styles[0] = "Templar";
			$build->styles[1] = "Bishop";
			$build->styles[2] = "Archon";
			break;
			//==================DRUID======================
			case "druid":
			$build->fullName = "Druid";
			$build->monogram = 6;
			$build->desc = "Druids are a mix of healer and damage dealer.<br> Their 3 styles focus on either Crowd Control, Heals, or Offense.";
			$build->styles[0] = "Preserver";
			$build->styles[1] = "Warden";
			$build->styles[2] = "Hierophant";
			break;
			//==================ENCHANTER======================
			case "enchanter":
			$build->fullName = "Enchanter";
			$build->monogram = 14;
			$build->desc = "Enchanters have had a heavy modification on Rebuild EQ.<br> Due to illusions no longer being easily accessible, illusions are now more offensive. Their builds focus on either debuffs, domination, or inspiration.";
			$build->styles[0] = "Illusionist";
			$build->styles[1] = "Entrancer";
			$build->styles[2] = "Beguiler";
			break;
			//==================MAGICIAN======================
			case "magician":
			$build->fullName = "Magician";
			$build->monogram = 13;
			$build->desc = "Magicians are conjurers of creatures from other planes or offensive specialists.<br> Their 3 styles focus on either stronger pets, area of effect damage, or empowering their utility skills";
			$build->styles[0] = "Conjurer";
			$build->styles[1] = "Elementalist";
			$build->styles[2] = "Geomancer";
			break;
			//==================MONK======================
			case "monk":
			$build->fullName = "Monk";
			$build->monogram = 7;
			$build->desc = "Monks are disciplined fighters.<br> Their 3 styles focus on either melee dps, supporting others with chakra abilities, or utility pulling.";
			$build->styles[0] = "Master";
			$build->styles[1] = "Transcendant";
			$build->styles[2] = "Ashenhand";
			break;
			//==================NECROMANCER======================
			case "necromancer":
			$build->fullName = "Necromancer";
			$build->monogram = 11;
			$build->desc = "Necromancers are master of the dead.<br> They have the best DoTs of any class with one focus. The other 2 focus on debuffs, and tanking.";
			$build->styles[0] = "Heretic";
			$build->styles[1] = "Lich";
			$build->styles[2] = "Warlock";
			break;
			//==================PALADIN======================
			case "paladin":
			$build->monogram = 3;
			$build->fullName = "Paladin";
			$build->desc = "Paladins are the holy knights.<br> Their 3 styles focus on better healing and support, tanking, or damage dealing.";
			$build->styles[0] = "Protector";
			$build->styles[1] = "Knight";
			$build->styles[2] = "Crusader";
			break;
			//==================RANGER======================
			case "ranger":
			$build->fullName = "Ranger";
			$build->monogram = 4;
			$build->desc = "Rangers are friends with beasts.<br> Their 3 styles focus on either better archery, enabling and strengthening a beast companion, or supporting others.";
			$build->styles[0] = "Archer";
			$build->styles[1] = "Hunter";
			$build->styles[2] = "Plainswalker";
			break;
			//==================ROGUE======================
			case "rogue":
			$build->fullName = "Rogue";
			$build->monogram = 9;
			$build->desc = "Rogues are thieves who specialize in deception.<br> Their 3 styles focus on dealing damage, being an evasive tank, or stealing.";
			$build->styles[0] = "Assassin";
			$build->styles[1] = "Deceiver";
			$build->styles[2] = "Bandit";
			break;
			//==================SHAMAN======================
			case "shaman":
			$build->fullName = "Shaman";
			$build->monogram = 10;
			$build->desc = "Shamans are one with spirits. <br><font color='#41974D'>Prophet</font> specializes in healing<br> <font color='#2A87C7'>Oracle</font> focus on debuffs/DoTs/pet<br> <font color='#A93640'>Elder</font> excel at melee/procs";
			$build->styles[0] = "Prophet";
			$build->styles[1] = "Oracle";
			$build->styles[2] = "Elder";
			break;
			//==================WARRIOR======================
			case "warrior":
			$build->fullName = "Warrior";
			$build->monogram = 1;
			$build->desc = "Warriors are hearty duelists.<br> Gladiators will hone their blade mastery to allow them to deal damage unheard of before, Brawlers live off the thrill of battle, and Champions seek glory with their ability to survive.";
			$build->styles[0] = "Gladiator";
			$build->styles[1] = "Brawler";
			$build->styles[2] = "Champion";
			break;
			//==================WIZARD======================
			case "wizard":
			$build->fullName = "Wizard";
			$build->monogram = 12;
			$build->desc = "Wizards are masters of the elements.<br> Evokers deal high elemental damage. Channelers focus on utility, while Sage is focused on support.";
			$build->styles[0] = "Evoker";
			$build->styles[1] = "Channeler";
			$build->styles[2] = "Sage";
			break;
			//==================SHADOWKNIGHT======================
			case "shadowknight":
			default:
			$class = "shadowknight";
			$build->fullName = "Shadow Knight";
			$build->monogram = 5;
			
			$build->desc = "Shadow Knights are fighters with necromancer powers.<br><font color='#41974D'>Bloodreaver</font> specializes in tanking and lifetaps.<br> <font color='#2A87C7'>Defiler</font> focus on dealing damage.<br> <font color='#A93640'>Revenant</font> excel at pulling.";
			$build->styles[0] = "Bloodreaver";
			$build->styles[1] = "Defiler";
			$build->styles[2] = "Revenant";
			break;
		}
		return $build;
	}

	private function get_skills($class) {

		$skills = array();
		switch($class) {
			//==================BARD======================
			case "bard":
			break;
			//==================CLERIC======================
			case "cleric":
			//0
			$newSkill = new stdClass();
			$newSkill->title = "Divine Bash";
			$newSkill->desc = 'Bash now has a chance to heal nearby group members for <em data-base="2">2</em>% of your maximum health<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[0] = $newSkill;
			break;

			//4
			$newSkill = new stdClass();
			$newSkill->title = "Harken the Gods";
			$newSkill->desc = 'Yaulp now also grants <em data-base="5">5</em> accuracy, <em data-base="5">5</em> attack, and <em data-base="2">2</em> mana regen<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[4] = $newSkill;

			//6
			$newSkill = new stdClass();
			$newSkill->title = "Blessing of Haste";
			$newSkill->desc = 'All spell haste you cast is now <em data-base="5">5</em> accuracy, <em data-base="5">5</em> attack, and <em data-base="2">2</em> mana regen<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[6] = $newSkill;

			//8
			$newSkill = new stdClass();
			$newSkill->title = "Hammer of Justice";
			$newSkill->desc = 'Empowers the summoned hammer line with stronger versions<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[8] = $newSkill;
			break;


			//==================DRUID======================
			case "druid":
			break;
			//==================ENCHANTER======================
			case "enchanter":
			break;
			//==================MAGICIAN======================
			case "magician":
			break;
			//==================MONK======================
			case "monk":
			break;
			//==================NECROMANCER======================
			case "necromancer":
			break;
			//==================PALADIN======================
			case "paladin":
			$newSkill = new stdClass();
			$newSkill->title = "Rodcet's Gift";
			$newSkill->desc = 'Instant healing spells have a <em data-base="2">2</em>% chance to heal the entire group<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[0] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Hand of Piety";
			$newSkill->desc = 'Grants the Hand of Piety AA, allowing the user to heal a target for <em data-base="2">2</em>% of their max health <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[2] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Instill Purpose";
			$newSkill->desc = 'Divine Purpose and Breath of Tunare now grant <em data-base="20">20</em>% more hitpoint regeneration <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[4] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Refreshing Breeze";
			$newSkill->desc = 'Instant heals have a <em data-base="1">1</em>% chance to grant mana to the healed target<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[6] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Elixir of Nife";
			$newSkill->desc = 'Nife proc effects now also grant a chance to cause a group heal for <em data-base="1">1</em>% of a member\'s max hitpoints as well as give mana back to the Paladin<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Soul Cleansing";
			$newSkill->desc = 'Cleansing heal over time spells now have a <em data-base="2">2</em>% chance per rank to cure an ailment<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[10] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Placeholder";
			$newSkill->desc = 'Placeholder <em data-base="2">2</em>% chance per rank to cure an ailment<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[13] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Wave of Marr";
			$newSkill->desc = 'All wave-based group spells cost <em data-base="10">10</em>% less mana to cast<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[16] = $newSkill;


			$newSkill = new stdClass();
			$newSkill->title = "Shield of Nife";
			$newSkill->desc = 'Grants an Undead-only damage shield that deals <em data-base="7">7</em> damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[18] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Armor of Faith";
			$newSkill->desc = 'Damage taken from Undead have a <em data-base="1">1</em>% chance to be reduced by <em data-base="12">12</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[20] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Purification";
			$newSkill->desc = 'Grants the Purification AA, causing a <em data-base="2">2</em>% chance that all negative effects on self are cured<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[22] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Holy Servant";
			$newSkill->desc = 'When a nearby group member is attacked, there is a <em data-base="2">2</em>% chance that <em data-base="5">5</em>% of the dealt damage is redirected to the paladin reduced by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[24] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Divine Stun";
			$newSkill->desc = 'Grants the Divine Stun AA, causing a target to be stunned and marked with divine anger. Any time the Paladin casts a heal spell on a group member, the marked enemy gains an additional <em data-base="200">200</em>hatred<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[26] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Act of Valor";
			$newSkill->desc = 'Grants the Act of Valor AA, summoning a squire that dutifully assist the Paladin, while also granting a divine intervention save to group members by healing them for <em data-base="20">20</em>% of his health<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[28] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Ward of Tunare";
			$newSkill->desc = 'Passively grants Ward of Tunare, causing a <em data-base="3">3</em>% chance a heal for <em data-base="10">100</em> hitpoints will trigger when taking damage from an enemy<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[31] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Resist Temptation";
			$newSkill->desc = 'Grants a defensive discipline as well as a high magic resistance for <em data-base="60">60</em> seconds <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[34] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Zealot's Fervor";
			$newSkill->desc = 'Any time a heal is casted by a paladin, up to <em data-base="1">1</em> enemies are dealt <em data-base="1">1</em>% of the healing as damage. <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[36] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Knight's Advantage";
			$newSkill->desc = '2 handed weapons deal an additional <em data-base="5">5</em>% damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[38] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Chosen";
			$newSkill->desc = 'All self proc buffs deal <em data-base="25">25</em>% more damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[40] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Purpose of Marr";
			$newSkill->desc = 'Valor of Marr now grants <em data-base="10">10</em>% additional attack speed<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[42] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Flame of Light";
			$newSkill->desc = 'Flame of Light now deals an additional <em data-base="20">20</em>% damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[44] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Dismiss Evil";
			$newSkill->desc = 'When attacking an evil creature, gives a <em data-base="1">1</em>% chance to critical hit<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[46] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Frail";
			$newSkill->desc = 'Stuns have a <em data-base="1">1</em>% chance to also root the target<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[49] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Slay Undead";
			$newSkill->desc = 'Grants the passive Slay Undead with a <em data-base="1">1</em>% chance<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[52] = $newSkill;


			break;
			//==================RANGER======================
			case "ranger":
			break;
			//==================ROGUE======================
			case "rogue":
			break;
			//==================SHAMAN======================
			case "shaman":
			//0
			$newSkill = new stdClass();
			$newSkill->title = "Spirit of Speed";
			$newSkill->desc = 'Spirit of Wolf lasts <em data-base="20">20</em>% longer<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[0] = $newSkill;
			//1
			//2
			$newSkill = new stdClass();
			$newSkill->title = "Purify Soul";
			$newSkill->desc = 'Grants the Purify Soul AA, which cures target of disease, poison, as well as gives a <em data-base="10">10</em>% chance to heal the target by <em data-base="1">1</em>% max HP per tick regen<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-1.png";
			$skills[2] = $newSkill;
			//3
			//4
			$newSkill = new stdClass();
			$newSkill->title = "Ancestral Aid";
			$newSkill->desc = 'Grants the Ancestral Aid AA, which casts focus line buff scaled to your level.<br>Rank 1: +STR<br>Rank 2: +DEX<br>Rank 3: +AGI<br>Rank 4: +STA<br>Rank 5: +HP';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-3.png";
			$skills[4] = $newSkill;
			//5
			//6
			$newSkill = new stdClass();
			$newSkill->title = "Extended Haste";
			$newSkill->desc = 'Improves attack speed spells used by the caster by increasing their duration by <em data-base="30">30</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-4.png";
			$skills[6] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Spiritual Healing";
			$newSkill->desc = 'Heals recover an additional <em data-base="20">20</em>% health<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-8.png";	
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Covenant of Spirit";
			$newSkill->desc = 'Grants the Covenent of Spirit AA, which imbues divine intervention on the target with a <em data-base="2">2</em>% chance to save<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-1.png";	
			$skills[10] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Reinforce Torpor";
			$newSkill->desc = 'Reduces the negative effects of Torpor by <em data-base="20">20</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-2.png";	
			$skills[13] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Fateseeler's Boon";
			$newSkill->desc = 'Grants a group buff that increases critical damage by 70% with all skills, chance to critical hit by 50% with all skills, as well as a 400 hitpoint per tick regen. Each rank reduces recast by<em data-base="30">30</em> seconds<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-3.png";	
			$skills[16] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Cannibalize";
			$newSkill->desc = 'Grants the Cannibalization AA, increasing effectiveness by <em data-base="10">10</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-4.png";	
			$skills[18] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Spirit Call";
			$newSkill->desc = 'Grants the Spirit Call AA, granted a new pet with <em data-base="10">10</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-5.png";	
			$skills[20] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Virulent Paralysis";
			$newSkill->desc = 'Grants the Virulent Paralysis AA, causing a target to be immobilized. Each rank increases duration by <em data-base="6">6</em> seconds <span class="perLevel"> per rank</span>. At max rank, also knocks back target.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-6.png";	
			$skills[22] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Poison";
			$newSkill->desc = 'All poison-based DoTs now deal <em data-base="5">5</em>% additional damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-8.png";	
			$skills[24] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Extended Turgur";
			$newSkill->desc = 'Increases duration of slow by <em data-base="5">5</em>% as well as penetrates magic defense by <em data-base="5">5</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-0.png";	
			$skills[26] = $newSkill;
			//37
			//38
			$newSkill = new stdClass();
			$newSkill->title = "Ancient Wrath";
			$newSkill->desc = 'All direct damage spells now deal <em data-base="10">10</em>% more damage as well as <em data-base="1">1</em>% chance to critical hit<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-1.png";
			$skills[28] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Turgur's Echo";
			$newSkill->desc = 'When a slow-based spell is resisted, the spell will have a <em data-base="2">2</em>% chance to try again to land.<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-2.png";	
			$skills[31] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Spiritual Channeling";
			$newSkill->desc = 'While this ability is active, all spells cost HP rather than mana. Cooldown of reuse is reduced by <em data-base="6">6</em>seconds<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-3.png";	
			$skills[34] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Fury";
			$newSkill->desc = 'Fleeting Fury now grants a proc line similar to puma with <em data-base="20">20</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-4.png";	
			$skills[36] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Rabid Bear";
			$newSkill->desc = 'Grants the Rabid Bear AA, granting <em data-base="2">2</em>% attack speed and the tainted bite proc line with <em data-base="20">20</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-4.png";	
			$skills[38] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Ancestral Guard";
			$newSkill->desc = 'Grants the Ancestral Guard AA, granting <em data-base="2">2</em>% chance of evading damage with mitigation<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-4.png";	
			$skills[40] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Call of the Ancients";
			$newSkill->desc = 'Grants the Call of the Ancients AA, summoning a spirit that deals <em data-base="1">1</em> of an enemy\'s current health (maximum <em data-base="100">100</em>) per attack<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-4.png";	
			$skills[42] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Spiritual Wrath";
			$newSkill->desc = 'Grants the Spiritual Wrath AA, attacking your target<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-4.png";	
			$skills[44] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Mark of Sloth";
			$newSkill->desc = 'On each attack, grants a chance to trigger a sloth effect, causing the next direct damage spell to deal <em data-base="5">5</em>% bonus damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-4.png";	
			$skills[46] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Feral Swipe";
			$newSkill->desc = 'Grants the Feral Swipe AA, giving a bonus attack ability with <em data-base="5">5</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-4.png";	
			$skills[49] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Paragon of Spirit";
			$newSkill->desc = 'Grants the Paragon of Spirit AA, giving a mana and hp regen ability <em data-base="20">20</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/gunzerker-gunlust-4.png";	
			$skills[52] = $newSkill;

			break;
			//==================WARRIOR======================
			case "warrior":

			break;
			//==================WIZARD======================
			case "wizard":

			break;
			//==================SHADOWKNIGHT======================
			case "shadowknight":
			default:
			//0
			$newSkill = new stdClass();
			$newSkill->title = "Leech Touch";
			$newSkill->desc = 'Grants the Leech Touch AA, improves lifetap damage by <em data-base="4">4</em>% and <em data-base="1">1</em>% chance to critical heal<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-leechtouch.png";	
			$skills[0] = $newSkill;
			//1
			//2
			$newSkill = new stdClass();
			$newSkill->title = "Gouging Skin";
			$newSkill->desc = 'When attacked, causes a <em data-base="+4">+4</em> point damage shield and <em data-base="+20">+20</em> hate<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-gougingskin.png";	
			$skills[2] = $newSkill;
			//3
			//4
			$newSkill = new stdClass();
			$newSkill->title = "Hungering Aura";
			$newSkill->desc = 'Improves lifetaps by <em data-base="+6">+6</em>% healing for each enemy attacking you with a maximum of <em data-base="+1">+1</em> enemies<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-hungeringaura.png";	
			$skills[4] = $newSkill;
			//5
			//6
			$newSkill = new stdClass();
			$newSkill->title = "Steadfast Servant";
			$newSkill->desc = 'Grants the Steadfast Servant, summoning a pet at <em data-base="+20">+20</em>% power<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-steadfastservant.png";	
			$skills[6] = $newSkill;
			//7
			//8
			$newSkill = new stdClass();
			$newSkill->title = "Zevfeer's Feast";
			$newSkill->desc = 'Improves Siphon Strength and Abduct Strength to tap the target for HP and Mana for up to <em data-base="+1">+1</em>% your maximum health and mana<span class="perLevel"> per rank</span> to give it to group.';
			$newSkill->image = "/images/builds/icons/rb-sk-zevfeersfeast.png";	
			$skills[8] = $newSkill;
			//9
			//10
			$newSkill = new stdClass();
			$newSkill->title = "Sworn Enemy";
			$newSkill->desc = 'When you use taunt, you mark a target as your sworn enemy. For the next 3 ticks, any spell damage dealt to target causes an additional <em data-base="100">100</em> hate<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-swornenemy.png";	
			$skills[10] = $newSkill;
			//11
			//12
			//13
			$newSkill = new stdClass();
			$newSkill->title = "Banshee's Mirror";
			$newSkill->desc = 'Banshee\'s Aura now has a <em data-base="+1">+1</em>% chance to reduce <em data-base="+3">+3</em>% of damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-bansheesmirror.png";
			$skills[13] = $newSkill;
			//14
			//15
			//16
			$newSkill = new stdClass();
			$newSkill->title = "Aura of Vampirism";
			$newSkill->desc = 'Grants the entire group <em data-base="+4">+4</em>% spell vampirism and <em data-base="+10">+10</em>% melee vampirism<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-auraofvampirism.png";	
			$skills[16] = $newSkill;
			//17
			// TIER 2
			//18
			$newSkill = new stdClass();
			$newSkill->title = "Festering Spear";
			$newSkill->desc = 'Improve spear type spells by (level * <em data-base="1">1</em>) bonus damage, <em data-base="10">10</em>% damage, and <em data-base="1">1</em>% critical blast chance <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-festeringspear.png";
			$skills[18] = $newSkill;
			//19
			//20
			$newSkill = new stdClass();
			$newSkill->title = "Festering Wound";
			$newSkill->desc = 'Improves DoT damage by <em data-base="+4">+4</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-festeringwound.png";	
			$skills[20] = $newSkill;
			//21
			//22
			$newSkill = new stdClass();
			$newSkill->title = "Rotten Core";
			$newSkill->desc = 'Increases attack by <em data-base="+8">+8</em>% for a short duration each time a target dies nearby with a maximum of <em data-base="+1">+1</em> enemies<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-rottencore.png";	
			$skills[22] = $newSkill;
			//23
			//24
			$newSkill = new stdClass();
			$newSkill->title = "Lingering Pain";
			$newSkill->desc = 'All direct damage spells have a <em data-base="1">1</em>%<span class="perLevel"> per rank</span> chance to cause bonus damage over time effects.';
			$newSkill->image = "/images/builds/icons/rb-sk-lingeringpain.png";
			$skills[24] = $newSkill;
			//25
			//26
			$newSkill = new stdClass();
			$newSkill->title = "Blood Oath";
			$newSkill->desc = 'While using a 2 handed weapon, increases damage by <em data-base="10">10</em>%, while causing negative effects of healing gets reduced by <em data-base="20">20</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-bloodoath.png";	
			$skills[26] = $newSkill;					
			//27
			//28
			$newSkill = new stdClass();
			$newSkill->title = "Gift of Urash";
			$newSkill->desc = 'Increases all skill damage by <em data-base="+5">+5</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-giftofurash.png";	
			$skills[28] = $newSkill;
			//29
			//30
			//31
			$newSkill = new stdClass();
			$newSkill->title = "Unholy Focus";
			$newSkill->desc = 'Improves all direct damage spells to penetrate <em data-base="10">10</em>% spell resists<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-unholyfocus.png";	
			$skills[31] = $newSkill;
			//32
			//33
			//34
			$newSkill = new stdClass();
			$newSkill->title = "Bash of Death";
			$newSkill->desc = 'When you bash a target, there is a <em data-base="1">1</em>% chance to cast harm touch<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-bashofdeath.png";	
			$skills[34] = $newSkill;
			//35
			// TIER 3
			//36
			$newSkill = new stdClass();
			$newSkill->title = "Embrace Death";
			$newSkill->desc = 'Grants you the Death Peace AA, giving the ability to feign death as well as heal you for <em data-base="+2">+2</em>% maximum health on use<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-embracedeath.png";	
			$skills[36] = $newSkill;
			//37
			//38
			$newSkill = new stdClass();
			$newSkill->title = "Darkness";
			$newSkill->desc = 'All darkness type spells slow movement for an additional <em data-base="4">4</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-darkness.png";	
			$skills[38] = $newSkill;
			//39
			//40
			$newSkill = new stdClass();
			$newSkill->title = "Empathetic Soul";
			$newSkill->desc = 'Improves Dark Empathy by granting an additional <em data-base="+40">+40</em> hitpoints healed and <em data-base="+0.5">+0.5</em>% max mana <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-empatheticsoul.png";	
			$skills[40] = $newSkill;
			//41
			//42
			//43
			$newSkill = new stdClass();
			$newSkill->title = "Embrace Shadow";
			$newSkill->desc = 'Each time you feign death, grants a <em data-base="20">20</em>% chance<span class="perLevel"> per rank</span> to instantly be invisible to both living and undead creatures.';
			$newSkill->image = "/images/builds/icons/rb-sk-embraceshadow.png";	
			$skills[43] = $newSkill;
			//44
			//45
			//46
			$newSkill = new stdClass();
			$newSkill->title = "Siphon of Death";
			$newSkill->desc = 'Scream of Death and Shroud of Death now also grant a mana tap for <em data-base="5">5</em>% of damage dealt<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-siphondeath.png";	
			$skills[46] = $newSkill;					
			//47
			//48
			$newSkill = new stdClass();
			$newSkill->title = "Nightmare";
			$newSkill->desc = 'Fear now causes target to freeze in panic for <em data-base="2">2</em>seconds<span class="perLevel"> per rank</span> before fleeing.';
			$newSkill->image = "/images/builds/icons/rb-sk-nightmare.png";
			$skills[48] = $newSkill;					
			//49
			//50
			$newSkill = new stdClass();
			$newSkill->title = "Mental Resistance";
			$newSkill->desc = 'Gives a <em data-base="2">2</em>% chance to resist stun effects<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-sk-mentalresistance.png";	
			$skills[50] = $newSkill;
			//51
			//52
			$newSkill = new stdClass();
			$newSkill->title = "Cloak of Shadows";
			$newSkill->desc = 'Grants the Cloak of the Shadows AA, allowing you to step into the shadows, causing a <em data-base="5">5</em>% chance that all targets will forget your actions.';
			$newSkill->image = "/images/builds/icons/rb-sk-cloakofshadow.png";
			$skills[52] = $newSkill;
			//53
		
			break;
		}
		return $skills;
	}
}

