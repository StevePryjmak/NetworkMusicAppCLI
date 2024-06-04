#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <unordered_map>
#include <tuple>
#include <map>
#include <cstdarg>


class VirtualUser {
protected:
    std::string name;
    std::string login;
    std::string password;
    //std::vector<Playlist> playlists; // add when Playlist class will be created

    using FunctionType = std::function<void()>;
    using CommandInfo = std::tuple<std::string, std::string, FunctionType>;

    std::map<std::string, CommandInfo> command_map;

public:
    va_list args;
    std::string output;
    virtual std::string get_option() = 0;
    virtual void log_out() = 0;
    virtual void show_playlists() = 0;
    virtual void generate_random_playlist() = 0;
    virtual void favorites() = 0;
    virtual void my_profile() = 0;
    virtual void delete_playlist() = 0;
    virtual void become_artist() = 0;
    virtual std::string executeCommand(const std::string& command, int args_count, ...) = 0;
};