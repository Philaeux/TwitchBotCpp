#pragma once

#include <string>

using namespace std;

class Configuration {
    public:
        Configuration();
        ~Configuration();
        string irc_bot_name() { return _irc_bot_name; };
        string irc_oauth_token() { return _irc_oauth_token; };
        string irc_channel() { return _irc_channel; };
        string api_client_id() { return _api_client_id; };
        string api_client_secret() { return _api_client_secret; };
        string api_client_oauth_token() { return _api_client_oauth_token; };
        void parse_config(const int& argc, char** argv);

    private:
        string _cfg_file;
        string _irc_bot_name;
        string _irc_oauth_token;
        string _irc_channel;
        string _api_client_id;
        string _api_client_secret;
        string _api_client_oauth_token;
};
