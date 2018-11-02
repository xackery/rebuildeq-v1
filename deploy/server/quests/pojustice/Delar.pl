sub EVENT_SAY { 
	my $rc = 0;
	my $rcTotal = 0;
	my $prefix = "";
	my $classid = $client->GetClass();
	
	if ($text=~/about/i) {
		quest::say("Heirlooms are a way to transfer NO TRADE items between characters on your account. The NO TRADE items it supports are unadorned and corroded armor pieces from Temple of Veeshan.");
		quest::say("It is free to take from me heirlooms you have previously given to me in the past. However, to  [ ".quest::saylink("deposit")." ] them, you must complete the heirloom quest. This also must be completed to do tier progression.");
		quest::say("You can also learn more, for example [ ".quest::saylink("what are tiers")." ], if you like.");
		return;
	}

	if ($text=~/what are tiers/i) {
		quest::say("Tiers are a way higher level mobs are adjusted to cause difficulty without heavily padding stats. You are penalized when attacking tiered monsters when not of equal tier.");
		quest::say("You can identify tiered monsters by considering them, they will have a level of [T#], # being a number of 1+");
		return;
	}


	if ($text=~/tov/i) {
		$prefix = "tov";
		$tmp_id = 0;		
		if ($text=~/$prefix head/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24961; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24968; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24975; #leather
			}
			else {
				$tmp_id = 24982; #silk
			}
		}

		if ($text=~/$prefix chest/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24956; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24963; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24970; #leather
			}
			else {
				$tmp_id = 24977; #silk
			}
		}
		if ($text=~/$prefix arm/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24958; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24965; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24972; #leather
			}
			else {
				$tmp_id = 24979; #silk
			}
		}
		if ($text=~/$prefix wrist/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24960; #plate
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24967; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24974; #leather
			}
			else {
				$tmp_id = 24981; #silk
			}
		}
		if ($text=~/$prefix hand/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24962; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24969; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24976; #leather
			}
			else {
				$tmp_id = 24983; #silk
			}
		}
		if ($text=~/$prefix leg/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24957; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24964; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24971; #leather
			}
			else {
				$tmp_id = 24978; #silk
			}
		}
		if ($text=~/$prefix feet/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24959; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24966; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24973; #leather
			}
			else {
				$tmp_id = 24980; #silk
			}
		}
		if ($tmp_id > 0) {
			$acct_id = $client->AccountID();

			if (!defined $qglobals{"$acct_id-$prefix-$tmp_id"} || $qglobals{"$acct_id-$prefix-$tmp_id"} < 1) {
				quest::say("You do not have any items stored that match that category. $acct_id-$prefix-$tmp_id");
				return;
			}			
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
			quest::setglobal("$acct_id-$prefix-$tmp_id", $count-1, 2, "F");
			quest::summonitem($tmp_id);
			quest::say("Here is your heirloom item, $name");
			return;
		}

		quest::say("Pick a slot: [ ".quest::saylink("$prefix head")." ], [ ".quest::saylink("$prefix chest")." ], [ ".quest::saylink("$prefix arms")." ]. [ ".quest::saylink("$prefix wrist")." ], [ ".quest::saylink("$prefix hands")." ], [ ".quest::saylink("$prefix legs")." ], [ ".quest::saylink("$prefix feet")." ]");
		return;
	}



	if ($text=~/kael/i) {
		$prefix = "kael";
		$tmp_id = 0;		
		if ($text=~/$prefix head/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24905; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24912; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24919; #leather
			}
			else {
				$tmp_id = 24926; #silk
			}
		}

		if ($text=~/$prefix chest/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24900; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24907; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24914; #leather
			}
			else {
				$tmp_id = 24921; #silk
			}
		}
		if ($text=~/$prefix arm/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24902; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24909; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24916; #leather
			}
			else {
				$tmp_id = 24923; #silk
			}
		}
		if ($text=~/$prefix wrist/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24904; #plate
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24911; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24918; #leather
			}
			else {
				$tmp_id = 24925; #silk
			}
		}
		if ($text=~/$prefix hand/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24906; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24913; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24920; #leather
			}
			else {
				$tmp_id = 24927; #silk
			}
		}
		if ($text=~/$prefix leg/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24901; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24908; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24915; #leather
			}
			else {
				$tmp_id = 24922; #silk
			}
		}
		if ($text=~/$prefix feet/i) {
			if ($classid == 3 || $classid == 8 || $classid == 1 || $classid == 5 || $classid == 2) {
				$tmp_id = 24903; #plate			
			}
			elsif ($classid == 4 || $classid == 9 || $classid == 10) {
				$tmp_id = 24910; #chain
			}
			elsif ($classid == 6 || $classid == 7) {
				$tmp_id = 24917; #leather
			}
			else {
				$tmp_id = 24924; #silk
			}
		}
		if ($tmp_id > 0) {
			$acct_id = $client->AccountID();

			if (!defined $qglobals{"$acct_id-$prefix-$tmp_id"} || $qglobals{"$acct_id-$prefix-$tmp_id"} < 1) {
				quest::say("You do not have any items stored that match that category. $acct_id-$prefix-$tmp_id");
				return;
			}			
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
			quest::setglobal("$acct_id-$prefix-$tmp_id", $count-1, 2, "F");
			quest::summonitem($tmp_id);
			quest::say("Here is your heirloom item, $name");
			return;
		}

		quest::say("Pick a slot: [ ".quest::saylink("$prefix head")." ], [ ".quest::saylink("$prefix chest")." ], [ ".quest::saylink("$prefix arms")." ]. [ ".quest::saylink("$prefix wrist")." ], [ ".quest::saylink("$prefix hands")." ], [ ".quest::saylink("$prefix legs")." ], [ ".quest::saylink("$prefix feet")." ]");
		return;
	}




	#if ($text=~/radiant/i || $text=~/rc/i) {
	#	$rcTotal = 0;
	#	$tmp_id = 40903;
	#	if (defined $qglobals{"$acct_id-$prefix-$tmp_id"} && $qglobals{"$acct_id-$prefix-$tmp_id"} > 0) {
	#		$rcTotal = $qglobals{"$acct_id-$prefix-$tmp_id"}*250;
	#	}
	#	$prefix = "rc";
	#	quest::say("You currently have $rcTotal radiant crystals available. [ ".quest::saylink("claim radiant crystals")." ]");		
	#	return;
	#}

	#if ($text=~/claim radiant/i || $text=~/rc/i) {
	#	$prefix = "rc";
	#	$rcTotal = 0;
	#	$tmp_id = 40903;
	#	if (defined $qglobals{"$acct_id-$prefix-$tmp_id"} && $qglobals{"$acct_id-$prefix-$tmp_id"} > 0) {
	#		$rcTotal = $qglobals{"$acct_id-$prefix-$tmp_id"}*250;
	#	}
	#	if ($rcTotal < 1) {
	#		quest::say("You do not have any radiant crystals to claim.");
	#		return;
	#	}
	#	$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
	#	quest::setglobal("$acct_id-$prefix-$tmp_id", $count-1, 2, "F");
	#	quest::summonitem($tmp_id, 250);
	#	$rcTotal -= 250;
	#	quest::say("You claimed 250 radiant crystals. You have $rcTotal remaining. [ ".quest::saylink("claim radiant crystals")." ]");
	#	return;
	#}
	if ($text=~/unlock tier/i) {
		if (!quest::istaskcompleted(314)) { # completed before.
			quest::say("You must first learn how to [ ".quest::saylink("deposit")." ] into heirlooms before you can unlock tiers.");
			return;
		}
		if ($ulevel < 60) { #not enough levels
			quest::say("You must reach level 60 before you can unlock tiers.");
			return;
		}
		if (!quest::istaskcompleted(501)) { #tier 1 task
			if (quest::istaskactive(501)) { #ongoing
				quest::say("You appear to be working on your tier 1 task. You can do it!");
				return;
			}
			if (!quest::istaskactive(501)) { #not done yet
				quest::say("Very well. Here is the path to unlock Tier 1.");
				quest::assigntask(501);
				return;
			}
		}
		if (!quest::istaskcompleted(502)) { #tier 2 task
			if (quest::istaskactive(502)) { #ongoing
				quest::say("You appear to be working on your tier 2 task. You can do it!");
				return;
			}
			if (!quest::istaskactive(502)) { #not done yet
				quest::say("Very well. Here is the path to unlock Tier 2.");
				quest::assigntask(502);
				return;
			}
		}
		if (!quest::istaskcompleted(503)) { #tier 3 task
			if (quest::istaskactive(503)) { #ongoing
				quest::say("You appear to be working on your tier 3 task. You can do it!");
				return;
			}
			if (!quest::istaskactive(503)) { #not done yet
				quest::say("Very well. Here is the path to unlock Tier 3.");
				quest::assigntask(503);
				return;
			}
		}
		if (!quest::istaskcompleted(504)) { #tier 4 task
			if (quest::istaskactive(504)) { #ongoing
				quest::say("You appear to be working on your tier 4 task. You can do it!");
				return;
			}
			if (!quest::istaskactive(504)) { #not done yet
				quest::say("Very well. Here is the path to unlock Tier 4.");
				quest::assigntask(504);
				return;
			}
		}
		if (!quest::istaskcompleted(505)) { #tier 5 task
			if (quest::istaskactive(505)) { #ongoing
				quest::say("You appear to be working on your tier 5 task. You can do it!");
				return;
			}
			if (!quest::istaskactive(505)) { #not done yet
				quest::say("Very well. Here is the path to unlock Tier 5.");
				quest::assigntask(505);
				return;
			}
		}
		if (!quest::istaskcompleted(506)) { #tier 6 task
			if (quest::istaskactive(506)) { #ongoing
				quest::say("You appear to be working on your tier 6 task. You can do it!");
				return;
			}
			if (!quest::istaskactive(506)) { #not done yet
				quest::say("Very well. Here is the path to unlock Tier 6.");
				quest::assigntask(506);
				return;
			}
		}
		if (!quest::istaskcompleted(507)) { #tier 7 task
			if (quest::istaskactive(507)) { #ongoing
				quest::say("You appear to be working on your tier 7 task. You can do it!");
				return;
			}
			if (!quest::istaskactive(507)) { #not done yet
				quest::say("Very well. Here is the path to unlock Tier 7.");
				quest::assigntask(507);
				return;
			}
		}
		if (!quest::istaskcompleted(508)) { #tier 8 task
			if (quest::istaskactive(508)) { #ongoing
				quest::say("You appear to be working on your tier 8 task. You can do it!");
				return;
			}
			if (!quest::istaskactive(508)) { #not done yet
				quest::say("Very well. Here is the path to unlock Tier 8.");
				quest::assigntask(508);
				return;
			}
		}
		if (!quest::istaskcompleted(509)) { #tier 9 task
			if (quest::istaskactive(509)) { #ongoing
				quest::say("You appear to be working on your tier 9 task. You can do it!");
				return;
			}
			if (!quest::istaskactive(509)) { #not done yet
				quest::say("Very well. Here is the path to unlock Tier 9.");
				quest::assigntask(509);
				return;
			}
		}
		if (!quest::istaskcompleted(510)) { #tier 10 task
			if (quest::istaskactive(510)) { #ongoing
				quest::say("You appear to be working on your tier 10 task. You can do it!");
				return;
			}
			if (!quest::istaskactive(510)) { #not done yet
				quest::say("Very well. Here is the path to unlock Tier 10.");
				quest::assigntask(510);
				return;
			}
		}
		quest::say("You have unlocked all tiers available at this time. Good job!");
		return;
    }

	if ($text=~/deposit/i) { #heirloom key task
		if (!quest::istaskcompleted(314) && !quest::istaskactive(314)) { #haven't started yet
			quest::say("To deposit into heirlooms, you must help me find my key. My best guess of where it is, is look at various locations and monsters I have interacted with as of late.");
			quest::assigntask(314);
			return;
		}
		if (quest::istaskcompleted(314)) { # completed before.
			if ($ulevel < 60) {
				quest::say("You already have the ability to deposit items. Once you reach level 60, come back to me and we can talk about [ ".quest::saylink("what are tiers")." ], and how to unlock them.");
				return;
			}
			quest::say("You already have the ability to deposit items. Perhaps you want to learn how to [ ".quest::saylink("unlock tiers")." ] ?");
			return;
		}
		if (quest::istaskactive(314)) { #task is ongoing
			if (quest::istaskactivityactive(314, 8)) { #finished up to last step
				quest::updatetaskactivity(314, 8);
				quest::say("Oh, you're finally back! Want to hear the most ironic thing..? I had the key here, in my pocket, all this time! Thank you for your effort, however.");
				if ($ulevel < 60) {
					quest::say("Once you reach level 60, come back to me and we can talk about [ ".quest::saylink("what are tiers")." ], and how to unlock them.");
					return;
				}
				quest::say("I see you are level 60. How about we continue on to how to [ ".quest::saylink("unlock tiers")." ] ?");
				return;
			}
			quest::say("Keep looking for that key, and we can start depositing items again!");
			return;		   
		}
    }

	if ($text=~/heirloom/i) {
		quest::say("Pick a category: [ ". quest::saylink("tov") . " ], [ " . quest::saylink("kael") . " ]. (Note this only works with unadorned and corroded items, completed items cannot be traded)."); #, [ " . quest::saylink("Radiant Crystals") . " ].");
		if (!quest::istaskcompleted(314)) {
			quest::say("Are you interested in learning how to [ ". quest::saylink("deposit") . " ]  items to your heirloom?");
		}
		return;
	}

	if ($ulevel < 60) {
		quest::say("Oh yes, greetings. I am a keeper of [ ". quest::saylink("heirlooms")." ]. Want to learn [ ". quest::saylink("about")." ] them, as well as what tiers are?");
		return;
	} else {
		quest::say("Oh yes, greetings. I am a keeper of [ ". quest::saylink("heirlooms")." ]. Want to learn [ ". quest::saylink("about")." ] them? Since you are level 60, you can possibly [ ". quest::saylink("unlock tiers")." ], too.");
		return;
	}	
	return;
}


