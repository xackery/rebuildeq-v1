/*
This package syncronizes artifact merchant with latest changes
*/

package main

import (
	"fmt"
	_ "github.com/go-sql-driver/mysql"
	"github.com/jmoiron/sqlx"
	"github.com/xackery/eqemuconfig"
	"github.com/xackery/goeq/item"
	"github.com/xackery/goeq/merchant"
	"github.com/xackery/rebuildeq/sheetgo/sheet"
	"google.golang.org/api/sheets/v4"
	"strconv"
)

var config *eqemuconfig.Config

type changeStruct struct {
	oldid     int64
	newid     int64
	ldonprice int64
}

var sheetId = "1c2s3kNZ-O-SaKKoos6dUrLblqbV53NGbIGQ42TmDmL0"
var merchSlot = 0
var npcid = 999221

var srv *sheets.Service
var db *sqlx.DB

func main() {

	fmt.Println("init")
	config, err := eqemuconfig.GetConfig()
	if err != nil {
		fmt.Println("Error getting config:", err.Error())
		return
	}

	db, err = connectDB(config)
	if err != nil {
		fmt.Println("Error connecting to DB:", err.Error())
		return
	}
	/*
		_, err = db.Exec(fmt.Sprintf("DELETE FROM merchantlist WHERE merchantid = %d", npcid))
		if err != nil {
			fmt.Println("Error deleting merchanlist", err.Error())
			return
		}
	*/
	srv, err = sheet.NewService()
	if err != nil {
		fmt.Println("error starting service", err.Error())
		return
	}

	changeList := []changeStruct{}
	changeList, err = getChangeList("Armor!D7:I100")
	if err != nil {
		fmt.Println("error getting changelist", err.Error())
		return
	}
	doChanges(changeList)

	changeList, err = getChangeList("Armor!P7:U100")
	if err != nil {
		fmt.Println("error getting changelist", err.Error())
		return
	}
	doChanges(changeList)

	changeList, err = getChangeList("Armor!AB7:AG100")
	if err != nil {
		fmt.Println("error getting changelist", err.Error())
		return
	}
	doChanges(changeList)

	changeList, err = getChangeList("Weapon!D7:I100")
	if err != nil {
		fmt.Println("error getting changelist", err.Error())
		return
	}
	doChanges(changeList)

	changeList, err = getChangeList("Weapon!P7:U100")
	if err != nil {
		fmt.Println("error getting changelist", err.Error())
		return
	}
	doChanges(changeList)

	changeList, err = getChangeList("Weapon!AB7:AG100")
	if err != nil {
		fmt.Println("error getting changelist", err.Error())
		return
	}
	doChanges(changeList)

	fmt.Println("Done")
	return
}

func getChangeList(readRange string) (changeList []changeStruct, err error) {
	resp, err := srv.Spreadsheets.Values.Get(sheetId, readRange).Do()
	if err != nil {
		err = fmt.Errorf("Unable to retrieve data from sheet. %v\n", err)
		return
	}
	var newid int64
	var oldid int64
	var price int64

	if len(resp.Values) > 0 {
		for _, row := range resp.Values {
			if len(row) < 6 {
				err = fmt.Errorf("Not enough rows matched: %d", len(row))
				return
			}
			newid, err = strconv.ParseInt(fmt.Sprintf("%s", row[0]), 10, 64)
			if err != nil {
				err = fmt.Errorf("error parsing row %s", err.Error())
				return
			}

			oldid, err = strconv.ParseInt(fmt.Sprintf("%s", row[4]), 10, 64)
			if err != nil {
				err = fmt.Errorf("error parsing row %s", err.Error())
				return
			}
			price, err = strconv.ParseInt(fmt.Sprintf("%s", row[5]), 10, 64)
			if err != nil {
				err = fmt.Errorf("error parsing row %s", err.Error())
				return
			}
			if newid == 0 || oldid == 0 || price == 0 {
				err = fmt.Errorf("Error with parsing, 0 values")
				return
			}

			changeList = append(changeList, changeStruct{
				newid:     newid,
				oldid:     oldid,
				ldonprice: price,
			})
		}
	} else {
		err = fmt.Errorf("No data returned.")
		return
	}
	return
}

func doChanges(changeList []changeStruct) {
	for _, change := range changeList {
		merchSlot++
		err := DoReplace(change)
		if err != nil {
			fmt.Println("Error on", change.oldid, change.newid, err.Error())
			return
		}
	}
}

