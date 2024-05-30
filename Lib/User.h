#pragma once
#include <iostream>
#include "VirtualUser.h"

class User : public VirtualUser {

public:
    User(std::string name, std::string login, std::string password) {
        this->name = name;
        this->login = login;
        this->password = password;
    }

    void log_out() override {}; // save data (also depends if function on in client or server)
    void show_playlists() override {};
    void generate_random_playlist() override {};
    void favorites() override {};
    void my_profile() override {};
    void delete_playlist() override {};
    void become_artist() override {}; //overide to change this* to Artist
    
};
