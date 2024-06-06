#include <Networking/server/tcp_server.h>

#include <iostream>


using boost::asio::ip::tcp;
TCPServer::TCPServer(IPV ipv, int port) : ip_version(ipv), port(port),
    acceptor(io_context, tcp::endpoint(ip_version == IPV::V4 ? tcp::v4() : tcp::v6(), port)) {}


int TCPServer::run() {
    try {
        start_accept();
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }
    return 0;
}

void TCPServer::Broadcast(const std::string &message) {
    for (auto& connection : connections) {
        connection.first->Post(message);
    }
}

void TCPServer::start_accept() {
    socket.emplace(io_context);

    // Asynchronously accept the connection
    acceptor.async_accept(*socket, [this](const boost::system::error_code& error) {
        if (!error) {
            // Create a new TCP connection
            auto connection = TCPConnection::Create(std::move(*socket));
            auto user = nullptr;//new VirtualUser("User"); // Initialize user class, customize as needed

            connections.emplace_back(connection, user);

            if (OnJoin) {
                OnJoin(connection);
            }

            connection->Start(
                [this, connection](const std::string& message) {
                    if (OnClientMessage) {
                        OnClientMessage(connection, message);
                    }
                },
                [this, connection]() {
                    // Remove the connection and user from the connections vector
                    auto it = std::find_if(connections.begin(), connections.end(),
                        [connection](const auto& pair) { return pair.first == connection; });
                    if (it != connections.end()) {
                        delete it->second; 
                        connections.erase(it);
                    }

                    if (OnLeave) {
                        OnLeave(connection);
                    }
                }
            );
        } else {
            // Log the error or handle it as necessary
            std::cerr << "Accept error: " << error.message() << std::endl;
        }

        // Start accepting the next connection
        start_accept();
    });
}




std::string get_first_word(const std::string& message) {
    std::istringstream stream(message);
    std::string first_word;
    stream >> first_word;// first_word is invisible sumbol
    stream >> first_word;

    // Check if the last character is a newline and remove it
    if (!first_word.empty() && first_word.back() == '\n') {
        first_word.pop_back();
    }

    return first_word;
}


void TCPServer::handle_message(TCPConnection::pointer connection, const std::string& message) {
    //Broadcast(message);
    auto it = std::find_if(connections.begin(), connections.end(), 
        [connection](const auto& pair) { return pair.first == connection; });

    if (it == connections.end()) return;

    std::cout << message<<std::endl;

    // implement leter to use something lile map opthin - comand to do something
    std::string option;
    std::stringstream ss(message);
    


    ss >> option; // Not shure why first is not my opthin comand but invisible sumbol
    ss >> option;

    if(option == "Log_in") {
        // initialize user (it must check if user exist from db and if password is correct)
        std::string username, password;
        ss >> username;
        ss >> password;
        std::cout << username << " " << password << std::endl;
        it->second = new Artist("User", username, password);



        const std::string& message1 = "logined\n";
        std::cout<< message1 <<std::endl;
        connection->Post(message1);
        connection->Post("Chose opthin: \n" + it->second->get_option()); // + "\n"
        return;
    }

    auto user = it->second;
    Admin* admin = dynamic_cast<Admin*>(user);
    Artist* artist = dynamic_cast<Artist*>(user); // maybe it will be neded later

    if (user == nullptr) {
        connection->Post("You must log in first\n");
        return;
    }

    if (option == "7") {
        std::string argument1;
        ss >> argument1;
        user->execute_command<void(std::string)>(option, argument1);
    }
    if (option == "11" && admin != nullptr) {
        std::string argument1;
        ss >> argument1;
        user->execute_command<void(std::string)>(option, argument1);
    }
    if(option == "9" && artist != nullptr) { // this and priwious could be done in one if
        std::string argument1;
        ss >> argument1;
        user->execute_command<void(std::string)>(option, argument1);
    }
    else
    {
        user->execute_command<void()>(option);
    }



    std::string response =  user->output;
    connection->Post(response + "\n\n");
    connection->Post("Chose opthin: \n" + it->second->get_option()); 

}