func DoReplace(change changeStruct) (err error) {
	rows, err := db.Queryx("SELECT * FROM items WHERE id = ? LIMIT 1", change.oldid)
	if err != nil {
		fmt.Println("Error initial", err.Error())
		return
	}

	//iterate results
	for rows.Next() {

		curItem := &item.Item{}
		err = rows.StructScan(&curItem)
		if err != nil {
			fmt.Println("Error scanning", err.Error())
			return
		}
		//fmt.Println(curItem)
		curItem.Id = int(change.newid)
		curItem.Artifactflag = 1
		curItem.Loregroup = 0
		curItem.Ldonprice = int(change.ldonprice)
		curItem.Ldonsellbackrate = 25
		curItem.Nodrop = 0
		curItem.Price = 0
		curItem.Ldonsold = 1
		curItem.Ldontheme = 1

		itemList := "REPLACE INTO items (id, minstatus, Name, aagi, ac, accuracy, acha, adex, aint, artifactflag, asta, astr, attack, augrestrict, augslot1type, augslot1visible, augslot2type, augslot2visible, augslot3type, augslot3visible, augslot4type, augslot4visible, augslot5type, augslot5visible, augslot6type, augslot6visible, augtype, avoidance, awis, bagsize, bagslots, bagtype, bagwr, banedmgamt, banedmgraceamt, banedmgbody, banedmgrace, bardtype, bardvalue, book, casttime, casttime_, charmfile, charmfileid, classes, color, combateffects, extradmgskill, extradmgamt, price, cr, damage, damageshield, deity, delay, augdistiller, dotshielding, dr, clicktype, clicklevel2, elemdmgtype, elemdmgamt, endur, factionamt1, factionamt2, factionamt3, factionamt4, factionmod1, factionmod2, factionmod3, factionmod4, filename, focuseffect, fr, fvnodrop, haste, clicklevel, hp, regen, icon, idfile, itemclass, itemtype, ldonprice, ldontheme, ldonsold, light, lore, loregroup, magic, mana, manaregen, enduranceregen, material, herosforgemodel, maxcharges, mr, nodrop, norent, pendingloreflag, pr, procrate, races, `range`, reclevel, recskill, reqlevel, sellrate, shielding, size, skillmodtype, skillmodvalue, slots, clickeffect, spellshield, strikethrough, stunresist, summonedflag, tradeskills, favor, weight, UNK012, UNK013, benefitflag, UNK054, UNK059, booktype, recastdelay, recasttype, guildfavor, UNK123, UNK124, attuneable, nopet, updated, comment, UNK127, pointtype, potionbelt, potionbeltslots, stacksize, notransfer, stackable, UNK134, UNK137, proceffect, proctype, proclevel2, proclevel, UNK142, worneffect, worntype, wornlevel2, wornlevel, UNK147, focustype, focuslevel2, focuslevel, UNK152, scrolleffect, scrolltype, scrolllevel2, scrolllevel, UNK157, serialized, verified, serialization, source, UNK033, lorefile, UNK014, svcorruption, skillmodmax, UNK060, augslot1unk2, augslot2unk2, augslot3unk2, augslot4unk2, augslot5unk2, augslot6unk2, UNK120, UNK121, questitemflag, UNK132, clickunk5, clickunk6, clickunk7, procunk1, procunk2, procunk3, procunk4, procunk6, procunk7, wornunk1, wornunk2, wornunk3, wornunk4, wornunk5, wornunk6, wornunk7, focusunk1, focusunk2, focusunk3, focusunk4, focusunk5, focusunk6, focusunk7, scrollunk1, scrollunk2, scrollunk3, scrollunk4, scrollunk5, scrollunk6, scrollunk7, UNK193, purity, evoitem, evoid, evolvinglevel, evomax, clickname, procname, wornname, focusname, scrollname, dsmitigation, heroic_str, heroic_int, heroic_wis, heroic_agi, heroic_dex, heroic_sta, heroic_cha, heroic_pr, heroic_dr, heroic_fr, heroic_cr, heroic_mr, heroic_svcorrup, healamt, spelldmg, clairvoyance, backstabdmg, created, elitematerial, ldonsellbackrate, scriptfileid, expendablearrow, powersourcecapacity, bardeffect, bardeffecttype, bardlevel2, bardlevel, bardunk1, bardunk2, bardunk3, bardunk4, bardunk5, bardname, bardunk7, UNK214, UNK219, UNK220, UNK221, heirloom, UNK223, UNK224, UNK225, UNK226, UNK227, UNK228, UNK229, UNK230, UNK231, UNK232, UNK233, UNK234, placeable, UNK236, UNK237, UNK238, UNK239, UNK240, UNK241, epicitem) VALUES (:id, :minstatus, :Name, :aagi, :ac, :accuracy, :acha, :adex, :aint, :artifactflag, :asta, :astr, :attack, :augrestrict, :augslot1type, :augslot1visible, :augslot2type, :augslot2visible, :augslot3type, :augslot3visible, :augslot4type, :augslot4visible, :augslot5type, :augslot5visible, :augslot6type, :augslot6visible, :augtype, :avoidance, :awis, :bagsize, :bagslots, :bagtype, :bagwr, :banedmgamt, :banedmgraceamt, :banedmgbody, :banedmgrace, :bardtype, :bardvalue, :book, :casttime, :casttime_, :charmfile, :charmfileid, :classes, :color, :combateffects, :extradmgskill, :extradmgamt, :price, :cr, :damage, :damageshield, :deity, :delay, :augdistiller, :dotshielding, :dr, :clicktype, :clicklevel2, :elemdmgtype, :elemdmgamt, :endur, :factionamt1, :factionamt2, :factionamt3, :factionamt4, :factionmod1, :factionmod2, :factionmod3, :factionmod4, :filename, :focuseffect, :fr, :fvnodrop, :haste, :clicklevel, :hp, :regen, :icon, :idfile, :itemclass, :itemtype, :ldonprice, :ldontheme, :ldonsold, :light, :lore, :loregroup, :magic, :mana, :manaregen, :enduranceregen, :material, :herosforgemodel, :maxcharges, :mr, :nodrop, :norent, :pendingloreflag, :pr, :procrate, :races, :range, :reclevel, :recskill, :reqlevel, :sellrate, :shielding, :size, :skillmodtype, :skillmodvalue, :slots, :clickeffect, :spellshield, :strikethrough, :stunresist, :summonedflag, :tradeskills, :favor, :weight, :UNK012, :UNK013, :benefitflag, :UNK054, :UNK059, :booktype, :recastdelay, :recasttype, :guildfavor, :UNK123, :UNK124, :attuneable, :nopet, :updated, :comment, :UNK127, :pointtype, :potionbelt, :potionbeltslots, :stacksize, :notransfer, :stackable, :UNK134, :UNK137, :proceffect, :proctype, :proclevel2, :proclevel, :UNK142, :worneffect, :worntype, :wornlevel2, :wornlevel, :UNK147, :focustype, :focuslevel2, :focuslevel, :UNK152, :scrolleffect, :scrolltype, :scrolllevel2, :scrolllevel, :UNK157, :serialized, :verified, :serialization, :source, :UNK033, :lorefile, :UNK014, :svcorruption, :skillmodmax, :UNK060, :augslot1unk2, :augslot2unk2, :augslot3unk2, :augslot4unk2, :augslot5unk2, :augslot6unk2, :UNK120, :UNK121, :questitemflag, :UNK132, :clickunk5, :clickunk6, :clickunk7, :procunk1, :procunk2, :procunk3, :procunk4, :procunk6, :procunk7, :wornunk1, :wornunk2, :wornunk3, :wornunk4, :wornunk5, :wornunk6, :wornunk7, :focusunk1, :focusunk2, :focusunk3, :focusunk4, :focusunk5, :focusunk6, :focusunk7, :scrollunk1, :scrollunk2, :scrollunk3, :scrollunk4, :scrollunk5, :scrollunk6, :scrollunk7, :UNK193, :purity, :evoitem, :evoid, :evolvinglevel, :evomax, :clickname, :procname, :wornname, :focusname, :scrollname, :dsmitigation, :heroic_str, :heroic_int, :heroic_wis, :heroic_agi, :heroic_dex, :heroic_sta, :heroic_cha, :heroic_pr, :heroic_dr, :heroic_fr, :heroic_cr, :heroic_mr, :heroic_svcorrup, :healamt, :spelldmg, :clairvoyance, :backstabdmg, :created, :elitematerial, :ldonsellbackrate, :scriptfileid, :expendablearrow, :powersourcecapacity, :bardeffect, :bardeffecttype, :bardlevel2, :bardlevel, :bardunk1, :bardunk2, :bardunk3, :bardunk4, :bardunk5, :bardname, :bardunk7, :UNK214, :UNK219, :UNK220, :UNK221, :heirloom, :UNK223, :UNK224, :UNK225, :UNK226, :UNK227, :UNK228, :UNK229, :UNK230, :UNK231, :UNK232, :UNK233, :UNK234, :placeable, :UNK236, :UNK237, :UNK238, :UNK239, :UNK240, :UNK241, :epicitem)"

		_, err = db.NamedExec(itemList, curItem)
		if err != nil {
			fmt.Println(err.Error())
		}

		merchantList := "INSERT INTO merchantlist (merchantid, slot, item, faction_required, level_required, alt_currency_cost, classes_required, probability) VALUES (:merchantid, :slot, :item, :faction_required, :level_required, :alt_currency_cost, :classes_required, :probability)"
		curMerch := merchant.MerchantList{
			Merchantid:        npcid,
			Slot:              merchSlot,
			Item:              curItem.Id,
			Faction_required:  -1100,
			Alt_currency_cost: curItem.Ldonprice,
			Classes_required:  65535,
			Probability:       100,
		}

		fmt.Println("Adding", npcid, merchSlot, curItem.Id)

		_, err = db.NamedExec(merchantList, curMerch)
		if err != nil {
			fmt.Println(err.Error())
		}
		return
	}
	err = fmt.Errorf("No record found")
	return
}

func connectDB(config *eqemuconfig.Config) (db *sqlx.DB, err error) {
	//Connect to DB
	db, err = sqlx.Open("mysql", fmt.Sprintf("%s:%s@tcp(%s:%s)/%s?charset=utf8&parseTime=true", config.Database.Username, config.Database.Password, config.Database.Host, config.Database.Port, config.Database.Db))
	if err != nil {
		return
	}
	return
}
