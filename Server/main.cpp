#include <iostream>
#include <Networking/server/tcp_server.h>

int main(int argc, char* argv[]) {
    try {
        createDirectories();
        TCPServer server {IPV::V4, 1337};

        server.OnJoin = [](TCPConnection::pointer connection) {
            std::cout << "User has joined the server: " << connection->get_username() << std::endl;
        };

        server.OnLeave = [](TCPConnection::pointer connection) {
            // TODO: Implement user leave handling delete conection and VirtualUser fomr map
            std::cout << "User has left the server: " << connection->get_username() << std::endl;
        };

        server.OnClientMessage = [&server](TCPConnection::pointer connection, const std::string& message) {
            server.handle_message(connection, message);
        };

        std::cout << "Server is running on port 1337" << std::endl;

        server.run();
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
