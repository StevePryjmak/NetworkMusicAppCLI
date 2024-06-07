#include <Networking/server/UserLib/Admin.h>



void Admin::initialize_commands() {
    User::initialize_commands();
    add_function("11", "Show All Users", std::function<void()>(std::bind(&Admin::show_all_users, this)));
    add_function("12", "Show All Artists", std::function<void()>(std::bind(&Admin::show_all_artists, this)));
    add_function("13", "Show All Admins", std::function<void()>(std::bind(&Admin::show_all_admins, this)));
    add_function("14", "Add Admin(input username)", std::function<void(std::string)>(std::bind(&Admin::add_admin, this, std::placeholders::_1)));
}



Admin::Admin(const std::string& name, const std::string& login, const std::string& password)
    : User(name, login, password) {
    initialize_commands();
}