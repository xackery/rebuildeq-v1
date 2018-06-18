#ifndef STRING_IDS
#define STRING_IDS

//These strings are loaded from eqstr_us.txt, but may vary between client versions. Maybe we could make this an enum that's dependent on the client version?
#define GENERIC_9_STRINGS			1		//%1 %2 %3 %4 %5 %6 %7 %8 %9
#define TARGET_OUT_OF_RANGE			100		//Your target is out of range, get closer!
#define TARGET_NOT_FOUND			101		//Target player not found.
#define TRADE_CANCEL_LORE			104		//Trade cancelled, duplicated Lore Items would result.
#define CANNOT_BIND					105		//You cannot form an affinity with this area. Try a city.
#define SPELL_DOES_NOT_WORK_HERE	106		//This spell does not work here.
#define SPELL_DOES_NOT_WORK_PLANE	107		//This spell does not work on this plane.
#define CANT_SEE_TARGET				108		//You cannot see your target.
#define MGB_STRING					113		//The next group buff you cast will hit all targets in range.
#define ABILITY_FAILED				116		//Your ability failed. Timer has been reset.
#define ESCAPE						114		//You escape from combat, hiding yourself from view.
#define AA_OFF						119		//Alternate Experience is *OFF*.
#define AA_ON						121		//Alternate Experience is *ON*.
#define TARGET_TOO_FAR				124		//Your target is too far away, get closer!
#define PROC_TOOLOW					126		//Your will is not sufficient to command this weapon.
#define PROC_PETTOOLOW				127		//Your pet's will is not sufficient to command its weapon.
#define YOU_FLURRY					128		//You unleash a flurry of attacks.
#define FAILED_DISARM_TRAP			129		//You failed to disarm the trap.
#define DOORS_LOCKED				130		//It's locked and you're not holding the key.
#define DOORS_CANT_PICK				131		//This lock cannot be picked.
#define DOORS_INSUFFICIENT_SKILL	132		//You are not sufficiently skilled to pick this lock.
#define DOORS_GM					133		//You opened the locked door with your magic GM key.
#define ITEMS_INSUFFICIENT_LEVEL	136		//You are not sufficient level to use this item.
#define GAIN_XP						138		//You gain experience!!
#define GAIN_GROUPXP				139		//You gain party experience!!
#define BOW_DOUBLE_DAMAGE			143		//Your bow shot did double dmg.
#define YOU_ARE_BEING_BANDAGED		147		//Someone is bandaging you.
#define FORAGE_GRUBS				150		//You have scrounged up some fishing grubs.
#define FORAGE_WATER				151		//You have scrounged up some water.
#define FORAGE_FOOD					152		//You have scrounged up some food.
#define FORAGE_DRINK				153		//You have scrounged up some drink.
#define FORAGE_NOEAT				154		//You have scrounged up something that doesn't look edible.
#define FORAGE_FAILED				155		//You fail to locate any food nearby.
#define ALREADY_FISHING				156		//You are already fishing!
#define FISHING_NO_POLE				160		//You can't fish without a fishing pole, go buy one.
#define FISHING_EQUIP_POLE			161		//You need to put your fishing pole in your primary hand.
#define FISHING_NO_BAIT				162		//You can't fish without fishing bait, go buy some.
#define FISHING_CAST				163		//You cast your line.
#define NOT_SCARING					164		//You're not scaring anyone.
#define FISHING_STOP				165		//You stop fishing and go on your way.
#define FISHING_LAND				166		//Trying to catch land sharks perhaps?
#define FISHING_LAVA				167		//Trying to catch a fire elemental or something?
#define FISHING_FAILED				168		//You didn't catch anything.
#define FISHING_POLE_BROKE			169		//Your fishing pole broke!
#define FISHING_SUCCESS				170		//You caught, something...
#define FISHING_SUCCESS_FISH_NAME	421		//You caught %1!
#define FISHING_SPILL_BEER			171		//You spill your beer while bringing in your line.
#define FISHING_LOST_BAIT			172		//You lost your bait!
#define SPELL_FIZZLE				173		//Your spell fizzles!
#define MUST_EQUIP_ITEM				179		//You cannot use this item unless it is equipped.
#define MISS_NOTE					180		//You miss a note, bringing your song to a close!
#define CANNOT_USE_ITEM				181		//Your race, class, or deity cannot use this item.
#define ITEM_OUT_OF_CHARGES			182		//Item is out of charges.
#define TARGET_NO_MANA				191		//Your target has no mana to affect
#define TARGET_GROUP_MEMBER			196		//You must first target a group member.
#define SPELL_TOO_POWERFUL			197		//Your spell is too powerful for your intended target.
#define INSUFFICIENT_MANA			199		//Insufficient Mana to cast this spell!
#define SAC_TOO_LOW					203		//This being is not a worthy sacrifice.
#define SAC_TOO_HIGH				204		//This being is too powerful to be a sacrifice.
#define CANNOT_SAC_SELF				205		//You cannot sacrifice yourself.
#define SILENCED_STRING				207		//You *CANNOT* cast spells, you have been silenced!
#define CANNOT_AFFECT_PC			210		//That spell can not affect this target PC.
#define SPELL_NEED_TAR				214		//You must first select a target for this spell!
#define ONLY_ON_CORPSES				221		//This spell only works on corpses.
#define CANT_DRAIN_SELF				224		//You can't drain yourself!
#define CORPSE_NOT_VALID			230		//This corpse is not valid.
#define CORPSE_TOO_OLD				231		//This player cannot be resurrected. The corpse is too old.
#define CAST_OUTDOORS				234		//You can only cast this spell in the outdoors.
#define SPELL_RECAST				236		//Spell recast time not yet met.
#define SPELL_RECOVERY				237		//Spell recovery time not yet met.
#define CANNOT_MEZ					239		//Your target cannot be mesmerized.
#define CANNOT_MEZ_WITH_SPELL		240		//Your target cannot be mesmerized (with this spell).
#define IMMUNE_STUN					241		//Your target is immune to the stun portion of this effect.
#define IMMUNE_ATKSPEED				242		//Your target is immune to changes in its attack speed.
#define IMMUNE_FEAR					243		//Your target is immune to fear spells.
#define IMMUNE_MOVEMENT				244		//Your target is immune to changes in its run speed.
#define ONLY_ONE_PET				246		//You cannot have more than one pet at a time.
#define CANNOT_CHARM_YET			248		//Your target is too high of a level for your charm spell.
#define CANNOT_AFFECT_NPC			251		//That spell can not affect this target NPC.
#define FD_CAST_ON					254		//You are no longer feigning death, because a spell hit you.
#define SUSPEND_MINION_HAS_AGGRO	256		//Your pet is the focus of something's attention.
#define NO_PET						255		//You do not have a pet.
#define GATE_FAIL					260		//Your gate is too unstable, and collapses.
#define CORPSE_CANT_SENSE			262		//You cannot sense any corpses for this PC in this zone.
#define SPELL_NO_HOLD				263		//Your spell did not take hold.
#define CANNOT_CHARM				267		//This NPC cannot be charmed.
#define SPELL_NO_EFFECT				268		//Your target looks unaffected.
#define NO_INSTRUMENT_SKILL			269		//Stick to singing until you learn to play this instrument.
#define REGAIN_AND_CONTINUE			270		//You regain your concentration and continue your casting.
#define SPELL_WOULDNT_HOLD			271		//Your spell would not have taken hold on your target.
#define MISSING_SPELL_COMP			272		//You are missing some required spell components.
#define INVIS_BEGIN_BREAK			275		//You feel yourself starting to appear.
#define DISCIPLINE_CONLOST			278		//You lose the concentration to remain in your fighting discipline.
#define REZ_REGAIN					289		//You regain some experience from resurrection.
#define DUP_LORE					290		//Duplicate lore items are not allowed.
#define TGB_ON						293		//Target other group buff is *ON*.
#define TGB_OFF						294		//Target other group buff is *OFF*.
#define DISARMED_TRAP				305		//You have disarmed the trap.
#define LDON_SENSE_TRAP1			306		//You do not Sense any traps.
#define TRADESKILL_NOCOMBINE		334		//You cannot combine these items in this container type!
#define TRADESKILL_FAILED			336		//You lacked the skills to fashion the items together.
#define TRADESKILL_TRIVIAL			338		//You can no longer advance your skill from making this item.
#define TRADESKILL_SUCCEED			339		//You have fashioned the items together to create something new!
#define EVADE_SUCCESS				343		//You have momentarily ducked away from the main combat.
#define EVADE_FAIL					344		//Your attempts at ducking clear of combat fail.
#define HIDE_FAIL					345		//You failed to hide yourself.
#define HIDE_SUCCESS				346		//You have hidden yourself from view.
#define SNEAK_SUCCESS				347		//You are as quiet as a cat stalking its prey.
#define SNEAK_FAIL					348		//You are as quiet as a herd of running elephants.
#define MEND_CRITICAL				349		//You magically mend your wounds and heal considerable damage.
#define MEND_SUCCESS				350		//You mend your wounds and heal some damage.
#define MEND_WORSEN					351		//You have worsened your wounds!
#define MEND_FAIL					352		//You have failed to mend your wounds.
#define LDON_SENSE_TRAP2			367		//You have not detected any traps.
#define TRAP_TOO_FAR				368		//You are too far away from that trap to affect it.
#define FAIL_DISARM_DETECTED_TRAP	370		//You fail to disarm the detected trap.
#define LOOT_LORE_ERROR				371		//You cannot loot this Lore Item. You already have one.
#define PICK_LORE					379		//You cannot pick up a lore item you already possess.
#define POISON_TOO_HIGH				382		// This poison is too high level for you to apply.
#define CONSENT_DENIED				390		//You do not have consent to summon that corpse.
#define DISCIPLINE_RDY				393		//You are ready to use a new discipline now.
#define CONSENT_INVALID_NAME		397		//Not a valid consent name.
#define CONSENT_NPC					398		//You cannot consent NPC\'s.
#define CONSENT_YOURSELF			399		//You cannot consent yourself.
#define SONG_NEEDS_DRUM				405		//You need to play a percussion instrument for this song
#define SONG_NEEDS_WIND				406		//You need to play a wind instrument for this song
#define SONG_NEEDS_STRINGS			407		//You need to play a stringed instrument for this song
#define SONG_NEEDS_BRASS			408		//You need to play a brass instrument for this song
#define AA_GAIN_ABILITY				410		//You have gained the ability "%T1" at a cost of %2 ability %T3.
#define AA_IMPROVE					411		//You have improved %T1 %2 at a cost of %3 ability %T4.
#define AA_REUSE_MSG				413		//You can use the ability %B1(1) again in %2 hour(s) %3 minute(s) %4 seconds.
#define AA_REUSE_MSG2				414		//You can use the ability %B1(1) again in %2 minute(s) %3 seconds.
#define YOU_HEALED					419		//%1 has healed you for %2 points of damage.
#define BEGINS_TO_GLOW				422		//Your %1 begins to glow.
#define ALREADY_INVIS				423		//%1 tries to cast an invisibility spell on you, but you are already invisible.
#define YOU_ARE_PROTECTED			424		//%1 tries to cast a spell on you, but you are protected.
#define TARGET_RESISTED				425		//Your target resisted the %1 spell.
#define YOU_RESIST					426		//You resist the %1 spell!
#define YOU_CRIT_HEAL				427		//You perform an exceptional heal! (%1)
#define YOU_CRIT_BLAST				428		//You deliver a critical blast! (%1)
#define SUMMONING_CORPSE			429		//Summoning your corpse.
#define SUMMONING_CORPSE_OTHER		430		//Summoning %1's corpse.
#define MISSING_SPELL_COMP_ITEM		433		//You are missing %1.
#define OTHER_HIT_NONMELEE			434		//%1 was hit by non-melee for %2 points of damage.
#define SPELL_WORN_OFF_OF			436		//Your %1 spell has worn off of %2.
#define SPELL_WORN_OFF				437		//Your %1 spell has worn off.
#define PET_TAUNTING				438		//Taunting attacker, Master.
#define INTERRUPT_SPELL				439		//Your spell is interrupted.
#define LOSE_LEVEL					442		//You LOST a level! You are now level %1!
#define GAIN_ABILITY_POINT			446		//You have gained an ability point! You now have %1 ability point%2.
#define GAIN_LEVEL					447		//You have gained a level! Welcome to level %1!
#define LANG_SKILL_IMPROVED			449		//Your language skills have improved.
#define OTHER_LOOTED_MESSAGE		466		//--%1 has looted a %2--
#define LOOTED_MESSAGE				467		//--You have looted a %1--
#define FACTION_WORST				469		//Your faction standing with %1 could not possibly get any worse.
#define FACTION_WORSE				470		//Your faction standing with %1 got worse.
#define FACTION_BEST				471		//Your faction standing with %1 could not possibly get any better.
#define FACTION_BETTER				472		//Your faction standing with %1 got better.
#define PET_REPORT_HP				488		//I have %1 percent of my hit points left.
#define PET_NO_TAUNT				489		//No longer taunting attackers, Master.
#define PET_DO_TAUNT				490		//Taunting attackers as normal, Master.
#define CORPSE_DECAY1				495		//This corpse will decay in %1 minute(s) %2 seconds.
#define DISC_LEVEL_ERROR			503		//You must be a level %1 ... to use this discipline.
#define DISCIPLINE_CANUSEIN			504		//You can use a new discipline in %1 minutes %2 seconds.
#define PVP_ON						552		//You are now player kill and follow the ways of Discord.
#define GENERIC_STRINGID_SAY		554		//%1 says '%T2'
#define CANNOT_WAKE					555		//%1 tells you, 'I am unable to wake %2, master.'
#define PET_HOLD_SET_ON				698		//The pet hold mode has been set to on.
#define PET_HOLD_SET_OFF			699		//The pet hold mode has been set to off.
#define PET_FOCUS_SET_ON			700		//The pet focus mode has been set to on.
#define PET_FOCUS_SET_OFF			701		//The pet focus mode has been set to off.
#define PET_SPELLHOLD_SET_ON		702		//The pet spellhold mode has been set to on.
#define PET_SPELLHOLD_SET_OFF		703		//The pet spellhold mode has been set to off.
#define GUILD_NAME_IN_USE			711		//You cannot create a guild with that name, that guild already exists on this server.
#define GM_GAINXP					1002	//[GM] You have gained %1 AXP and %2 EXP (%3).
#define MALE_SLAYUNDEAD				1007	//%1's holy blade cleanses his target!(%2)
#define FEMALE_SLAYUNDEAD			1008	//%1's holy blade cleanses her target!(%2)
#define FINISHING_BLOW				1009	//%1 scores a Finishing Blow!!
#define ASSASSINATES				1016	//%1 ASSASSINATES their victim!!
#define CRIPPLING_BLOW				1021	//%1 lands a Crippling Blow!(%2)
#define CRITICAL_HIT				1023	//%1 scores a critical hit! (%2)
#define DEADLY_STRIKE				1024	//%1 scores a Deadly Strike!(%2)
#define RESISTS_URGE				1025	//%1 resists their urge to flee.
#define BERSERK_START				1027	//%1 goes into a berserker frenzy!
#define DEATH_PACT					1028	//%1's death pact has been benevolently fulfilled!
#define DIVINE_INTERVENTION			1029	//%1 has been rescued by divine intervention!
#define BERSERK_END					1030	//%1 is no longer berserk.
#define GATES						1031	//%1 Gates.
#define GENERIC_SAY					1032	//%1 says '%2'
#define OTHER_REGAIN_CAST			1033	//%1 regains concentration and continues casting.
#define GENERIC_SHOUT				1034	//%1 shouts '%2'
#define GENERIC_EMOTE				1036	//%1 %2
#define OTHER_CRIT_HEAL				1039	//%1 performs an exceptional heal! (%2)
#define OTHER_CRIT_BLAST			1040	//%1 delivers a critical blast! (%2)
#define NPC_ENRAGE_START			1042	//%1 has become ENRAGED.
#define NPC_ENRAGE_END				1043	//%1 is no longer enraged.
#define NPC_RAMPAGE					1044	//%1 goes on a RAMPAGE!
#define NPC_FLURRY					1045	//%1 executes a FLURRY of attacks on %2!
#define DISCIPLINE_FEARLESS			1076	//%1 becomes fearless.
#define DUEL_FINISHED				1088	//dont know text
#define EATING_MESSAGE				1091	//Chomp, chomp, chomp... %1 takes a bite from a %2.
#define DRINKING_MESSAGE			1093	//Glug, glug, glug... %1 takes a drink from a %2.
#define SUCCESSFUL_TAUNT			1095	//I'll teach you to interfere with me %3.
#define PET_SIT_STRING				1130	//Changing position, Master.
#define PET_CALMING					1131	//Sorry, Master..calming down.
#define PET_FOLLOWING				1132	//Following you, Master.
#define PET_GUARDME_STRING			1133	//Guarding you, Master.
#define PET_GUARDINGLIFE			1134	//Guarding with my life..oh splendid one.
#define PET_GETLOST_STRING			1135	//As you wish, oh great one.
#define PET_LEADERIS				1136	//My leader is %3.
#define I_FOLLOW_NOONE				1137	//I follow no one.
#define PET_ON_HOLD					1138	//Waiting for your order to attack, Master.
#define NOT_LEGAL_TARGET			1139	//I beg forgiveness, Master. That is not a legal target.
#define MERCHANT_BUSY				1143	//I'm sorry, I am busy right now.
#define MERCHANT_GREETING			1144	//Welcome to my shop, %3.
#define MERCHANT_HANDY_ITEM1		1145	//Hello there, %3. How about a nice %4?
#define MERCHANT_HANDY_ITEM2		1146	//Greetings, %3. You look like you could use a %4.
#define MERCHANT_HANDY_ITEM3		1147	//Hi there %3, just browsing? Have you seen the %4 I just got in?
#define MERCHANT_HANDY_ITEM4		1148	//Welcome to my shop, %3. You would probably find a %4 handy.
#define WONT_SELL_RACE1				1154 	//I don't like to speak to %B3(12) much less sell to them!
#define WONT_SELL_CLASS1			1155 	//It's %B3(13) like you that are ruining the continent...get OUT!
#define WONT_SELL_CLASS2			1156 	//Isn't there some kind of ordinance against %B3(13) crawling out from under their rocks?
#define WONT_SELL_CLASS3			1157 	//%B3(13) like you don't have any place in my shop..now make way for welcome customers.
#define WONT_SELL_CLASS4			1158 	//I thought scumbag %B3(13) like you just stole whatever they need.  Now GET OUT!
#define WONT_SELL_CLASS5			1159 	//I don't have anything to do with %B3(13)..move along.
#define WONT_SELL_NONSTDRACE1		1160 	//I don't have anything to do with your little gang..move along.
#define WONT_SELL_RACE2				1161 	//It's not enough that you %B3(12) have ruined your own land. Now get lost!
#define WONT_SELL_RACE3				1162 	//I have something here that %B3(12) use..let me see...it's the EXIT, now get LOST!
#define WONT_SELL_RACE4				1163 	//Don't you %B3(12) have your own merchants?  Whatever, I'm not selling anything to you!
#define WONT_SELL_NONSTDRACE2		1164 	//Members of your little "club" have ruined things around here..get lost!
#define WONT_SELL_NONSTDRACE3		1165 	//I don't have anything to do with your damned club..move along.
#define WONT_SELL_DEEDS1			1166 	//Creatures like you make me sick..the things you do..get out of here Pagan!
#define WONT_SELL_DEEDS2			1167 	//After all the things you've done..the things you believe in..leave my shop!
#define WONT_SELL_DEEDS3			1168 	//Actions speak louder than beliefs, and I despise both your actions and all you believe in.
#define WONT_SELL_DEEDS4			1169 	//Get out of here now!
#define WONT_SELL_DEEDS5			1170 	//I am tolerant by nature..but infidels like you push me past my limit..get out!
#define WONT_SELL_DEEDS6			1171 	//I cannot abide you or your actions against all that is right..BE GONE!
#define AA_POINT					1197	//point
#define AA_POINTS					1215	//points
#define SPELL_FIZZLE_OTHER			1218	//%1's spell fizzles!
#define MISSED_NOTE_OTHER			1219	//A missed note brings %1's song to a close!
#define SPELL_LEVEL_REQ				1226	//This spell only works on people who are level %1 and under.
#define CORPSE_DECAY_NOW			1227	//This corpse is waiting to expire.
#define CORPSE_ITEM_LOST			1228	//Your items will no longer stay with you when you respawn on death. You will now need to return to your corpse for your items.
#define CORPSE_EXP_LOST				1229	//You will now lose experience when you die.
#define FLICKERS_PALE_LIGHT			1230	//Your %1 flickers with a pale light.
#define PULSES_WITH_LIGHT			1231	//Your %1 pulses with light as your vision sharpens.
#define FEEDS_WITH_POWER			1232	//Your %1 feeds you with power.
#define POWER_DRAIN_INTO			1233	//You feel your power drain into your %1.
#define SEEMS_DRAINED				1234	//Your %1 seems drained of power.
#define ALIVE_WITH_POWER			1235	//Your %1 feels alive with power.
#define SPARKLES					1236	//Your %1 sparkles.
#define GROWS_DIM					1237	//Your %1 grows dim.
#define BEGINS_TO_SHINE				1238	//Your %1 begins to shine.
#define SURNAME_REJECTED			1374	//Your new surname was rejected. Please try a different name.
#define DUEL_DECLINE				1383	//%1 has declined your challenge to duel to the death.
#define DUEL_ACCEPTED				1384	//%1 has already accepted a duel with someone else.
#define DUEL_CONSIDERING			1385	//%1 is considering a duel with someone else.
#define PLAYER_REGAIN				1394	//You have control of yourself again.
#define REZZ_ALREADY_PENDING		1379	//You were unable to restore the corpse to life, but you may have success with a later attempt.
#define IN_USE						1406	//Someone else is using that. Try again later.
#define DUEL_FLED					1408	//%1 has defeated %2 in a duel to the death! %3 has fled like a cowardly dog!
#define MEMBER_OF_YOUR_GUILD		1429
#define OFFICER_OF_YOUR_GUILD		1430
#define LEADER_OF_YOUR_GUILD		1431
#define TRADE_HAS_BEEN_CANCELLED	1449
#define RECEIVED_PLATINUM			1452	//You receive %1 Platinum from %2.
#define RECEIVED_GOLD				1453	//You receive %1 Gold from %2.
#define RECEIVED_SILVER				1454	//You receive %1 Silver from %2.
#define RECEIVED_COPPER				1455	//You receive %1 Copper from %2.
#define STRING_FEIGNFAILED			1456	//%1 has fallen to the ground.
#define DOORS_SUCCESSFUL_PICK		1457	//You successfully picked the lock.
#define PLAYER_CHARMED				1461	//You lose control of yourself!
#define TRADER_BUSY					1468	//That Trader is currently with a customer. Please wait until their transaction is finished.
#define SENSE_CORPSE_DIRECTION		1563	//You sense a corpse in this direction.
#define QUEUED_TELL					2458	//[queued]
#define QUEUE_TELL_FULL				2459	//[zoing and queue is full]
#define SUSPEND_MINION_UNSUSPEND	3267	//%1 tells you, 'I live again...'
#define SUSPEND_MINION_SUSPEND		3268	//%1 tells you, 'By your command, master.'
#define ONLY_SUMMONED_PETS			3269	//3269 This effect only works with summoned pets.
#define SUSPEND_MINION_FIGHTING		3270	//Your pet must be at peace, first.
#define ALREADY_SHIELDED			3279	//Either you or your target is already being shielded.
#define START_SHIELDING				3281	//%1 begins to use %2 as a living shield!
#define END_SHIELDING				3282	//%1 ceases protecting %2.
#define TRADESKILL_MISSING_ITEM		3455	//You are missing a %1.
#define TRADESKILL_MISSING_COMPONENTS	3456	//Sorry, but you don't have everything you need for this recipe in your general inventory.
#define TRADESKILL_LEARN_RECIPE		3457	//You have learned the recipe %1!
#define EXPEDITION_MIN_REMAIN		3551	//You only have %1 minutes remaining before this expedition comes to an end.
#define LOOT_NOT_ALLOWED			3562	//You are not allowed to loot the item: %1.
#define NOT_YOUR_TRAP				3671	//You cannot remove this, you are only allowed to remove traps you have set.
#define NO_CAST_ON_PET				4045	//You cannot cast this spell on your pet.
#define REWIND_WAIT					4059	//You must wait a bit longer before using the rewind command again.
#define CORPSEDRAG_LIMIT			4061	//You are already dragging as much as you can!
#define CORPSEDRAG_ALREADY			4062	//You are already dragging %1.
#define CORPSEDRAG_SOMEONE_ELSE		4063	//Someone else is dragging %1.
#define CORPSEDRAG_BEGIN			4064	//You begin to drag %1.
#define CORPSEDRAG_STOPALL			4065	//You stop dragging the corpses.
#define CORPSEDRAG_STOP				4066	//You stop dragging the corpse.
#define SOS_KEEPS_HIDDEN			4086	//Your Shroud of Stealth keeps you hidden from watchful eyes.␣␣
#define	TARGET_TOO_CLOSE			4602	//You are too close to your target. Get farther away.
#define WHOALL_NO_RESULTS			5029	//There are no players in EverQuest that match those who filters.
#define TELL_QUEUED_MESSAGE			5045	//You told %1 '%T2. %3'
#define TOLD_NOT_ONLINE				5046	//%1 is not online at this time.
#define PETITION_NO_DELETE			5053	//You do not have a petition in the queue.
#define PETITION_DELETED			5054	//Your petition was successfully deleted.
#define ALREADY_IN_RAID				5060	//%1 is already in a raid.
#define GAIN_RAIDEXP				5085	//You gained raid experience!
#define DUNGEON_SEALED				5141	//The gateway to the dungeon is sealed off to you.  Perhaps you would be able to enter if you needed to adventure there.
#define ADVENTURE_COMPLETE			5147	//You received %1 points for successfully completing the adventure.
#define SUCCOR_FAIL					5169	//The portal collapes before you can escape!
#define PET_ATTACKING				5501	//%1 tells you, 'Attacking %2 Master.'
#define AVOID_STUNNING_BLOW			5753	//You avoid the stunning blow.
#define FATAL_BOW_SHOT				5745	//%1 performs a FATAL BOW SHOT!!
#define SUSPECT_SEES_YOU			5746	//You suspect that this being can see you.
#define MELEE_SILENCE				5806	//You *CANNOT* use this melee ability, you are suffering from amnesia!
#define DISCIPLINE_REUSE_MSG		5807	//You can use the ability %1 again in %2 hour(s) %3 minute(s) %4 seconds.
#define DISCIPLINE_REUSE_MSG2		5808	//You can use the ability %1 again in %2 minute(s) %3 seconds.
#define FAILED_TAUNT				5811	//You have failed to taunt your target.
#define PHYSICAL_RESIST_FAIL		5817	//Your target avoided your %1 ability.
#define AA_NO_TARGET				5825	//You must first select a target for this ability!
#define FORAGE_MASTERY				6012	//Your forage mastery has enabled you to find something else!
#define GUILD_BANK_CANNOT_DEPOSIT	6097	// Cannot deposit this item. Containers must be empty, and only one of each LORE and no NO TRADE or TEMPORARY items may be deposited.
#define GUILD_BANK_FULL				6098	// There is no more room in the Guild Bank.
#define GUILD_BANK_TRANSFERRED		6100	// '%1' transferred to Guild Bank from Deposits.
#define GUILD_BANK_EMPTY_HANDS		6108	// You must empty your hands to withdraw from the Guild Bank.
#define TRANSFORM_FAILED			6326	//This mold cannot be applied to your %1.
#define TRANSFORM_COMPLETE			6327	//You have successfully transformed your %1.
#define DETRANSFORM_FAILED			6341 	//%1 has no transformation that can be removed.
#define GENERIC_STRING				6688	//%1 (used to any basic message)
#define SENTINEL_TRIG_YOU			6724	//You have triggered your sentinel.
#define SENTINEL_TRIG_OTHER			6725	//%1 has triggered your sentinel.
#define IDENTIFY_SPELL				6765	//Item Lore: %1.
#define PET_NOW_HOLDING				6834	//Now holding, Master.  I will not start attacks until ordered.
#define PET_ON_GHOLD				6843	//Pet greater hold has been set to on.
#define PET_OFF_GHOLD				6846	//Pet greater hold has been set to off.
#define PET_GHOLD_ON_MSG			6847	//Now greater holding master.  I will only attack something new if ordered.
#define PET_ON_REGROUPING			6854	//Now regrouping, master.
#define PET_OFF_REGROUPING			6855	//No longer regrouping, master.
#define BUFF_NOT_BLOCKABLE			7608	//You cannot block this effect.
#define LDON_DONT_KNOW_TRAPPED		7552	//You do not know if this object is trapped.
#define LDON_HAVE_DISARMED			7553	//You have disarmed %1!
#define LDON_ACCIDENT_SETOFF		7554	//You accidentally set off the trap!
#define LDON_HAVE_NOT_DISARMED		7555	//You have not disarmed %1.
#define LDON_ACCIDENT_SETOFF2		7556	//You accidentally set off the trap!
#define LDON_CERTAIN_TRAP			7557	//You are certain that %1 is trapped.
#define LDON_CERTAIN_NOT_TRAP		7558	//You are certain that %1 is not trapped.
#define LDON_CANT_DETERMINE_TRAP	7559	//You are unable to determine if %1 is trapped.
#define LDON_PICKLOCK_SUCCESS		7560	//You have successfully picked %1!
#define LDON_PICKLOCK_FAILURE		7561	//You have failed to pick %1.
#define LDON_STILL_LOCKED			7562	//You cannot open %1, it is locked.
#define LDON_BASH_CHEST				7563	//%1 try to %2 %3, but do no damage.
#define DOORS_NO_PICK				7564	//You must have a lock pick in your inventory to do this.
#define LDON_NO_LOCKPICK			7564	//You must have a lock pick in your inventory to do this.
#define LDON_WAS_NOT_LOCKED			7565	//%1 was not locked.
#define LDON_WAS_NOT_TRAPPED		7566	//%1 was not trapped
#define GAIN_GROUP_LEADERSHIP_POINT	8585	//
#define GAIN_RAID_LEADERSHIP_POINT	8589	//
#define MAX_GROUP_LEADERSHIP_POINTS	8584	//
#define MAX_RAID_LEADERSHIP_POINTS	8591	//
#define LEADERSHIP_EXP_ON			8653	//
#define LEADERSHIP_EXP_OFF			8654	//
#define CURRENT_SPELL_EFFECTS		8757	//%1's current spell effects:
#define GAIN_GROUP_LEADERSHIP_EXP	8788	//
#define GAIN_RAID_LEADERSHIP_EXP	8789	//
#define BUFF_MINUTES_REMAINING		8799	//%1 (%2 minutes remaining)
#define NO_MORE_TRAPS				9002	//You have already placed your maximum number of traps.
#define FEAR_TOO_HIGH				9035	//Your target is too high of a level for your fear spell.
#define SLOW_MOSTLY_SUCCESSFUL		9029	//Your spell was mostly successful.
#define SLOW_PARTIALLY_SUCCESSFUL	9030	// Your spell was partially successful.
#define SLOW_SLIGHTLY_SUCCESSFUL	9031	//Your spell was slightly successful.
#define SPELL_OPPOSITE_EFFECT		9032	//Your spell may have had the opposite effect of what you desired.
#define HAS_BEEN_AWAKENED			9037	//%1 has been awakened by %2.
#define YOU_HEAL					9068	//You have healed %1 for %2 points of damage.
#define YOUR_HIT_DOT				9072	//%1 has taken %2 damage from your %3.
#define HIT_NON_MELEE				9073	//%1 hit %2 for %3 points of non-melee damage.
#define GLOWS_BLUE					9074	//Your %1 glows blue.
#define GLOWS_RED					9075	//Your %1 glows red.
#define SHAKE_OFF_STUN				9077	//You shake off the stun effect!
#define STRIKETHROUGH_STRING		9078	//You strike through your opponent's defenses!
#define SPELL_REFLECT				9082	//%1's spell has been reflected by %2.
#define NO_MORE_AURAS				9160	//You do not have sufficient focus to maintain that ability.
#define NEW_SPELLS_AVAIL			9149	//You have new spells available to you. Check the merchants near your guild master.
#define FD_CAST_ON_NO_BREAK			9174	//The strength of your will allows you to resume feigning death.
#define SNEAK_RESTRICT				9240	//You can not use this ability because you have not been hidden for long enough.
#define PET_NOW_FOCUSING			9254	//Focusing on one target, Master.
#define PET_NOT_FOCUSING			9263	//No longer focusing on one target, Master.
#define PET_NOT_CASTING				9264	//Not casting spells, Master.
#define PET_CASTING					9291	//Casting spells normally, Master.
#define NO_CAST_IN_COMBAT			9190	//You can not cast this spell while in combat.
#define NO_CAST_OUT_OF_COMBAT		9191	//You can not cast this spell while out of combat.
#define NO_ABILITY_IN_COMBAT		9192	//You can not use this ability while in combat.
#define NO_ABILITY_OUT_OF_COMBAT	9194	//You can not use this ability while out of combat.
#define AE_RAMPAGE					11015	//%1 goes on a WILD RAMPAGE!
#define FACE_ACCEPTED				12028	//Facial features accepted.
#define SPELL_LEVEL_TO_LOW			12048	//You will have to achieve level %1 before you can scribe the %2.
#define ATTACKFAILED				12158	//%1 try to %2 %3, but %4!
#define HIT_STRING					12183	//hit
#define CRUSH_STRING				12191	//crush
#define PIERCE_STRING				12193	//pierce
#define KICK_STRING					12195	//kick
#define STRIKE_STRING				12197	//strike
#define BACKSTAB_STRING				12199	//backstab
#define BASH_STRING					12201	//bash
#define GUILD_NOT_MEMBER			12242	//You are not a member of any guild.
#define MEMBER_OF_X_GUILD			12256
#define OFFICER_OF_X_GUILD			12257
#define LEADER_OF_X_GUILD			12258
#define NOT_IN_A_GUILD				12259
#define TARGET_PLAYER_FOR_GUILD_STATUS		12260
#define GROUP_INVITEE_NOT_FOUND		12268	//You must target a player or use /invite <name> to invite someone to your group.
#define GROUP_INVITEE_SELF			12270	//12270 You cannot invite yourself.
#define NO_LONGER_HIDDEN			12337   //You are no longer hidden.
#define STOP_SNEAKING				12338	//You stop sneaking
#define NOT_IN_CONTROL				12368	//You do not have control of yourself right now.
#define ALREADY_CASTING				12442	//You are already casting a spell!
#define SHIMMERS_BRIEFLY			12444	//Your %1 shimmers briefly.
#define SENSE_CORPSE_NOT_NAME		12446	//You don't sense any corpses of that name.
#define SENSE_CORPSE_NONE			12447	//You don't sense any corpses.
#define SCREECH_BUFF_BLOCK			12448	//Your immunity buff protected you from the spell %1!
#define NOT_HOLDING_ITEM			12452	//You are not holding an item!
#define SENSE_UNDEAD				12471	//You sense undead in this direction.
#define SENSE_ANIMAL				12472	//You sense an animal in this direction.
#define SENSE_SUMMONED				12473	//You sense a summoned being in this direction.
#define SENSE_NOTHING				12474	//You don't sense anything.
#define SENSE_TRAP					12475	//You sense a trap in this direction.
#define LDON_SENSE_TRAP3			12476	//You don't sense any traps.
#define INTERRUPT_SPELL_OTHER		12478	//%1's casting is interrupted!
#define YOU_HIT_NONMELEE			12481	//You were hit by non-melee for %1 damage.
#define TRACK_LOST_TARGET			12681	//You have lost your tracking target.
#define TRACK_STRAIGHT_AHEAD		12676
#define TRACK_AHEAD_AND_TO			12677
#define TRACK_TO_THE				12678
#define TRACK_BEHIND_AND_TO			12679
#define TRACK_BEHIND_YOU			12680
#define BEAM_SMILE					12501	//%1 beams a smile at %2
#define SONG_ENDS_ABRUPTLY			12686	//Your song ends abruptly.
#define SONG_ENDS					12687	//Your song ends.
#define SONG_ENDS_OTHER				12688	//%1's song ends.
#define SONG_ENDS_ABRUPTLY_OTHER	12689	//%1's song ends abruptly.
#define DIVINE_AURA_NO_ATK			12695	//You can't attack while invulnerable!
#define TRY_ATTACKING_SOMEONE		12696	//Try attacking someone other than yourself, it's more productive
#define RANGED_TOO_CLOSE			12698	//Your target is too close to use a ranged weapon!
#define BACKSTAB_WEAPON				12874	//You need a piercing weapon as your primary weapon in order to backstab
#define MORE_SKILLED_THAN_I			12931	//%1 tells you, 'You are more skilled than I! What could I possibly teach you?'
#define SURNAME_EXISTS				12939	//You already have a surname. Operation failed.
#define SURNAME_LEVEL				12940	//You can only submit a surname upon reaching the 20th level. Operation failed.
#define SURNAME_TOO_LONG			12942	//Surname must be less than 20 characters in length.
#define REPORT_ONCE					12945	//You may only submit a report once per time that you zone. Thank you.
#define NOW_INVISIBLE				12950	//%1 is now Invisible.
#define NOW_VISIBLE					12951	//%1 is now Visible.
#define GUILD_NOT_MEMBER2			12966	//You are not in a guild.
#define HOT_HEAL_SELF				12976 	//You have been healed for %1 hit points by your %2.
#define HOT_HEAL_OTHER				12997	//You have healed %1 for %2 hit points with your %3.
#define HOT_HEALED_OTHER			12998	//%1 healed you for %2 hit points by %3.
#define DISC_LEVEL_USE_ERROR		13004	//You are not sufficient level to use this discipline.
#define TOGGLE_ON					13172	//Asking server to turn ON your incoming tells.
#define TOGGLE_OFF					13173	//Asking server to turn OFF all incoming tells for you.
#define DUEL_INPROGRESS				13251	//You have already accepted a duel with someone else cowardly dog.
#define OTHER_HIT_DOT				13327	//%1 has taken %2 damage from %3 by %4.
#define GENERIC_MISS				15041	//%1 missed %2


