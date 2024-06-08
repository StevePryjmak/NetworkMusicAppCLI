#include <Networking/server/UserLib/Artist.h>

void Artist::initialize_commands() {
    User::initialize_commands();
    add_function(13, "Add Song", std::function<void()>(std::bind(&Artist::add_song, this))); // Change declaratoin later
    add_function(14, "Delete Song", std::function<void(std::string)>(std::bind(&Artist::delete_song, this, std::placeholders::_1))); // Change declaratoin later
    add_function(15, "Show My Songs", std::function<void()>(std::bind(&Artist::show_my_songs, this))); // Change declaratoin later
}



Artist::Artist(const std::string& name, const std::string& login, const std::string& password) : User(name, login, password) {
    initialize_commands();
}

void Artist::become_artist() {
    output = "You are already an artist";
}