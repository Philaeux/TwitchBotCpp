#include <twitchbot/chat_client.hxx>

#include <iostream>
#include <regex>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>

namespace twitchbot {

  ChatClient::ChatClient(Configuration& cfg, boost::asio::io_context& io):
    _cfg(cfg),
    _io(io),
    _socket(io)
  { };

  void ChatClient::connect() {
    _socket.close();
    boost::asio::ip::tcp::resolver resolver{ _io };
    auto endpoints = resolver.resolve("irc.chat.twitch.tv", "6667");
    boost::system::error_code error;
    auto finalEndpoint = boost::asio::connect(_socket, endpoints.begin(), endpoints.end(), error);

    if (error) {
      std::cout << "Error connecting to IRC server." << std::endl;
      return;
    }

    std::cout << "IRC Connected." << std::endl;
    login();
    boost::asio::async_read_until(_socket, _in_buffer, "\r\n",
      boost::bind(&ChatClient::on_socket_line, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
  };

  void ChatClient::say(std::string message) {
    send_line("PRIVMSG #" + _cfg.irc_channel() + " :" + message);
  };

  void ChatClient::login() {
    send_line("PASS " + _cfg.irc_oauth_token());
    send_line("NICK " + _cfg.irc_bot_name());
    send_line("JOIN #" + _cfg.irc_channel());
    send_line("CAP REQ :twitch.tv/tags twitch.tv/commands");
  };

  void ChatClient::on_socket_line(const boost::system::error_code& error, size_t s) {
    std::istream is{ &_in_buffer };
    std::string line;
    std::getline(is, line);
    on_line(line);
    boost::asio::async_read_until(_socket, _in_buffer, "\r\n",
      boost::bind(&ChatClient::on_socket_line, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
  };

  std::regex regex_message("@(.*) :(.*)@(.*) PRIVMSG #(.*) :(.*)");
  std::regex regex_badges("badges=([^;]*);?");
  std::regex regex_user("display-name=([^;]*);?");
  std::regex regex_reward_id("custom-reward-id=([^;]*);?");

  void ChatClient::on_line(std::string line) {
    std::smatch matches;
    if (line.size() > 5 && line.substr(0, 6) == "PING :") {
      send_line("PONG :" + line.substr(6));
    }
    else if (std::regex_search(line, matches, regex_message)) {
      std::string badges = matches[1];
      std::string message = matches[5];
      std::string user{ "" };
      std::string reward_id{ "" };
      bool is_mod = false;
      bool is_sub = false;
      std::smatch submatches;
      if (std::regex_search(badges, submatches, regex_user)) user = submatches[1];
      if (std::regex_search(badges, submatches, regex_reward_id)) reward_id = submatches[1];
      if (std::regex_search(badges, submatches, regex_badges)) {
        if (submatches[1].str().find("moderator") != std::string::npos || submatches[1].str().find("broadcaster") != std::string::npos) is_mod = true;
        if (submatches[1].str().find("subscriber") != std::string::npos) is_sub = true;
      }

      if (reward_id == "") on_message(user, is_mod, is_sub, message);
      else on_reward(user, reward_id, message);
    }
  };

  void ChatClient::on_message(std::string user, bool is_mod, bool is_sub, std::string message) {
    std::cout << user;
    if (is_mod)
      std::cout << "[M]";
    if (is_sub)
      std::cout << "[S]";
    std::cout << ": " << message << std::endl;
  };

  void ChatClient::on_reward(std::string user, std::string reward_id, std::string message) {
    std::cout << user << "(" << reward_id << "): " << message << std::endl;
  };

  void ChatClient::send_line(std::string data) {
    data += "\r\n";

    _out_buffer.push_back(std::move(data));

    // if size == 1 then we are the only one sending
    // Otherwise an other callback is already sending
    if (_out_buffer.size() == 1) {
      socket_send();
    }
  };

  void ChatClient::socket_send() {
    if (_out_buffer.empty()) {
      return;
    }

    _socket.async_send(
      boost::asio::buffer(_out_buffer.front().data(), _out_buffer.front().size()),
      boost::bind(&ChatClient::on_socket_sent, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred)
    );
  };

  void ChatClient::on_socket_sent(const boost::system::error_code& error, size_t s) {
    if (error) {
      std::cout << "Error sending: " << error << std::endl;
      return;
    }

    auto bytes_sent = std::min(s, _out_buffer.front().size());
    auto& sent_string = _out_buffer.front();
    sent_string.erase(sent_string.begin(), sent_string.begin() + bytes_sent);
    if (sent_string.empty()) {
      _out_buffer.erase(_out_buffer.begin());
    }

    if (!_out_buffer.empty()) {
      socket_send();
    }
  };

}
