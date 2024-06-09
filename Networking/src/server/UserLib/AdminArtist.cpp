#include <Networking/server/UserLib/AdminArtist.h>



// void AdminArtist::initialize_commands() {
//     Admin::initialize_commands();
//     add_function("11", "Show All Users", std::function<void()>(std::bind(&AdminArtist::show_all_users, this)));
//     add_function("12", "Show All Artists", std::function<void()>(std::bind(&AdminArtist::show_all_artists, this)));
//     add_function("13", "Show All Admins", std::function<void()>(std::bind(&AdminArtist::show_all_admins, this)));
//     add_function("14", "Add Admin(input username)", std::function<void(std::string)>(std::bind(&AdminArtist::add_admin, this, std::placeholders::_1)));
//     add_function("15", "Add Song", std::function<void()>(std::bind(&AdminArtist::add_song, this)));
//     add_function("16", "Delete Song", std::function<void(std::string)>(std::bind(&AdminArtist::delete_song, this, std::placeholders::_1)));
//     add_function("17", "Show My Songs", std::function<void()>(std::bind(&AdminArtist::show_my_songs, this)));
// } // TODO Neet to be changed later(check if it check for admin or for artist) fiirst because it have 2 base pointers)


void AdminArtist::load_my_songs(Playlist my_songs) {
    Artist::load_my_songs(my_songs);
}