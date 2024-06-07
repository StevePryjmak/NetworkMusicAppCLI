#pragma once 
#include "User.h"

class Artist : public User {
protected:
    void initialize_commands() override;
    std::vector<Playlist> my_songs; // TODO: Implement this
public:
    Artist(const std::string& name, const std::string& login, const std::string& password);
    void become_artist() override;

    void add_song() {output = "sould be refactored and take more argumets but when we got masage add song second argument aka song have multimple words and  need to be read properly ...";}; // add song to my_songs
    void delete_song(std::string song_name) {output = "sonng " + song_name + "Deletion not implemented";}; // delete song from my_songs
    void show_my_songs() {output = "Show artist songs";}; // show all songs from my_songs
    
};



