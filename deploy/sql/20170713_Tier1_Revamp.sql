##### Disable spawns in Plane of Sky:

UPDATE spawn2 SET enabled = 0 WHERE id = 241757; # The Avatar of Sky
UPDATE spawn2 SET enabled = 0 WHERE id = 241827; # Noble of Air
UPDATE spawn2 SET enabled = 0 WHERE id = 241828; # Spiroc of Air
UPDATE spawn2 SET enabled = 0 WHERE id = 241826; # Harpie of Air
UPDATE spawn2 SET enabled = 0 WHERE id = 2681; # The Storm Mistress
UPDATE spawn2 SET enabled = 0 WHERE id = 58532; # Eternal Spirit
UPDATE spawn2 SET enabled = 0 WHERE id = 2633; # The Gale Caller
 
##### Disable spawns in Plane of Hate:

UPDATE spawn2 SET enabled = 0 WHERE id = 21941; # The Deathrot Knight  

##### Disable spawns in Plane of Fear:

UPDATE spawn2 SET enabled = 0 WHERE id = 13833; # The Tempest Reaver

##### Replace Tier Boss spawns:

UPDATE spawnentry SET npcID = 32040 WHERE npcID = 999249; # Lord Nagafen
UPDATE spawnentry SET npcID = 73057 WHERE npcID = 999250; # Lady Vox
# Maestro of Rancor
UPDATE npc_types SET name= 'Innoruuk' WHERE id = 76007; # Innoruuk
UPDATE spawn2 SET enabled = 0 WHERE id = 241825 ; # Dragon of Fear
UPDATE npc_types SET name= 'Cazic_Thule' WHERE id = 72003; # Cazic Thule
UPDATE spawnentry SET npcID = 39138 WHERE npcID = 2000051; # Master Yael
UPDATE spawnentry SET npcID = 71075 WHERE npcID = 2000058; # Keeper of Souls

##### Reset player tier progress:

DELETE FROM character_tasks WHERE taskid IN (501, 502, 503, 504, 505, 506, 507, 508, 509, 510);
DELETE FROM character_activities WHERE taskid IN (501, 502, 503, 504, 505, 506, 507, 508, 509, 510);
DELETE FROM completed_tasks WHERE taskid IN (501, 502, 503, 504, 505, 506, 507, 508, 509, 510);

##### Update loot tables:

DELETE FROM loottable_entries WHERE lootdrop_id = 676;
DELETE FROM lootdrop WHERE id = 676;
DELETE FROM lootdrop_entries WHERE lootdrop_id = 676;

DELETE FROM lootdrop_entries WHERE item_id IN (SELECT id FROM items WHERE name LIKE '%(out of era)%');
DELETE FROM lootdrop WHERE id NOT IN (SELECT DISTINCT(lootdrop_id) FROM lootdrop_entries);


##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### ##### 

#### Tune Cazic Thule attack speed

UPDATE `rebuildeq`.`npc_types` SET `attack_speed`='-18', `attack_delay`='20' WHERE `id`='72003';
