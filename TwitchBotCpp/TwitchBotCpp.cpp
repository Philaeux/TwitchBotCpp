#include "Configuration.h"
#include "Strategy.h"
#include "TwitchBotCpp.h"
#include "TwitchChatClient.h"

int main(int argc, char** argv) {
	Configuration cfg;
	cfg.parse_config(argc, argv);

	boost::asio::io_context io;
	TwitchChatClient chat_client{cfg, io}; 
	chat_client.connect();
	io.run();
}
