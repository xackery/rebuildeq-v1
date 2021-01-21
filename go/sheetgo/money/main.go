/*
Takes snapshots of player's money and puts it on google drive.
*/

package main

import (
	"fmt"
	_ "github.com/go-sql-driver/mysql"
	"github.com/jmoiron/sqlx"
	"github.com/xackery/eqemuconfig"
	"github.com/xackery/goeq/character"
	"github.com/xackery/rebuildeq/sheetgo/sheet"
	"google.golang.org/api/sheets/v4"
	"time"
)

var config *eqemuconfig.Config

var sheetId = "1NTM8-CmLhH344Omb7UyUWnjy_9a6IAN5_lLQ9jnDngo"

var srv *sheets.Service
var db *sqlx.DB

func main() {
	//get config
	config, err := eqemuconfig.GetConfig()
	if err != nil {
		fmt.Println("Error getting config:", err.Error())
		return
	}

	//connect to db
	db, err = connectDB(config)
	if err != nil {
		fmt.Println("Error connecting to DB:", err.Error())
		return
	}

	//prepare google sheet service
	srv, err = sheet.NewService()
	if err != nil {
		fmt.Println("error starting service", err.Error())
		return
	}

	//get the first empty row in A2 column
	resp, err := srv.Spreadsheets.Values.Get(sheetId, "Money!A2:A366").Do()
	if err != nil {
		fmt.Println("Unable to get data:", err.Error())
		return
	}
	if len(resp.Values) < 1 {
		fmt.Println("No values returned")
		return
	}
	newIndex := 2
	for _, row := range resp.Values {
		newIndex++
		if len(fmt.Sprintf("%s", row[0])) < 1 {
			break
		}
	}

	//prep pages
	grandTotalMoney := 0
	valueRange := &sheets.ValueRange{
		MajorDimension: "ROWS",
		Values:         [][]interface{}{[]interface{}{time.Now().Format("01-02-2006"), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}},
		//Range:          "B4",
	}

	//get ranges of levels
	row := 2
	for i := 5; i < 61; i = i + 5 {
		newMoney := getMoneyTotal((i - 4), i)
		valueRange.Values[0][row] = newMoney

		fmt.Println("Levels", (i - 4), "to", i, "had", newMoney)
		grandTotalMoney += newMoney
		row++
	}
	//upgrade grand total line
	valueRange.Values[0][1] = grandTotalMoney

	//update sheet
	_, err = srv.Spreadsheets.Values.Update(sheetId, fmt.Sprintf("A%d", newIndex), valueRange).ValueInputOption("USER_ENTERED").Do()
	if err != nil {
		fmt.Println("Error updating:", err.Error())
		return
	}

}

func getMoneyTotal(minLevel int, maxLevel int) (moneyTotal int) {
	rows, err := db.Queryx("SELECT cc.* FROM character_currency cc INNER JOIN character_data cd ON cd.id = cc.id WHERE cd.level >= ? AND cd.level <= ? ", minLevel, maxLevel)
	if err != nil {
		fmt.Println("Error querying currency", err.Error())
		return
	}

	//iterate results
	for rows.Next() {
		curMoney := &character.CharacterCurrency{}
		err = rows.StructScan(&curMoney)
		if err != nil {
			fmt.Println("Error scanning", err.Error())
			return
		}
		moneyTotal += curMoney.Platinum * 1000
		moneyTotal += curMoney.Gold * 100
		moneyTotal += curMoney.Silver * 10
		moneyTotal += curMoney.Copper
		moneyTotal += curMoney.Platinum_bank * 1000
		moneyTotal += curMoney.Gold_bank * 100
		moneyTotal += curMoney.Silver_bank * 10
		moneyTotal += curMoney.Copper_bank
	}
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
