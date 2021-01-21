package main

import (
	//"encoding/binary"
	"fmt"
	"github.com/xackery/eqemuconfig"
	"net"
	//"strconv"
	"bytes"
	"github.com/lunixbochs/struc"
	"io"
	"strings"
	"time"
)

var config *eqemuconfig.Config

/*
Unknown Packet Size: %!u(uint32=31), Opcode: 0x4005, Buffer:        Xackery      //when someone joined, maybe
*/

func main() {
	var err error
	//Load config in same directory
	config, err = eqemuconfig.GetConfig()
	if err != nil {
		fmt.Println("Error loading config:", err.Error())
		return
	}
	var conn net.Conn
	for {
		connectLoop(conn)
	}
}

func connectLoop(conn net.Conn) {
	var err error
	fmt.Printf("Connecting to %s:%s... ", config.World.Tcp.Ip, config.World.Tcp.Port)
	conn, err = net.Dial("tcp", config.World.Tcp.Ip+":"+config.World.Tcp.Port)
	if err != nil {
		fmt.Println("Error connecting: ", err.Error())
		fmt.Println("Trying again in 10 seconds...")
		time.Sleep(10 * time.Second)
		return
	}

	_, err = conn.Write(makeModePacket())
	if err != nil {
		fmt.Println("Error writing mode packet:", err.Error())
		return
	}
	_, err = conn.Write(makeAuthPacket())
	if err != nil {
		fmt.Println("Error writing auth packet:", err.Error())
	}
	fmt.Println("Success!")
	go connectionKeepAlive(conn)
	//go testMessage(conn)
	go whoAll(conn)
	go readInbound(conn)
	select {}
}

func whoAll(conn net.Conn) {
	///var err error
	time.Sleep(5 * time.Second)

	//initialize whoall
	//packet := []byte{0x0f, 0x00, 0x00, 0x00, 0x00, 0x28, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00}
	//conn.Write(packet)
	//send a xackery sourced whoall
	packet := []byte{0x97, 0x00, 0x00, 0x00, 0x00, 0x0b, 0x00, 0x2c, 0x01, 0x08, 0x01, 0x00, 0x00, 0x58, 0x61, 0x63,
		0x6b, 0x65, 0x72, 0x79, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff,
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff}
	conn.Write(packet)
	fmt.Println("Sent who packet~")
}

//Test sending a message into world. Heavily WIP. Crashes world currnetly.
func testMessage(conn net.Conn) {
	var err error
	time.Sleep(5 * time.Second)

	payload := &ServerChannelMessage{
		From:    "Xackery",
		ChanNum: 260,
		Message: "Hello!",
	}

	var buf *bytes.Buffer
	buf = bytes.NewBuffer(make([]byte, 1024))
	packet := make([]byte, 1024)
	err = struc.Pack(buf, payload)
	if err != nil {
		fmt.Println("Error packing payload", err.Error())
		return
	}

	_, err = io.ReadFull(buf, packet)
	if err != nil {
		fmt.Println("Error reading buffer", err.Error())
		return
	}

	msg := &ServerPacketOut{
		Opcode: ServerOP_ChannelMessage,
		Buffer: packet,
	}

	err = struc.Pack(buf, msg)
	if err != nil {
		fmt.Println("Error packing msg", err.Error())
		return
	}

	_, err = io.ReadFull(buf, packet)
	if err != nil {
		fmt.Println("Error reading buffer", err.Error())
		return
	}

	n, err := conn.Write(packet)
	if err != nil {
		fmt.Println("Error writing packet", err.Error())
	}
	fmt.Println("Sent packet!", n)
	//fmt.Printf("%#x", packet)
}

//Poll for inbound messages.
func readInbound(conn net.Conn) {
	var err error

	packet := make([]byte, 1024)
	conn.Read(packet) //When this starts there's always a single echo back that can be discarded..
	for {

		packet := make([]byte, 1024)
		_, err = conn.Read(packet)
		if err != nil {
			if err == io.EOF {
				//fmt.Println("EOF")
				continue
			}
			fmt.Println("Error reading packet:", err.Error())
			return
		}
		fmt.Println(packet)

		var buf *bytes.Buffer
		buf = bytes.NewBuffer(packet)
		fmt.Println(packet)
		sp := &ServerPacket{}
		err = struc.Unpack(buf, sp)
		if err != nil {
			fmt.Printf("Error unpacking server packet, Opcode: %#x: %s\n", sp.Opcode, err.Error())
			//fmt.Printf("Size: %u, Opcode: %#x, Buffer: %s\n\n", sp.Size, sp.Opcode, sp.Buffer)
			//fmt.Printf("%#X - %s\n", packet, string(packet))
			continue
		}
		switch sp.Opcode {
		case 0x00:
			//fmt.Println("Ignoring 0 pad (this is an echo of PING is my theory, 07000000000000")
		case ServerOP_Speech:
			fmt.Println("Speech", sp.Buffer)
			speech := &ServerSpeech{}
			buf = bytes.NewBufferString(sp.Buffer)
			err = struc.Unpack(buf, speech)
			speech.From = strings.Trim(speech.From, "\x00")
			speech.To = strings.Trim(speech.To, "\x00")
			speech.Message = strings.Trim(speech.Message, "\x00")
			fmt.Printf("Status: %i, From: %s, To: %s, Message: %s, Type: %i, Misc: %v\n", speech.MinStatus, speech.From, speech.To, speech.Message, speech.Type, speech)
		default:
			fmt.Printf("Unknown Packet Found. Size: %u, Opcode: %#x, Buffer: %s\n\n", sp.Size, sp.Opcode, sp.Buffer)
		}
	}
}

//Keep connection alive.
func connectionKeepAlive(conn net.Conn) {
	packet := []byte{0x07, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0}
	for {
		time.Sleep(20 * time.Second)
		conn.Write(packet)
	}
}

func makeModePacket() (modePacket []byte) {
	modePacket = make([]byte, 18)
	modePacket[0] = 0
	out := []byte("**PACKETMODEQS**")
	for i, b := range out {
		modePacket[i+1] = b
	}
	modePacket[17] = 0x0d
	return
}

func makeAuthPacket() (authPacket []byte) {
	authPacket = make([]byte, 23)
	authPacket[0] = 0x17
	authPacket[1] = 0x0
	authPacket[2] = 0x0
	authPacket[3] = 0x0
	authPacket[4] = 0x0  //this is ServerOP_ZAuth
	authPacket[5] = 0x25 //this is ServerOP_ZAuth
	authPacket[6] = 0x0
	authPacket[7] = 0x6c
	authPacket[8] = 0xe6
	authPacket[9] = 0x0a
	authPacket[10] = 0xcd
	authPacket[11] = 0xde
	authPacket[12] = 0x9f
	authPacket[13] = 0x9d
	authPacket[14] = 0x47
	authPacket[15] = 0x3c
	authPacket[16] = 0x4c
	authPacket[17] = 0x06
	authPacket[18] = 0x68
	authPacket[19] = 0xe5
	authPacket[20] = 0x05
	authPacket[21] = 0x54
	authPacket[22] = 0x09
	return
}
