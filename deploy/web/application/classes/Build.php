<?php defined('SYSPATH') or die('No direct script access.');

class Build {
	public static function clean($build) {
		$skipElements = array(1, 3, 5, 7,9, 11, 12, 14, 15, 17, 19, 21, 23, 25, 27, 29, 30, 32, 33, 35, 37, 39, 41, 43, 45, 47, 48, 50, 51,  53);
		$skipElements = array_flip($skipElements);
		//Validate For tier-reqs TOTALS
		for ($i = 0; $i < 53; $i++) {
			if (strlen($build) <= $i) { //if an element doesn't exist, pad it with 0
				$build[$i] = "0";
			} else if (isset($skipElements[$i])) { //if an element is an invalid element, skip it
				$build[$i] = "0";
			}
		}
		$build = substr($build, 0, 53); //trim it to max 53
		return $build;
	}

	public static function validate($build, $level) {
		$tier11 = 0;
		$tier12 = 0;
		$tier13 = 0;
		$tier14 = 0;
		$tier15 = 0;
		$tier16 = 0;
		$tier21 = 0;
		$tier22 = 0;
		$tier23 = 0;
		$tier24 = 0;
		$tier25 = 0;
		$tier26 = 0;
		$tier31 = 0;
		$tier32 = 0;
		$tier33 = 0;
		$tier34 = 0;
		$tier35 = 0;
		$tier36 = 0;
		$level = intval($level);
		if ($level > 60 || $level < 1) {
			return false;
		}
		

		$grandTotal = 0;
		//Validate For tier-reqs TOTALS
		for ($i = 0; $i < 53; $i++) {
			if (strlen($build) <= $i) {
				$val = 0;
			} else {
				$val = intval($build[$i]);
			}
			if ($val > 5 || $val < 0) return false;

			if ($i >= 0 && $i <= 2) $tier11 += $val;
			if ($i >= 18 && $i <= 20) $tier21 += $val;
			if ($i >= 36 && $i <= 38) $tier31 += $val;

			if ($i >= 3 && $i <= 5) $tier12 += $val;
			if ($i >= 21 && $i <= 23) $tier22 += $val; 
			if ($i >= 39 && $i <= 41) $tier32 += $val;

			if ($i >= 6 && $i <= 8) $tier13 += $val;
			if ($i >= 24 && $i <= 26) $tier23 += $val;
			if ($i >= 42 && $i <= 44) $tier33 += $val;

			if ($i >= 9 && $i <= 11) $tier14 += $val;
			if ($i >= 27 && $i <= 29) $tier24 += $val;
			if ($i >= 45 && $i <= 47) $tier34 += $val;

			if ($i >= 12 && $i <= 14) $tier15 += $val;
			if ($i >= 30 && $i <= 32) $tier25 += $val;
			if ($i >= 48 && $i <= 50) $tier35 += $val;


			if ($i >= 15 && $i <= 17) $tier16 += $val;
			if ($i >= 33 && $i <= 35) $tier26 += $val;
			if ($i >= 51 && $i <= 53) $tier36 += $val;
			$grandTotal += $val;
		}

		$tierTotal = 0;
		if ($tier12 >= 1 && $tier11 < 5) return false;
		$tierTotal += $tier12 + $tier11;
		if ($tier13 >= 1 && $tierTotal < 10) return false;
		$tierTotal += $tier13;
		if ($tier14 >= 1 && $tierTotal < 15) return false;
		$tierTotal += $tier14;
		if ($tier15 >= 1 && $tierTotal < 20) return false;
		$tierTotal += $tier15;
		if ($tier16 >= 1 && $tierTotal < 25) return false;

		$tierTotal = 0;
		if ($tier22 >= 1 && $tier21 < 5) return false;
		$tierTotal += $tier21 + $tier22;
		if ($tier23 >= 1 && $tierTotal < 10) return false;
		$tierTotal += $tier23;
		if ($tier24 >= 1 && $tierTotal < 15) return false;
		$tierTotal += $tier24;
		if ($tier25 >= 1 && $tierTotal < 20) return false;
		$tierTotal += $tier25;
		if ($tier26 >= 1 && $tierTotal < 25) return false;		

		$tierTotal = 0;
		if ($tier32 >= 1 && $tier31 < 5) return false;
		$tierTotal += $tier32 + $tier31;
		if ($tier33 >= 1 && $tierTotal < 10) return false;
		$tierTotal += $tier33;
		if ($tier34 >= 1 && $tierTotal < 15) return false;
		$tierTotal += $tier34;
		if ($tier35 >= 1 && $tierTotal < 20) return false;
		$tierTotal += $tier35;
		if ($tier36 >= 1 && $tierTotal < 25) return false;		
		if ($grandTotal > $level) {
			return false;
		}

		return true;
	}


	public static function convert_class($class) {
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
		return "unknown";
	}

	public static function get_build_info($class) {
		$build = new stdClass();
		$build->styles = array();
		switch ($class) {
			//==================BARD======================
			case "bard":
			$build->fullName = "Bard";
			$build->monogram = 8;
			$build->desc = "Bards are enhanced with their songs being more powerful, focused on utility.<br>
			Cassindra's Secret is a second form of mana song.<br>
			Many new combat enhancements assist bards in their usefulness.";
			$build->styles[0] = "Virtuoso";
			$build->styles[1] = "Swordsinger";
			$build->styles[2] = "Maestro";
			break;
			//==================CLERIC======================
			case "cleric":
			$build->fullName = "Cleric";
			$build->monogram = 2;
			$build->desc = "Clerics have adapted to be more combat ready, focused on healing.<br>
			Clerics focus on many procs.<br>
			Clerics no longer have complete heal.<br>
			Healer classes have an innate mana tap when they melee.";
			$build->styles[0] = "Templar";
			$build->styles[1] = "Bishop";
			$build->styles[2] = "Archon";
			break;
			//==================DRUID======================
			case "druid":
			$build->fullName = "Druid";
			$build->monogram = 6;
			$build->desc = "Druids have been enhanced in their heal role, focused on healing.<br>
			DoTs can be built to do significant damage.<br>
			Healer classes have an innate mana tap when they melee.";
			$build->styles[0] = "Preserver";
			$build->styles[1] = "Warden";
			$build->styles[2] = "Hierophant";
			break;
			//==================ENCHANTER======================
			case "enchanter":
			$build->fullName = "Enchanter";
			$build->monogram = 14;
			$build->desc = "Enchanters have mastered magic, focused on utility.<br>
			They are very effective at shutting down caster enemies with backfire.<br>
			Mesmerize only lasts 1 tick until you train Enthrall.<br>
			Shallow-breath line spells only last 1 tick until you train Drown.";
			$build->styles[0] = "Illusionist";
			$build->styles[1] = "Entrancer";
			$build->styles[2] = "Beguiler";
			break;
			//==================MAGICIAN======================
			case "magician":
			$build->fullName = "Magician";
			$build->monogram = 13;
			$build->desc = "Magicians specialize in conjuration of items, focused on utility.<br>
			Their pets are significantly weaker than live EQ, and do not hold aggro well.";
			$build->styles[0] = "Conjurer";
			$build->styles[1] = "Elementalist";
			$build->styles[2] = "Geomancer";
			break;
			//==================MONK======================
			case "monk":
			$build->fullName = "Monk";
			$build->monogram = 7;
			$build->desc = "Monks are disciplined fighters who help allies and pull enemies, focused on utility.<br>
			Monks do not compare to the damage of Rogues.<br>
			Monks do not need to worry about weight, their AC bonus always applies.";
			$build->styles[0] = "Master";
			$build->styles[1] = "Transcendant";
			$build->styles[2] = "Ashenhand";
			break;

			//==================NECROMANCER======================
			case "necromancer":
			$build->fullName = "Necromancer";
			$build->monogram = 11;
			$build->desc = "Necromancers have mastered the black arts manipulating both the living and dead, focused on utility.<br>
			Their pets are significantly weaker than live EQ, and do not hold aggro well.";
			$build->styles[0] = "Heretic";
			$build->styles[1] = "Lich";
			$build->styles[2] = "Warlock";
			break;

			//==================PALADIN======================
			case "paladin":
			$build->monogram = 3;
			$build->fullName = "Paladin";
			$build->desc = "Paladins are a mix of warrior and cleric, focused on tank.<br>
			With the Protector line, they can nearly be a viable healer choice.<br>
			Tanks are able to unlock the Charm of Defense, giving Defensive Discipline.";
			$build->styles[0] = "Protector";
			$build->styles[1] = "Knight";
			$build->styles[2] = "Crusader";
			break;

			//==================RANGER======================
			case "ranger":
			$build->fullName = "Ranger";
			$build->monogram = 4;
			$build->desc = "Rangers are a mix of warrior and druid, focused on utility.<br>
			Within a group, they are viable archers to deal ranged damage.";
			$build->styles[0] = "Archer";
			$build->styles[1] = "Hunter";
			$build->styles[2] = "Plainswalker";
			break;

			//==================ROGUE======================
			case "rogue":
			$build->fullName = "Rogue";
			$build->monogram = 9;
			$build->desc = "Rogues are assassins who specialize in deception, focused on damage.<br>
			Rogues are the best damage dealers in the melee classification.";
			$build->styles[0] = "Assassin";
			$build->styles[1] = "Deceiver";
			$build->styles[2] = "Bandit";
			break;

			//==================SHAMAN======================
			case "shaman":
			$build->fullName = "Shaman";
			$build->monogram = 10;
			$build->desc = "Shamans weild spiritual powers to bring aid to allies, focused on healing.<br>
			Healer classes have an innate mana tap when they melee.";
			$build->styles[0] = "Prophet";
			$build->styles[1] = "Oracle";
			$build->styles[2] = "Elder";
			break;

			//==================WARRIOR======================
			case "warrior":
			$build->fullName = "Warrior";
			$build->monogram = 1;
			$build->desc = "Warriors are masters of weapons, focused on tank.<br>
			Warriors are no longer the definitive best tank, competing with the Knights with defensive disciplines.<br>
			Tanks are able to unlock the Charm of Defense, giving Defensive Discipline";
			$build->styles[0] = "Gladiator";
			$build->styles[1] = "Brawler";
			$build->styles[2] = "Champion";
			break;

			//==================WIZARD======================
			case "wizard":
			$build->fullName = "Wizard";
			$build->monogram = 12;
			$build->desc = "Wizards are masters of the elements, focused on damage.<br>
			Wizards deal the highest damage of all magical users.";
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
			$build->desc = "Shadow Knights are a mix between warrior and necromancer, focused on tank.<br>
			Tanks are able to unlock the Charm of Defense, giving Defensive Discipline.";
			$build->styles[0] = "Bloodreaver";
			$build->styles[1] = "Defiler";
			$build->styles[2] = "Revenant";
			break;
		}
		return $build;
	}