//Encounter Types
#define EN_ZOMBIE 187000
#define EN_DOPPLEGANGER 187001
#define EN_ARCHER 187002
#define EN_ORC 187003
#define EN_BANDIT 187004 //12016
#define EN_HILLGIANT 187005
#define EN_WISP 187006
#define EN_AIRELEMENTAL 187007
#define EN_FROGLOK 187008
#define EN_TROLLGUARD 187009
#define EN_GYPSY 187010//37065, 37075
#define EN_DERVISH 187011 //34118, 34097, 34024, 34036, 34117, 34082
#define EN_MADMAN 187012 //37007
#define EN_SANDGIANT 187013 //37138
#define EN_FREEPORT 187014 //34045
#define EN_ANCIENTCYCLOPS 187015 //35139
#define EN_GRIFFIN 187016 //22187
#define EN_KODIAK 187017 //22125
#define EN_FUNGUS 187018 //11016 sporali
#define EN_SPECTRE 187019 //37021 spectre
#define EN_ALLIGATOR 187020 //37104 lockjaw
#define EN_COLDAIN 187021 //129060 an_icewell_sentry
#define EN_KAELGIANT 187022 //113419 a_kael_giant, rare 113079
#define EN_RYGORR 187023 //116006 Oracle of Ry`Gorr, 116011 Ry`Gorr elite guard
#define EN_WYVERN 187024 //117003 Wyvern
#define EN_KOBOLD 187025 //101101 warren
#define EN_MISTMOORE 187026

