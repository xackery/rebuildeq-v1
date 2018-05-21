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
		}

		quest::say("Pick a slot: [ ".quest::saylink("$prefix head")." ], [ ".quest::saylink("$prefix chest")." ], [ ".quest::saylink("$prefix arms")." ]. [ ".quest::saylink("$prefix wrist")." ], [ ".quest::saylink("$prefix hands")." ], [ ".quest::saylink("$prefix legs")." ], [ ".quest::saylink("$prefix feet")." ]");
		return;
	}

	if ($text=~/kael/i) {		
		$prefix = "kael";
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
				quest::say("Tier 2 is not yet implemented. Come back at a later time!");
				#quest::assigntask(501);
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
	if (!quest::istaskcompleted(314)) {				
		quest::say("You cannot deposit into the [ ".quest::saylink("heirloom") ." ] chests until you finish my quest.");
		return;
	}


	if (!quest::istaskcompleted(501)) {
		if(plugin::check_handin(\%itemcount, 1001 => 1)) { #eat potions
			quest::say("Thank you for your potion of experience for tier 1 progression, $name.");	
			return;
		}		
	}

#Need to check if 1,2,3 or 4 stacks of experience bottles are turned in, otherwise player gets credit and items are returned.
  if(plugin::check_handin(\%itemcount, 100001 => 1)) {
	quest::say("Thank you for your potion of experience, $name.");
    return;
  }
    if(plugin::check_handin(\%itemcount, 100001 => 2)) {
	quest::say("Thank you for your potion of experience, $name.");
    return;
  }
    if(plugin::check_handin(\%itemcount, 100001 => 3)) {
	quest::say("Thank you for your potion of experience, $name.");
    return;
  }
    if(plugin::check_handin(\%itemcount, 100001 => 4)) {
	quest::say("Thank you for your potion of experience, $name.");
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

  plugin::return_items(\%itemcount);  
}