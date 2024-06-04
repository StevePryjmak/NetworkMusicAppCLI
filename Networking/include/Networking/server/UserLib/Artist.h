#pragma once 
#include "User.h"

class Artist : public User {
protected:
    //std::vector<Playlist> my_songs; 
public:
    Artist(std::string name, std::string login, std::string password) : User(name, login, password) {}

    void log_out() override; // save data (also depends if function on in client or server)

    //----------------------------------------------------------------
    // void show_playlists() override;
    // void generate_random_playlist() override;
    // void favorites() override;
    // void my_profile() override;
    // void delete_playlist() override;
    // --------------------------------------------------------------- Implemented in User class 

    void become_artist() override; //override to do nothing

    void add_song(); // add song to my_songs
    void delete_song(); // delete song from my_songs
    void edit_song(); // edit song from my_songs
    void show_my_songs(); // show all songs from my_songs
    
};