//Feats
#define FEAT_PETNAMING 300
#define FEAT_PETDISCIPLINE 301
#define FEAT_CHARMOFDEFENSE 302
#define FEAT_FRONTSTUN 303
#define FEAT_CURSEDFRAGMENTS 304
#define FEAT_INNATERUNSPEED 305
#define FEAT_MYSTICALATTUNING 306
#define FEAT_GETTINGSTARTED 307
#define FEAT_PETAFFINITY 308
#define FEAT_CHARMOFMANA 309
#define FEAT_CHARMOFINSTRUMENTS 310
#define FEAT_CHARMOFDAGGERS 311
#define FEAT_HEALTHOFTARGETSTARGET 312

//Tiers
#define TIER_1 501
#define TIER_2 502
#define TIER_3 503
#define TIER_4 504
#define TIER_5 505
#define TIER_6 506
#define TIER_7 507
#define TIER_8 508
#define TIER_9 509


//Build Skills
#define RB_BRD_ELEMENTALHARMONY 0
#define RB_BRD_HEALINGTREBLE 2
#define RB_BRD_PSALMOFNORRATH 4
#define RB_BRD_CASSINDRASCHORUS 6
#define RB_BRD_SHIELDOFSONGS 8
#define RB_BRD_KATTASCONCORD 10
#define RB_BRD_CASSINDRASSECRET 13
#define RB_BRD_KINSONG 16
#define RB_BRD_JONTHONSWHISTLE 18
#define RB_BRD_OFFHANDATTACK 20
#define RB_BRD_INNATESONGBLADE 22
#define RB_BRD_WARSONGOFZEK 24
#define RB_BRD_DANCEOFBLADES 26
#define RB_BRD_BLADEDANCER 28
#define RB_BRD_HARMONICAFFINITY 31
#define RB_BRD_BARDSWISH 34
#define RB_BRD_CHANTCYCLE 36
#define RB_BRD_BOASTFULBELLOW 38
#define RB_BRD_SELOSCRESCENDO 40
#define RB_BRD_SOOTHINGMELODY 42
#define RB_BRD_SHOUT 44
#define RB_BRD_SIRENSSONG 46
#define RB_BRD_LINGERINGTWILIGHT 49
#define RB_BRD_FADINGMEMORIES 52

