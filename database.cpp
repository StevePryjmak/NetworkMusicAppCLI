#include "database.h"
#include <filesystem>

/*
* Directories
* 
* root
* |
* |-|users
* |	|
* | |-|{user.login}
* |   |
* |   |-|userPlaylists
* |   | |
* |	  | |{playlistId1}.txt
* |   | |{playlistId2}.txt
* |   |
* |   |credentials.txt
* |
* |-|public
* | |
* | |-|songs
* | | |
* | | |-|{songId}
* | |   |
* | |   |info.txt
*/

/*
* Playlist
* 
* {playlistId1}.txt - coma separated songIds
* 
*/

bool PlaylistDataInterface::isValidNewName(const std::string& name, const std::string& login) const noexcept {
	if (!existName(name, login))
		return false;
	if (name.empty() && name.size() > 50)
		return false;
	for (char c : name) {
		if (!std::isalnum(static_cast<unsigned char>(c))) {
			return false;
		}
	}
	return true;
}

bool PlaylistDataInterface::existName(const std::string& name, const std::string& login) const noexcept {
	std::ifstream file("User/playlist/" + name);//////////////////////
	if (file.is_open())
	{
		file.close();
		return true;
	}
	else
		return false;
}
bool PlaylistDataInterface::findName(const std::string& name, const std::string& login) const noexcept {

}
void PlaylistDataInterface::savePlaylist(const Playlist& playlist,const std::string& login) const {

}
void PlaylistDataInterface::deletePlaylist(const std::string& name,const std::string& login) const {

}
Playlist PlaylistDataInterface::loadPlaylist(const std::string& name,const std::string& login) const {

}

/*
* User
* 
* login must be uniqe
* 
* credentials.txt
*	{name} 
*   {password} 
*   {accessLevel}
*	{description} 
*/

std::string UserDataInterface::getPassword(const std::string& login) const {
	if (!findLogin(login)) {
		throw std::exception("Invalid login");
	}
	return "HiszpañskaInkwizycja1@";
}

bool UserDataInterface::findLogin(const std::string& login) const noexcept {
	return true;
}

bool UserDataInterface::isValidPassword(const std::string& password) const noexcept {

}

bool UserDataInterface::existLogin(const std::string& login) const noexcept {
	std::ifstream file("Users/" + login);
	if (file.is_open())
	{
		file.close();
		return true;
	}
	else
		return false;
}

bool UserDataInterface::isValidNewLogin(const std::string& login) const noexcept {
	if (existLogin(login))
		return false;
	if (login.empty() && login.size() > 50)
		return false;
	for (char c : login) {
		if (!std::isalnum(static_cast<unsigned char>(c))) {
			return false;
		}
	}
	return true;
}
bool UserDataInterface::isValidName(const std::string& name) const noexcept {
	return true;
}

void UserDataInterface::addUser(const std::string& name, const std::string& login, const std::string& password) const {
	if (!isValidName(name) || !isValidNewLogin(login) || !isValidPassword(password)) {
		throw std::exception("Invalid Credentials");
	}
	//create folder
}
void UserDataInterface::deleteUser(const std::string& login) const {
	if (!findLogin(login)) {
		throw std::exception("Invalid login");
	}
}
void UserDataInterface::changeName(const std::string& login, const std::string& name) const {
	if (!findLogin(login)) {
		throw std::exception("Invalid login");
	}
	if (!isValidName(name)) {
		throw std::exception("Invalid name");
	}
	//change name
}

void UserDataInterface::changePassword(const std::string& login, const std::string& oldPass, const std::string& newPass) const {
	if (getPassword(login) == generateHash(oldPass)) {
		throw std::exception("Invalid credentials");
	}
	if (!isValidPassword(newPass)) {
		throw std::exception("Invalid password");
	}
	//change name
}
	
void UserDataInterface::changeAccessLevel(const std::string& login, int newAccessLevel) const {
	if (!findLogin(login)){
		throw std::exception("Invalid login");
	}
	//change accesslevel
}

virtualUser* UserDataInterface::loadUser(const std::string& login) const {

}
/*
* Song
* 
* info.txt
*	{name}
*	{artist}
*	{genre}
*	{duration}
*	{year}
*	{file path}
*/

bool SongDataInterface::existName(const std::string& name) const noexcept
{
	std::ifstream file("public/song/" + name);
	if (file.is_open())
	{
		file.close();
		return true;
	}
	else
		return false;
}

bool SongDataInterface::isValidNewName(const std::string& name) const noexcept {
	if (existName(name))
		return false;
	if (name.empty() && name.size() > 50)
		return false;
	for (char c : name) {
		if (!std::isalnum(static_cast<unsigned char>(c))) {
			return false;
		}
	}
	return true;
}


bool SongDataInterface::findName(const std::string& name) const noexcept
{
	return false;
}

void SongDataInterface::saveSong(const Song& song) const
{
}

void SongDataInterface::deleteSong(const std::string& name) const
{
}

Song SongDataInterface::loadSong(const std::string& name) const
{
	return Song();
}

std::string generateHash(const std::string& password) noexcept {

}