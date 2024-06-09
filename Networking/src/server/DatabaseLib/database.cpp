#include <Networking/server/DatabaseLib/database.h>


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
* | | |-|{songId.txt}
* |
* |id.txt
*/

/*
* Playlist
* 
* {playlistId1}.txt - space separated songIds
* 
*/
std::string replaceSpaces(const std::string& str)
{
    std::string result = str;
    for (char& c : result) {
        if (c == ' ') {
            c = '_';
        }
    }
	return result;
}

std::string restoreSpaces(const std::string& str)
{
   std::string result = str;
    for (char& c : result) {
        if (c == '_') {
            c = ' ';
        }
    }
	return result;
}



bool PlaylistDataInterface::isValidNewName(const std::string& name, const std::string& login) const noexcept {
	if (existName(name, login))
		return false;
	if (name.empty() && name.size() > 50)
		return false;
	for (char c : name) {
		if (!(std::isalnum(c)) || c == ' ') {
			return false;
		}
	}
	return true;
}

bool PlaylistDataInterface::existName(const std::string& name, const std::string& login) const noexcept {
	std::ifstream file("Users/" + replaceSpaces(login) + "/userPlaylists/" + replaceSpaces(name)+ ".txt");
	if (file.is_open())
	{
		file.close();
		return true;
	}
	else
		return false;
}