#define RB_CLR_BELIEVE 0
#define RB_CLR_WARDOFVIE 2
#define RB_CLR_HARKENTHEGODS 4
#define RB_CLR_BLESSINGOFHASTE 6
#define RB_CLR_DIVINEHAMMER 8
#define RB_CLR_MARKOFKARN 10
#define RB_CLR_AUGMENTEDRETRIBUTION 13
#define RB_CLR_DIVINEAVATAR 16
#define RB_CLR_INSTILLLIFE 18
#define RB_CLR_DIVINEBASH 20
#define RB_CLR_INTENSITYOFTHERESOLUTE 22
#define RB_CLR_CELESTIALREGENERATION 24
#define RB_CLR_DIVINEARBITRATION 26
#define RB_CLR_DIVINERESURRECTION 28
#define RB_CLR_PROMISE 31
#define RB_CLR_HARMONICBALANCE 34
#define RB_CLR_STRIKE 36
#define RB_CLR_WARDOFREBUKE 38
#define RB_CLR_FISTOFTHEGODS 40
#define RB_CLR_DIVINERETRIBUTION 42
#define RB_CLR_TURNUNDEAD 44
#define RB_CLR_EXQUISITEBENEDICTION 46
#define RB_CLR_MARKOFRETRIBUTION 49
#define RB_CLR_DEATHPACT 52

