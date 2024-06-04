#pragma once
#include "User.h"

class Admin : public User {

public:
    Admin(std::string name, std::string login, std::string password) : User(name, login, password) {}

    void log_out() override {}; // save data (also depends if function on in client or server)



    //void ban(); // ban user
    //void unban(); // unban user
    void test() {std::cout<<"Function was caled secsefuly using dynamic cast"<<std::endl;} // test function to check if dynamic cast works;
    void show_all_users(); // show all users
    void show_all_artists(); // show all artists
    void show_all_admins(); // show all admins
    //void show_all_banned(); // show all banned users
    void add_admin(); // add admin to use those class sould use dynamic cast

};



class Admin : public User {
protected:
    void initializeCommands() {
        command_map = {
            {"1", {"My Profile", "Displays user's profile", [this]() { my_profile(); }}},
            {"2", {"Generate Random Playlist", "Generates a random playlist", [this]() { generate_random_playlist(); }}},
            {"3", {"Show Playlists", "Shows user playlists", [this]() { show_playlists(); }}},
            {"4", {"Favorites", "Shows user's favorite songs", [this]() { favorites(); }}},
            {"5", {"Become Artist", "Switches user role to artist", [this]() { become_artist(); }}},

            //{"6", {"Log Out", "Logs out user", [this]() { log_out(); }}},
            {"6", {"Test", "Test command", [this]() { test(); }}},
            {"7", {"Delete Playlist", "Deletes a playlist", [this]() { delete_playlist(); }}},
            {"8", {"Show All Users", "Shows all users", [this]() { show_all_users(); }}},
            {"9", {"Show All Artists", "Shows all artists", [this]() { show_all_artists(); }}},
            {"10", {"Show All Admins", "Shows all admins", [this]() { show_all_admins(); }}},
            {"11", {"Add Admin", "Adds an admin", [this]() { add_admin(); }}},
        };
    }

public:
    Admin(const std::string& name, const std::string& login, const std::string& password)
        : User(name, login, password) {
        initializeCommands();
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
    void add_admin() { output = "Implement adding admin"; }
};