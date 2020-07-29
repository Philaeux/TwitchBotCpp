#ifndef TWITCHBOT_CHAT_CLIENT_HXX_
#define TWITCHBOT_CHAT_CLIENT_HXX_

#include <deque>
#include <memory>
#include <string>

#include <boost/asio.hpp>

#include <twitchbot/configuration.hxx>

namespace twitchbot {

  class ChatClient {
   public:
    ChatClient(Configuration& cfg, boost::asio::io_context& io);
    ~ChatClient() { };
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
    boost::asio::io_context& _io;
    boost::asio::ip::tcp::socket _socket;
    boost::asio::streambuf _in_buffer;
    std::deque<std::string> _out_buffer;
  };

}

#endif
