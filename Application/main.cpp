#include <iostream>
#include "../Lib/VirtualUser.h"
#include "../Lib/User.h"
#include "../Lib/Artist.h"
#include "../Lib/Admin.h"


int main()
{
    std::vector<VirtualUser*> users;
    users.push_back(new User("name", "login", "password"));
    users.push_back(new Admin("name", "login", "password"));

    users[0]->log_out();
    users[1]->log_out();

    Admin* admin = dynamic_cast<Admin*>(users[1]);
    if (admin) {
        admin->test();
    }
}