#define RB_DRU_ENTRAP 0
#define RB_DRU_ONEWITHNATURE 2
#define RB_DRU_TELEPORTBIND 4
#define RB_DRU_EXODUS 6
#define RB_DRU_CALLOFTHEWILD 8
#define RB_DRU_SECONDARYRECALL 10
#define RB_DRU_RINGAFFINITY 13
#define RB_DRU_DIRECHARM 16
#define RB_DRU_REGENERATION 18
#define RB_DRU_CONVERGENCEOFSPIRITS 20
#define RB_DRU_LIFEFLOW 22
#define RB_DRU_SPIRITOFTHEWOOD 24
#define RB_DRU_SPIRITUALAWAKENING 26
#define RB_DRU_NATURESBOON 28
#define RB_DRU_NATURESWHISPER 31
#define RB_DRU_NATURESGUARDIAN 34
#define RB_DRU_INTENSITY 36
#define RB_DRU_LINGERINGPAIN 38
#define RB_DRU_FOCUSEDSWARM 40
#define RB_DRU_BLESSINGOFRO 42
#define RB_DRU_WHIRLINGDISASTER 44
#define RB_DRU_STINGINGAFFLICTION 46
#define RB_DRU_DEEPROOTS 49
#define RB_DRU_NATURESBLIGHT 52

