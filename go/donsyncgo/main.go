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
)

var config *eqemuconfig.Config

type changeStruct struct {
	oldid        int
	newid        int
	ldonprice    int
	ldonsellback int
}

var merchSlot = 0
var npcid = 999221

func main() {
	fmt.Println("init")
	config, err := eqemuconfig.GetConfig()
	if err != nil {
		fmt.Println("Error getting config:", err.Error())
		return
	}
	db, err := connectDB(config)
	if err != nil {
		fmt.Println("Error connecting to DB:", err.Error())
		return
	}

	_, err = db.Exec(fmt.Sprintf("DELETE FROM merchantlist WHERE merchantid = %d", npcid))
	if err != nil {
		fmt.Println("Error deleting merchanlist", err.Error())
		return
	}

	changeList := []changeStruct{
		changeStruct{newid: 100200, oldid: 9350, ldonprice: 87},
		changeStruct{newid: 100201, oldid: 7314, ldonprice: 110},
		changeStruct{newid: 100202, oldid: 11912, ldonprice: 87},
		changeStruct{newid: 100203, oldid: 10325, ldonprice: 87},
		changeStruct{newid: 100204, oldid: 5424, ldonprice: 110},
		changeStruct{newid: 100205, oldid: 6692, ldonprice: 110},
		changeStruct{newid: 100206, oldid: 9027, ldonprice: 133},
		changeStruct{newid: 100207, oldid: 7323, ldonprice: 110},
		changeStruct{newid: 100208, oldid: 5642, ldonprice: 145},
		changeStruct{newid: 100209, oldid: 6305, ldonprice: 179},
		changeStruct{newid: 100210, oldid: 13942, ldonprice: 168},
		changeStruct{newid: 100211, oldid: 1676, ldonprice: 87},
		changeStruct{newid: 100212, oldid: 6932, ldonprice: 30},
		changeStruct{newid: 100213, oldid: 57018, ldonprice: 30},
		changeStruct{newid: 100214, oldid: 11913, ldonprice: 30},
		changeStruct{newid: 100215, oldid: 5011, ldonprice: 87},
		changeStruct{newid: 100216, oldid: 52036, ldonprice: 87},
		changeStruct{newid: 100217, oldid: 52026, ldonprice: 87},
		changeStruct{newid: 100218, oldid: 8312, ldonprice: 87},
		changeStruct{newid: 100220, oldid: 5665, ldonprice: 168},
		changeStruct{newid: 100300, oldid: 5622, ldonprice: 224},
		changeStruct{newid: 100301, oldid: 3616, ldonprice: 397},
		changeStruct{newid: 100302, oldid: 6625, ldonprice: 339},
		changeStruct{newid: 100303, oldid: 7254, ldonprice: 454},
		changeStruct{newid: 100304, oldid: 5661, ldonprice: 512},
		changeStruct{newid: 100305, oldid: 7318, ldonprice: 339},
		changeStruct{newid: 100306, oldid: 7312, ldonprice: 569},
		changeStruct{newid: 100307, oldid: 9028, ldonprice: 454},
		changeStruct{newid: 100308, oldid: 7210, ldonprice: 512},
		changeStruct{newid: 100309, oldid: 9206, ldonprice: 339},
		changeStruct{newid: 100310, oldid: 5163, ldonprice: 224},
		changeStruct{newid: 100311, oldid: 7050, ldonprice: 167},
		changeStruct{newid: 100312, oldid: 6675, ldonprice: 339},
		changeStruct{newid: 100313, oldid: 11552, ldonprice: 339},
		changeStruct{newid: 100314, oldid: 7406, ldonprice: 454},
		changeStruct{newid: 100315, oldid: 6681, ldonprice: 339},
		changeStruct{newid: 100316, oldid: 5057, ldonprice: 454},
		changeStruct{newid: 100317, oldid: 7238, ldonprice: 454},
		changeStruct{newid: 100318, oldid: 10581, ldonprice: 339},
		changeStruct{newid: 100319, oldid: 5631, ldonprice: 454},
		changeStruct{newid: 100320, oldid: 11630, ldonprice: 454},
		changeStruct{newid: 100321, oldid: 6359, ldonprice: 397},
		changeStruct{newid: 100322, oldid: 10219, ldonprice: 339},
		changeStruct{newid: 100400, oldid: 5155, ldonprice: 2162},
		changeStruct{newid: 100401, oldid: 9311, ldonprice: 782},
		changeStruct{newid: 100402, oldid: 5665, ldonprice: 1242},
		changeStruct{newid: 100403, oldid: 11645, ldonprice: 2392},
		changeStruct{newid: 100404, oldid: 7211, ldonprice: 1932},
		changeStruct{newid: 100405, oldid: 5156, ldonprice: 2162},
		changeStruct{newid: 100406, oldid: 11626, ldonprice: 1702},
		changeStruct{newid: 100407, oldid: 5649, ldonprice: 1472},
		changeStruct{newid: 100408, oldid: 7222, ldonprice: 1702},
		changeStruct{newid: 100409, oldid: 9315, ldonprice: 1242},
		changeStruct{newid: 100410, oldid: 10859, ldonprice: 2392},
		changeStruct{newid: 100411, oldid: 5667, ldonprice: 2162},
		changeStruct{newid: 100412, oldid: 7237, ldonprice: 1242},
		changeStruct{newid: 100413, oldid: 14722, ldonprice: 1702},
		changeStruct{newid: 100414, oldid: 11607, ldonprice: 1242},
		changeStruct{newid: 100415, oldid: 5401, ldonprice: 1242},
		changeStruct{newid: 100416, oldid: 5152, ldonprice: 1702},
		changeStruct{newid: 100417, oldid: 9205, ldonprice: 1242},
		changeStruct{newid: 100418, oldid: 11644, ldonprice: 1702},
		changeStruct{newid: 100419, oldid: 11585, ldonprice: 1242},
		changeStruct{newid: 100420, oldid: 6685, ldonprice: 1932},
		changeStruct{newid: 100421, oldid: 6679, ldonprice: 1932},
		changeStruct{newid: 100422, oldid: 6404, ldonprice: 1242},
		changeStruct{newid: 100423, oldid: 6610, ldonprice: 1472},
		changeStruct{newid: 100424, oldid: 5158, ldonprice: 1932},
		changeStruct{newid: 100425, oldid: 14759, ldonprice: 782},
		changeStruct{newid: 100600, oldid: 4504, ldonprice: 58},
		changeStruct{newid: 100601, oldid: 10366, ldonprice: 73},
		changeStruct{newid: 100602, oldid: 3212, ldonprice: 93},
		changeStruct{newid: 100603, oldid: 3040, ldonprice: 87},
		changeStruct{newid: 100604, oldid: 1410, ldonprice: 73},
		changeStruct{newid: 100605, oldid: 4313, ldonprice: 87},
		changeStruct{newid: 100606, oldid: 11978, ldonprice: 93},
		changeStruct{newid: 100607, oldid: 11911, ldonprice: 87},
		changeStruct{newid: 100608, oldid: 11584, ldonprice: 93},
		changeStruct{newid: 100609, oldid: 3312, ldonprice: 73},
		changeStruct{newid: 100610, oldid: 10587, ldonprice: 101},
		changeStruct{newid: 100611, oldid: 2341, ldonprice: 99},
		changeStruct{newid: 100612, oldid: 2373, ldonprice: 84},
		changeStruct{newid: 100613, oldid: 1617, ldonprice: 73},
		changeStruct{newid: 100614, oldid: 2332, ldonprice: 73},
		changeStruct{newid: 100615, oldid: 2345, ldonprice: 64},
		changeStruct{newid: 100616, oldid: 10314, ldonprice: 73},
		changeStruct{newid: 100617, oldid: 10338, ldonprice: 87},
		changeStruct{newid: 100618, oldid: 11902, ldonprice: 107},
		changeStruct{newid: 100619, oldid: 10148, ldonprice: 101},
		changeStruct{newid: 100620, oldid: 2731, ldonprice: 93},
		changeStruct{newid: 100621, oldid: 2406, ldonprice: 99},
		changeStruct{newid: 100622, oldid: 1259, ldonprice: 99},
		changeStruct{newid: 100623, oldid: 3150, ldonprice: 107},
		changeStruct{newid: 100624, oldid: 3151, ldonprice: 107},
		changeStruct{newid: 100625, oldid: 3152, ldonprice: 107},
		changeStruct{newid: 100626, oldid: 3153, ldonprice: 107},
		changeStruct{newid: 100627, oldid: 3154, ldonprice: 107},
		changeStruct{newid: 100628, oldid: 3155, ldonprice: 107},
		changeStruct{newid: 100629, oldid: 3156, ldonprice: 107},
		changeStruct{newid: 100630, oldid: 3181, ldonprice: 107},
		changeStruct{newid: 100631, oldid: 3182, ldonprice: 107},
		changeStruct{newid: 100632, oldid: 3183, ldonprice: 107},
		changeStruct{newid: 100633, oldid: 3184, ldonprice: 107},
		changeStruct{newid: 100634, oldid: 3185, ldonprice: 107},
		changeStruct{newid: 100635, oldid: 3186, ldonprice: 107},
		changeStruct{newid: 100636, oldid: 3187, ldonprice: 107},
		changeStruct{newid: 100637, oldid: 3188, ldonprice: 107},
		changeStruct{newid: 100638, oldid: 3189, ldonprice: 107},
		changeStruct{newid: 100639, oldid: 3190, ldonprice: 107},
		changeStruct{newid: 100640, oldid: 3191, ldonprice: 107},
		changeStruct{newid: 100641, oldid: 3192, ldonprice: 107},
		changeStruct{newid: 100642, oldid: 4153, ldonprice: 107},
		changeStruct{newid: 100643, oldid: 4154, ldonprice: 107},
		changeStruct{newid: 100644, oldid: 4155, ldonprice: 107},
		changeStruct{newid: 100645, oldid: 4156, ldonprice: 107},
		changeStruct{newid: 100646, oldid: 4157, ldonprice: 107},
		changeStruct{newid: 100647, oldid: 4158, ldonprice: 107},
		changeStruct{newid: 100648, oldid: 4159, ldonprice: 107},
		changeStruct{newid: 100649, oldid: 4173, ldonprice: 107},
		changeStruct{newid: 100650, oldid: 4174, ldonprice: 107},
		changeStruct{newid: 100651, oldid: 4175, ldonprice: 107},
		changeStruct{newid: 100652, oldid: 4176, ldonprice: 107},
		changeStruct{newid: 100653, oldid: 4177, ldonprice: 107},
		changeStruct{newid: 100654, oldid: 4178, ldonprice: 107},
		changeStruct{newid: 100655, oldid: 4179, ldonprice: 107},
		changeStruct{newid: 100656, oldid: 4180, ldonprice: 107},
		changeStruct{newid: 100657, oldid: 4181, ldonprice: 107},
		changeStruct{newid: 100658, oldid: 4182, ldonprice: 107},
		changeStruct{newid: 100659, oldid: 4183, ldonprice: 107},
		changeStruct{newid: 100660, oldid: 4184, ldonprice: 107},
		changeStruct{newid: 100661, oldid: 4185, ldonprice: 107},
		changeStruct{newid: 100662, oldid: 4186, ldonprice: 107},
		changeStruct{newid: 100663, oldid: 4187, ldonprice: 107},
		changeStruct{newid: 100664, oldid: 4188, ldonprice: 107},
		changeStruct{newid: 100665, oldid: 4331, ldonprice: 107},
		changeStruct{newid: 100666, oldid: 4334, ldonprice: 107},
		changeStruct{newid: 100667, oldid: 4335, ldonprice: 107},
		changeStruct{newid: 100668, oldid: 4337, ldonprice: 107},
		changeStruct{newid: 100800, oldid: 14714, ldonprice: 470},
		changeStruct{newid: 100801, oldid: 14751, ldonprice: 388},
		changeStruct{newid: 100802, oldid: 10151, ldonprice: 421},
		changeStruct{newid: 100803, oldid: 11917, ldonprice: 388},
		changeStruct{newid: 100804, oldid: 10854, ldonprice: 470},
		changeStruct{newid: 100805, oldid: 3307, ldonprice: 421},
		changeStruct{newid: 100806, oldid: 4302, ldonprice: 470},
		changeStruct{newid: 100807, oldid: 4504, ldonprice: 453},
		changeStruct{newid: 100808, oldid: 14751, ldonprice: 486},
		changeStruct{newid: 100809, oldid: 2347, ldonprice: 486},
		changeStruct{newid: 100810, oldid: 11538, ldonprice: 453},
		changeStruct{newid: 100811, oldid: 2461, ldonprice: 453},
		changeStruct{newid: 100812, oldid: 11624, ldonprice: 503},
		changeStruct{newid: 100813, oldid: 10593, ldonprice: 519},
		changeStruct{newid: 100814, oldid: 1412, ldonprice: 503},
		changeStruct{newid: 100815, oldid: 1904, ldonprice: 486},
		changeStruct{newid: 100816, oldid: 1358, ldonprice: 453},
		changeStruct{newid: 100817, oldid: 2458, ldonprice: 437},
		changeStruct{newid: 100818, oldid: 10361, ldonprice: 453},
		changeStruct{newid: 100819, oldid: 2741, ldonprice: 453},
		changeStruct{newid: 100820, oldid: 17404, ldonprice: 486},
		changeStruct{newid: 100821, oldid: 6680, ldonprice: 503},
		changeStruct{newid: 100822, oldid: 2738, ldonprice: 486},
		changeStruct{newid: 100823, oldid: 10150, ldonprice: 519},
		changeStruct{newid: 100824, oldid: 1194, ldonprice: 453},
		changeStruct{newid: 100825, oldid: 1408, ldonprice: 486},
		changeStruct{newid: 100826, oldid: 10216, ldonprice: 503},
		changeStruct{newid: 100827, oldid: 10143, ldonprice: 519},
		changeStruct{newid: 100828, oldid: 1354, ldonprice: 486},
		changeStruct{newid: 100829, oldid: 6329, ldonprice: 470},
		changeStruct{newid: 100830, oldid: 4169, ldonprice: 453},
		changeStruct{newid: 100831, oldid: 4166, ldonprice: 503},
		changeStruct{newid: 100832, oldid: 4170, ldonprice: 470},
		changeStruct{newid: 100833, oldid: 4161, ldonprice: 486},
		changeStruct{newid: 100834, oldid: 14045, ldonprice: 453},
		changeStruct{newid: 100835, oldid: 4515, ldonprice: 503},
		changeStruct{newid: 100836, oldid: 4517, ldonprice: 503},
		changeStruct{newid: 100837, oldid: 4518, ldonprice: 503},
		changeStruct{newid: 100838, oldid: 4519, ldonprice: 503},
		changeStruct{newid: 100839, oldid: 4521, ldonprice: 503},
		changeStruct{newid: 100840, oldid: 4522, ldonprice: 503},
		changeStruct{newid: 100841, oldid: 4524, ldonprice: 503},
		changeStruct{newid: 100842, oldid: 4525, ldonprice: 503},
		changeStruct{newid: 100843, oldid: 4526, ldonprice: 503},
		changeStruct{newid: 100844, oldid: 4528, ldonprice: 503},
		changeStruct{newid: 100845, oldid: 4529, ldonprice: 503},
		changeStruct{newid: 100846, oldid: 4531, ldonprice: 503},
		changeStruct{newid: 100847, oldid: 4532, ldonprice: 503},
		changeStruct{newid: 100848, oldid: 4533, ldonprice: 503},
		changeStruct{newid: 100849, oldid: 4535, ldonprice: 503},
		changeStruct{newid: 100850, oldid: 4536, ldonprice: 503},
		changeStruct{newid: 100851, oldid: 4538, ldonprice: 503},
		changeStruct{newid: 100852, oldid: 4539, ldonprice: 503},
		changeStruct{newid: 100853, oldid: 4540, ldonprice: 503},
		changeStruct{newid: 100854, oldid: 4542, ldonprice: 503},
		changeStruct{newid: 100855, oldid: 4543, ldonprice: 503},
		changeStruct{newid: 100856, oldid: 4545, ldonprice: 503},
		changeStruct{newid: 100857, oldid: 4546, ldonprice: 503},
		changeStruct{newid: 100858, oldid: 4547, ldonprice: 503},
		changeStruct{newid: 100859, oldid: 4549, ldonprice: 503},
		changeStruct{newid: 100860, oldid: 4550, ldonprice: 503},
		changeStruct{newid: 100861, oldid: 4552, ldonprice: 503},
		changeStruct{newid: 100862, oldid: 4553, ldonprice: 503},
		changeStruct{newid: 100863, oldid: 4554, ldonprice: 503},
		changeStruct{newid: 100864, oldid: 4556, ldonprice: 503},
		changeStruct{newid: 100865, oldid: 4557, ldonprice: 503},
		changeStruct{newid: 100866, oldid: 4559, ldonprice: 503},
		changeStruct{newid: 100867, oldid: 4560, ldonprice: 503},
		changeStruct{newid: 100868, oldid: 4561, ldonprice: 503},
		changeStruct{newid: 100869, oldid: 4563, ldonprice: 503},
		changeStruct{newid: 100870, oldid: 4564, ldonprice: 503},
		changeStruct{newid: 100871, oldid: 4566, ldonprice: 503},
		changeStruct{newid: 100872, oldid: 4567, ldonprice: 503},
		changeStruct{newid: 100873, oldid: 4568, ldonprice: 503},
		changeStruct{newid: 100874, oldid: 4570, ldonprice: 503},
		changeStruct{newid: 100875, oldid: 4571, ldonprice: 503},
		changeStruct{newid: 100876, oldid: 4573, ldonprice: 503},
		changeStruct{newid: 100877, oldid: 4574, ldonprice: 503},
		changeStruct{newid: 100878, oldid: 4575, ldonprice: 503},
		changeStruct{newid: 100879, oldid: 4577, ldonprice: 503},
		changeStruct{newid: 100880, oldid: 4941, ldonprice: 503},
		changeStruct{newid: 100881, oldid: 4942, ldonprice: 503},
		changeStruct{newid: 100882, oldid: 4943, ldonprice: 503},
		changeStruct{newid: 100883, oldid: 4945, ldonprice: 503},
		changeStruct{newid: 100884, oldid: 4947, ldonprice: 503},
		changeStruct{newid: 100885, oldid: 4948, ldonprice: 503},
		changeStruct{newid: 101000, oldid: 14709, ldonprice: 2657},
		changeStruct{newid: 101001, oldid: 14730, ldonprice: 4727},
		changeStruct{newid: 101002, oldid: 17403, ldonprice: 3347},
		changeStruct{newid: 101003, oldid: 1622, ldonprice: 2657},
		changeStruct{newid: 101004, oldid: 1620, ldonprice: 3002},
		changeStruct{newid: 101005, oldid: 11646, ldonprice: 4727},
		changeStruct{newid: 101006, oldid: 11621, ldonprice: 4727},
		changeStruct{newid: 101007, oldid: 14746, ldonprice: 4382},
		changeStruct{newid: 101008, oldid: 11641, ldonprice: 5072},
		changeStruct{newid: 101009, oldid: 1262, ldonprice: 3692},
		changeStruct{newid: 101010, oldid: 10313, ldonprice: 3347},
		changeStruct{newid: 101011, oldid: 1608, ldonprice: 4037},
		changeStruct{newid: 101012, oldid: 11601, ldonprice: 3347},
		changeStruct{newid: 101013, oldid: 4407, ldonprice: 3347},
		changeStruct{newid: 101014, oldid: 4133, ldonprice: 4037},
		changeStruct{newid: 101015, oldid: 2300, ldonprice: 4382},
		changeStruct{newid: 101016, oldid: 17353, ldonprice: 3347},
		changeStruct{newid: 101017, oldid: 1357, ldonprice: 4037},
		changeStruct{newid: 101018, oldid: 10580, ldonprice: 3347},
		changeStruct{newid: 101019, oldid: 4171, ldonprice: 4037},
		changeStruct{newid: 101020, oldid: 4164, ldonprice: 4037},
		changeStruct{newid: 101021, oldid: 4520, ldonprice: 4382},
		changeStruct{newid: 101022, oldid: 4516, ldonprice: 4382},
		changeStruct{newid: 101023, oldid: 4523, ldonprice: 4382},
		changeStruct{newid: 101024, oldid: 4527, ldonprice: 4382},
		changeStruct{newid: 101025, oldid: 4530, ldonprice: 4382},
		changeStruct{newid: 101026, oldid: 4534, ldonprice: 4382},
		changeStruct{newid: 101027, oldid: 4537, ldonprice: 4382},
		changeStruct{newid: 101028, oldid: 4541, ldonprice: 4382},
		changeStruct{newid: 101029, oldid: 4544, ldonprice: 4382},
		changeStruct{newid: 101030, oldid: 4548, ldonprice: 4382},
		changeStruct{newid: 101031, oldid: 4551, ldonprice: 4382},
		changeStruct{newid: 101032, oldid: 4555, ldonprice: 4382},
		changeStruct{newid: 101033, oldid: 4558, ldonprice: 4382},
		changeStruct{newid: 101034, oldid: 4562, ldonprice: 4382},
		changeStruct{newid: 101035, oldid: 4565, ldonprice: 4382},
		changeStruct{newid: 101036, oldid: 4569, ldonprice: 4382},
		changeStruct{newid: 101037, oldid: 4572, ldonprice: 4382},
		changeStruct{newid: 101038, oldid: 4576, ldonprice: 4382},
		changeStruct{newid: 101039, oldid: 4946, ldonprice: 4382},
		changeStruct{newid: 101040, oldid: 4944, ldonprice: 4382},
	}

	for _, change := range changeList {
		db, err = connectDB(config)
		if err != nil {
			fmt.Println("Error connecting to DB:", err.Error())
			return
		}
		merchSlot++
		err = DoReplace(db, change)
		if err != nil {
			fmt.Println("Error on", change.oldid, change.newid, err.Error())
			return
		}
		db.Close()
	}

	fmt.Println("Done")
	return
}

func DoReplace(db *sqlx.DB, change changeStruct) (err error) {
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
		curItem.Id = change.newid
		curItem.Artifactflag = 1
		curItem.Loregroup = 0
		curItem.Ldonprice = change.ldonprice
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
