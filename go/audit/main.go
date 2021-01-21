package main

import ()

func main() {
	//all inventory
	//SELECT i.charid, c.name, it.name  FROM inventory i INNER JOIN items it ON it.id = i.itemid INNER JOIN `character_data` c ON c.id = i.charid;

	//shared bank
	//SELECT sb.acctid, c.name, it.name  FROM sharedbank sb INNER JOIN items it ON it.id = sb.itemid INNER JOIN `character_data` c ON c.account_id = sb.acctid;

	//Cards
	//SELECT i.charid, c.name, it.name  FROM inventory i INNER JOIN items it ON it.id = i.itemid INNER JOIN `character_data` c ON c.id = i.charid WHERE it.NAME LIKE '%card%';
}
