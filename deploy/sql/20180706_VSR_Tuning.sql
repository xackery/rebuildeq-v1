UPDATE npc_types SET hp = 125000 WHERE id = 102126;
UPDATE loottable_entries SET droplimit = 1, mindrop = 1 WHERE lootdrop_id = 22080;
DELETE FROM lootdrop WHERE id IN (123563, 123564);
DELETE FROM lootdrop_entries WHERE lootdrop_id IN (123563, 123564);
DELETE FROM loottable_entries WHERE lootdrop_id IN (123563, 123564);
