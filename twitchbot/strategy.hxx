#ifndef TWITCHBOT_STRATEGY_HXX_
#define TWITCHBOT_STRATEGY_HXX_

#include <string>

#include <twitchbot/configuration.hxx>
#include <twitchbot/chat_client.hxx>

namespace twitchbot {
  
  class Strategy {
   public:
    Strategy(Configuration& cfg, ChatClient& chat_client);
    ~Strategy() { };

   private:
    Configuration& _cfg;
    ChatClient& _chat_client;
  };

}

#endif // TWITCHBOT_STRATEGY_HXX_