sub EVENT_ITEM {

#Begin experience bottle turn in code.
  my $tier = 0;
  my $task_id = 0;
  my $activity_id = 0;
  my $bottle_goal = 0;

  if (quest::istaskactive(501)) { $tier = 1; $task_id = 501; $activity_id = 8; $bottle_goal = 1; }
  if (quest::istaskactive(502)) { $tier = 2; $task_id = 502; $activity_id = 10; $bottle_goal = 2; }
  if (quest::istaskactive(503)) { $tier = 3; $task_id = 503; $activity_id = 9; $bottle_goal = 3; }
  if (quest::istaskactive(504)) { $tier = 4; $task_id = 504; $activity_id = 6; $bottle_goal = 4; }
  if (quest::istaskactive(505)) { $tier = 5; $task_id = 505; $activity_id = 8; $bottle_goal = 5; }
  if (quest::istaskactive(506)) { $tier = 6; $task_id = 506; $activity_id = 8; $bottle_goal = 6; }
  if (quest::istaskactive(507)) { $tier = 7; $task_id = 507; $activity_id = 3; $bottle_goal = 7; }
  if (quest::istaskactive(508)) { $tier = 8; $task_id = 508; $activity_id = 7; $bottle_goal = 8; }
  if (quest::istaskactive(509)) { $tier = 9; $task_id = 509; $activity_id = 5; $bottle_goal = 9; }
  if (quest::istaskactive(510)) { $tier = 10; $task_id = 510; $activity_id = 8; $bottle_goal = 10; }

  my $bottle_message = "Thank you for your potion of experience for tier $tier progression, $name.";
  my $bottle_task_active = quest::istaskactivityactive($task_id, $activity_id);
  my $bottles_previously_turned_in = quest::gettaskactivitydonecount($task_id, $activity_id);
  my $bottles_turned_in = 0;
  
  if ($item1 == 100001 && $item1_charges >= 1){
        $bottles_turned_in += $item1_charges;
  }
  if ($item2 == 100001 && $item2_charges >= 1){
		$bottles_turned_in += $item2_charges;
  }
  if ($item3 == 100001 && $item3_charges >= 1){
		$bottles_turned_in += $item3_charges;
  }   
  if ($item4 == 100001 && $item4_charges >= 1){
		$bottles_turned_in += $item4_charges;
  }
      
  my $bottle_new_total = $bottles_previously_turned_in + $bottles_turned_in;
  if($bottle_task_active == 1 && $bottle_new_total <= $bottle_goal) {
	if(plugin::check_handin(\%itemcount, 100001 => 1)) {
	  quest::say($bottle_message);
	  $client->Message(15,"You received credit for turning in ". $bottles_turned_in . " full experience bottle(s).");
	  quest::updatetaskactivity($task_id, $activity_id, $bottles_turned_in);
	  return;
	}
	if(plugin::check_handin(\%itemcount, 100001 => 2)) {
	  quest::say($bottle_message);
  	  $client->Message(15,"You received credit for turning in ". $bottles_turned_in . " full experience bottle(s).");
	  quest::updatetaskactivity($task_id, $activity_id, $bottles_turned_in);
	  return;
	}
	if(plugin::check_handin(\%itemcount, 100001 => 3)) {
	  quest::say($bottle_message);
	  $client->Message(15,"You received credit for turning in ". $bottles_turned_in . " full experience bottle(s).");
	  quest::updatetaskactivity($task_id, $activity_id, $bottles_turned_in);
	  return;
	}
	if(plugin::check_handin(\%itemcount, 100001 => 4)) {
	  quest::say($bottle_message);
	  $client->Message(15,"You received credit for turning in ". $bottles_turned_in . " full experience bottle(s).");
	  quest::updatetaskactivity($task_id, $activity_id, $bottles_turned_in);
	  return;
	}
  }
#End experience bottle turn in code.

	if (!quest::istaskcompleted(314)) {				
		quest::say("You cannot deposit into the [ ".quest::saylink("heirloom") ." ] chests until you finish my quest.");
		return;
	}

	$acct_id = $client->AccountID();
	$tmp_id = 0;
	#if(plugin::check_handin(\%itemcount, 40903 => 250)) {			
	#	$tmp_id = 40903;
	#	$prefix = "rc";
	#	$count = 0;
	#	if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
	#		$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
	#	}
	#	quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
	#	quest::say("Thank you for the stack of radiant crystals, $name.");
	#}

	if(plugin::check_handin(\%itemcount, 24961 => 1)) { #plate			
		$tmp_id = 24961;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24968 => 1)) { #chain
		$tmp_id = 24968;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24975 => 1)) {#leather
		$tmp_id = 24975;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24982 => 1)) { #silk
		$tmp_id = 24982;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24956 => 1)) { #plate			
		$tmp_id = 24956;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24963 => 1)) { #chain
		$tmp_id = 24963;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24970 => 1)) { #leather
		$tmp_id = 24970;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24977 => 1)) { #silk
		$tmp_id = 24977;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24958 => 1)) { #plate			
		$tmp_id = 24958;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24965 => 1)) { #chain
		$tmp_id = 24965;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24972 => 1)) { #leather
		$tmp_id = 24972;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24979 => 1)) { #silk
		$tmp_id = 24979;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24960 => 1)) { #plate			
		$tmp_id = 24960;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24967 => 1)) { #chain
		$tmp_id = 24967;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24974 => 1)) { #leather
		$tmp_id = 24974;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24981 => 1)) { #silk
		$tmp_id = 24981;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24962 => 1)) { #plate			
		$tmp_id = 24962;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24969 => 1)) { #chain
		$tmp_id = 24969;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24976 => 1)) { #leather
		$tmp_id = 24976;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24983 => 1)) { #silk
		$tmp_id = 24983;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24957 => 1)) { #plate			
		$tmp_id = 24957;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24964 => 1)) { #chain
		$tmp_id = 24964;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24971 => 1)) { #leather
		$tmp_id = 24971;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24978 => 1)) { #silk
		$tmp_id = 24978;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24959 => 1)) { #plate			
		$tmp_id = 24959;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24966 => 1)) { #chain
		$tmp_id = 24966;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24973 => 1)) { #leather
		$tmp_id = 24973;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if(plugin::check_handin(\%itemcount, 24980 => 1)) { #silk
		$tmp_id = 24980;
		$prefix = "tov";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}

	## === KAEL ===
	if (plugin::check_handin(\%itemcount, 24905 => 1)) { #kael plate			
		$tmp_id = 24905;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24912 => 1)) { #kael chain
		$tmp_id = 24912;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24919 => 1)) { #kael leather
		$tmp_id = 24919;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24926 => 1)) { #kael silk
		$tmp_id = 24926;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24900 => 1)) { #kael plate			
		$tmp_id = 24900;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24907 => 1)) { #kael chain
		$tmp_id = 24907;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24914 => 1)) { #kael leather
		$tmp_id = 24914;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24921 => 1)) { #kael silk
		$tmp_id = 24921;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24902 => 1)) { #kael plate			
		$tmp_id = 24902;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24909 => 1)) { #kael chain
		$tmp_id = 24909;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24916 => 1)) { #kael leather
		$tmp_id = 24916;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24923 => 1)) { #kael silk
		$tmp_id = 24923;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24904 => 1)) { #kael plate
		$tmp_id = 24904;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24911 => 1)) { #kael chain
		$tmp_id = 24911;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24918 => 1)) { #kael leather
		$tmp_id = 24918;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24925 => 1)) { #kael silk
		$tmp_id = 24925;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24906 => 1)) { #kael plate			
		$tmp_id = 24906;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24913 => 1)) { #kael chain
		$tmp_id = 24913;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24920 => 1)) { #kael leather
		$tmp_id = 24920;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24927 => 1)) { #kael silk
		$tmp_id = 24927;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24901 => 1)) { #kael plate			
		$tmp_id = 24901;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24908 => 1)) { #kael chain
		$tmp_id = 24908;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24915 => 1)) { #kael leather
		$tmp_id = 24915;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24922 => 1)) { #kael silk
		$tmp_id = 24922;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24903 => 1)) { #kael plate			
		$tmp_id = 24903;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24910 => 1)) { #kael chain
		$tmp_id = 24910;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24917 => 1)) { #kael leather
		$tmp_id = 24917;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
	if (plugin::check_handin(\%itemcount, 24924 => 1)) { #kael silk
		$tmp_id = 24924;
		$prefix = "kael";
		$count = 0;
		if (defined $qglobals{"$acct_id-$prefix-$tmp_id"}) {
			$count = $qglobals{"$acct_id-$prefix-$tmp_id"};
		}
		quest::setglobal("$acct_id-$prefix-$tmp_id", $count+1, 2, "F");
		quest::say("Thank you for the item, $name.");
	}
  plugin::return_items(\%itemcount);  
}