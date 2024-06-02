#pragma once
#include <string>
#include <exception>
#include <vector>
#include "song.h"
#include "playlist.h"

class PlaylistDataInterface {
private:
	bool isValidName(const std::string name) const noexcept;
	bool findName(const std::string name) const noexcept;
public:
	void savePlaylist(const Playlist& playlist) const;
	void deletePlaylist(const std::string name) const;
	Playlist loadPlaylist(const std::string name) const;
};

class UserDataInterface {
private:
	std::string generateHash(const std::string& password) const noexcept;
	std::string getPassword(const std::string& login) const;
	bool findLogin(const std::string& login) const noexcept;
	bool isValidPassword(const std::string& password) const noexcept;
	bool isValidLogin(const std::string& login) const noexcept;
	bool isValidNewLogin(const std::string& login) const noexcept;
	bool isValidName(const std::string& name) const noexcept;
public:
	void addUser(const std::string& name, const std::string& login, const std::string& password) const;
	void deleteUser(const std::string login) const;
	void changeName(const std::string& login, const std::string& name) const;
	void changePassword(const std::string& login, const std::string& oldPass, const std::string& newPass) const;
	void changeAccessLevel(const std::string login, int newAccessLevel) const;
	virtualUser* loadUser(const std::string login) const;
};

class SongDataInterface {
private:
	bool isValidName(const std::string name) const noexcept;
	bool findName(const std::string name) const noexcept;
public:
	void saveSong(const Song& song) const;
	void deleteSong(const std::string name) const;
	Song loadSong(const std::string name) const;
};