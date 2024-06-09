#include <Networking/server/UserLib/Admin.h>
#include <Networking/server/UserLib/Artist.h>
#include <Networking/server/UserLib/AdminArtist.h>


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



void Admin::show_all_users() {
    command_map.clear();
    UserDataInterface user_db;
    std::vector<std::string> users = user_db.getLogins();
    if (login_index >= users.size()) login_index = 0;
    output = "Users:\n";
    curent_menu = "Users";
    //std::vector<VirtualUser*> users;
    int count = 1;
    for (;login_index < users.size() && count < 10; ++login_index, ++count)
    {
        unsigned int al = user_db.getAccessLevel(users[login_index]);
        std::string al_string;
        if (al == 0) al_string += users[login_index] + " Admin";
        else if (al == 1) al_string += users[login_index] + " User";
        else if (al == 2) al_string += users[login_index] + " Artist";
        else if (al == 3) al_string += users[login_index] + " AdminArtist";
        else al_string += users[login_index] + " Unknown";

        User* user = nullptr;
        if (al == 0)  user = new Admin(user_db.getUserName(users[login_index]),users[login_index], "pass" );
        else if (al == 1)  user = new  User(user_db.getUserName(users[login_index]),users[login_index], "pass" );
        else if (al == 2)  user = new  Artist(user_db.getUserName(users[login_index]),users[login_index], "pass" );
        else if (al == 3)  user = new  AdminArtist(user_db.getUserName(users[login_index]),users[login_index], "pass" );
        else  user = new User(user_db.getUserName(users[login_index]),users[login_index], "pass" );
        add_function(count, al_string, std::function<void()>(std::bind(&Admin::show_user_profile,  this, users[login_index])));

    }
    if(login_index < users.size())  add_function(11, "Net page", std::function<void()>(std::bind(&Admin::show_all_users, this)));
    if(login_index >= 10) add_function(12, "Previous page", std::function<void()>(std::bind(&Admin::show_all_user_privious, this)));
    add_function(0, "Back to main menu", std::function<void()>(std::bind(&Admin::initialize_commands, this)));

    id_index += 10 - count;

}

void Admin::show_all_user_privious() {
    login_index = std::max(0, static_cast<int>(login_index) - 20);
    show_all_users();
}

void Admin::show_user_profile(std::string username) {
    UserDataInterface user_db;
    unsigned int al = user_db.getAccessLevel(username);
    std::string al_string;
    if (al == 0) al_string +=  "Admin";
    else if (al == 1) al_string += "User";
    else if (al == 2) al_string += "Artist";
    else if (al == 3) al_string += "AdminArtist";
    else al_string += "Unknown";
    output = "User profile:\n";
    output += "Name: " + user_db.getUserName(username) + "\n";
    output += "Login: " + username + "\n";
    output += "Playlists:\n";
    PlaylistDataInterface playlists_db;
    std::vector<Playlist> playlists = playlists_db.getPlaylists(username);
    for (auto& playlist : playlists) {
        output += playlist.getName() + "\n";
    }
    output += "Access level: " + al_string + "\n";
    // add_function(0, "Back to users", std::function<void()>(std::bind(&Admin::show_all_users, this)));
}


void Admin::become_artist() {
    PlaylistDataInterface playlists_db;
    Playlist my_songs("My_Songs");
    playlists_db.savePlaylist(my_songs, login);
    UserDataInterface users_db;
    users_db.changeAccessLevel(login, 3);
    output = "You are an artist not. For apdate you need to relogin\n";
}