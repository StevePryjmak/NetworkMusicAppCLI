#pragma once
#include <iostream>
#include "VirtualUser.h"

class User : public VirtualUser {
protected:
    void initializeCommands() {
        command_map = {
            {"1", {"My Profile", "Displays user's profile", [this]() { my_profile(); }}},
            {"2", {"Generate Random Playlist", "Generates a random playlist", [this]() { generate_random_playlist(); }}},
            {"3", {"Show Playlists", "Shows user playlists", [this]() { show_playlists(); }}},
            {"4", {"Favorites", "Shows user's favorite songs", [this]() { favorites(); }}},
            {"5", {"Become Artist", "Switches user role to artist", [this]() { become_artist(); }}},
            {"6", {"Log Out", "Logs out user", [this]() { log_out(); }}},
            {"7", {"Test", "Test command", [this]() { test(); }}},
            {"8", {"Delete Playlist", "Deletes a playlist", [this]() { delete_playlist(); }}},
        };
    }

public:
    User(const std::string& name, const std::string& login, const std::string& password);

    std::string get_option() override;
    void test() { std::cout << "User test" << std::endl; }

    void log_out() override {} // probably no needed
    void show_playlists() override { output = "Implement show_playlists form bd";}
    void generate_random_playlist() override { output = "Implement generate_random_playlist form bd";}
    void favorites() override { output = "Implement favorites form bd";}
    void my_profile() override;
    void delete_playlist() override {}
    void become_artist() override { output = "Implement become_artist by changing this* to artist";}

    std::string executeCommand(const std::string& command, int args_count, ...) override;
};


