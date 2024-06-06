#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <tuple>
#include <map>

#include <any>
#include <cstdarg>


struct FunctionHolder {
    std::string description;
    std::any function;
};


class VirtualUser {
protected:
    std::string name;
    std::string login;
    std::string password;
    //std::vector<Playlist> playlists; // add when Playlist class will be created

    std::map<std::string, FunctionHolder> command_map;
    void virtual initialize_commands() = 0;
public:
    virtual ~VirtualUser() = default;

    virtual std::string get_option() = 0;
    virtual void log_out() = 0;
    virtual void show_playlists() = 0;
    virtual void generate_random_playlist() = 0;
    virtual void favorites() = 0;
    virtual std::string my_profile() = 0;
    virtual  void delete_playlist(std::string palylist_name) = 0;
    virtual void become_artist() = 0;

    std::string output;


    template <typename Func, typename... Args> // It is posible to add return type typename ReturnType but not realy needed
    std::string execute_command(const std::string& name, Args... args) {
        try {
            auto& holder = command_map.at(name);
            auto func = std::any_cast<std::function<Func>>(holder.function);
            func(std::forward<Args>(args)...);
        } catch (const std::bad_any_cast& e) {
            std::cout << "Bad any cast: " << e.what() << std::endl;
        } catch (const std::out_of_range&) {
            std::cout << "Function not found: " << name << std::endl;
            output = "Input valid command\n";
        }
        return output;
    }


    template <typename Func>
    void add_function(const std::string& name, const std::string& description, Func func) {
        command_map[name] = FunctionHolder{description, std::function(func)};
    }
};