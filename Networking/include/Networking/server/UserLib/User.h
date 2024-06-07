#pragma once
#include <iostream>
#include "VirtualUser.h"


class User : public VirtualUser {
protected:
    void initialize_commands() override {
        command_map.clear();
        curent_menu = "main";
        output = "Main menu\n";
        add_function("1", "My_prifile", std::function<void()>(std::bind(&User::my_profile, this)));
        add_function("2", "Show Playlists", std::function<void()>(std::bind(&User::show_playlists, this)));
        add_function("3", "Favorites", std::function<void()>(std::bind(&User::favorites, this)));
        add_function("4", "Become Artist", std::function<void()>(std::bind(&User::become_artist_feedback, this)));
        add_function("5", "Log Out", std::function<void()>(std::bind(&User::log_out, this)));
        add_function("6", "Generate Random Playlist", std::function<void()>(std::bind(&User::generate_random_playlist, this)));
        add_function("7", "Delete Playlist (Input playlist name)", std::function<void(std::string)>(std::bind(&User::delete_playlist, this, std::placeholders::_1)));
        add_function("8", "Add Favorite Song (Input song name)", std::function<void(std::string)>(std::bind(&User::add_favorite_song, this, std::placeholders::_1)));
    }

    void initialize_playlist_map() {
        command_map.clear();
        curent_menu = "playlists";
        int counter = 0;
        for (const auto& playlist : playlists) {
            ++counter;
            add_function(std::to_string(counter), playlist.getName(),
                         std::function<std::string()>(std::bind(&Playlist::getPlaylist, &playlist)));
        }
        add_function("back", "Back to main menu", std::function<void()>(std::bind(&User::initialize_commands, this)));
    }
public:
    User(const std::string& name, const std::string& login, const std::string& password);

    std::string get_option() override;
    void load_playlists(std::vector<Playlist> playlists) override;
    void load_favorites_playlist(Playlist favorite_playlist) override;

    void log_out() override {} // probably no needed
    void show_playlists() override;
    void generate_random_playlist() override {output = "Generate random playlist\n"; std::cout << output;}
    void favorites() override {output = "Favorites\n"; std::cout << output;}
    void add_favorite_song(std::string name) override {output = "Do nothing for now\n"; std::cout << output;}
    std::string my_profile() override;
    void delete_playlist(std::string palylist_name) override {output = "Playlist " + palylist_name + " deleted\n"; std::cout << output;}
    void become_artist_feedback() override {output = "You are an artist now\n"; std::cout << output;}
    void become_artist(VirtualUser*& user_pointer) override;

};


