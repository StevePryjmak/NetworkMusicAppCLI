#include "database.h"
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
* | |
* | |
* | |-|playlists
* | | |
* |	| |{playlistId1}.txt
* | | |{playlistId2}.txt
*/

/*
* Playlist
* 
* {playlistId1}.txt - coma separated songIds
* 
*/

bool PlaylistDataInterface::isValidName(const std::string name) const noexcept {

}
bool PlaylistDataInterface::findName(const std::string name) const noexcept {

}
void PlaylistDataInterface::savePlaylist(const Playlist& playlist) const {

}
void PlaylistDataInterface::deletePlaylist(const std::string name) const {

}
Playlist PlaylistDataInterface::loadPlaylist(const std::string name) const {

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

std::string UserDataInterface::generateHash(const std::string& password) const noexcept {

}

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
	return true;
}

bool UserDataInterface::isValidLogin(const std::string& login) const noexcept {
	return true;
}

bool UserDataInterface::isValidNewLogin(const std::string& login) const noexcept {
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
void UserDataInterface::deleteUser(const std::string login) const {
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
	
void UserDataInterface::changeAccessLevel(const std::string login, int newAccessLevel) const {
	if (!findLogin(login)){
		throw std::exception("Invalid login");
	}
	//change accesslevel
}

virtualUser* UserDataInterface::loadUser(const std::string) const {

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

bool SongDataInterface::isValidName(const std::string name) const noexcept
{
	return false;
}

bool SongDataInterface::findName(const std::string name) const noexcept
{
	return false;
}

void SongDataInterface::saveSong(const Song& song) const
{
}

void SongDataInterface::deleteSong(const std::string name) const
{
}

Song SongDataInterface::loadSong(const std::string name) const
{
	return Song();
}
