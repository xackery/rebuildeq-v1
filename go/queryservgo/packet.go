package main

import ()

type ServerChannelMessage struct {
	DeliverTo string `struc:"[64]byte,little"`  //char deliverto[64];
	To        string `struc:"[64]byte,little"`  //char to[64];
	From      string `struc:"[64]byte,little"`  //char from[64];
	FromAdmin uint8  `struc:"uint8,little"`     //uint8 fromadmin;
	NoReply   bool   `struc:"bool,little"`      //bool noreply;
	ChanNum   uint16 `struc:"uint16,little"`    //uint16 chan_num;
	GuildDBId uint32 `struc:"uint32,little"`    //uint32 guilddbid;
	Language  uint16 `struc:"uint16,little"`    //uint16 language;
	Queued    uint8  `struc:"uint8,little"`     //uint8 queued; // 0 = not queued, 1 = queued, 2 = queue full, 3 = offline
	Message   string `struc:"[511]byte,little"` //char message[0];
}

type ServerPacket struct {
	Size         uint32  `struc:"uint32,little,sizeof=Buffer"` //uint32 size
	Precode      [1]byte //this is an odd padding issue
	Opcode       uint16  `struc:"uint16,little"` //uint16 opcode
	Buffer       string
	Wpos         uint32 `struc:"uint32,little"` //uint32 _wpos
	Rpos         uint32 `struc:"uint32,little"` //uint32 _rpos
	Compressed   bool   `struc:"bool,little"`   //bool   compressed
	InflatedSize uint32 `struc:"uint32,little"` //uint32 InflatedSize
	Destination  uint32 `struc:"uint32,little"` //uint32 destination*/
}

type ServerPacketOut struct {
	Size    uint32  `struc:"uint32,little,sizeof=Buffer"` //uint32 size
	Precode [1]byte //this is an odd padding issue
	Opcode  uint16  `struc:"uint16,little"` //uint16 opcode
	Buffer  []byte
}

type ServerWhoAll struct {
	Admin    int16  `struc:"int16,little"`    //int16 admin;
	FromId   int32  `struc:"uint32,little"`   //uint32 fromid;
	From     string `struc:"[64]byte,little"` //char from[64];
	Whom     string `struc:"[64]byte,little"` //char whom[64];
	Race     uint16 `struc:"uint16,little"`   //uint16 wrace; // FF FF = no race
	Class    uint16 `struc:"uint16,little"`   //uint16 wclass; // FF FF = no class
	LvlLow   uint16 `struc:"uint16,little"`   //uint16 lvllow; // FF FF = no numbers
	LvlHigh  uint16 `struc:"uint16,little"`   //uint16 lvlhigh; // FF FF = no numbers
	GmLookup uint16 `struc:"uint16,little"`   //uint16 gmlookup; // FF FF = not doing /who all gm
}

type ServerSpeech struct {
	To        string `struc:"[64]byte,little"`  //stringchar	to[64];
	From      string `struc:"[64]byte,little"`  //char	from[64];
	GuildDBId int64  `struc:"uint32,little"`    //uint32	guilddbid;
	MinStatus int64  `struc:"int16,little"`     //int16	minstatus;
	Type      int64  `struc:"uint32,little"`    //uint32	type;
	Message   string `struc:"[511]byte,little"` //char	message[0];
}

type ServerMotd struct {
	MyName string `struc:"[64]byte,little"`  //char	myname[64]; // User that set the motd
	Motd   string `struc:"[512]byte,little"` //char	motd[512]; // the new MoTD
}
