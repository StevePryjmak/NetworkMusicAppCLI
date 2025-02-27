#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <tuple>
#include <map>
#include <unordered_map>
#include <Networking/server/SongLib/Playlist.h>
#include <Networking/server/DatabaseLib/database.h>
#include <type_traits>
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
    std::vector<Playlist> playlists;
    Playlist favorite_playlist;
    unsigned int id_index = 0;
    unsigned int login_index = 0;

    std::map<int, FunctionHolder> command_map;
    Playlist database_temp;
    void virtual initialize_commands() = 0;
public:
    virtual ~VirtualUser() = default;

    virtual std::string get_option() = 0;
    virtual void log_out() = 0;
    virtual void show_playlists() = 0;
    virtual void generate_random_playlist(int number_of_songs) = 0;
    virtual void favorites() = 0;
    virtual void add_favorite_song(std::string name) = 0;
    virtual std::string my_profile() = 0;
    virtual  void delete_playlist(std::string palylist_name) = 0;
    virtual void create_playlist(std::string playlist_name) = 0;
    virtual void add_song_to_playlist(std::string playlist_name, std::string song_name) = 0;
    virtual void show_songs_from_database() = 0;
    virtual void show_songs_from_datbase_privious() = 0;
    virtual void help() = 0;

    virtual void become_artist() = 0;
    virtual void load_playlists(std::vector<Playlist> playlists) = 0;
    virtual void load_favorites_playlist(Playlist favorite_playlist) = 0;
    virtual void load_my_songs(Playlist my_songs) = 0;

    std::string output;
    std::string curent_menu;


    template <typename Func, typename... Args>
    std::string execute_command(int key, Args... args);

    template <typename Func>
    void add_function(int key, const std::string& description, Func func);
};






template <typename Func, typename... Args> // It is posible to add return type typename ReturnType but not realy needed
std::string VirtualUser::execute_command(int key, Args... args) {
    try {
        auto& holder = command_map.at(key);
        auto func = std::any_cast<std::function<Func>>(holder.function);
        if constexpr (std::is_same_v<std::invoke_result_t<std::function<Func>, Args...>, std::string>) {
            output = func(std::forward<Args>(args)...);
        } else {
            func(std::forward<Args>(args)...);
        }
    } catch (const std::bad_any_cast& e) {
        std::cout << "Bad any cast: " << e.what() << std::endl;
    } catch (const std::out_of_range&) {
        std::cout << "Function not found: " << name << std::endl;
        output = "Input valid command\n";
    }
    return output;
}


template <typename Func>
void VirtualUser::add_function(int key, const std::string& description, Func func) {
    command_map[key] = FunctionHolder{description, std::function(func)};
}