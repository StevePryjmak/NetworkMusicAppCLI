#include <Networking/server/SongLib/Song.h>
#include "stdexcept"

Song::Song(unsigned int id, std::string name, std::string artist, std::string genre, unsigned int duration, unsigned int year)
{
	Song::id = id;
	if (not name.length()) {
		throw std::invalid_argument("Name cannot be empty");
	}
	Song::name = name;
	if (not artist.length()) {
		throw std::invalid_argument("Artist cannot be empty");
	}
	Song::artist = artist;
	Song::genre = genre;
	Song::duration = duration;
	Song::year = year;
}

std::string Song::getName() const noexcept
{
	return Song::name;
}

std::string Song::getArtist() const noexcept
{
	return Song::artist;
}

/*void Song::addToPlaylist(Playlist p)
{
	p.addToPlaylist(*this);
}*/

std::string Song::getGenre() const noexcept 
{
	return Song::genre;
}

std::string Song::getDescription() const noexcept
{
	std::string description = getName() + " | ";
	description += (getArtist()+" | "+formatDuration());
	return description;
}

unsigned int Song::getDuration() const noexcept
{
	return Song::duration;
}


std::string Song::formatDuration() const noexcept
{
	std::string res = "";
	res += std::to_string(Song::duration / 60);
	res += ":";
	if (Song::duration % 60 < 10)
		res += "0";
	res += std::to_string(Song::duration % 60);
	return res;
}

unsigned int Song::getYear() const noexcept
{
	return Song::year;
}