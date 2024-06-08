#include <Networking/server/UserLib/User.h>
#include <Networking/server/UserLib/Artist.h>
#include <iostream>


void User::initialize_commands() {
    command_map.clear();
    curent_menu = "main";
    output = "Main menu\n";
    add_function(10, "Add Song to Playlist (Input playlist name and song name)", std::function<void(std::string, std::string)>(std::bind(&User::add_song_to_playlist, this, std::placeholders::_1, std::placeholders::_2)));
    add_function(1, "My_prifile", std::function<void()>(std::bind(&User::my_profile, this)));
    add_function(2, "Show Playlists", std::function<void()>(std::bind(&User::show_playlists, this)));
    add_function(3, "Favorites", std::function<void()>(std::bind(&User::favorites, this)));
    add_function(4, "Become an Artist", std::function<void()>(std::bind(&User::become_artist, this)));
    add_function(5, "Log Out", std::function<void()>(std::bind(&User::log_out, this)));
    add_function(6, "Generate Random Playlist(Input number of Songs and Genre(not required))", std::function<void(int)>(std::bind(&User::generate_random_playlist, this, std::placeholders::_1)));
    add_function(7, "Delete Playlist (Input playlist name)", std::function<void(std::string)>(std::bind(&User::delete_playlist, this, std::placeholders::_1)));
    add_function(8, "Add Favorite Song (Input song name)", std::function<void(std::string)>(std::bind(&User::add_favorite_song, this, std::placeholders::_1)));
    add_function(9, "Create Playlist (Input playlist name)", std::function<void(std::string)>(std::bind(&User::create_playlist, this, std::placeholders::_1)));
}

void User::initialize_playlist_map() {
    command_map.clear();
    curent_menu = "playlists";
    int counter = 0;
    for (const auto& playlist : playlists) {
        ++counter;
        add_function(counter, playlist.getName(),
                        std::function<std::string()>(std::bind(&Playlist::getPlaylist, &playlist)));
    }
    add_function(0, "Back to main menu", std::function<void()>(std::bind(&User::initialize_commands, this)));
}




User::User(const std::string& name, const std::string& login, const std::string& password) {
    this->name = name;
    this->login = login;
    this->password = password;
    initialize_commands();
}

std::string User::get_option() {
    std::string option = "";
    for (const auto& pair : command_map) {
        option += std::to_string(pair.first) + ". " + pair.second.description + "\n";
    }
    return option;
}

void User::load_playlists(std::vector<Playlist> playlists) {
    this->playlists = playlists;
}

void User::load_favorites_playlist(Playlist favorite_playlist) {
    this->favorite_playlist = favorite_playlist;
}

std::string User::my_profile() {
    output = "My profile:\n";
    output += "username: " + name + "\nlogin: " + login + "\n";
    return output;
}

void User::show_playlists() {
    output = "Playlists:\n";
    initialize_playlist_map();
}

void User::favorites()  {
    output = favorite_playlist.getPlaylist();
}

void User::generate_random_playlist(int number_of_songs) {
    PlaylistDataInterface playlists_db;
    Playlist random_playlist = playlists_db.getRandomPlaylist(login, number_of_songs);
    playlists.push_back(random_playlist);
    output = "Your random playlist:\n";
    output += random_playlist.getPlaylist();
}

void User::add_favorite_song(std::string name) {
    PlaylistDataInterface playlists_db;
    if(!playlists_db.songExists(name)) {
        output = "Sorry! We dont't have " + name + " in our data base\n";
        return;
    }
    favorite_playlist.addToPlaylist(playlists_db.loadSong(name));
    playlists_db.savePlaylist(favorite_playlist, login);
    output = "Song " + name + " added to favorites\n";
}

void User::delete_playlist(std::string playlist_name) {
    if(playlist_name == "My_Songs" || playlist_name == "favorites") {
        output = "You can't delete program playlist\n";
        return;
    }
    PlaylistDataInterface playlists_db;
    if(!playlists_db.playlistExists(playlist_name, login)) {
        output = "Playlist " + playlist_name + " not found\n";
        output += "Please input valid playlist name\n";
        return;
    }
    playlists_db.deletePlaylist(playlist_name, login);
    output = "Playlist " + playlist_name + " deleted\n";
}

void User::create_playlist(std::string playlist_name) {
    PlaylistDataInterface playlists_db;
    if(playlists_db.playlistExists(playlist_name, login)) {
        output = "Playlist " + playlist_name + " already exists\n";
        output += "Please input another playlist name\n";
        return;
    }
    Playlist new_playlist(playlist_name);
    playlists_db.savePlaylist(new_playlist, login);
    playlists.push_back(new_playlist);
    output = "Playlist " + playlist_name + " created\n";
}

void User::add_song_to_playlist(std::string playlist_name, std::string song_name) {
    PlaylistDataInterface playlists_db;
    if(!playlists_db.playlistExists(playlist_name, login)) {
        output = "Playlist " + playlist_name + " not found\n";
        output += "Please input valid playlist name\n";
        return;
    }
    if(!playlists_db.songExists(song_name)) {
        output = "Song " + song_name + " not found\n";
        output += "Please input valid song name\n";
        return;
    }
    Playlist playlist = playlists_db.loadPlaylist(playlist_name, login);
    playlist.addToPlaylist(playlists_db.loadSong(song_name));
    playlists_db.savePlaylist(playlist, login);
    output = "Song " + song_name + " added to playlist " + playlist_name + "\n";

    playlists.clear();
    load_playlists(playlists_db.getPlaylists(login));
}


void User::become_artist() {
    PlaylistDataInterface playlists_db;
    Playlist my_songs("My_Songs");
    playlists_db.savePlaylist(my_songs, login);
    UserDataInterface users_db;
    users_db.changeAccessLevel(login, 2);
    output = "You are an artist not. For apdate you need to relogin\n";
}