#pragma once
#include <string>
#include <exception>
#include <vector>
#include <fstream>
#include <Networking/server/SongLib/Song.h>
#include <Networking/server/SongLib/Playlist.h>
#include <Networking/server/UserLib/User.h>
#include <iostream>
#include <filesystem>
#include <sstream>

class SongDataInterface {
private:
	bool existId(unsigned int id) const noexcept;
public:
	void saveSong(const Song& song) const;
	void deleteSong(unsigned int id) const;
	Song loadSong(unsigned int id) const;
};


class PlaylistDataInterface: public SongDataInterface {
private:
	bool existName(const std::string& name, const std::string& login) const noexcept;
	bool isValidNewName(const std::string& name, const std::string& login) const noexcept;
public:
	void savePlaylist(Playlist& playlist, const std::string& login);
	void deletePlaylist(const std::string& name, const std::string& login) const;
	Playlist loadPlaylist(const std::string& name, const std::string& login) const;
};

class UserDataInterface {
private:
	std::string getPassword(const std::string& login) const;
	bool isValidPassword(const std::string& password) const noexcept;
	bool existLogin(const std::string& login) const noexcept;
	bool isValidNewLogin(const std::string& login) const noexcept;
	bool isValidName(const std::string& name) const noexcept;
public:
	void addUser(const std::string& name, const std::string& login, const std::string& password, unsigned int privilageLevel) const;
	void deleteUser(const std::string& login) const;
	void changeAccessLevel(const std::string& login, int newAccessLevel) const;
};

std::string generateHash(const std::string& password) noexcept;