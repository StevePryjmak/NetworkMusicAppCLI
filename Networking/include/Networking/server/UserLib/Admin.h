#pragma once
#include "User.h"


class Admin : public User {
protected:
    void initialize_commands() override{
        add_function("1", "My_prifile", std::function<void()>(std::bind(&Admin::my_profile, this)));
        add_function("2", "Show Playlists", std::function<void()>(std::bind(&Admin::show_playlists, this)));
        add_function("3", "Favorites", std::function<void()>(std::bind(&Admin::favorites, this)));
        add_function("4", "Become Artist", std::function<void()>(std::bind(&Admin::become_artist, this)));
        add_function("5", "Log Out", std::function<void()>(std::bind(&Admin::log_out, this)));              // could be removed later
        add_function("6", "Generate Random Playlist", std::function<void()>(std::bind(&Admin::generate_random_playlist, this)));
        add_function("7", "Delete Playlist", std::function<void(std::string)>(std::bind(&Admin::delete_playlist, this, std::placeholders::_1)));
        add_function("8", "Show All Users", std::function<void()>(std::bind(&Admin::show_all_users, this)));
        add_function("9", "Show All Artists", std::function<void()>(std::bind(&Admin::show_all_artists, this)));
        add_function("10", "Show All Admins", std::function<void()>(std::bind(&Admin::show_all_admins, this)));
        add_function("11", "Add Admin(input username)", std::function<void(std::string)>(std::bind(&Admin::add_admin, this, std::placeholders::_1)));


    }

public:
    Admin(const std::string& name, const std::string& login, const std::string& password)
        : User(name, login, password) {
        initialize_commands();
    }

    //----------------------------------------------------------------
    // void show_playlists() override;
    // void generate_random_playlist() override;
    // void favorites() override;
    // void my_profile() override;
    // void delete_playlist() override;
    // --------------------------------------------------------------- Implemented in User class 

    // void log_out() override { std::cout << "Logged out" << std::endl; } probably no neded
    void test() { output = "Admin test";}
    void show_all_users() { output = "Implement showing all users"; }
    void show_all_artists() { output = "Implement showing all artists"; }
    void show_all_admins() { output = "Implement howing all admins" ; }
    void add_admin(std::string username) { output = "Implemet " + username + " Additoin to users"; }
};