#pragma once
#include <string>
//#include "Playlist.h"
class Song
{
private:
	unsigned int id;
	std::string name;
	std::string artist; //might add artist id so it is easier to identificate the artist
	std::string genre;
	unsigned int duration; //in seconds
	unsigned int year;
public:
	Song(unsigned int id, std::string name, std::string artist, std::string genre, unsigned int duration, unsigned int year = 2024);
	//Song(unsigned int id, std::string name, Artist* artist, std::string genre, unsigned int duration, unsigned int year); //implement after merging with users classes
	//void addToPlaylist(Playlist p);
	std::string getName() const noexcept;
	std::string getArtist() const noexcept;
	std::string getGenre() const noexcept;
	std::string getDescription() const noexcept;
	unsigned int getDuration() const noexcept;
	std::string formatDuration() const noexcept;
	unsigned int getYear() const noexcept;
	unsigned int getId() const noexcept;
};

