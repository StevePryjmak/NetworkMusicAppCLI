#pragma once
#include <string>
class Song
{
private:
	unsigned int id;
	std::string name;
	std::string artist; //mo¿na zmieniæ na klasê Artist
	std::string style;
	unsigned int duration; //in seconds
	unsigned int year = 2024;
public:
	Song(unsigned int id, std::string name, std::string artist, std::string style="unknown", unsigned int duration, unsigned int year);
	std::string getSongDescription() const noexcept;
	std::string getName() const noexcept;
	std::string getArtist() const noexcept;
	std::string getStyle() const noexcept;
	unsigned int getDuration() const noexcept;
	unsigned int getYear() const noexcept;

};