void PlaylistDataInterface::savePlaylist(Playlist& playlist,const std::string& login) {
	std::ofstream file("users/" + replaceSpaces(login) + "/userPlaylists/" + replaceSpaces(playlist.getName())+ ".txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	for(auto i = playlist.begin(); i != playlist.end(); i++)
	{
		file<<(*i).getId()<<" ";
	}
	file<<std::endl;
	file.close();

}
void PlaylistDataInterface::deletePlaylist(const std::string& name, const std::string& login) const {
	if (!std::filesystem::remove("users/" + replaceSpaces(login) + "/userPlaylists/" + replaceSpaces(name)+ ".txt"))
		throw std::runtime_error("Unable to delete file");
}

Playlist PlaylistDataInterface::loadPlaylist(const std::string& name,const std::string& login) const {
	std::ifstream file("users/" + replaceSpaces(login) + "/userPlaylists/" + replaceSpaces(name) + ".txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	Playlist pl = Playlist(name);
	int songId;
	while(file >> songId)
	{
		pl.addToPlaylist(loadSong(songId));
	}
	file.close();
	return pl;
}

std::vector<std::string> PlaylistDataInterface::getPlalistsNames(const std::string& login) const
{
	std::vector<std::string> names;
	if (std::filesystem::is_empty("users/"+login+"/userPlaylists"))
		return names;
	for (const auto& entry : std::filesystem::directory_iterator("users/"+login+"/userPlaylists")) 
	{
        names.push_back(restoreSpaces(entry.path().stem().string()));
    }
	return names;
}


std::vector<Playlist> PlaylistDataInterface::getPlaylists(const std::string& login) const
{
	std::vector<Playlist> playlists;
	std::vector<std::string> names = getPlalistsNames(login);
	for (const std::string& name : names) {
		playlists.push_back(loadPlaylist(name, login));
	}
	return playlists;
}

Playlist PlaylistDataInterface::getRandomPlaylist(const std::string& login, int songs_number)
{
	Playlist pl = Playlist("Random");
	for (int i = 0; i < songs_number; i++) {
		pl.addToPlaylist(loadSong(getRandomSongId()));
	}
	savePlaylist(pl, login);
	return pl;
}

Playlist PlaylistDataInterface::getRandomPlaylist(const std::string& login, int songs_number, std::string genre)
{
	if(genre.empty())
		return getRandomPlaylist(login, songs_number);
	Playlist pl = Playlist("Random_"+ genre);
	for (int i = 0; i < songs_number; i++) {
		pl.addToPlaylist(loadSong(getRandomSongId(genre)));
	}
	savePlaylist(pl, login);
	return pl;
}

bool PlaylistDataInterface::playlistExists(const std::string& name, const std::string& login) const noexcept
{
	std::ifstream file("users/" + replaceSpaces(login) + "/userPlaylists/" + replaceSpaces(name)+ ".txt");
	if (file.is_open())
	{
		file.close();
		return true;
	}
	else
		return false;
}
/*
* User
* 
* login must be uniqe
* 
* credentials.txt
*	{password} {name} {accessLevel}
*/

std::string UserDataInterface::getPassword(const std::string& login) const {
	if (!existLogin(login)) {
		throw std::runtime_error("Invalid login");
	}
	std::ifstream file("users/" + replaceSpaces(login)+"/credentials.txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	std::string pass;
	file>>pass;
	file.close();
	return pass;
}

bool UserDataInterface::isValidPassword(const std::string& password) const noexcept {
	return true;
}

bool UserDataInterface::existLogin(const std::string& login) const noexcept {
	std::ifstream file("users/" + replaceSpaces(login)+"/credentials.txt");
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
		if (!std::isalnum(c)) {
			return false;
		}
	}
	return true;
}
bool UserDataInterface::isValidName(const std::string& name) const noexcept {
	if (name.empty() && name.size() > 50)
		return false;
	for (char c : name) {
		if (!std::isalnum(c)) {
			return false;
		}
	}
	return true;
}

void UserDataInterface::addUser(const std::string& name, const std::string& login, const std::string& password, unsigned int privilageLevele) const {
	if (!isValidName(name) || !isValidNewLogin(login) || !isValidPassword(password)) {
		throw std::runtime_error("Invalid Credentials");
	}
	std::filesystem::create_directories("users/"+ replaceSpaces(login) + "/userPlaylists");
	std::ofstream file("users/" + replaceSpaces(login)+"/credentials.txt");
	std::ofstream favorite("users/" + replaceSpaces(login) + "/userPlaylists/" + "favorites"+ ".txt");
	if (!file.is_open() || !favorite.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	file<<generateHash(password)<<" "<<replaceSpaces(name)<<" "<<privilageLevele<<std::endl;
	file.close();
}

void UserDataInterface::deleteUser(const std::string& login) const {
	if (!std::filesystem::remove_all("users/" + replaceSpaces(login)))
		throw std::runtime_error("Unable to delete file");
}

void UserDataInterface::changeAccessLevel(const std::string& login, int newAccessLevel) const {
	if (!existLogin(login)){
		throw std::runtime_error("Invalid login");
	}
	std::ifstream file("users/" + replaceSpaces(login)+"/credentials.txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	std::string pass;
	file>>pass;
	std::string name;
	file>>name;
	file.close();
	std::ofstream ofile("users/" + replaceSpaces(login)+"/credentials.txt");
	if (!ofile.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	ofile<<pass<<" "<<name<<" "<<newAccessLevel<<std::endl;
	ofile.close();
}

unsigned int UserDataInterface::getAccessLevel(const std::string& login) const {
	if (!existLogin(login)){
		throw std::runtime_error("Invalid login");
	}
	std::ifstream file("users/" + replaceSpaces(login)+"/credentials.txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	std::string pass;
	file>>pass;
	std::string name;
	file>>name;
	unsigned int accessLevel;
	file>>accessLevel;
	file.close();
	return accessLevel;
}

bool UserDataInterface::validUserData(const std::string& login, const std::string& password) const noexcept
{
	std::ifstream file("users/" + replaceSpaces(login) +"/credentials.txt");
	if (!file.is_open())
	{
		return false;
	}
	std::string pass;
	file>>pass;
	file.close();
	return pass==password;
}

std::string UserDataInterface::getUserName(const std::string& login) const
{
	std::ifstream file("users/" + replaceSpaces(login)+"/credentials.txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	std::string name;
	file>>name;
	file>>name;
	file.close();
	return name;
}

std::vector<std::string> UserDataInterface::getLogins() const noexcept
{
	std::vector<std::string> logins;
	if (std::filesystem::is_empty("users"))
		return logins;
	for (const auto& entry : std::filesystem::directory_iterator("users")) 
	{
        logins.push_back(restoreSpaces(entry.path().stem().string()));
    }
	return logins;
}

/*
* Song
* 
* info.txt
*	{name} {artist} {genre} {duration} {year}
*/
unsigned int SongDataInterface::nextId;

SongDataInterface::SongDataInterface()
{
	loadNextId();
}

void SongDataInterface::loadNextId()
{
	std::ifstream file("id.txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	file>>SongDataInterface::nextId;
	file.close();
}
	
void SongDataInterface::saveNextId() const
{
	std::ofstream file("id.txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	file<<SongDataInterface::nextId;
	file.close();
}

bool SongDataInterface::existId(unsigned int id) const noexcept
{
	std::ifstream file("public/songs/" + std::to_string(id) + ".txt");
	if (file.is_open())
	{
		file.close();
		return true;
	}
	else
		return false;
}

void SongDataInterface::saveSong(const Song& song) const
{
	std::ofstream file("public/songs/" + std::to_string(song.getId()) + ".txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	file<<replaceSpaces(song.getName())<<" "<<replaceSpaces(song.getArtist())<<" "<<replaceSpaces(song.getGenre())<<" "
	<<song.getDuration()<<" "<<song.getYear()<<std::endl;
	file.close();
	std::ofstream lyrics("public/lyrics/text" + std::to_string(song.getId()) + ".txt");
	if (!lyrics.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	if (song.getLyrics() == "") return;
	lyrics<<song.getLyrics();
	lyrics.close();
}

void SongDataInterface::deleteSong(unsigned int id) const
{
		if (!std::filesystem::remove("public/songs/" + std::to_string(id) + ".txt"))
			throw std::runtime_error("Unable to delete file");
}

Song SongDataInterface::loadSong(unsigned int id) const
{
	std::ifstream file("public/songs/" + std::to_string(id) + ".txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	std::string name;
	file>>name;
	std::string artist;
	file>>artist;
	std::string genre;
	file>>genre;
	unsigned int duration;
	file>>duration;
	unsigned int year;
	file>>year;
	std::ifstream lyrics("public/lyrics/text" + std::to_string(id) + ".txt");
	std::ostringstream text;
	if (lyrics.is_open())
	{
		text << lyrics.rdbuf();
		lyrics.close();
	}
	Song s = Song(id, restoreSpaces(name), restoreSpaces(artist),
	restoreSpaces(genre), text.str(), duration, year);
	file.close();
	return s;
}

Song SongDataInterface::loadSong(std::string name) const
{
	for (unsigned int id : getSongsIds())
	{
		Song s = loadSong(id);
		if (s.getName() == name)
			return s;
	}
	throw std::runtime_error("Song not found");
}

unsigned int SongDataInterface::getRandomSongId() const
{
	std::vector<unsigned int> ids = getSongsIds();
	return ids[rand()%ids.size()];
}

unsigned int SongDataInterface::getRandomSongId(std::string genre) const
{
	std::vector<unsigned int> ids = getSongsIds();
	std::vector<unsigned int> genreIds;
	for (unsigned int id : ids)
	{
		Song s = loadSong(id);
		if (s.getGenre() == genre)
			genreIds.push_back(id);
	}
	return genreIds[rand()%genreIds.size()];
}

unsigned int SongDataInterface::getNextIdAndIncrement() noexcept
{
	unsigned int tmp = SongDataInterface::nextId++;
	saveNextId();
	return tmp;
}

std::vector<unsigned int> SongDataInterface::getSongsIds() const noexcept
{
	std::vector<unsigned int> ids;
	if (std::filesystem::is_empty("public/songs"))
		return ids;
	for (const auto& entry : std::filesystem::directory_iterator("public/songs")) 
	{
        ids.push_back(std::stoi(entry.path().stem().string()));
    }
	return ids;
}

bool SongDataInterface::songExists(std::string name) const noexcept
{
	for (unsigned int id : getSongsIds())
		if (loadSong(id).getName() == name)
			return true;
	return false;
}

unsigned int SongDataInterface::getEmptyId() noexcept
{
	unsigned int id = 1;
	while(existId(id))
		id++;
	if (id == nextId)
		id = getNextIdAndIncrement();
	return id;
}

unsigned int SongDataInterface::getSongId(std::string name) const {
	for (unsigned int id : getSongsIds())
	{
		Song s = loadSong(id);
		if (s.getName() == name)
			return id;
	}
	throw std::runtime_error("Song not found");
}
bool SongDataInterface::checkIfAutorOfSong(std::string artist_name, unsigned int song_id) const {
	std::ifstream file("public/songs/" + std::to_string(song_id) + ".txt");
	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open file");
	}
	std::string name;
	file>>name;
	file>>name;
	file.close();
	return name == artist_name;

}

void createDirectories() noexcept
{
	std::filesystem::create_directories("public/songs");
	std::filesystem::create_directories("public/lyrics");
	std::filesystem::create_directories("users");
	std::ifstream f("id.txt");
	if (!f.is_open())
	{
		std::ofstream file("id.txt");
		file<<"1"<<std::endl;
	}
	f.close();
}

std::string generateHash(const std::string& password) noexcept 
{
	return password;
}

