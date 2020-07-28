#include "Strategy.h"

Strategy::Strategy(Configuration& cfg, TwitchChatClient& twitch_chat_client):
    _cfg(cfg), _twitch_chat_client(twitch_chat_client)
{ };
