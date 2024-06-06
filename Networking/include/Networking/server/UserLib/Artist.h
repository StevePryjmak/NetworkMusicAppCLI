#pragma once 
#include "User.h"

class Artist : public User {
protected:
    void initialize_commands() override {
        add_function("1", "My_prifile", std::function<void()>(std::bind(&User::my_profile, this)));
        add_function("2", "Show Playlists", std::function<void()>(std::bind(&User::show_playlists, this)));
        add_function("3", "Favorites", std::function<void()>(std::bind(&User::favorites, this)));
        add_function("4", "Become Artist", std::function<void()>(std::bind(&User::become_artist, this)));
        add_function("5", "Log Out", std::function<void()>(std::bind(&User::log_out, this)));
        add_function("6", "Generate Random Playlist", std::function<void()>(std::bind(&User::generate_random_playlist, this)));
        add_function("7", "Delete Playlist (Input playlist name)", std::function<void(std::string)>(std::bind(&User::delete_playlist, this, std::placeholders::_1)));
        add_function("8", "Add Song", std::function<void()>(std::bind(&Artist::add_song, this))); // Change declaratoin later
        add_function("9", "Delete Song", std::function<void(std::string)>(std::bind(&Artist::delete_song, this, std::placeholders::_1))); // Change declaratoin later
        add_function("10", "Show My Songs", std::function<void()>(std::bind(&Artist::show_my_songs, this))); // Change declaratoin later

    }
    //std::vector<Playlist> my_songs; 
public:
    Artist(std::string name, std::string login, std::string password) : User(name, login, password) {}


    void log_out() override {} // Save

    //----------------------------------------------------------------
    // void show_playlists() override;
    // void generate_random_playlist() override;
    // void favorites() override;
    // void my_profile() override;
    // void delete_playlist() override;
    // --------------------------------------------------------------- Implemented in User class 

    void become_artist() override {return;}; //override to do nothing

    void add_song() {output = "sould be refactored and take more argumets but when we got masage add song second argument aka song have multimple words and  need to be read properly ...";}; // add song to my_songs
    void delete_song(std::string song_name) {output = "sonng " + song_name + "Deletion not implemented";}; // delete song from my_songs
    void show_my_songs() {output = "Show artist songs";}; // show all songs from my_songs
    
};



