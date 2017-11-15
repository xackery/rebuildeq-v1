#ifndef NATS_H
#define NATS_H

#include "nats.h"

#include "../common/global_define.h"
#include "../common/types.h"
#include "../common/timer.h"
#include "../common/proto/message.pb.h"
#include "../common/servertalk.h"

class NatsManager
{
public:
	NatsManager();
	~NatsManager();

	void Process();
	void OnChannelMessage(ServerChannelMessage_Struct * msg);
	void OnEmoteMessage(ServerEmoteMessage_Struct * msg);
	void SendAdminMessage(std::string adminMessage);
	void ChannelMessageEvent(eqproto::ChannelMessage* message);
	void CommandMessageEvent(eqproto::CommandMessage* message, const char* reply);
	void SendChannelMessage(eqproto::ChannelMessage* message);
	void Save();
	void Load();
protected:
	natsConnection *conn = NULL;
	natsStatus      s;
	natsStatistics *stats = NULL;
	natsOptions *opts = NULL;
	natsSubscription *testSub = NULL;
	natsSubscription *channelMessageSub = NULL;
	natsSubscription *commandMessageSub = NULL;
	natsSubscription *adminMessageSub = NULL;
	//int testSubMax = 100;
};

#endif