#include <Networking/server/UserLib/User.h>
#include <Networking/server/UserLib/Artist.h>
#include <iostream>


User::User(const std::string& name, const std::string& login, const std::string& password) {
    this->name = name;
    this->login = login;
    this->password = password;
    initialize_commands();


    // Test code
    Playlist playlist1("playlist1");
    Song song1(1, "song1", "artist1", "genre", 2021, 3);
    playlist1.addToPlaylist(song1);
    playlists.push_back(playlist1);
    std::string s = playlist1.getPlaylist();
    std::cout << s << std::endl;

}

std::string User::get_option() {
    std::string option = "";
    for (const auto& pair : command_map) {
        option += pair.first + ". " + pair.second.description + "\n";
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


void User::become_artist(VirtualUser*& user_pointer) {
    User* new_artist = new Artist(name, login, password);
    delete user_pointer; // Delete the current user object to avoid memory leaks
    user_pointer = new_artist;
    output = "You have become an artist\n";
}