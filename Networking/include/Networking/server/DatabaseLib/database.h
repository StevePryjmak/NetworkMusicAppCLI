#pragma once
#include <string>
#include <exception>
#include <vector>
#include <fstream>
#include <Networking/server/SongLib/Song.h>
#include <Networking/server/SongLib/Playlist.h>
#include <Networking/server/UserLib/User.h>
#include <filesystem>
#include <sstream>

class SongDataInterface {
private:
	void loadNextId();
	void saveNextId() const;
	bool existId(unsigned int id) const noexcept;
public:
	static unsigned int nextId;
	SongDataInterface();
	void saveSong(const Song& song) const;                     // TODO save song text also
	void deleteSong(unsigned int id) const;
	Song loadSong(unsigned int id) const;                      // TODO get song text also
	Song loadSong(std::string name) const;
	std::vector<unsigned int> getSongsIds() const noexcept;
	unsigned int getRandomSongId() const;
	unsigned int getRandomSongId(std::string genre) const;  // this and priwiouse function should be merged
	unsigned int getNextIdAndIncrement() noexcept;
	bool songExists(std::string name) const noexcept;
	unsigned int getEmptyId() noexcept;
};


class PlaylistDataInterface: public SongDataInterface {
private:
	bool existName(const std::string& name, const std::string& login) const noexcept;
	bool isValidNewName(const std::string& name, const std::string& login) const noexcept;
public:
	void savePlaylist(Playlist& playlist, const std::string& login);
	void deletePlaylist(const std::string& name, const std::string& login) const;
	Playlist loadPlaylist(const std::string& name, const std::string& login) const;
	std::vector<std::string> getPlalistsNames(const std::string& login) const;
	std::vector<Playlist> getPlaylists(const std::string& login) const;
	Playlist getRandomPlaylist(const std::string& login, int songs_number); // also saves in the database
	Playlist getRandomPlaylist(const std::string& login, int songs_number, std::string genre); // this and priwiouse function should be merged
	bool playlistExists(const std::string& name, const std::string& login) const noexcept;
};	

class UserDataInterface {
private:
	std::string getPassword(const std::string& login) const;
	bool isValidPassword(const std::string& password) const noexcept;
	bool isValidNewLogin(const std::string& login) const noexcept;
	bool isValidName(const std::string& name) const noexcept;
public:
	void addUser(const std::string& name, const std::string& login, const std::string& password, unsigned int privilageLevel) const;
	void deleteUser(const std::string& login) const;
	unsigned int getAccessLevel(const std::string& login) const;
	void changeAccessLevel(const std::string& login, int newAccessLevel) const;
	bool validUserData(const std::string& login, const std::string& password) const noexcept;
	bool existLogin(const std::string& login) const noexcept;
	std::string getUserName(const std::string& login) const;
	std::vector<std::string> getLogins() const noexcept;
};

void createDirectories() noexcept;
std::string generateHash(const std::string& password) noexcept;