#pragma once 
#include "User.h"

class Artist : public virtual User {
protected:
    void initialize_commands() override;
    Playlist my_songs; // TODO: Implement this
public:
    Artist(const std::string& name, const std::string& login, const std::string& password);
    void become_artist() override;

    void add_song(std::string name, std::string genre, std::string lyrics, int duratoin);
    void load_my_songs(Playlist my_songs) override;
    void delete_song(std::string song_name);
    void show_my_songs();
};



