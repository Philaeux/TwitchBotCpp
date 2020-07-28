#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <deque>
#include <memory>
#include <string>

#include "Configuration.h"

namespace asio = boost::asio;
using tcp = asio::ip::tcp;

class TwitchChatClient {
    public:
        TwitchChatClient(Configuration& cfg, asio::io_context& io);
        ~TwitchChatClient() { };
        void connect();
        void say(std::string message);

    private:
        void login();
        void on_socket_line(const boost::system::error_code& error, size_t s);
        void on_line(std::string line);
        void on_message(std::string user, bool is_mod, bool is_sub, std::string message);
        void on_reward(std::string user, std::string reward_id, std::string message);
        void send_line(std::string data);
        void socket_send();
        void on_socket_sent(const boost::system::error_code& error, size_t s);

        Configuration& _cfg;
        asio::io_context& _io;
        tcp::socket _socket;
        asio::streambuf _in_buffer;
        std::deque<std::string> _out_buffer;
};
