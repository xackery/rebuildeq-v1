#adjust the level that exp loss and item loss starts at to match the website descriptions
UPDATE rule_values SET rule_value="11" WHERE rule_name="Character:DeathExpLossLevel" AND ruleset_id="1";
UPDATE rule_values SET rule_value="41" WHERE rule_name="Character:DeathItemLossLevel" AND ruleset_id="1";
