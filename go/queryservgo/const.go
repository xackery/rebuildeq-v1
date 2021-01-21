package main

import ()

const (
	ServerOP_KeepAlive      = 0x0001 // packet to test if port is still open
	ServerOP_ChannelMessage = 0x0002 // broadcast/guildsay
	ServerOP_SetZone        = 0x0003 // client -> server zoneinfo
	ServerOP_ShutdownAll    = 0x0004 // exit(0);
	ServerOP_ZoneShutdown   = 0x0005 // unload all data, goto sleep mode
	ServerOP_ZoneBootup     = 0x0006 // come out of sleep mode and load zone specified
	ServerOP_ZoneStatus     = 0x0007 // Shows status of all zones
	ServerOP_SetConnectInfo = 0x0008 // Tells server address and port #
	ServerOP_EmoteMessage   = 0x0009 // Worldfarts
	ServerOP_ClientList     = 0x000A // Update worldserver's client list, for #whos
	ServerOP_Who            = 0x000B // #who
	ServerOP_ZonePlayer     = 0x000C // #zone, or #summon
	ServerOP_KickPlayer     = 0x000D // #kick

	ServerOP_RefreshGuild = 0x000E // Notice to all zoneservers to refresh their guild cache for ID# in packet (ServerGuildRefresh_Struct)
	ServerOP_VoiceMacro   = 0x000F
	//ServerOP_GuildInvite =		0x0010
	ServerOP_DeleteGuild                = 0x0011 // ServerGuildID_Struct
	ServerOP_GuildRankUpdate            = 0x0012
	ServerOP_GuildCharRefresh           = 0x0013
	ServerOP_GuildMemberUpdate          = 0x0014
	ServerOP_RequestOnlineGuildMembers  = 0x0015
	ServerOP_OnlineGuildMembersResponse = 0x0016
	ServerOP_LFGuildUpdate              = 0x0017

	ServerOP_FlagUpdate          = 0x0018 // GM Flag updated for character, refresh the memory cache
	ServerOP_GMGoto              = 0x0019
	ServerOP_MultiLineMsg        = 0x001A
	ServerOP_Lock                = 0x001B // For #lock/#unlock inside server
	ServerOP_Motd                = 0x001C // For changing MoTD inside server.
	ServerOP_Uptime              = 0x001D
	ServerOP_Petition            = 0x001E
	ServerOP_KillPlayer          = 0x001F
	ServerOP_UpdateGM            = 0x0020
	ServerOP_RezzPlayer          = 0x0021
	ServerOP_ZoneReboot          = 0x0022
	ServerOP_ZoneToZoneRequest   = 0x0023
	ServerOP_AcceptWorldEntrance = 0x0024
	ServerOP_ZAAuth              = 0x0025
	ServerOP_ZAAuthFailed        = 0x0026
	ServerOP_ZoneIncClient       = 0x0027 // Incoming client
	ServerOP_ClientListKA        = 0x0028
	ServerOP_ChangeWID           = 0x0029
	ServerOP_IPLookup            = 0x002A
	ServerOP_LockZone            = 0x002B
	ServerOP_ItemStatus          = 0x002C
	ServerOP_OOCMute             = 0x002D
	ServerOP_Revoke              = 0x002E
	//		0x002F
	ServerOP_GroupIDReq             = 0x0030
	ServerOP_GroupIDReply           = 0x0031
	ServerOP_GroupLeave             = 0x0032 // for disbanding out of zone folks
	ServerOP_RezzPlayerAccept       = 0x0033
	ServerOP_SpawnCondition         = 0x0034
	ServerOP_SpawnEvent             = 0x0035
	ServerOP_SetLaunchName          = 0x0036
	ServerOP_RezzPlayerReject       = 0x0037
	ServerOP_SpawnPlayerCorpse      = 0x0038
	ServerOP_Consent                = 0x0039
	ServerOP_Consent_Response       = 0x003a
	ServerOP_ForceGroupUpdate       = 0x003b
	ServerOP_OOZGroupMessage        = 0x003c
	ServerOP_DisbandGroup           = 0x003d //for disbanding a whole group cross zone
	ServerOP_GroupJoin              = 0x003e //for joining ooz folks
	ServerOP_UpdateSpawn            = 0x003f
	ServerOP_SpawnStatusChange      = 0x0040
	ServerOP_ReloadTasks            = 0x0060
	ServerOP_DepopAllPlayersCorpses = 0x0061
	ServerOP_ReloadTitles           = 0x0062
	ServerOP_QGlobalUpdate          = 0x0063
	ServerOP_QGlobalDelete          = 0x0064
	ServerOP_DepopPlayerCorpse      = 0x0065
	ServerOP_RequestTellQueue       = 0x0066 // client asks for it's tell queues
	ServerOP_ChangeSharedMem        = 0x0067

	ServerOP_RaidAdd         = 0x0100 //in use
	ServerOP_RaidRemove      = 0x0101 //in use
	ServerOP_RaidDisband     = 0x0102 //in use
	ServerOP_RaidLockFlag    = 0x0103 //in use
	ServerOP_RaidGroupLeader = 0x0104 //in use
	ServerOP_RaidLeader      = 0x0105 //in use
	ServerOP_RaidGroupSay    = 0x0106 //in use
	ServerOP_RaidSay         = 0x0107 //in use
	ServerOP_DetailsChange   = 0x0108 //in use

	ServerOP_UpdateGroup       = 0x010A //in use
	ServerOP_RaidGroupDisband  = 0x010B //in use
	ServerOP_RaidChangeGroup   = 0x010C //in use
	ServerOP_RaidGroupAdd      = 0x010D
	ServerOP_RaidGroupRemove   = 0x010E
	ServerOP_GroupInvite       = 0x010F
	ServerOP_GroupFollow       = 0x0110
	ServerOP_GroupFollowAck    = 0x0111
	ServerOP_GroupCancelInvite = 0x0112
	ServerOP_RaidMOTD          = 0x0113

	ServerOP_InstanceUpdateTime       = 0x014F
	ServerOP_AdventureRequest         = 0x0150
	ServerOP_AdventureRequestAccept   = 0x0151
	ServerOP_AdventureRequestDeny     = 0x0152
	ServerOP_AdventureRequestCreate   = 0x0153
	ServerOP_AdventureData            = 0x0154
	ServerOP_AdventureDataClear       = 0x0155
	ServerOP_AdventureCreateDeny      = 0x0156
	ServerOP_AdventureDataRequest     = 0x0157
	ServerOP_AdventureClickDoor       = 0x0158
	ServerOP_AdventureClickDoorReply  = 0x0159
	ServerOP_AdventureClickDoorError  = 0x015a
	ServerOP_AdventureLeave           = 0x015b
	ServerOP_AdventureLeaveReply      = 0x015c
	ServerOP_AdventureLeaveDeny       = 0x015d
	ServerOP_AdventureCountUpdate     = 0x015e
	ServerOP_AdventureZoneData        = 0x015f
	ServerOP_AdventureAssaCountUpdate = 0x0160
	ServerOP_AdventureFinish          = 0x0161
	ServerOP_AdventureLeaderboard     = 0x0162

	ServerOP_WhoAll               = 0x0210
	ServerOP_FriendsWho           = 0x0211
	ServerOP_LFGMatches           = 0x0212
	ServerOP_LFPUpdate            = 0x0213
	ServerOP_LFPMatches           = 0x0214
	ServerOP_ClientVersionSummary = 0x0215
	ServerOP_LSInfo               = 0x1000
	ServerOP_LSStatus             = 0x1001
	ServerOP_LSClientAuth         = 0x1002
	ServerOP_LSFatalError         = 0x1003
	ServerOP_SystemwideMessage    = 0x1005
	ServerOP_ListWorlds           = 0x1006
	ServerOP_PeerConnect          = 0x1007
	ServerOP_NewLSInfo            = 0x1008
	ServerOP_LSRemoteAddr         = 0x1009
	ServerOP_LSAccountUpdate      = 0x100A

	ServerOP_EncapPacket             = 0x2007 // Packet within a packet
	ServerOP_WorldListUpdate         = 0x2008
	ServerOP_WorldListRemove         = 0x2009
	ServerOP_TriggerWorldListRefresh = 0x200A
	ServerOP_WhoAllReply             = 0x2010
	ServerOP_SetWorldTime            = 0x200B
	ServerOP_GetWorldTime            = 0x200C
	ServerOP_SyncWorldTime           = 0x200E

	ServerOP_LSZoneInfo         = 0x3001
	ServerOP_LSZoneStart        = 0x3002
	ServerOP_LSZoneBoot         = 0x3003
	ServerOP_LSZoneShutdown     = 0x3004
	ServerOP_LSZoneSleep        = 0x3005
	ServerOP_LSPlayerLeftWorld  = 0x3006
	ServerOP_LSPlayerJoinWorld  = 0x3007
	ServerOP_LSPlayerZoneChange = 0x3008

	ServerOP_UsertoWorldReq  = 0xAB00
	ServerOP_UsertoWorldResp = 0xAB01

	ServerOP_LauncherConnectInfo = 0x3000
	ServerOP_LauncherZoneRequest = 0x3001
	ServerOP_LauncherZoneStatus  = 0x3002
	ServerOP_DoZoneCommand       = 0x3003

	ServerOP_UCSMessage               = 0x4000
	ServerOP_UCSMailMessage           = 0x4001
	ServerOP_ReloadRules              = 0x4002
	ServerOP_ReloadRulesWorld         = 0x4003
	ServerOP_CameraShake              = 0x4004
	ServerOP_QueryServGeneric         = 0x4005
	ServerOP_CZSignalClient           = 0x4006
	ServerOP_CZSignalClientByName     = 0x4007
	ServerOP_CZMessagePlayer          = 0x4008
	ServerOP_ReloadWorld              = 0x4009
	ServerOP_ReloadLogs               = 0x4010
	ServerOP_ReloadPerlExportSettings = 0x4011
	/* Query Server OP Codes */
	ServerOP_QSPlayerLogTrades               = 0x5010
	ServerOP_QSPlayerLogHandins              = 0x5011
	ServerOP_QSPlayerLogNPCKills             = 0x5012
	ServerOP_QSPlayerLogDeletes              = 0x5013
	ServerOP_QSPlayerLogMoves                = 0x5014
	ServerOP_QSPlayerLogMerchantTransactions = 0x5015
	ServerOP_QSSendQuery                     = 0x5016
	ServerOP_CZSignalNPC                     = 0x5017
	ServerOP_CZSetEntityVariableByNPCTypeID  = 0x5018
	ServerOP_Speech                          = 0x4513
)
