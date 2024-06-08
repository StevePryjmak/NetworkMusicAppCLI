#pragma once
#include "User.h"


class Admin : public virtual User {
protected:
    void initialize_commands() override;

public:
    Admin(const std::string& name, const std::string& login, const std::string& password);

    void become_artist() { output = "implement this"; } // TODO: Implement this
    void show_all_users() { output = "Implement showing all users"; }
    void show_all_artists() { output = "Implement showing all artists"; }
    void show_all_admins() { output = "Implement howing all admins" ; }
    void add_admin(std::string username) { output = "Implemet " + username + " Additoin to users"; }
};