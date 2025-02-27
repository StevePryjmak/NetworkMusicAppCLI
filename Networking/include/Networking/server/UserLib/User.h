#pragma once
#include <iostream>
#include "VirtualUser.h"


class User : public virtual VirtualUser {
protected:
    void initialize_commands() override;

    void initialize_playlist_map();
    void initialize_playlist_options(Playlist &playlist);
    void initialize_songs_map(Playlist &playlist);

public:
    User(const std::string& name, const std::string& login, const std::string& password);

    std::string get_option() override;
    void load_playlists(std::vector<Playlist> playlists) override;
    void load_favorites_playlist(Playlist favorite_playlist) override;
    void load_my_songs(Playlist my_songs) override {};

    void log_out() override {output = "logged_out";}
    void show_playlists() override;
    void generate_random_playlist(int number_of_songs) override;
    void favorites() override;
    void add_favorite_song(std::string name) override;
    std::string my_profile() override;
    void delete_playlist(std::string palylist_name) override;

    void create_playlist(std::string playlist_name) override;
    void add_song_to_playlist(std::string playlist_name, std::string song_name) override;

    void become_artist() override;
    void show_songs_from_database() override;
    void show_songs_from_datbase_privious() override;
    void help() override;
};


