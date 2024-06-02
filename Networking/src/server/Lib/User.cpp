#include <Networking/server/Lib/User.h>
//#include "../../../include/Networking/server/Lib/User.h"
#include <iostream>

User::User(const std::string& name, const std::string& login, const std::string& password) {
    this->name = name;
    this->login = login;
    this->password = password;
    initializeCommands();
}

std::string User::executeCommand(const std::string& command, int args_count, ...) {
    auto it = command_map.find(command);
    if (it == command_map.end()){

        std::cout << "Unknown command: " << command << std::endl;
        return "Invalid command\n";
    }
    va_end(args);
    output = "";
    va_start(args, args_count);
    std::cout << std::get<1>(it->second) << std::endl; // Print description
    (std::get<2>(it->second))(); // Call the function
    return output;
}

std::string User::get_option() {
    //int i = 1;
    std::string option = "";
    for (const auto& pair : command_map) {
        option += pair.first + ". " + std::get<1>(pair.second) + "\n";
        //++i;
    }
    output = option;
    return option;
}

void User::my_profile() {
    output = "My profile:\n";
    output += "username: " + name + "\n login: " + login + "\n";
}


// int main()
// {
//     std::vector<VirtualUser*> users;
//     users.push_back(new User("name", "login", "password"));
//     //users.push_back(new Admin("name", "login", "password"));
//     std::string s = users[0]->get_option();
//     std::cout << s << std::endl;
// }