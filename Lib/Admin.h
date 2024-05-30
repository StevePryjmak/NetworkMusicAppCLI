#pragma once
#include "User.h"

class Admin : public User {

public:
    Admin(std::string name, std::string login, std::string password) : User(name, login, password) {}

    void log_out() override {std::cout<<"Loged out";}; // save data (also depends if function on in client or server)

    //----------------------------------------------------------------
    // void show_playlists() override;
    // void generate_random_playlist() override;
    // void favorites() override;
    // void my_profile() override;
    // void delete_playlist() override;
    // --------------------------------------------------------------- Implemented in User class 

    //void ban(); // ban user
    //void unban(); // unban user
    void test() {std::cout<<"Function was caled secsefuly using dynamic cast"<<std::endl;} // test function to check if dynamic cast works;
    void show_all_users(); // show all users
    void show_all_artists(); // show all artists
    void show_all_admins(); // show all admins
    //void show_all_banned(); // show all banned users
    void add_admin(); // add admin to use those class sould use dynamic cast

};