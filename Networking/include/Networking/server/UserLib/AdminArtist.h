#include <Networking/server/UserLib/Artist.h>
#include <Networking/server/UserLib/Admin.h>



class AdminArtist : public Artist, public Admin {
protected:
    void initialize_commands() override {
        Artist::initialize_commands();
        Admin::add_function(16, "Show All Users", std::function<void()>(std::bind(&Admin::show_all_users, this)));
        Admin::add_function(17, "Add Admin(input username)", std::function<void(std::string)>(std::bind(&Admin::add_admin, this, std::placeholders::_1)));
    }

public:
    AdminArtist(const std::string& name, const std::string& login, const std::string& password)
        : User(name, login, password), Admin(name, login, password), Artist(name, login, password) {
        initialize_commands();
    }
    void load_my_songs(Playlist my_songs) override;
    void become_artist() override {
        Artist::become_artist();
    }

    
};