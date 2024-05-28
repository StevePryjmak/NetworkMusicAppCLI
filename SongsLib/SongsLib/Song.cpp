#include "Song.h"
#include "stdexcept"

Song::Song(unsigned int id, std::string name, std::string artist, std::string style="unknown", unsigned int duration, unsigned int year)
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
	Song::style = style;
	Song::duration = duration;
	Song::year = year;
}

std::string Song::getSongDescription() const noexcept
{
	return getName() + " " + getArtist() + " " + getYear();
}

std::string Song::getName() const noexcept
{
	return Song::name;
}

std::string Song::getArtist() const noexcept
{
	return Song::artist;
}

unsigned int Song::getDuration() const noexcept
{
	return Song::duration;
}

unsigned int Song::getYear() const noexcept
{
	return Song::year;
}
