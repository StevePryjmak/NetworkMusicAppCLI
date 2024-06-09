
#include <Networking/server/tcp_server.h>
#include <iostream>
#include <vector>


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

    acceptor.async_accept(*socket, [this](const boost::system::error_code& error) {
        if (!error) {

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
            std::cout << "Accept error: " << error.message() << std::endl;
        }
        start_accept();
    });
}




std::vector<std::string> get_arguments(const std::string& message) {
    std::vector<std::string> arguments;
    std::istringstream stream(message);
    std::string argument;
    stream >> argument;// first_word is invisible sumbol
    stream >> argument;

    while (stream >> argument) {
        if (argument[0] == '"' && argument.back() == '"') {
            if (argument.size() == 2) continue;
            argument = argument.substr(1, argument.size() - 2);
        } else if (argument[0] == '"') {
            std::string temp;
            std::string quoted_argument = argument.substr(1);
            while (stream >> temp) {
                if (temp.back() == '"') {
                    quoted_argument += " " + temp.substr(0, temp.size() - 1);
                    break;
                } else {
                    quoted_argument += " " + temp;
                }
            }
            argument = quoted_argument;
        }

        arguments.push_back(argument);
    }

    for(auto arg : arguments) {
        std::cout << arg << std::endl;
    }

    return arguments;
}

void TCPServer::handle_logining(TCPConnection::pointer connection, const std::string& message) {

    std::vector<std::string> args = get_arguments(message);
    if(!users_db.validUserData(args[0], args[1])) {
        connection->Post("Invalid username or password\n");
        return;
    }
    if(args.size() < 2) {
        connection->Post("Login or pasword cant be emty\n");
        return;
    }

    auto it = std::find_if(connections.begin(), connections.end(), 
        [connection](const auto& pair) { return pair.first == connection; });

    int al = users_db.getAccessLevel(args[0]);

    if (al == 0)       it->second = new Admin(users_db.getUserName(args[0]), args[0], args[1]);
    else if (al == 1)  it->second = new User(users_db.getUserName(args[0]), args[0], args[1]);
    else if (al == 2) {
        it->second = new Artist(users_db.getUserName(args[0]), args[0], args[1]);
        it->second->load_my_songs(playlists_db.loadPlaylist("My_Songs", args[0])); 
    }
    else if (al == 3) {
        it->second = new AdminArtist(users_db.getUserName(args[0]), args[0], args[1]);
        it->second->load_my_songs(playlists_db.loadPlaylist("My_Songs", args[0])); 
    }
    it->second->load_playlists(playlists_db.getPlaylists(args[0]));
    it->second->load_favorites_playlist(playlists_db.loadPlaylist("favorites", args[0]));
}

// void TCPServer::handle_sign_in(TCPConnection::pointer connection, const std::string& message) {
//         std::vector<std::string> args = get_arguments(message);

//         if (users_db.existLogin(args[1])) {
//             connection->Post("Username already exist\n");
//             return;
//         }
//         if(args.size() < 3) {
//             connection->Post("Login or pasword cant be emty\n");
//             return;
//         }
//         auto it = std::find_if(connections.begin(), connections.end(), [connection](const auto& pair) { return pair.first == connection; });
//         it->second = new User(args[0], args[1], args[2]);
//         users_db.addUser(args[0], args[1], args[2], 1);
// }


void TCPServer::handle_message(TCPConnection::pointer connection, const std::string& message) {


    auto it = std::find_if(connections.begin(), connections.end(), [connection](const auto& pair) { return pair.first == connection; });
    if (it == connections.end()) return;
    std::cout << message<<std::endl;

    std::string option_log;
    std::stringstream ss(message);

    ss >> option_log;
    ss >> option_log;

    if(option_log == "Log_in") {
        handle_logining(connection, message);

        const std::string& message1 = "logined\n";
        connection->Post(message1);
        connection->Post("Chose opthin: \n" + it->second->get_option());
        return;
    }

    if(option_log == "Sign_in") {
        std::string name, username, password;
        ss >> name;
        ss >> username;
        ss >> password;
        if (users_db.existLogin(username)) {
            connection->Post("Username already exist\n");
            return;
        }
        it->second = new User(name, username, password);
        users_db.addUser(name, username, password, 1);
        //handle_sign_in(connection, message); // maybe it will be debuged later
        

        const std::string& message1 = "logined\n";
        std::cout<< message1 <<std::endl;
        connection->Post(message1);
        connection->Post("Chose opthin: \n" + it->second->get_option());
        return;
    }

    int option;
    std::stringstream ss_loged(message);
    std::vector<std::string> arguments = get_arguments(message);


    ss_loged >> option_log; 
    ss_loged >> option;

    auto user = it->second;
    Admin* admin = dynamic_cast<Admin*>(user);
    Artist* artist = dynamic_cast<Artist*>(user);
    AdminArtist* admin_artist = dynamic_cast<AdminArtist*>(user);
    try {
        if (user == nullptr) {
            connection->Post("You must log in first\n");
            return;
        }

        if(user->curent_menu == "main") {
            if (option == 5) {
                user->execute_command<void()>(option);
                connection->Post(user->output + "\n");
                connection->Post("Press random key to continue\n");
                it->second = nullptr;
                return;
            }
            if (option == 6) {
                int argument1;
                ss >> argument1;
                user->execute_command<void(int)>(option, argument1);
            }
            else if (option == 7 || option == 8 || option == 9 || (option == 14 && (admin != nullptr || artist != nullptr)) ||  
                    (option == 17 && admin_artist != nullptr)) 
            {

                if(arguments.size() == 0) 
                    connection->Post("This function requeres input\n");
                else
                    user->execute_command<void(std::string)>(option, arguments[0]);
            }
            else if (option == 10) {

                if(arguments.size() < 2)
                    connection->Post("This function requeres input\n");
                else
                    user->execute_command<void(std::string, std::string)>(option, arguments[0], arguments[1]);
            }
            else if(option == 13 && artist!=nullptr)
            {
                if(arguments.size() < 4)
                    connection->Post("This function requeres input\n");
                else
                    user->execute_command<void(std::string, std::string, std::string, int)>(option, arguments[0], arguments[1], arguments[2], std::stoi(arguments[3]));
            }
            else
                user->execute_command<void()>(option);
        }
        else if(user->curent_menu == "playlists" && option != 0) {

            //user->execute_command<std::string()>(option);
            user->execute_command<void()>(option);
        }
        else if(user->curent_menu == "songs" && option != 11 && option != 0 && option != 12) 
        user->execute_command<std::string()>(option);
        else if(user->curent_menu == "playlist_options") {
            user->execute_command<std::string()>(option);
        }
        else if(user->curent_menu == "Users") {
            user->execute_command<void()>(option);
        }
        else user->execute_command<void()>(option);

    } catch (std::exception& e) {
        std::cout << e.what() << std::endl;
        user->output = "Something weent wrong. Try again\n";
    }

    std::string response =  user->output;
    connection->Post(response + "\n\n");
    connection->Post("Chose opthin: \n" + it->second->get_option()); 

}