	public static function get_skills($class) {

		$skills = array();
		switch($class) {
			//==================BARD======================
			case "bard":
			$newSkill = new stdClass();
			$newSkill->title = "Elemental Harmony";
			$newSkill->desc = 'Resistant songs (lvl 9) now grant an additional <em data-base="10">10</em> resistance to each resistance type<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-elementalharmony.png";	
			$skills[0] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Healing Treble";
			$newSkill->desc = 'Healing effects on songs (lvl 6) are <em data-base="10">10</em>% more effective<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-healingtreble.png";	
			$skills[2] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Psalm of Norrath";
			$newSkill->desc = 'Damage shield effects on songs (lvl 25) are <em data-base="20">20</em>% more effective<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-psalmofnorrath.png";	
			$skills[4] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Cassindra's Chorus";
			$newSkill->desc = 'Mana effects on songs (lvl 20) are <em data-base="10">10</em>% more effective<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-cassindraschorus.png";	
			$skills[6] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Shield of Songs";
			$newSkill->desc = 'Rune effects on songs (lvl 49) are <em data-base="20">20</em>% more effective<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-shieldofsongs.png";	
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Katta's Concord";
			$newSkill->desc = 'Katta\'s Song of Sword (lvl 39) now also gives a 100 proc chance to those with the buff that deals (level * <em data-base="0.4">0.4</em>) damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-kattasconcord.png";
			$skills[10] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Cassindra's Secret";
			$newSkill->desc = 'Enhances Cassindra\'s Elegy (lvl 44) to also give <em data-base="2">2</em> mana<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-rizlonaspurpose.png";	
			$skills[13] = $newSkill;

			//http://everquest.allakhazam.com/db/spell.html?spell=6239
			$newSkill = new stdClass();
			$newSkill->title = "Kinsong";
			$newSkill->desc = 'Grants the Lesson of the Devoted AA, Increasing the groups spell critical dot dmg, dot, and accuracy. 10 minute recast time, each rank reduces recast by 30 seconds.';
			$newSkill->image = "/images/builds/icons/rb-brd-kinsong.png";	
			$skills[16] = $newSkill;
			

			$newSkill = new stdClass();
			$newSkill->title = "Jonthon's Whistle";
			$newSkill->desc = 'Grants the bard a passive 300 mod proc that deals (level * 2 * <em data-base="0.2">0.2</em>) magic damage.';
			$newSkill->image = "/images/builds/icons/rb-brd-jonathonswhistle.png";
			$skills[18] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Offhand Attack";
			$newSkill->desc = 'All offhand attacks (lvl 17) have <em data-base="5">5</em>% additional chance to hit<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-offhandattack.png";	
			$skills[20] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Innate Songblade";
			$newSkill->desc = 'Increases chance to hit and damage by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-innatesongblade.png";	
			$skills[22] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Warsong of Zek";
			$newSkill->desc = 'Increases bard\'s melee damage by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-warsongofzek.png";	
			$skills[24] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Dance of Blades";
			$newSkill->desc = 'Grants the Dance of Blades AA, increasing chance to dual wield and double attack as well as proc Bladewhirl at <em data-base="20">20</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-danceofblades.png";	
			$skills[26] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Blade Dancer";
			$newSkill->desc = 'When a bard is attacked while in a group, increases chance to dodge by <em data-base="2">2</em>%<span class="perLevel"> per rank</span> per player in group.';
			$newSkill->image = "/images/builds/icons/rb-brd-cacophony.png";
			$skills[28] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Harmonic Affinity";
			$newSkill->desc = 'Increases proc chance modifier by <em data-base="5">5</em>% <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-harmonicaffinity.png";	
			$skills[31] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Bard's Wish";
			$newSkill->desc = 'When rank 5, all beneficial songs last an additional tick.';
			$newSkill->image = "/images/builds/icons/rb-brd-bardswish.png";	
			$skills[34] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Chant Cycle";
			$newSkill->desc = 'Chants with DoT effects now deal <em data-base="1">1</em>% more damage per ally in group <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-chantcycle.png";	
			$skills[36] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Boastful Bellow";
			$newSkill->desc = 'Grants the Boastful Bellow AA, and lowers the reuse time by <em data-base="10">10</em> seconds<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-boastfulbellow.png";	
			$skills[38] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Selo's Crescendo";
			$newSkill->desc = 'Selo\'s movement songs now work indoors while you are equal or below level <em data-base="12">12</em><span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-seloscrescendo.png";	
			$skills[40] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Soothing Melody";
			$newSkill->desc = 'When the bard uses a song with a healing effect on themselves, reduces hate of their target by (heal amount * <em data-base="2">2</em>)<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-shieldofnotes.png";	
			$skills[42] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Shout";
			$newSkill->desc = 'Increases range of PB AE songs by <em data-base="20">20</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-shout.png";	
			$skills[44] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Siren's Song";
			$newSkill->desc = 'Charm songs (lvl 27) now cost <em data-base="10">10</em>% less mana<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-songofstone.png";	
			$skills[46] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Lingering Twilight";
			$newSkill->desc = 'Mesmerizing songs last <em data-base="0.6">0.6</em> ticks longer<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-lingeringtwilight.png";	
			$skills[49] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Fading Memories";
			$newSkill->desc = 'Grants the Fading Memories AA, allowing you to escape all aggressions towards you, By default this costs 50% of your max mana, reduced by <em data-base="5">5</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-brd-fadingmemories.png";	
			$skills[52] = $newSkill;
			break;

			//==================CLERIC======================
			case "cleric":
			$newSkill = new stdClass();
			$newSkill->title = "Believe";
			$newSkill->desc = 'The cleric gains a 300 mod proc that deals (level * 0.75 * <em data-base="0.2">0.2</em>) magic damage, and half the damage is health back to the cleric.';
			$newSkill->image = "/images/builds/icons/rb-clr-believe.png";
			$skills[0] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Ward of Vie";
			$newSkill->desc = 'All ward spells last an additional <em data-base="20">20</em>% more maximum hitpoints<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-wardofvie.png";	
			$skills[2] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Harken the Gods";
			$newSkill->desc = 'Yaulp now gives increased accuracy, attack, and mana regen<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-harkenthegods.png";	
			$skills[4] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Blessing of Haste";
			$newSkill->desc = 'All spell haste spells are <em data-base="20">20</em>% more effective on you<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-blessingofhaste.png";	
			$skills[6] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Divine Hammer";
			$newSkill->desc = 'The cleric gains a <em data-base="60">60</em> mod proc that causes the Hand of the God spell, dealing 75-150 damage randomly.';
			$newSkill->image = "/images/builds/icons/rb-clr-divinehammer.png";	
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Mark of Karn";
			$newSkill->desc = 'Healing an ally with a single target spell, while they target an enemy, will cause the target to be affected by the Mark of Karn, healing allies who hit the enemy, for 0 to <em data-base="1">1</em>ticks randomly.';
			$newSkill->image = "/images/builds/icons/rb-clr-piouszealot.png";
			$skills[10] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Augmented Retribution";
			$newSkill->desc = 'The cleric gains a <em data-base="100">100</em> mod proc that deals a smite-like spell<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-augmentedretribution.png";	
			$skills[13] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Divine Avatar";
			$newSkill->desc = 'Grants the Divine Avatar AA, allowing a cleric many statistic bonuses and a <em data-base="10">10</em>% chance dodge and longer duration <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-divineavatar.png";	
			$skills[16] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Instill Life";
			$newSkill->desc = 'When an ally is healed, there is a <em data-base="2">2</em>% chance to heal for a bonus of <em data-base="2">2</em>% the target\'s max health<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-instilllife.png";
			$skills[18] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Divine Bash";
			$newSkill->desc = 'When the cleric uses bash, they heal for <em data-base="4">4</em>% of the cleric\'s max hp per rank to a group member with lowest health<span class="perLevel"> per rank</span>. This does not heal the cleric.';
			$newSkill->image = "/images/builds/icons/rb-clr-divinebash.png";	
			$skills[20] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Intensity of the Resolute";
			$newSkill->desc = 'Courage now grants Cleric buffs<br>Rank 1: +Spell Haste<br>Rank 2: +AC<br>Rank 3: +HP<br>Rank 4: +Symbol<br>Rank 5: +Yaulp';
			$newSkill->image = "/images/builds/icons/rb-clr-intensifiedresolution.png";
			$skills[22] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Celestial Regeneration";
			$newSkill->desc = 'Grants the Celestial Regeneration AA, restoring <em data-base="36">36</em> hitpoints and <em data-base="2">2</em> mana for 8 ticks<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-celestialbreeze.png";	
			$skills[24] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Divine Arbitration";
			$newSkill->desc = 'Grants the Divine Arbitration AA, balancing the damage each member of your group has taken, with a cooldown reduction of <em data-base="30">30</em> seconds<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-divinearbitration.png";	
			$skills[26] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Divine Resurrection";
			$newSkill->desc = 'Grants the Divine Resurrection AA, reviving a fallen player. With a base of 24 hours, lowers cooldown by <em data-base="4">4</em> hours<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-divineressurection.png";	
			$skills[28] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Promise";
			$newSkill->desc = 'All heals done by the cleric now have a <em data-base="2">2</em> chance to have the mana cost reduced by <em data-base="10">10</em>% mana <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-promise.png";	
			$skills[31] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Harmonic Balance";
			$newSkill->desc = 'Grants the Lesson of the Devoted AA, balancing the group\'s hitpoints and healing them. 10 minute recast time, each rank reduces recast by 30 seconds.';
			$newSkill->image = "/images/builds/icons/rb-clr-harmonicbalance.png";	
			$skills[34] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Strike";
			$newSkill->desc = 'Increases the damage of all direct damage spells by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-strike.png";	
			$skills[36] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Ward of Rebuke";
			$newSkill->desc = 'Ward skills deal an additional <em data-base="2">2</em>% damage <span class="perLevel"> per rank</span> and give <em data-base="1">1</em>% of the damage <span class="perLevel"> per rank</span> back as mana.';
			$newSkill->image = "/images/builds/icons/rb-clr-wardofrebuke.png";	
			$skills[38] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Fist of the Gods";
			$newSkill->desc = 'Grants <em data-base="1">1</em> bane damage versus undead<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-fistofthegods.png";	
			$skills[40] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Divine Retribution";
			$newSkill->desc = 'Grants the Divine Retribution AA with <em data-base="20">20</em>%<span class="perLevel"> per rank</span> proc effectiveness.';
			$newSkill->image = "/images/builds/icons/rb-clr-divineretribution.png";	
			$skills[42] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Turn Undead";
			$newSkill->desc = 'Grants the Turn Undead AA dealing <em data-base="500">500</em> damage<span class="perLevel"> per rank</span> and a <em data-base="1">1</em>% chance<span class="perLevel"> per rank</span> to deal 32000 damage.';
			$newSkill->image = "/images/builds/icons/rb-clr-turnundead.png";	
			$skills[44] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Exquisite Benediction";
			$newSkill->desc = 'While meleeing an undead creature, increases proc chance of all build procs by <em data-base="20">20</em>';
			$newSkill->image = "/images/builds/icons/rb-clr-exquisitebenediction.png";	
			$skills[46] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Mark of Retribution";
			$newSkill->desc = 'Increases the damage of Mark of Retribution by <em data-base="20">20</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-markofretribution.png";	
			$skills[49] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Death Pact";
			$newSkill->desc = 'Healing an ally with a single target spell gives them a 0 to <em data-base="1">1</em> tick duration random death pact buff<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-clr-avatarsboon.png";	
			$skills[52] = $newSkill;
			break;

			//==================DRUID======================
			case "druid":
			$newSkill = new stdClass();
			$newSkill->title = "Entrap";
			$newSkill->desc = 'Grants the Entrap AA, snaring the target. Mana cost increases across levels. <br>
			Rank 1 Snares by 41%-96%, 0 resist adjustment, 0.4% mana cost reduction.<br>
			Rank 2 Snares by 57%-121%, -50 resist adjustment, 0.8% mana cost reduction.<br>
			Rank 3 Snares by 57%-141%, -50 resist adjustment, 1.2% mana cost reduction.<br>
			Rank 4 Snares by 57%-141%, -85 resist adjustment, 1.6% mana cost reduction.<br>
			Rank 5 Snares by 57%-141%, -85 resist adjustment, 3.2% mana cost reduction.<br>';
			$newSkill->image = "/images/builds/icons/rb-dru-entrap.png";	
			$skills[0] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "One With Nature";
			$newSkill->desc = 'Grants a passive where each time you are hit, <em data-base="2">2</em>% of the damage is converted into mana<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-dru-treeform.png";
			$skills[2] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Teleport Bind";
			$newSkill->desc = 'Grants the teleport bind AA. Costs <em data-base="85">85</em>% of maximumum mana. Each additional rank decreases the mana cost by 15%.';
			$newSkill->image = "/images/builds/icons/rb-dru-teleportbind.png";
			$skills[4] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Exodus";
			$newSkill->desc = 'Grants the Exodus AA, which has a base 5 second cast time. Each rank reduces casting time by 1 second.';
			$newSkill->image = "/images/builds/icons/rb-dru-exodus.png";
			$skills[6] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Call of the Wild";
			$newSkill->desc = 'Grants the Call of the Wild AA, causing enemies nearby to be stunned. Each rank reduces recast time by 300 seconds.';
			$newSkill->image = "/images/builds/icons/rb-dru-callofthewild.png";
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Secondary Recall";
			$newSkill->desc = 'Grants Secondary Recall AA. Each rank reduces the recast time substantially, 1: 24hrs, 2: 18 hrs, 3: 12hrs, 4: 6hrs, 5: 3hrs.';
			$newSkill->image = "/images/builds/icons/rb-dru-secondaryrecall.png";
			$skills[10] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Ring Affinity";
			$newSkill->desc = 'Ring spells cast <em data-base="5">5</em>% faster and cost <em data-base="10">10</em>%% less mana.';
			$newSkill->image = "/images/builds/icons/rb-dru-ringaffinity.png";
			$skills[13] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Dire Charm";
			$newSkill->desc = 'Charm animals from -10 to -5 of your level, based on rank. They get a pet-like adjusted stats, this is an experiment for future mage pet AI improvements.';
			$newSkill->image = "/images/builds/icons/rb-dru-direcharm.png";
			$skills[16] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Regeneration";
			$newSkill->desc = 'Grants the druid an innate hp regeneration of Level * 0.2 hitpoints (minimum 2) per tick, a self only damage shield of <em data-base="2">2</em>,  as well as any duration regeneration spells casted by the druid give <em data-base="20">20</em>% additional hitpoint regeneration per tick while in the same zone as the druid<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-dru-regeneration.png";
			$skills[18] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Convergence of Spirits";
			$newSkill->desc = 'Grants the Convergence of Spirits AA, giving a heal over time that heals for <em data-base="0.5">0.5</em>% of the target\'s max health per tick for <em data-base="6">6</em> seconds. This also causes normal heals to be boosted by <em data-base="5">5</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-dru-convergenceofspirits.png";
			$skills[20] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Lifeflow";
			$newSkill->desc = 'While an ally has Covergence of Spirits or Nature\'s Boon buff on them, they are granted a <em data-base="1">1</em>% death save chance, healing when triggered for 8000 hitpoints<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-dru-lifeflow.png";
			$skills[22] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Spirit of the Wood";
			$newSkill->desc = 'Grants the Spirit of the Wood AA, which casts buffs scaled based on your level and the target\'s level.<br>Rank 1: STR<br>Rank 2: HP Regen<br>Rank 3: HP<br>Rank 4: Damage Shield<br>Rank 5: Doubles Duration';
			$newSkill->image = "/images/builds/icons/rb-dru-spiritofthewood.png";
			$skills[24] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Spiritual Awakening";
			$newSkill->desc = 'The druid gains a 300 mod proc that deals (level * 1.5 * <em data-base="0.2">0.2</em>) magic damage and melee hits tap <em data-base="1">1</em> mana from the target.';
			$newSkill->image = "/images/builds/icons/rb-dru-spiritualawakening.png";
			$skills[26] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Nature's Boon";
			$newSkill->desc = 'Grants the Nature\'s Boon AA, where the target receives a buff that lasts 84 seconds, duration reduced by <em data-base="12">12</em> seconds due to rank. When the buff fades, the target is healed for <em data-base="20">20</em>% of the druid\'s max mana. If Nature\'s Boon is removed early, it will heal for a portion based on duration buff lasted. This also causes normal heals to be boosted by <em data-base="5">5</em>%<span class="perLevel"> per rank</span>. ';
			$newSkill->image = "/images/builds/icons/rb-dru-naturesboon.png";
			$skills[28] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Nature's Whisper";
			$newSkill->desc = 'While a target is affected by Nature\'s Boon or Convergence of Spirits, the druid as well as the target regain <em data-base="2">2</em>% of any healing done from these spells as mana.<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-dru-natureswhisper.png";
			$skills[31] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Nature's Guardian";
			$newSkill->desc = 'Grants the Nature\'s Guardian AA, where <em data-base="3">3</em>% of the caster\'s max mana is infused by nature and can be transferred to a target or to the caster<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-dru-naturesguardian.png";
			$skills[34] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Intensity";
			$newSkill->desc = 'When an enemy is affected by a DoT, it deals <em data-base="0.7">0.7</em>% more damage for each ally in group.';
			$newSkill->image = "/images/builds/icons/rb-dru-intensity.png";	
			$skills[36] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Lingering Pain";
			$newSkill->desc = 'When a direct spell is casted, a 0 to <em data-base="1">1</em> tick duration DoT will also affect the target if the spell casted was obtained within 15 levels of the enemy\'s level<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-dru-lingeringpain.png";	
			$skills[38] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Focused Swarm";
			$newSkill->desc = 'When standing nearby a mob, DoTs now deal <em data-base="1">1</em>% more damage for each ally in group. This damage bonus reduces by 10% for every 20m you\'re away from an enemy<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-dru-focusedswarm.png";	
			$skills[40] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Blessing of Ro";
			$newSkill->desc = 'All Ro debuffs now spread to 0 to <em data-base="1">1</em> additional enemies within <em data-base="5">5</em>m of an affected target if they are on the aggro list of the druid.';
			$newSkill->image = "/images/builds/icons/rb-dru-blessingofro.png";	
			$skills[42] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Whirling Disaster";
			$newSkill->desc = 'Direct Damage spells now also stun for (0 to <em data-base="1">1</em>/2) seconds if the target is at least 5 levels below the druid.';
			$newSkill->image = "/images/builds/icons/rb-dru-whirlingdisaster.png";
			$skills[44] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Stinging Affliction";
			$newSkill->desc = 'DoTs and Direct Damage spells have a <em data-base="1"></em>% chance to critical hit<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-dru-stingingaffliction.png";	
			$skills[46] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Deep Roots";
			$newSkill->desc = 'When a root wears off, there is a <em data-base="3"></em>% chance the target will be snared if it is not already<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-dru-deeproots.png";	
			$skills[49] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Nature's Blight";
			$newSkill->desc = 'Grants the Lesson of the Devoted AA, causing the target to take 5% increased spell damage. 5 minute recast time, each rank reduces recast by 30 seconds..';
			$newSkill->image = "/images/builds/icons/rb-dru-naturesblight.png";	
			$skills[52] = $newSkill;
			break;
			
			//==================ENCHANTER======================
			case "enchanter":
			$newSkill = new stdClass();
			$newSkill->title = "Nightmare";
			$newSkill->desc = 'DoT spells do an additional <em data-base="1"></em>% damage per ally in group<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-nightmare.png";
			$skills[0] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Crippling Presence";
			$newSkill->desc = 'When an enemy is affected by a disempowering spell, they deal <em data-base="2"></em>% less damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-cripplingpresence.png";
			$skills[2] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Soothing Words";
			$newSkill->desc = 'Grants the Soothing Words AA, reducing your target\'s hatred for their current target by 5000 points if that creature\'s target is a member of your group or raid. Each rank reduces cooldown by <em data-base="30"></em> seconds<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-soothingwords.png";
			$skills[4] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Mind over Matter";
			$newSkill->desc = 'Grants the Mind over Matter AA, absorbing damage in mana before hitpoints. Each rank improves reduction by <em data-base="2"></em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-mindovermatter.png";
			$skills[6] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Beneficial Dispell";
			$newSkill->desc = 'When using a spell with a cancel magic effect, increases chance by <em data-base="20"></em>%<span class="perLevel"> per rank</span> that a beneficial buff will not be affected.';
			$newSkill->image = "/images/builds/icons/rb-enc-beneficialdispell.png";
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Persuasion";
			$newSkill->desc = 'Increases buy and sell price to merchants by <em data-base="3"></em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-persuasion.png";
			$skills[10] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Choke";
			$newSkill->desc = 'While an enemy is under the effect of a shallow-breath line debuff, the enemy takes (level *<em data-base="1"></em>/4) damage <span class="perLevel"> per rank</span> when they land an attack.';
			$newSkill->image = "/images/builds/icons/rb-enc-choke.png";
			$skills[13] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Drown";
			$newSkill->desc = 'Lowers mana cost of DoTs by <em data-base="3">%</em> tick<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-drown.png";
			$skills[16] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Enthrall";
			$newSkill->desc = 'Each rank reduces mana cost of mesmerize spells by <em data-base="1">1</em>%, at max rank increases duration by 1 tick<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-enthrall.png";
			$skills[18] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Tash";
			$newSkill->desc = 'While an enemy is tashed, other group members are granted a 300 mod (enemy level * <em data-base="0.2"></em>) damage proc while attacking<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-tash.png";
			$skills[20] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Backfire";
			$newSkill->desc = 'Wandering Mind, Scryer\'s Bypass, and Torment of Argli now have the backfire effect. If an enemy successfully channels a spell, they are interrupted, this spell effect is removed, and the enemy takes (enemy level * 25 * <em data-base="0.2">0.2</em>) damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-backfire.png";
			$skills[22] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Energy Burn";
			$newSkill->desc = 'When you use a spell that takes mana from an enemy, you now deal (mana taken * <em data-base="0.7">0.4</em>) damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-energyburn.png";
			$skills[24] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Feedback";
			$newSkill->desc = 'When you use a detrimental spell, you deal <em data-base="10">10</em> bonus damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-feedback.png";
			$skills[26] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Focus";
			$newSkill->desc = 'When you use a spell with a stun component, reduces hate generated by <em data-base="7">7</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-focus.png";
			$skills[28] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Lifeflow";
			$newSkill->desc = 'When you use a spell that takes mana from an enemy with mana, you heal for (mana taken * <em data-base="0.4">0.4</em>) hitpoints<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-lifeflow.png";
			$skills[31] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Extended Charm";
			$newSkill->desc = 'When you charm an enemy, increases the minimum duration by 0 to <em data-base="1">1</em> ticks<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-direcharm.png";
			$skills[34] = $newSkill;


			$newSkill = new stdClass();
			$newSkill->title = "Mind Devorour";
			$newSkill->desc = 'When you cast a detrimental spell against a monster with mana, you have a <em data-base="2">2</em>% chance to recover <em data-base="10">10</em>% mana<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-entropy.png";
			$skills[36] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Color Shock";
			$newSkill->desc = 'Grants the Color Shock AA, causing a chance to stun when attacked. Chance increases by <em data-base="1">1</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-colorshock.png";
			$skills[38] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Mana Spear";
			$newSkill->desc = 'When you use a spell that takes mana from an enemy, increases chance to land by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-manaspear.png";
			$skills[40] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Flowing Thought";
			$newSkill->desc = 'Breeze now grants the enchanter many of their buffs.<br>Rank 1: Breeze (to mana users)<br>Rank 2: Visage Line (+to tanks, -to rest)<br>Rank 3: Gift Line and Brilliance/Insight (to mana users)<br>Rank 4: Haste (to non-casters)<br>Rank 5: Doubles duration of buffs'; 			
			$newSkill->image = "/images/builds/icons/rb-enc-flowingthought.png";
			$skills[42] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Subtle Casting";
			$newSkill->desc = 'Lowers aggression when casting a spell by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-enc-subtlecasting.png";
			$skills[44] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Bad Moon";
			$newSkill->desc = 'While grouped with an enchanter, all allies gain an innate 100 proc that deals a (level * <em data-base="0.2">0.2</em>) lifetap<span class="perLevel"> per rank</span>';
			$newSkill->image = "/images/builds/icons/rb-enc-badmoon.png";
			$skills[46] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Tranquility";
			$newSkill->desc = 'While in a group, you and your allies gain (level * <em data-base="0.1">0.1</em>) mana regen per tick<span class="perLevel"> per rank</span>';
			$newSkill->image = "/images/builds/icons/rb-enc-tranquility.png";
			$skills[49] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Reclaim";
			$newSkill->desc = 'When you tell your pet to leave, you will gain (mana * <em data-base="0.2">0.2</em>) of back of it\'s mana cost with ratio of current to max hitpoints<span class="perLevel"> per rank</span>';
			$newSkill->image = "/images/builds/icons/rb-enc-reclaim.png";
			$skills[52] = $newSkill;			
			break;

			//==================MAGICIAN======================
			case "magician":
			$newSkill = new stdClass();
			$newSkill->title = "Summoning Focus";
			$newSkill->desc = 'Items summoned by the magician are reinforced, giving better stats. Additional ranks increase the level of spells affected.';
			$newSkill->image = "/images/builds/icons/rb-mag-summoningfocus.png";
			$skills[0] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Quick Summoning";
			$newSkill->desc = 'Reduces the cast time of pet summoning spells by <em data-base="10">10</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mag-quicksummoning.png";
			$skills[2] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Improved Reclaim Energy";
			$newSkill->desc = 'Increases the amount of mana returned by Reclaim Energy by <em data-base="5">5</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mag-improvedreclaimenergy.png";
			$skills[4] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Modulation Shard";
			$newSkill->desc = 'Summons a modulation rod with <em data-base="1">1</em> charge<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mag-modulationshard.png";
			$skills[6] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Companion's Intensity";
			$newSkill->desc = 'Increases your pet\'s damage melee damage by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mag-companionsdurability.png";
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Suspended Minion";
			$newSkill->desc = 'Grants the Suspended Minion AA, allowing you to suspend a minion to be recalled later. Further ranks allow preserving buffs and items while suspended.';
			$newSkill->image = "/images/builds/icons/rb-mag-suspendedminion.png";
			$skills[10] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Mend Companion";
			$newSkill->desc = 'Grants the Mend Companion AA, healing <em data-base="20">20</em>% of your pet\'s HP per rank';
			$newSkill->image = "/images/builds/icons/rb-mag-mendcompanion.png";
			$skills[13] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Companion of Necessity";
			$newSkill->desc = 'Grants the Companion of Necessity AA, summoning a temporary pet that will gain the attention of one creature and cause that creature to forget all anger when the pet dies. Each rank grants <em data-base="20">20</em>% of maximum duration.';
			$newSkill->image = "/images/builds/icons/rb-mag-companionofnecessity.png";
			$skills[16] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Shared Health";
			$newSkill->desc = 'Grants the Shared Health AA, causing <em data-base="10">10</em>% of your incoming damage<span class="perLevel"> per rank</span> to be sent to your pet instead.';
			$newSkill->image = "/images/builds/icons/rb-mag-sharedhealth.png";
			$skills[18] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Host in the Shell";
			$newSkill->desc = 'Grants the Host in the Shell AA, creating a rune effect on your pet with <em data-base="20">20</em>% of the rune\'s maximum value<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mag-hostintheshell.png";
			$skills[20] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Turn Summoned";
			$newSkill->desc = 'Grants the Turn Summoned AA, inflicing a DoT for <em data-base="500">500</em> damage per rank per tick for 4 ticks with a <em data-base="1">1</em>% chance<span class="perLevel"> per rank</span> to cause 32000 damage.';
			$newSkill->image = "/images/builds/icons/rb-mag-turnsummoned.png";
			$skills[22] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Frenzied Burnout";
			$newSkill->desc = 'Reduces the mana cost of direct damage spells by <em data-base="10">10</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mag-frenziedburnout.png";
			$skills[24] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Elemental Alacrity";
			$newSkill->desc = 'Improves element-based direct damage spells by <em data-base="4">4</em>% damage per rank.';
			$newSkill->image = "/images/builds/icons/rb-mag-elementalalacrity.png";
			$skills[26] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Call of the Hero";
			$newSkill->desc = 'Grants the Call of the Hero AA with reduced cast time and cooldown timer per rank.';
			$newSkill->image = "/images/builds/icons/rb-mag-callofthehero.png";
			$skills[28] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Clockwork Merchant";
			$newSkill->desc = 'Grants the Clockwork Banker AA that summons a merchant. Ranks decrease the cooldown substantially.';
			$newSkill->image = "/images/builds/icons/rb-mag-clockworkmerchant.png";
			$skills[31] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Servant of Ro";
			$newSkill->desc = 'Grants the Servant of Ro AA that calls a loyal servant into being who will repeatedly hurl fire at your target. Ranks increase the duration of this temprorary pet.';
			$newSkill->image = "/images/builds/icons/rb-mag-servantofro.png";
			$skills[34] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Dimensional Shield";
			$newSkill->desc = 'Grants Dimensional Shield AA that allows a chance to shadow step away from the attacking target. Ranks increase the chance of the defensive proc by <em data-base="20">20</em>% per rank.';
			$newSkill->image = "/images/builds/icons/rb-mag-dimensionalshield.png";
			$skills[36] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Heart of Stone";
			$newSkill->desc = 'Grants Heart of Stone AA that provides a melee guard. The melee guard is scaled at 10% per rank.';
			$newSkill->image = "/images/builds/icons/rb-mag-heartofstone.png";
			$skills[38] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Heart of Vapor";
			$newSkill->desc = 'Grants Heart of Vapor AA that reduces hate generated. The effectiveness of the spell is 20>% per rank.';
			$newSkill->image = "/images/builds/icons/rb-mag-heartofvapor.png";
			$skills[40] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Shock of Swords";
			$newSkill->desc = 'Increases the damage caused by sword and blade spells by <em data-base="4">4</em>% per rank.';
			$newSkill->image = "/images/builds/icons/rb-mag-shockofswords.png";
			$skills[42] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Heart of Ice";
			$newSkill->desc = 'Grants Heart of Ice AA that provides a spell guard. The spell guard is scaled at 10% per rank.';
			$newSkill->image = "/images/builds/icons/rb-mag-heartofice.png";
			$skills[44] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Quick Damage";
			$newSkill->desc = 'Reduces the cast time of direct damage spells that have casting times longer than 3 seconds. Each rank further decreases the cast time.';
			$newSkill->image = "/images/builds/icons/rb-mag-quickdamage.png";
			$skills[46] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Heart of Flames";
			$newSkill->desc = 'Grants Heart of Flames AA that provides a massive damage shield. The effectiveness of the spell is scaled at <em data-base="20">20</em>% <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mag-heartofflames.png";
			$skills[49] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Primal Fusion";
			$newSkill->desc = 'When you attack with a direct damage spell, your pet will also cast the spell dealing <em data-base="5">5</em> of it\'s damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mag-primalfusion.png";
			$skills[52] = $newSkill;
			break;

			//==================MONK======================
			case "monk":
			$newSkill = new stdClass();
			$newSkill->title = "Intensified Training";
			$newSkill->desc = 'The monk gains a 300 mod proc that deals (level * 1.25 * <em data-base="0.2">0.2</em>) magic damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-intensifiedtraining.png";
			$skills[0] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Familiarity";
			$newSkill->desc = 'Every time a special attack lands on an enemy, the monk gains <em data-base="2">2</em> armor against the target<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-familiarity.png";
			$skills[2] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Block";
			$newSkill->desc = 'Increases block by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-block.png";
			$skills[4] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Relentless Training";
			$newSkill->desc = 'Increases damage of Tiger Claw, Eagle Strike, Tail Whip and other special attacks by <em data-base="10">10</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-relentlesstraining.png";
			$skills[6] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Expose Weakness";
			$newSkill->desc = 'When using Tiger Claw, Eagle Strike, Tail Whip and other special attacks, increases accuracy of all attacking allies by 0 to <em data-base="2">2</em><span class="perLevel"> per rank</span> vs that enemy.';
			$newSkill->image = "/images/builds/icons/rb-mnk-exposeweakness.png";
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Destiny";
			$newSkill->desc = 'When you have an enemy targeted, increases avoidance by <em data-base="1">1</em>% <span class="perLevel"> per rank</span>';
			$newSkill->image = "/images/builds/icons/rb-mnk-destiny.png";
			$skills[10] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Wu's Quickening";
			$newSkill->desc = 'Reduces delay of your primary weapon by <em data-base="1">1</em> <span class="perLevel"> per rank</span>, to a minimum of 7.';
			$newSkill->image = "/images/builds/icons/rb-mnk-wusquickening.png";
			$skills[13] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Grace of the Order";
			$newSkill->desc = 'Grants the Lesson of the Devoted AA, increasing max health by 15% and a 250dd stun. 10 minute recast time, each rank reduces recast by 30 seconds.';
			$newSkill->image = "/images/builds/icons/rb-mnk-graceoftheorder.png";
			$skills[16] = $newSkill;


			$newSkill = new stdClass();
			$newSkill->title = "Partial Mending";
			$newSkill->desc = 'When mend fails, the monk still heals for <em data-base="10">10</em>% of the mending amount<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-partialmending.png";
			$skills[18] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Inner Chakra";
			$newSkill->desc = 'Heals received while using feign death, including mend, heal for an additional <em data-base="4">4</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-innerchakra.png";
			$skills[20] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Channel Chakra";
			$newSkill->desc = 'While your health is less than <em data-base="10">10</em>%, and no enemy is actively attacking you, your normal melee attacks lifetap for <em data-base="2">2</em>% damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-channelchakra.png";
			$skills[22] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Mending Aura";
			$newSkill->desc = 'When you use Mend, you now heal the rest of the group within <em data-base="5">5</em> meters for <em data-base="20">20</em>% the mend heal amount<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-mendingaura.png";
			$skills[24] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Divine Surge";
			$newSkill->desc = 'When you land Tiger Claw, Eagle Strike, Tail Whip or other special attacks, your group recovers <em data-base="0.75">0.75</em>% of a target\'s max mana and endurance when within <em data-base="5">5</em>m<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-divinesurge.png";
			$skills[26] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Improved Mend";
			$newSkill->desc = 'When you use Mend, you heal an additional 5% to <em data-base="10">10</em>% hitpoints<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-improvedmend.png";
			$skills[28] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Purify Body";
			$newSkill->desc = 'Grants the Purify Body AA, curing <em data-base="1">1</em> detrimental effect on the monk<span class="perLevel"> per rank</span>. At rank 5, it will also cure resurrection sickness.';
			$newSkill->image = "/images/builds/icons/rb-mnk-purifybody.png";
			$skills[31] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Tranquility";
			$newSkill->desc = 'When you are not affected by negative effects, not under feign death, nor are engaged by an enemy, and in a full group, you regenerate <em data-base="2">2</em>% of your total missing health per tick <span class="perLevel"> per rank</span>. Lesser group sizes give reduced healing.';
			$newSkill->image = "/images/builds/icons/rb-mnk-tranquility.png";
			$skills[34] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Agile Feet";
			$newSkill->desc = 'Increases your chance to resist snares by <em data-base="2">2</em>% <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-agilefeet.png";
			$skills[36] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Cowardly Stance";
			$newSkill->desc = 'Increases your movement speed by up to <em data-base="10">10</em>% based on missing health. Does not stack with movement buffs<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-cowardlystance.png";
			$skills[38] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Thunderfoot";
			$newSkill->desc = 'Grants a passive spell block that returns when used after (level - <em data-base="6">6</em>) seconds<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-thunderfoot.png";
			$skills[40] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Stoic Mind";
			$newSkill->desc = 'While your health is not below <em data-base="2">2</em>%, your resistance to spells is increased by <em data-base="3">3</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-stoicmind.png";
			$skills[42] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Grounded Essence";
			$newSkill->desc = 'Gives a <em data-base="2">2</em>% to resist an attempt at being summoned by an enemy<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-groundedessence.png";
			$skills[44] = $newSkill;


			$newSkill = new stdClass();
			$newSkill->title = "Slow Heart Rate";
			$newSkill->desc = 'When you feign death with health below <em data-base="2">2</em>%<span class="perLevel"> per rank</span>, your feign death will cause all enemies to immediately forget you';
			$newSkill->image = "/images/builds/icons/rb-mnk-slowheartrate.png";
			$skills[46] = $newSkill;


			$newSkill = new stdClass();
			$newSkill->title = "Mirror";
			$newSkill->desc = 'While your health is at 99% or higher, your chance to evade attacks is increased by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-mirror.png";
			$skills[49] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Moving Mountains";
			$newSkill->desc = 'When you use the throw stone ability against an enemy lower level than you, you now knockback the enemy <em data-base="1">1</em>m<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-mnk-movingmountains.png";
			$skills[52] = $newSkill;
			break;

			//==================NECROMANCER======================
			case "necromancer":
			$newSkill = new stdClass();
			$newSkill->title = "Corruption";
			$newSkill->desc = 'DoT damage is increased by <em data-base="1">1</em>% per ally in group<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-nec-corruption.png";
			$skills[0] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Cavorting Bones";
			$newSkill->desc = 'Empowers your pet to dynamically level with you at <em data-base="20">20</em>% effectiveness<span class="perLevel"> per rank</span>. Once 44+, at max rank the pet will lifetap. At 59+, the pet will be a spectre.';
			$newSkill->image = "/images/builds/icons/rb-nec-cavoringbones.png";
			$skills[2] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Shocking Bolt";
			$newSkill->desc = 'When a poison-based direct damage spell with bolt in it\'s name (or venom of the snake) lands on an enemy, the instant damage is increased by <em data-base="5">5</em>% <span class="perLevel"> per rank</span>. It also has a <em data-base="1">1</em>% chance to hit for quad damage.';
			$newSkill->image = "/images/builds/icons/rb-nec-shockingbolt.png";
			$skills[4] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Burning Soul";
			$newSkill->desc = 'When a fire-based DoT deals damage, it has a <em data-base="2">2</em>% chance to critical hit for double damage<span class="perLevel"> per rank</span>. (#toggle debugecho to see return)';
			$newSkill->image = "/images/builds/icons/rb-nec-burningsoul.png";
			$skills[6] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Lingering Curse";
			$newSkill->desc = 'Increases DoT duration by <em data-base="1">1</em> tick per rank, the duration is lowered the closer the enemy is to your level. Minimum 1 tick<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-nec-lingeringcurse.png";
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Decay";
			$newSkill->desc = 'While a DoT affects an enemy, mana is returned to the necromancer at a rate of <em data-base="1">1</em>% of cost per tick<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-nec-decay.png";
			$skills[10] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Splurt";
			$newSkill->desc = 'Splurt now deals <em data-base="10">10</em>% more damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-nec-splurt.png";
			$skills[13] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Venom Strike";
			$newSkill->desc = 'Poison-based direct damage spells such as Torbas line of spells, now have a <em data-base="1">1</em>% chance to also apply a poison damage over time<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-nec-venomstrike.png";
			$skills[16] = $newSkill;


			$newSkill = new stdClass();
			$newSkill->title = "Shroud of Death";
			$newSkill->desc = 'Your pet gains a 400 mod proc lifetap that deals (level * <em data-base="0.2">0.2</em>) magic damage and if Spirit Focus is trained and a focus target is set, a recourse heal for 100% of damage dealt is given<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-nec-shroudofdeath.png";
			$skills[18] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Life Burn";
			$newSkill->desc = 'Unlocks the Life Burn AA, dealing <em data-base="2">2</em>% of your current health as damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-nec-lifeburn.png";
			$skills[20] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Pact of Hate";
			$newSkill->desc = 'Dark Pact line spells now regenerate an additional <em data-base="10">10</em>% mana based on damage dealt<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-nec-pactofhate.png";
			$skills[22] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Blood Magic";
			$newSkill->desc = 'Grants the Blood Magic AA, giving the necromancer the ability to cast spells at the cost of health. With a base of 10 minutes, each rank reduces cooldown by 30 seconds.';
			$newSkill->image = "/images/builds/icons/rb-nec-bloodmagic.png";
			$skills[24] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Life Blood";
			$newSkill->desc = 'Increases amount healed by lifetaps by (<em data-base="2">2</em>% * group size) <span class="perLevel"> per rank</span> and increases chance to critical heal by <em data-base="2">2</em>%.';
			$newSkill->image = "/images/builds/icons/rb-nec-lifeblood.png";
			$skills[26] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Spirit Focus";
			$newSkill->desc = 'Enables use of the #focus command, transferring recourses such as life taps to the focused ally for <em data-base="16">16</em>% of the recourse given<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-nec-spiritfocus.png";
			$skills[28] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Dying Grasp";
			$newSkill->desc = 'Grants the Dying Grasp AA, a high damage, fast casting lifetap. Base cooldown of 360 seconds, each rank reduces cooldown by 30 seconds.';
			$newSkill->image = "/images/builds/icons/rb-nec-dyinggrasp.png";
			$skills[31] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Servant of Blood";
			$newSkill->desc = 'Grants the Lesson of the Devoted AA, summoning a blood skeleton that lifetaps health to the group for 30 seconds. 10 minute recast time, each rank reduces recast by 30 seconds.';
			$newSkill->image = "/images/builds/icons/rb-nec-servantofblood.png";
			$skills[34] = $newSkill;

			/*$newSkill = new stdClass();
			$newSkill->title = "Life Link";
			$newSkill->desc = 'Necromancer pets now recourse to the #focus target, or the necro themselves.<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-nec-venomstrike.png";
			$skills[31] = $newSkill;*/
			break;


			//==================PALADIN======================
			case "paladin":
			$newSkill = new stdClass();
			$newSkill->title = "Rodcet's Gift";
			$newSkill->desc = 'Single target healing spells now spread to allies within <em data-base="10">10</em>m of the healed target, healing them for <em data-base="2">2</em>% the original heal amount<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-rodcetsgift.png";
			$skills[0] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Hand of Piety";
			$newSkill->desc = 'Grants the Hand of Piety AA, allowing the user to heal the group for <em data-base="2">2</em>% of their max health <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-handofpiety.png";
			$skills[2] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Instill Purpose";
			$newSkill->desc = 'Divine Purpose and Breath of Tunare now grant <em data-base="20">20</em>% more hitpoint regeneration <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-instillpurpose.png";
			$skills[4] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Refreshing Breeze";
			$newSkill->desc = 'All healing except Hand of Piety give healed targets <em data-base="0.5">0.5</em>% of amount healed as mana<span class="perLevel"> per rank</span>. Does not work when healing yourself.';
			$newSkill->image = "/images/builds/icons/rb-pal-refreshingbreeze.png";
			$skills[6] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Brell's Blessing";
			$newSkill->desc = 'Courage now grants Paladin buffs<br>Rank 1: AC<br>Rank 2: HP Line 1<br>Rank 3: HP Symbol Line<br>Rank 4: HP Line 2 (Brell)<br>Rank 5: Double duration.';
			$newSkill->image = "/images/builds/icons/rb-pal-brellsblessing.png";
			$skills[8] = $newSkill;			

			$newSkill = new stdClass();
			$newSkill->title = "Soul Cleansing";
			$newSkill->desc = 'Cleansing heal over time spells now have a <em data-base="2">2</em>% chance to cure an ailment<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-soulcleansing.png";
			$skills[10] = $newSkill;

 			$newSkill = new stdClass();
			$newSkill->title = "Wave of Marr";
			$newSkill->desc = 'All wave-based group spells cost <em data-base="10">10</em>% less mana to cast<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-waveofmarr.png";
			$skills[13] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Ward of Tunare";
			$newSkill->desc = 'Passively grants the Paladin a <em data-base="6">6</em>% bonus when healed by other allies<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-wardoftunare.png";
			$skills[16] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Shield of Nife";
			$newSkill->desc = 'Grants an Undead-only damage shield that deals <em data-base="7">7</em> damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-shieldofnife.png";
			$skills[18] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Armor of Faith";
			$newSkill->desc = 'Damage taken from Undead is reduced by <em data-base="2.5">2.5</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-armoroffaith.png";
			$skills[20] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Purification";
			$newSkill->desc = 'Grants the Purification AA, curing <em data-base="1">1</em> detrimental effect on the paladin<span class="perLevel"> per rank</span>. At rank 5, it will also cure resurrection sickness.';
			$newSkill->image = "/images/builds/icons/rb-pal-purification.png";
			$skills[22] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Holy Servant";
			$newSkill->desc = 'When a group member within <em data-base="2">2</em>m is attacked, <em data-base="2.5">2.5</em>% of the dealt damage is redirected to the paladin and is reduced by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-holyservant.png";
			$skills[24] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Divine Stun";
			$newSkill->desc = 'Grants the Divine Stun AA, causing a target to be stunned and marked with divine anger. Any time the Paladin casts a heal spell on a group member, the marked enemy gains an additional <em data-base="200">200</em> hatred<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-divinestun.png";
			$skills[26] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Act of Valor";
			$newSkill->desc = 'Grants the Act of Valor AA, summoning a squire that will dutifully assist the Paladin, casting stuns and healing themself. Each rank increases his stats and power by <em data-base="20">20</em>% efficiency<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-actofvalor.png";
			$skills[28] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Elixir of Might";
			$newSkill->desc = 'Instrument of Nife and Divine Might proc effects now heal the Paladin for <em data-base="10">10</em>% of damage dealt as well as gain <em data-base="2">2</em> mana<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-elixirofmight.png";
			$skills[31] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Flames of Redemption";
			$newSkill->desc = 'Grants the Lesson of the Devoted AA, causing flames of redemption buff improving healing effectiveness by 25% and the flames of redemption DD proc. 10 minute recast time, each rank reduces recast by 30 seconds.';
			$newSkill->image = "/images/builds/icons/rb-pal-flamesofredemption.png";
			$skills[34] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Zealot's Fervor";
			$newSkill->desc = 'When a heal is casted by a paladin, up to <em data-base="1">1</em> nearby enemies of the target are dealt <em data-base="1">1</em>% of the healing as damage. <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-zealotsfervor.png";
			$skills[36] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Knight's Advantage";
			$newSkill->desc = '2 handed weapons deal an additional <em data-base="5">5</em>% damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-knightsadvantage.png";
			$skills[38] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Chosen";
			$newSkill->desc = 'All self proc buffs deal <em data-base="25">25</em>% more damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-chosen.png";
			$skills[40] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Purpose of Marr";
			$newSkill->desc = 'Valor of Marr now grants <em data-base="10">10</em>% additional attack speed<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-purposeofmarr.png";
			$skills[42] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Flame of Light";
			$newSkill->desc = 'Flame of Light now deals an additional <em data-base="20">20</em>% damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-flameoflight.png";
			$skills[44] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Dismiss Evil";
			$newSkill->desc = 'When attacking an evil creature, gives a <em data-base="1">1</em>% chance to critical hit<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-dismissevil.png";
			$skills[46] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Frail";
			$newSkill->desc = 'Stun spells also cripple the target for 0 to <em data-base="1">1</em>ticks <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-frail.png";
			$skills[49] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Slayer";
			$newSkill->desc = 'Grants an ability to cleanse the target, similar to Slay Undead, but works on ALL creature types, up to the level of the paladin, with a <em data-base="100">100</em> mod proc<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-pal-slayer.png";
			$skills[52] = $newSkill;
			break;
			//==================RANGER======================
			case "ranger":
			break;

			//==================ROGUE======================
			case "rogue":
			$newSkill = new stdClass();
			$newSkill->title = "Appraisal";
			$newSkill->desc = 'The rogue gains a 400 mod proc that deals (level * 3 * <em data-base="0.2">0.2</em>) magic damage as well as a fleeting fury buff.';
			$newSkill->image = "/images/builds/icons/rb-rog-appraisal.png";
			$skills[0] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Killing Spree";
			$newSkill->desc = 'Each time a creature is successfully killed, the rogue gains a killing spree counter. For a limited time, attacks deal an additional <em data-base="5">5</em>% damage per counter, with a cap of <em data-base="2">2</em> counters<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-killingspree.png";
			$skills[2] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Thief's Eyes";
			$newSkill->desc = 'Increases accuracy by <em data-base="2">2</em>% with all skills <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-thiefseyes.png";			
			$skills[4] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Sinister Strikes";
			$newSkill->desc = 'Increases offhand damage bonus by <em data-base="10">10</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-sinisterstrikes.png";	
			$skills[6] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Sneak Attack";
			$newSkill->desc = 'If a rogue is sneaking and uses a backstab while an enemy is greater than 70% hp, improves chance to hit with a backstab by <em data-base="2000">2000</em>% and critical chance increases by <em data-base="10">10</em>% <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-sneakattack.png";	
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Focused Stab";
			$newSkill->desc = 'Backstab has a <em data-base="5">5</em>% better chance to hit<span class="perLevel"> per rank</span> and when maxxed, allows a chance to backstabs from front.';
			$newSkill->image = "/images/builds/icons/rb-rog-focusedstab.png";	
			$skills[10] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Vital Organs";
			$newSkill->desc = 'Backstab deals <em data-base="20">20</em>% more damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-vitalorgans.png";
			$skills[13] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Assassin's Taint";
			$newSkill->desc = 'Grants the Lesson of the Devoted AA, granting the assassins taint buff that grants triple backstab and a proc that causes skill taken damage to be increased by 7%. 10 minute recast time, each rank reduces recast by 30 seconds.';
			$newSkill->image = "/images/builds/icons/rb-rog-assassinstaint.png";	
			$skills[16] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Sleight Distraction";
			$newSkill->desc = 'When the rogue successfully pick pockets an enemy (even if they do not obtain an item) while in a group, the enemy becomes mesmerized for 0 to <em data-base="1">1</em> ticks. The next time the enemy attacks the rogue it has a very high chance of missing. <span class="perLevel"> per rank</span>';
			$newSkill->image = "/images/builds/icons/rb-rog-sleightdistraction.png";
			$skills[18] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Jarring Stab";
			$newSkill->desc = 'When the rogue successfully backstabs an enemy, all enemies that are hated by the rogue have a reduction of (<em data-base="0.2">0.2</em> * damage) hate<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-jarringstab.png";
			$skills[20] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Untapped Potential";
			$newSkill->desc = 'When you successfully pickpocket, your group recovers <em data-base="1">1</em>% of a target\'s max mana when within <em data-base="5">5</em>m<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-untappedpotential.png";
			$skills[22] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Confuse";
			$newSkill->desc = 'When a rogue uses beg on an enemy, there is a very small chance to cause the enemy to be mesmerized for 6 seconds.';
			$newSkill->image = "/images/builds/icons/rb-rog-confuse.png";
			$skills[24] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Gangster's Paradise";
			$newSkill->desc = 'Rogue melee attacks passively cause <em data-base="10">10</em> less hate per attack, and when a rogue is out of combat and does not move for some time, they have a chance to gain a Shroud of Stealth like state. The chances of gaining Shroud of Stealth is increased when two rogues are grouped and near each other.';
			$newSkill->image = "/images/builds/icons/rb-rog-gangstersparadise.png";
			$skills[26] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Moss Stone";
			$newSkill->desc = 'When throw stone is used on a creature with less than 20% health and is not snared, it has a <em data-base="20">20</em>% chance to ensnare the enemy.';
			$newSkill->image = "/images/builds/icons/rb-rog-mossstone.png";
			$skills[28] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Duelist";
			$newSkill->desc = 'While engaged with a single enemy who is lesser level than the rogue, the rogue gains improved evasion. Many factors decrease the effectiveness of this skill, such as the level of the enemy and how much health they have.';
			$newSkill->image = "/images/builds/icons/rb-rog-duelist.png";
			$skills[31] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Escape";
			$newSkill->desc = 'Grants the Escape AA, allowing the rogue to escape combat instantly for 50% of your endurance bar. Endurance cost is reduced by <em data-base="10">10</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-escape.png";
			$skills[34] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Sleight of Strength";
			$newSkill->desc = 'When the rogue successfully pick pockets, they gain a random beneficial buff for 0 to <em data-base="1">1</em> ticks<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-sleightofstrength.png";
			$skills[36] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Haggle";
			$newSkill->desc = 'When a rogue sells or buys items, the price is improved by <em data-base="2">2</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-haggle.png";
			$skills[38] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Hidden Stash";
			$newSkill->desc = 'When a rogue pickpockets, they dive deeper into the enemy\'s pockets to discover a hidden stash of coin<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-hiddenstash.png";
			$skills[40] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Throwing Precision";
			$newSkill->desc = 'Increases the minimum damage of throwing daggers by <em data-base="10">10</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-throwingprecision.png";
			$skills[42] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Mugging Shot";
			$newSkill->desc = 'Adds a special proc based on the offhand wielded by the rogue, has a <em data-base="100">100</em> proc rate<span class="perLevel"> per rank</span>.<br>Mace: Lowers aggro by <em data-base="50">50</em> hate and interrupts foe.<br>	Sword: Deals <em data-base="5">5</em> damage. Dagger: Drains mana by <em data-base="100">100</em> and deals <em data-base="2">2</em> damage.';
			$newSkill->image = "/images/builds/icons/rb-rog-muggingshot.png";
			$skills[44] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Deadly Dagger";
			$newSkill->desc = 'Increases the maximum damage of throwing daggers by <em data-base="20">20</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-deadlydagger.png";
			$skills[46] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Thieves' Affinity";
			$newSkill->desc = 'Increases proc chance of innate and card weapon procs by <em data-base="2.5">2.5</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-thievesaffinity.png";
			$skills[49] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Hidden Dagger";
			$newSkill->desc = 'If an enemy is not engaged, and is hit by a dagger thrown by a rogue sneaking, it will break sneak, and has a <em data-base="15">15</em>% chance to not be social<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-rog-hiddendagger.png";
			$skills[52] = $newSkill;
			break;
			
			//==================SHAMAN======================
			case "shaman":
			//0
			$newSkill = new stdClass();
			$newSkill->title = "Spirit of Speed";
			$newSkill->desc = 'Spirit of Wolf lasts <em data-base="20">20</em>% longer<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-spiritofspeed.png";
			$skills[0] = $newSkill;
			//1
			//2
			$newSkill = new stdClass();
			$newSkill->title = "Purify Soul";
			$newSkill->desc = 'Grants the Purify Soul AA, which cures target of disease, poison, as well as gives a <em data-base="10">10</em>% chance to heal the target by <em data-base="1">1</em>% max HP per tick regen<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-purifysoul.png";
			$skills[2] = $newSkill;
			//3
			//4
			$newSkill = new stdClass();
			$newSkill->title = "Ancestral Aid";
			$newSkill->desc = 'Grants the Ancestral Aid AA, which casts focus line buff scaled to your level.<br>Rank 1: STR<br>Rank 2: DEX and AGI<br>Rank 3: STA<br>Rank 4: HP<br>Rank 5: Haste';
			$newSkill->image = "/images/builds/icons/rb-shm-ancestralaid.png";
			$skills[4] = $newSkill;
			//5
			//6
			$newSkill = new stdClass();
			$newSkill->title = "Extended Haste";
			$newSkill->desc = 'Improves attack speed spells used by the caster by increasing their duration by <em data-base="30">30</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-extendedhaste.png";
			$skills[6] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Spiritual Healing";
			$newSkill->desc = 'Heals to allies also heal the shaman <em data-base="5">5</em>% health<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-spiritualhealing.png";	
			$skills[8] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Covenant of Spirit";
			$newSkill->desc = 'Grants the Covenent of Spirit AA, which imbues divine intervention on the target with a <em data-base="2">2</em>% death save success<span class="perLevel"> per rank</span>.<b>NOT IMPLEMENTED</b>';
			$newSkill->image = "/images/builds/icons/rb-shm-covenantofspirit.png";
			$skills[10] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Reinforce Torpor";
			$newSkill->desc = 'Stoicism and Torpor heal for an additional <em data-base="10">10</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-reinforcetorpor.png";
			$skills[13] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Fateseer's Boon";
			$newSkill->desc = 'Grants the Lesson of the Devoted AA, giving a group buff that increases critical damage by 70% with all skills, chance to critical hit by 50% with all skills, as well as a 400 hitpoint per tick regen. 10 minute recast time, each rank reduces recast by 30 seconds.';
			$newSkill->image = "/images/builds/icons/rb-shm-fateseersboon.png";
			$skills[16] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Cannibalize";
			$newSkill->desc = 'Grants the Cannibalization AA, causing <em data-base="5">5</em>% current HP loss in exchange for mana at <em data-base="10">10</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-cannibalize.png";
			$skills[18] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Spirit Call";
			$newSkill->desc = 'Grants the Spirit Call AA, summoning a racial pet with <em data-base="10">10</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-spiritcall.png";
			$skills[20] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Virulent Paralysis";
			$newSkill->desc = 'Grants the Virulent Paralysis AA, causing a target to be immobilized. Each rank increases duration by <em data-base="6">6</em> seconds <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-virulentparalysis.png";
			$skills[22] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Poison";
			$newSkill->desc = 'All poison-based DoTs now deal <em data-base="1">1</em>% additional damage per ally in group<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-poison.png";
			$skills[24] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Extended Turgur";
			$newSkill->desc = 'Increases duration of slow by <em data-base="5">5</em>% as well as penetrates magic defense by <em data-base="5">5</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-extendedturgur.png";
			$skills[26] = $newSkill;
			//37
			//38
			$newSkill = new stdClass();
			$newSkill->title = "Ancient Wrath";
			$newSkill->desc = 'All direct damage spells now deal <em data-base="10">10</em>% more damage as well as <em data-base="1">1</em>% chance to critical hit<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-ancientwrath.png";
			$skills[28] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Turgur's Echo";
			$newSkill->desc = 'When a slow-based spell is resisted, the spell will try to land again with <em data-base="2">2</em> less resistance<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-turgursecho.png";
			$skills[31] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Spiritual Channeling";
			$newSkill->desc = 'While this ability is active, all spells cost HP rather than mana. Cooldown of reuse is reduced by <em data-base="6">6</em>seconds<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-spiritualchanneling.png";
			$skills[34] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Fury";
			$newSkill->desc = 'The shaman gains a 400 mod proc that deals (level * 1.5 * <em data-base="0.2">0.2</em>) magic damage.';
			$newSkill->image = "/images/builds/icons/rb-shm-fury.png";
			$skills[36] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Rabid Bear";
			$newSkill->desc = 'Grants the Rabid Bear AA, granting <em data-base="2">2</em>% attack speed and the tainted bite proc line with <em data-base="20">20</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-rabidbear.png";
			$skills[38] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Ancestral Guard";
			$newSkill->desc = 'Grants the Ancestral Guard AA, granting <em data-base="2">2</em>% evasion<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-ancestralguard.png";
			$skills[40] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Call of the Ancients";
			$newSkill->desc = 'Grants the Call of the Ancients AA, summoning a spirit that deals <em data-base="1">1</em> %of an enemy\'s current health (maximum <em data-base="100">100</em>) per attack<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-calloftheancients.png";
			$skills[42] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Spiritual Wrath";
			$newSkill->desc = 'Grants the Spiritual Wrath AA, attacking your target<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-spiritualwrath.png";
			$skills[44] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Mark of Sloth";
			$newSkill->desc = 'On each attack, grants a chance to trigger a sloth effect, causing the next direct damage spell to deal <em data-base="5">5</em>% bonus damage<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-markofsloth.png";
			$skills[46] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Feral Swipe";
			$newSkill->desc = 'Grants the Feral Swipe AA, giving a bonus attack ability with <em data-base="5">5</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-feralswipe.png";
			$skills[49] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Paragon of Spirit";
			$newSkill->desc = 'Grants the Paragon of Spirit AA, giving a mana and hp regen ability <em data-base="20">20</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shm-paragonofspirit.png";
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
			$newSkill->desc = 'Grants the Leech Touch AA, which replaces all normal Knight lifetaps. It will use your best lifetap, curved up, as well as improves all lifetaps by (<em data-base="2">2</em>% * group size) <span class="perLevel"> per rank</span> and grants a <em data-base="1">1</em>% critical heal rate<span class="perLevel"> per rank</span>.';
			$newSkill->desc = '.';
			$newSkill->image = "/images/builds/icons/rb-shd-leechtouch.png";	
			$skills[0] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Gouging Skin";
			$newSkill->desc = 'When attacked, causes a <em data-base="4">4</em> point damage shield and <em data-base="30">30</em> hate<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-gougingskin.png";	
			$skills[2] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Hungering Aura";
			$newSkill->desc = 'Improves lifetaps casted by Leech Touch or Innate Procs by <em data-base="5">5</em>% healing for each enemy attacking you with a maximum of <em data-base="1">1</em> enemies or group size, whichever is lower<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-hungeringaura.png";	
			$skills[4] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Steadfast Servant";
			$newSkill->desc = 'Grants the Steadfast Servant AA, summoning a pet at <em data-base="20">20</em>% effectiveness<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-steadfastservant.png";	
			$skills[6] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Zevfeer's Feast";
			$newSkill->desc = 'When you use the Leech Touch AA, your group recover <em data-base="0.5">0.5</em>% of a target\'s max mana when within <em data-base="5">5</em>m<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-zevfeersfeast.png";	
			$skills[8] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Sworn Enemy";
			$newSkill->desc = 'When you use taunt, you mark a target as your sworn enemy. For the next 3 ticks, any spell damage dealt to target causes an additional <em data-base="100">100</em> hate<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-swornenemy.png";	
			$skills[10] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Banshee's Mirror";
			$newSkill->desc = 'Passively grants the Shadow Knight a <em data-base="6">6</em>% bonus when healed by other allies<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-bansheesmirror.png";
			$skills[13] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Reaper's Strike";
			$newSkill->desc = 'Grants the Lesson of the Devoted AA, which improves accuracy by 50% and gain lifetap from weapon damage. 10 minute recast time, each rank reduces recast by 30 seconds.';
			$newSkill->image = "/images/builds/icons/rb-shd-reapersstrike.png";	
			$skills[16] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Festering Spear";
			$newSkill->desc = 'Improve spear type spells by (level * <em data-base="1">1</em>) bonus damage <span class="perLevel"> per rank</span>. Also gives a <em data-base="1">1</em>% chance to cause quad damage.';
			$newSkill->image = "/images/builds/icons/rb-shd-festeringspear.png";
			$skills[18] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Festering Wound";
			$newSkill->desc = 'Improves DoT damage by <em data-base="1">1</em>% for each ally in group<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-festeringwound.png";	
			$skills[20] = $newSkill;
		
			$newSkill = new stdClass();
			$newSkill->title = "Rotten Core";
			$newSkill->desc = 'Each time a creature is successfully killed, the knight gains a rotten core counter. For 60 seconds, each counter adds <em data-base="3">3</em>% damage<span class="perLevel"> per rank</span> to attacks, with a cap of <em data-base="1">1</em> counters. Getting a kill resets the counter.';
			$newSkill->image = "/images/builds/icons/rb-shd-rottencore.png";
			$skills[22] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Lingering Pain";
			$newSkill->desc = 'All direct damage spells cause a DoT effect for 0 to <em data-base="1">1</em> ticks<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-lingeringpain.png";
			$skills[24] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Blood Oath";
			$newSkill->desc = 'While using a 2 handed weapon, increases damage by <em data-base="5">5</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-bloodoath.png";	
			$skills[26] = $newSkill;
		
			$newSkill = new stdClass();
			$newSkill->title = "Gift of Urash";
			$newSkill->desc = 'Increases all skill damage by <em data-base="5">5</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-giftofurash.png";	
			$skills[28] = $newSkill;
		
			$newSkill = new stdClass();
			$newSkill->title = "Unholy Focus";
			$newSkill->desc = 'Enables use of the #focus command, transferring lifetaps to the focused ally for <em data-base="4">4</em>% of the recourse given<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-unholyfocus.png";	
			$skills[31] = $newSkill;
		
			$newSkill = new stdClass();
			$newSkill->title = "Bash of Death";
			$newSkill->desc = 'When you bash a target that is equal to your level or lower and the enemy is at <em data-base="10">10</em>% or less total health you deal an additional (level * <em data-base="1">1</em>) <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-bashofdeath.png";
			$skills[34] = $newSkill;
		
			$newSkill = new stdClass();
			$newSkill->title = "Embrace Death";
			$newSkill->desc = 'Grants you the Death Peace AA, giving the ability to feign death as well as heal you for <em data-base="1">1</em>% of missing health<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-embracedeath.png";	
			$skills[36] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Darkness";
			$newSkill->desc = 'All darkness type spells slow movement for an additional <em data-base="4">4</em>%<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-darkness.png";	
			$skills[38] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Empathetic Soul";
			$newSkill->desc = 'Improves Dark Empathy by granting an additional <em data-base="40">40</em> hitpoints healed and <em data-base="0.5">0.5</em>% max mana <span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-empatheticsoul.png";
			$skills[40] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Embrace Shadow";
			$newSkill->desc = 'Each time you feign death, you are instantly be invisible to both living and undead creatures for <em data-base="1">1</em> tick<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-embraceshadow.png";	
			$skills[42] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Siphon of Death";
			$newSkill->desc = 'Vampiric Embrace, Scream of Death and Shroud of Death now also grant a mana tap for <em data-base="5">5</em>% of damage dealt<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-siphonofdeath.png";
			$skills[44] = $newSkill;

			$newSkill = new stdClass();
			$newSkill->title = "Nightmare";
			$newSkill->desc = 'Fear now causes target to be stunned in panic for 0 to <em data-base="1">1</em> seconds<span class="perLevel"> per rank</span> before fleeing.';
			$newSkill->image = "/images/builds/icons/rb-shd-nightmare.png";
			$skills[46] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Mental Resistance";
			$newSkill->desc = 'Gives a <em data-base="2">2</em>% chance to resist stun effects<span class="perLevel"> per rank</span>.';
			$newSkill->image = "/images/builds/icons/rb-shd-mentalresistance.png";	
			$skills[49] = $newSkill;
			
			$newSkill = new stdClass();
			$newSkill->title = "Cloak of Shadows";
			$newSkill->desc = 'Grants the Cloak of the Shadows AA, allowing you to step into the shadows, causing a <em data-base="5">5</em>% chance that all targets will forget your actions.';
			$newSkill->image = "/images/builds/icons/rb-shd-cloakofshadows.png";
			$skills[52] = $newSkill;
			
			break;
		}
		return $skills;
	}

}