#define RB_ENC_NIGHTMARE 0
#define RB_ENC_CRIPPLINGPRESENCE 2
#define RB_ENC_SOOTHINGWORDS 4
#define RB_ENC_MINDOVERMATTER 6
#define RB_ENC_BENEFICIALDISPELL 8
#define RB_ENC_PERSUASION 10
#define RB_ENC_CHOKE 13
#define RB_ENC_DROWN 16
#define RB_ENC_ENTHRALL 18
#define RB_ENC_TASH 20
#define RB_ENC_BACKFIRE 22
#define RB_ENC_ENERGYBURN 24
#define RB_ENC_FEEDBACK 26 
#define RB_ENC_FOCUS 28
#define RB_ENC_LIFEFLOW 31
#define RB_ENC_EXTENDEDCHARM 34
#define RB_ENC_MINDDEVOURER 36
#define RB_ENC_COLORSHOCK 38
#define RB_ENC_MANASPEAR 40
#define RB_ENC_FLOWINGTHOUGHT 42
#define RB_ENC_SUBTLECASTING 44
#define RB_ENC_BADMOON 46
#define RB_ENC_TRANQUILITY 49
#define RB_ENC_RECLAIM 52

#define RB_MAG_SUMMONINGFOCUS 0
#define RB_MAG_QUICKSUMMONING 2
#define RB_MAG_IMPROVEDRECLAIMENERGY 4
#define RB_MAG_MODULATIONSHARD 6
#define RB_MAG_COMPANIONSINTENSITY 8
#define RB_MAG_SUSPENDEDMINION 10
#define RB_MAG_MENDCOMPANION 13
#define RB_MAG_COMPANIONOFNECESSITY 16
#define RB_MAG_SHAREDHEALTH 18
#define RB_MAG_HOSTINTHESHELL 20
#define RB_MAG_TURNSUMMONED 22
#define RB_MAG_FRENZIEDBURNOUT 24
#define RB_MAG_ELEMENTALALACRITY 26
#define RB_MAG_CALLOFTHEHERO 28
#define RB_MAG_CLOCKWORKMERCHANT 31
#define RB_MAG_SERVANTOFRO 34
#define RB_MAG_DIMENSIONALSHIELD 36
#define RB_MAG_HEARTOFSTONE 38
#define RB_MAG_HEARTOFVAPOR 40
#define RB_MAG_SHOCKOFSWORDS 42
#define RB_MAG_HEARTOFICE 44
#define RB_MAG_QUICKDAMAGE 46
#define RB_MAG_HEARTOFFLAMES 49
#define RB_MAG_PRIMALFUSION 52

