#pragma once
#include <iostream>
#include <vector>



class VirtualUser {
protected:
    std::string name;
    std::string login;
    std::string password;
    //std::vector<Playlist> playlists; // add when Playlist class will be created

public:
    void virtual log_out() = 0;
    void virtual show_playlists() = 0;
    void virtual generate_random_playlist() = 0;
    void virtual favorites() = 0;
    void virtual my_profile() = 0;
    void virtual delete_playlist() = 0;
    void virtual become_artist() = 0;
};
