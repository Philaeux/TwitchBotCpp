#ifndef TWITCHBOT_CONFIGURATION_HXX_
#define TWITCHBOT_CONFIGURATION_HXX_

#include <string>

namespace twitchbot {

  class Configuration {
  public:
    Configuration();
    ~Configuration();
    std::string irc_bot_name() { return _irc_bot_name; };
    std::string irc_oauth_token() { return _irc_oauth_token; };
    std::string irc_channel() { return _irc_channel; };
    std::string api_client_id() { return _api_client_id; };
    std::string api_client_secret() { return _api_client_secret; };
    std::string api_client_oauth_token() { return _api_client_oauth_token; };
    std::string strategy_sound_reward_id() { return _strategy_sound_reward_id; };
    void parse_config(const int& argc, char** argv);

  private:
    std::string _cfg_file;
    std::string _irc_bot_name;
    std::string _irc_oauth_token;
    std::string _irc_channel;
    std::string _api_client_id;
    std::string _api_client_secret;
    std::string _api_client_oauth_token;
    std::string _strategy_sound_reward_id;
  };

}

#endif // TWITCHBOT_CONFIGURATION_HXX_
