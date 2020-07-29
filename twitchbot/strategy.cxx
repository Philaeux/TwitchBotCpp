#include <twitchbot/strategy.hxx>

namespace twitchbot {

  Strategy::Strategy(Configuration& cfg, ChatClient& chat_client) :
    _cfg(cfg),
    _chat_client(chat_client)
  { };

}
