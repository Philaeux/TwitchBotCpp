#include <twitchbot/configuration.hxx>

#include <iostream>
#include <string>

#include <boost/filesystem/operations.hpp>
#include <boost/program_options.hpp>

namespace twitchbot {

	Configuration::Configuration(): 
		_cfg_file{ "default.cfg" },
		_irc_bot_name{ "MyTwitchBot" },
		_irc_oauth_token{ "oauth:randomfaketoken" },
		_irc_channel{ "#twitch" },
		_api_client_id{ "myfakeclientid" },
		_api_client_secret{ "myfakeclientsecret" },
		_api_client_oauth_token{ "myfakeclientoauthtoken" },
		_strategy_sound_reward_id{ "sounduuid" }
		{ };

	Configuration::~Configuration() { };

	void Configuration::parse_config(const int& argc, char** argv) {
		// Parse command line options
		boost::program_options::options_description desc{ "Allowed options" };
		desc.add_options()
			("help,h", "print usage message")
			("cfg", boost::program_options::value<std::string>(&_cfg_file)->default_value("default.cfg"), "configuration file to use");

		boost::program_options::variables_map vm;
		boost::program_options::store(boost::program_options::parse_command_line(argc, argv, desc), vm);
		boost::program_options::notify(vm);

		// Parse configuration options
		boost::program_options::options_description cfg_file_desc("Configuration file options");
		cfg_file_desc.add_options()
			("twitch_irc.bot_name", boost::program_options::value<std::string>(&_irc_bot_name), "Name of the irc bot used in Twitch chat")
			("twitch_irc.oauth_token", boost::program_options::value<std::string>(&_irc_oauth_token), "Oauth token to connect as this user")
			("twitch_irc.channel", boost::program_options::value<std::string>(&_irc_channel), "Channel to connect to in the irc server")
			("twitch_api.client_id", boost::program_options::value<std::string>(&_api_client_id), "Client ID for the twitch api")
			("twitch_api.client_secret", boost::program_options::value<std::string>(&_api_client_secret), "Client secret associated with the client id")
			("twitch_api.client_oauth_token", boost::program_options::value<std::string>(&_api_client_oauth_token), "Client oauth to login in specific api other than client secret")
			("strategy.sound_reward_id", boost::program_options::value<std::string>(&_strategy_sound_reward_id), "Id of the reward used to start sounds");

		// Load configuration file if exists
		std::string file_path = boost::filesystem::system_complete(argv[0]).parent_path().string() + "/cfg/" + _cfg_file;
		try {
			boost::program_options::store(parse_config_file(file_path.c_str(), cfg_file_desc), vm);
			boost::program_options::notify(vm);
		}
		catch (boost::wrapexcept<boost::program_options::reading_file> e) {
			std::cout << "Unknown configuration file \"" << file_path << "\", please check name." << std::endl;
			exit(EXIT_FAILURE);
		}
		catch (boost::wrapexcept<boost::program_options::unknown_option> e) {
			std::cout << "Unknown option \"" << e.get_option_name() << "\" in the configuration file, please check format." << std::endl;
			exit(EXIT_FAILURE);
		}
	};

}
