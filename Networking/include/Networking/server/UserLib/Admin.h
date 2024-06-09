#pragma once
#include "User.h"


class Admin : public virtual User {
protected:
    void initialize_commands() override;

public:
    Admin(const std::string& name, const std::string& login, const std::string& password);

    void load_my_songs(Playlist my_songs) override {};
    void become_artist() override;
    void show_all_users();
    void show_all_user_privious();
    void add_admin(std::string username);
};