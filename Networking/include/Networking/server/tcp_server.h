#pragma once

#include <Networking/server/tcp_connection.h>
#include <Networking/server/UserLib/User.h>
#include <Networking/server/UserLib/Admin.h>
#include <Networking/server/UserLib/Artist.h>
#include <Networking/server/DatabaseLib/database.h>
#include <boost/asio.hpp>
#include <unordered_set>
#include <optional>
#include <functional>
#include <vector>



enum class IPV {
    V4,
    V6
};

class TCPServer {
private:
    IPV ip_version;
    int port;

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::acceptor  acceptor;
    std::optional<boost::asio::ip::tcp::socket> socket;
    std::vector<std::pair<TCPConnection::pointer, VirtualUser*>> connections;
    UserDataInterface users_db;
    void start_accept();

public:
    TCPServer(IPV ipv, int port);
    int run();
    void Broadcast(const std::string& message);

    std::function<void(TCPConnection::pointer)> OnJoin;
    std::function<void(TCPConnection::pointer)> OnLeave;
    std::function<void(TCPConnection::pointer, const std::string&)> OnClientMessage;

    void handle_message(TCPConnection::pointer connection, const std::string& message);
};



