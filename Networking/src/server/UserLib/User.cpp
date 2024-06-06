#include <Networking/server/UserLib/User.h>
#include <iostream>

User::User(const std::string& name, const std::string& login, const std::string& password) {
    this->name = name;
    this->login = login;
    this->password = password;
    initialize_commands();
}

std::string User::get_option() {
    std::string option = "";
    for (const auto& pair : command_map) {
        option += pair.first + ". " + pair.second.description + "\n";
    }
    return option;
}

std::string User::my_profile() {
    output = "My profile:\n";
    output += "username: " + name + "\n login: " + login + "\n";
    return output;
}

// void User::become_artist(User*& user_pointer) {
//     // User* new_artist = new Artist(name, login, password);
//     // delete user_pointer; // Delete the current user object to avoid memory leaks
//     // user_pointer = new_artist;
//     // output = "You have become an artist\n";
// }