#define RB_MNK_INTENSIFIEDTRAINING 0
#define RB_MNK_FAMILIARITY 2
#define RB_MNK_BLOCK 4
#define RB_MNK_RELENTLESSTRAINING 6
#define RB_MNK_EXPOSEWEAKNESS 8
#define RB_MNK_DESTINY 10
#define RB_MNK_WUSQUICKENING 13
#define RB_MNK_GRACEOFTHEORDER 16
#define RB_MNK_PARTIALMENDING 18
#define RB_MNK_INNERCHAKRA 20
#define RB_MNK_CHANNELCHAKRA 22
#define RB_MNK_MENDINGAURA 24
#define RB_MNK_DIVINESURGE 26
#define RB_MNK_IMPROVEDMEND 28
#define RB_MNK_PURIFYBODY 31
#define RB_MNK_TRANQUILITY 34 
#define RB_MNK_AGILEFEET 36
#define RB_MNK_COWARDLYSTANCE 38
#define RB_MNK_THUNDERFOOT 40
#define RB_MNK_STOICMIND 42
#define RB_MNK_GROUNDEDESSENCE 44
#define RB_MNK_SLOWHEARTRATE 46
#define RB_MNK_MIRROR 49
#define RB_MNK_MOVINGMOUNTAINS 52


