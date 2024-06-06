#pragma once
#include <iostream>
#include "VirtualUser.h"


class User : public VirtualUser {
protected:
    void initialize_commands() override {
        add_function("1", "My_prifile", std::function<void()>(std::bind(&User::my_profile, this)));
        add_function("2", "Show Playlists", std::function<void()>(std::bind(&User::show_playlists, this)));
        add_function("3", "Favorites", std::function<void()>(std::bind(&User::favorites, this)));
        add_function("4", "Become Artist", std::function<void()>(std::bind(&User::become_artist, this)));
        add_function("5", "Log Out", std::function<void()>(std::bind(&User::log_out, this)));
        add_function("6", "Generate Random Playlist", std::function<void()>(std::bind(&User::generate_random_playlist, this)));
        add_function("7", "Delete Playlist (Input playlist name)", std::function<void(std::string)>(std::bind(&User::delete_playlist, this, std::placeholders::_1)));
    }

public:
    User(const std::string& name, const std::string& login, const std::string& password);

    std::string get_option() override;

    void log_out() override {} // probably no needed
    void show_playlists() override {output = "Show playlists\n"; std::cout << output;}
    void generate_random_playlist() override {output = "Generate random playlist\n"; std::cout << output;}
    void favorites() override {output = "Favorites\n"; std::cout << output;}
    std::string my_profile() override;
    void delete_playlist(std::string palylist_name) override {output = "Playlist " + palylist_name + " deleted\n"; std::cout << output;}
    void become_artist() override {}

};


