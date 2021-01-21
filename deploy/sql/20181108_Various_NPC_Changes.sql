#Issue #2766: Ice Burrower's in west waste are not suppose to summon
#Remove summon ability for Ice Borrowers
UPDATE `npc_types` SET `special_abilities` = NULL WHERE (`id` = '120010');

#Issue 1736 - Add (Armor Quest) last name to Lieutenant_Bythgar
UPDATE npc_types SET lastname="Armor Quest" WHERE id=115071; -- whovian (10-Nov-18  2:48:18)

#Issue 3306 - Cazic Thule loot table
#Remove loot from cazic
DELETE FROM lootdrop_entries WHERE lootdrop_id='677' AND item_id='11609'; -- whovian (10-Nov-18  3:25:07)
DELETE FROM lootdrop_entries WHERE lootdrop_id='677' AND item_id='11643'; -- whovian (10-Nov-18  3:25:43)
DELETE FROM lootdrop_entries WHERE lootdrop_id='677' AND item_id='11644'; -- whovian (10-Nov-18  3:26:05)
DELETE FROM lootdrop_entries WHERE lootdrop_id='677' AND item_id='11645'; -- whovian (10-Nov-18  3:26:30)
DELETE FROM lootdrop_entries WHERE lootdrop_id='677' AND item_id='11646'; -- whovian (10-Nov-18  3:26:42)
DELETE FROM lootdrop_entries WHERE lootdrop_id='677' AND item_id='11648'; -- whovian (10-Nov-18  3:26:48)
DELETE FROM lootdrop_entries WHERE lootdrop_id='677' AND item_id='17703'; -- whovian (10-Nov-18  3:26:51)
DELETE FROM lootdrop_entries WHERE lootdrop_id='677' AND item_id='20655'; -- whovian (10-Nov-18  3:26:59)
DELETE FROM lootdrop_entries WHERE lootdrop_id='677' AND item_id='11641'; -- whovian (10-Nov-18  3:35:02)
#Add loot to Cazic
INSERT INTO lootdrop_entries SET lootdrop_id=677, item_id=1550, equip_item=1, item_charges=1, multiplier=1, chance=14; -- whovian (10-Nov-18  3:37:10)
INSERT INTO lootdrop_entries SET lootdrop_id=677, item_id=1554, equip_item=1, item_charges=1, multiplier=1, chance=14; -- whovian (10-Nov-18  3:38:06)
INSERT INTO lootdrop_entries SET lootdrop_id=677, item_id=1551, equip_item=1, item_charges=1, multiplier=1, chance=14; -- whovian (10-Nov-18  3:38:26)
INSERT INTO lootdrop_entries SET lootdrop_id=677, item_id=1547, equip_item=1, item_charges=1, multiplier=1, chance=14; -- whovian (10-Nov-18  3:38:48)
INSERT INTO lootdrop_entries SET lootdrop_id=677, item_id=1549, equip_item=1, item_charges=1, multiplier=1, chance=14; -- whovian (10-Nov-18  3:39:05)
INSERT INTO lootdrop_entries SET lootdrop_id=677, item_id=1531, equip_item=1, item_charges=1, multiplier=1, chance=14; -- whovian (10-Nov-18  3:39:39)
INSERT INTO lootdrop_entries SET lootdrop_id=677, item_id=1552, equip_item=1, item_charges=1, multiplier=1, chance=14; -- whovian (10-Nov-18  3:39:56)
#Add Crimson Robe of Alendine to the golems since it will no longer drop from CT.
INSERT INTO lootdrop_entries SET lootdrop_id=8678, item_id=11641, equip_item=1, item_charges=1, multiplier=1, chance=5; -- whovian (10-Nov-18  3:27:59)
INSERT INTO lootdrop_entries SET lootdrop_id=8681, item_id=11641, equip_item=1, item_charges=1, multiplier=1, chance=5; -- whovian (10-Nov-18  3:30:16)
INSERT INTO lootdrop_entries SET lootdrop_id=165666, item_id=11641, equip_item=1, item_charges=1, multiplier=1, chance=5; -- whovian (10-Nov-18  3:30:31)
