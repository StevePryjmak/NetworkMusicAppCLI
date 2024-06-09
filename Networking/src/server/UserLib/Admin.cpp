#include <Networking/server/UserLib/Admin.h>



void Admin::initialize_commands() {
    User::initialize_commands();
    add_function(13, "Show All Users", std::function<void()>(std::bind(&Admin::show_all_users, this)));
    add_function(14, "Add Admin(input username)", std::function<void(std::string)>(std::bind(&Admin::add_admin, this, std::placeholders::_1)));
}



Admin::Admin(const std::string& name, const std::string& login, const std::string& password)
    : User(name, login, password) {
    initialize_commands();
}

void Admin::add_admin(std::string username) {
    UserDataInterface user_db;
    unsigned int al = user_db.getAccessLevel(username);
    if (al == 0 || al == 3) {output = "User " + username + " is already an admin."; return;}
    else if (al == 1)
        user_db.changeAccessLevel(username, 0);
    else if (al == 2)
        user_db.changeAccessLevel(username, 3);
}

void Admin::become_artist() {
    PlaylistDataInterface playlists_db;
    Playlist my_songs("My_Songs");
    playlists_db.savePlaylist(my_songs, login);
    UserDataInterface users_db;
    users_db.changeAccessLevel(login, 3);
    output = "You are an artist not. For apdate you need to relogin\n";
}