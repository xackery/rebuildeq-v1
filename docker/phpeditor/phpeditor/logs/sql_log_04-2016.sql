DELETE FROM inventory WHERE charid=604 AND slotid=310; -- packard (21-Apr-16  12:51:33)
UPDATE npc_types SET race="127", bodytype="67", special_abilities="19,1^20,1^" WHERE id=86051; -- Uncharted  (24-Apr-16  9:08:26)
UPDATE npc_types SET special_abilities = TRIM(TRAILING '^' FROM special_abilities); -- Uncharted  (24-Apr-16  9:08:26)
DELETE FROM pets WHERE npcID=86051; -- Uncharted  (24-Apr-16  9:08:26)
UPDATE npc_types SET race="127", bodytype="67", special_abilities="19,1^20,1^24,1^" WHERE id=86153; -- Uncharted  (24-Apr-16  9:09:01)
UPDATE npc_types SET special_abilities = TRIM(TRAILING '^' FROM special_abilities); -- Uncharted  (24-Apr-16  9:09:02)
DELETE FROM pets WHERE npcID=86153; -- Uncharted  (24-Apr-16  9:09:02)
DELETE FROM aa_timers WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM adventure_members WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM adventure_stats WHERE player_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM buyer WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_activities WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_alternate_abilities WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_alt_currency WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_backup WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_bandolier WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_bind WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_buffs WHERE character_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_currency WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_data WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_disciplines WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_enabledtasks WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_inspect_messages WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_languages WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_leadership_abilities WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_memmed_spells WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_pet_buffs WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_pet_info WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_pet_inventory WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_potionbelt WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_skills WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_spells WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_tasks WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_tribute WHERE id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM char_recipe_list WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM completed_tasks WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM discovered_items WHERE char_name=(SELECT name FROM character_data WHERE id=87); -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM faction_values WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM friends WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM group_id WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM guild_members WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM instance_list_player WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM inventory WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM keyring WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM mail WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM character_corpses WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM player_corpses_backup WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM player_titlesets WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM quest_globals WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM raid_members WHERE charid=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM timers WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM trader WHERE char_id=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM zone_flags WHERE charID=87; -- Uncharted  (24-Apr-16  13:05:21)
DELETE FROM account WHERE id=69764; -- Uncharted  (24-Apr-16  13:14:34)
DELETE FROM account_ip WHERE accid=69764; -- Uncharted  (24-Apr-16  13:14:34)
DELETE FROM account_rewards WHERE account_id=69764; -- Uncharted  (24-Apr-16  13:14:34)
DELETE FROM eventlog WHERE accountid=69764; -- Uncharted  (24-Apr-16  13:14:34)
DELETE FROM gm_ips WHERE account_id=69764; -- Uncharted  (24-Apr-16  13:14:34)
DELETE FROM sharedbank WHERE acctid=69764; -- Uncharted  (24-Apr-16  13:14:34)
UPDATE npc_faction SET primaryfaction=42 WHERE id=628; -- Uncharted  (24-Apr-16  15:13:05)
UPDATE npc_faction SET primaryfaction=366 WHERE id=628; -- Uncharted  (24-Apr-16  15:33:39)
INSERT INTO npc_faction SET id=1288, name="ToV North KoS", ignore_primary_assist="0"; -- Uncharted  (24-Apr-16  15:35:31)
UPDATE npc_types SET npc_faction_id=1288 WHERE id=124159; -- Uncharted  (24-Apr-16  15:35:31)
UPDATE npc_faction SET primaryfaction=366 WHERE id=1288; -- Uncharted  (24-Apr-16  15:36:53)
INSERT INTO npc_faction_entries SET npc_faction_id=1288, faction_id=42, value=-30, npc_value=1, temp=0; -- Uncharted  (24-Apr-16  15:37:22)
INSERT INTO npc_faction_entries SET npc_faction_id=1288, faction_id=134, value=-30, npc_value=1, temp=0; -- Uncharted  (24-Apr-16  15:37:36)
UPDATE npc_types SET npc_faction_id=1288 WHERE id=124158; -- Uncharted  (24-Apr-16  15:39:09)
UPDATE npc_faction SET primaryfaction=42 WHERE id=628; -- Uncharted  (24-Apr-16  15:39:59)
UPDATE npc_types SET npc_faction_id=1288 WHERE id=124012; -- Uncharted  (24-Apr-16  15:40:10)
UPDATE npc_types SET npc_faction_id=1079 WHERE id=124016; -- Uncharted  (24-Apr-16  15:40:24)
UPDATE npc_types SET npc_faction_id=1288 WHERE id=124016; -- Uncharted  (24-Apr-16  15:40:35)
UPDATE npc_types SET npc_faction_id=1288 WHERE id=124003; -- Uncharted  (24-Apr-16  15:41:49)
INSERT INTO peq_admin SET login="practice", password="5f4dcc3b5aa765d61d8327deb882cf99", administrator=1; -- Uncharted  (24-Apr-16  15:42:11)
UPDATE npc_types SET npc_faction_id=1288 WHERE id=124051; -- Uncharted  (24-Apr-16  15:44:18)
UPDATE npc_types SET npc_faction_id=1288 WHERE id=124050; -- Uncharted  (24-Apr-16  15:45:17)
UPDATE npc_types SET npc_faction_id=1288 WHERE id=124084; -- Uncharted  (24-Apr-16  15:46:03)
UPDATE npc_faction SET primaryfaction=134 WHERE id=628; -- Uncharted  (24-Apr-16  15:49:28)
INSERT INTO npc_faction SET id=1289, name="ToV hatchlings", ignore_primary_assist="0"; -- Uncharted  (24-Apr-16  15:58:58)
UPDATE npc_types SET npc_faction_id=1289 WHERE id=124042; -- Uncharted  (24-Apr-16  15:58:58)
UPDATE npc_faction SET primaryfaction=42 WHERE id=1289; -- Uncharted  (24-Apr-16  15:59:11)
INSERT INTO npc_faction_entries SET npc_faction_id=1289, faction_id=42, value=-30, npc_value=1, temp=0; -- Uncharted  (24-Apr-16  15:59:21)
INSERT INTO npc_faction_entries SET npc_faction_id=1289, faction_id=134, value=-30, npc_value=1, temp=0; -- Uncharted  (24-Apr-16  15:59:37)
UPDATE npc_types SET npc_faction_id=1289 WHERE id=124043; -- Uncharted  (24-Apr-16  16:00:14)
UPDATE npc_types SET npc_faction_id=1289 WHERE id=124041; -- Uncharted  (24-Apr-16  16:00:32)
UPDATE npc_types SET npc_faction_id=1289 WHERE id=124033; -- Uncharted  (24-Apr-16  16:01:18)
UPDATE npc_types SET npc_faction_id=1289 WHERE id=124045; -- Uncharted  (24-Apr-16  16:01:33)
UPDATE npc_types SET npc_faction_id=1289 WHERE id=124060; -- Uncharted  (24-Apr-16  16:01:49)
INSERT INTO mail (`charid`,`timestamp`,`from`,`subject`,`body`,`to`,`status`) VALUES (141,UNIX_TIMESTAMP(NOW()),"Admin","Test","... sads asd","Realshadows",1); -- uncharted (26-Apr-16  11:10:45)
