#pragma once

#include <string>

#include "Configuration.h"
#include "TwitchChatClient.h"

using namespace std;

class Strategy {
    public:
        Strategy(Configuration& cfg, TwitchChatClient& twitch_chat_client);
        ~Strategy() { };

    private:
        Configuration& _cfg;
        TwitchChatClient& _twitch_chat_client;
};
