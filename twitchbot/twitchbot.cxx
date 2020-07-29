#include <iostream>

#include <twitchbot/chat_client.hxx>
#include <twitchbot/configuration.hxx>
#include <twitchbot/strategy.hxx>

int main(int argc, char** argv) {
	twitchbot::Configuration cfg;
	cfg.parse_config(argc, argv);

	boost::asio::io_context io;
	twitchbot::ChatClient chat_client{ cfg, io };
	twitchbot::Strategy strategy{ cfg, chat_client };
	
	chat_client.connect();
	io.run();
}