#define RB_NEC_CORRUPTION 0
#define RB_NEC_CAVORTINGBONES 2
#define RB_NEC_SHOCKINGBOLT 4
#define RB_NEC_BURNINGSOUL 6
#define RB_NEC_LINGERINGCURSE 8
#define RB_NEC_DECAY 10
#define RB_NEC_SPLURT 13
#define RB_NEC_VENOMSTRIKE 16
#define RB_NEC_SHROUDOFDEATH 18
#define RB_NEC_LIFEBURN 20
#define RB_NEC_PACTOFHATE 22
#define RB_NEC_BLOODMAGIC 24
#define RB_NEC_LIFEBLOOD 26
#define RB_NEC_SPIRITFOCUS 28
#define RB_NEC_DYINGGRASP 31
#define RB_NEC_SERVANTOFBLOOD 34
#define RB_NEC_ARMOROFDEATH 36
#define RB_NEC_BLOODREALM 38
#define RB_NEC_DEATHLYAURA 40
#define RB_NEC_BURDENOFUNDEAD 42
#define RB_NEC_DEATHBLOOM 44
#define RB_NEC_ETERNITYOFUNDEATH 46
#define RB_NEC_GHOULCLAWS 49
#define RB_NEC_LICHKING 52

#define RB_PAL_RODCETSGIFT 0
#define RB_PAL_HANDOFPIETY 2
#define RB_PAL_INSTILLPURPOSE 4
#define RB_PAL_REFRESHINGBREEZE 6
#define RB_PAL_BRELLSBLESSING 8
#define RB_PAL_SOULCLEANSING 10
#define RB_PAL_WAVEOFMARR 13
#define RB_PAL_WARDOFTUNARE 16
#define RB_PAL_SHIELDOFNIFE 18
#define RB_PAL_ARMOROFFAITH 20
#define RB_PAL_PURIFICATION 22
#define RB_PAL_HOLYSERVANT 24
#define RB_PAL_DIVINESTUN 26
#define RB_PAL_ACTOFVALOR 28
#define RB_PAL_ELIXIROFMIGHT 31
#define RB_PAL_FLAMESOFREDEMPTION 34
#define RB_PAL_ZEALOTSFERVOR 36
#define RB_PAL_KNIGHTSADVANTAGE 38
#define RB_PAL_CHOSEN 40
#define RB_PAL_PURPOSEOFMARR 42
#define RB_PAL_FLAMEOFLIGHT 44
#define RB_PAL_DISMISSEVIL 46
#define RB_PAL_FRAIL 49
#define RB_PAL_SLAYER 52

#define RB_ROG_APPRAISAL 0
#define RB_ROG_KILLINGSPREE 2
#define RB_ROG_THIEFSEYES 4
#define RB_ROG_SINISTERSTRIKES 6
#define RB_ROG_SNEAKATTACK 8
#define RB_ROG_FOCUSEDSTAB 10
#define RB_ROG_VITALORGANS 13
#define RB_ROG_ASSASSINSTAINT 16
#define RB_ROG_SLEIGHTDISTRACTION 18
#define RB_ROG_JARRINGSTAB 20
#define RB_ROG_UNTAPPEDPOTENTIAL 22
#define RB_ROG_CONFUSE 24
#define RB_ROG_GANGSTERSPARADISE 26
#define RB_ROG_MOSSSTONE 28
#define RB_ROG_DUELIST 31
#define RB_ROG_ESCAPE 34
#define RB_ROG_SLEIGHTOFSTRENGTH 36
#define RB_ROG_HAGGLE 38
#define RB_ROG_HIDDENSTASH 40
#define RB_ROG_THROWINGPRECISION 42
#define RB_ROG_MUGGINGSHOT 44
#define RB_ROG_DEADLYDAGGER 46
#define RB_ROG_THIEVESAFFINITY 49
#define RB_ROG_HIDDENDAGGER 52

#define RB_SHD_LEECHTOUCH 0
#define RB_SHD_GOUGINGSKIN 2
#define RB_SHD_HUNGERINGAURA 4
#define RB_SHD_STEADFASTSERVANT 6
#define RB_SHD_ZEVFEERSFEAST 8
#define RB_SHD_SWORNENEMY 10
#define RB_SHD_BANSHEESMIRROR 13
#define RB_SHD_REAPERSSTRIKE 16
#define RB_SHD_FESTERINGSPEAR 18
#define RB_SHD_FESTERINGWOUND 20
#define RB_SHD_ROTTENCORE 22
#define RB_SHD_LINGERINGPAIN 24
#define RB_SHD_BLOODOATH 26
#define RB_SHD_GIFTOFURASH 28
#define RB_SHD_UNHOLYFOCUS 31
#define RB_SHD_BASHOFDEATH 34
#define RB_SHD_EMBRACEDEATH 36
#define RB_SHD_DARKNESS 38
#define RB_SHD_EMPATHETICSOUL 40
#define RB_SHD_EMBRACESHADOW 42
#define RB_SHD_SIPHONOFDEATH 44
#define RB_SHD_NIGHTMARE 46
#define RB_SHD_MENTALRESISTANCE 49
#define RB_SHD_CLOAKOFSHADOWS 52

#define RB_SHM_SPIRITOFSPEED 0
#define RB_SHM_PURIFYSOUL 2
#define RB_SHM_ANCESTRALAID 4
#define RB_SHM_EXTENDEDHASTE 6
#define RB_SHM_SPIRITUALHEALING 8
#define RB_SHM_COVENANTOFSPIRIT 10
#define RB_SHM_REINFORCETORPOR 13
#define RB_SHM_FATESEERSBOON 16
#define RB_SHM_CANNIBALIZE 18
#define RB_SHM_SPIRITCALL 20
#define RB_SHM_VIRULENTPARALYSIS 22
#define RB_SHM_POISON 24
#define RB_SHM_EXTENDEDTURGUR 26
#define RB_SHM_ANCIENTWRATH 28
#define RB_SHM_TURGURSECHO 31
#define RB_SHM_SPIRITUALCHANNELING 34
#define RB_SHM_FURY 36
#define RB_SHM_RABIDBEAR 38
#define RB_SHM_ANCESTRALGUARD 40
#define RB_SHM_CALLOFTHEANCIENTS 42
#define RB_SHM_SPIRITUALWRATH 44
#define RB_SHM_MARKOFSLOTH 46
#define RB_SHM_FERALSWIPE 49
#define RB_SHM_PARAGONOFSPIRIT 52

#endif

