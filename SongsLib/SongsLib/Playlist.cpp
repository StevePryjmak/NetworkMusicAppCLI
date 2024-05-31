#include "Playlist.h"

void Playlist::addToPlaylist(Song song) noexcept
{
	Playlist::playlist.push_back(song);
	Playlist::duration += song.getDuration();
}

Playlist::PlaylistIterator Playlist::begin()
{
	return PlaylistIterator(playlist.begin(), this);
}

Playlist::PlaylistIterator Playlist::deleteFromPlaylist(PlaylistIterator i)
{
	Playlist::duration -= (*i).getDuration();
	std::vector<Song>::const_iterator j = Playlist::playlist.erase(i.curr);
	return PlaylistIterator(j, this, i.shuffle);
}

Playlist::PlaylistIterator Playlist::end()
{
	return PlaylistIterator(playlist.end(), this);
}

Playlist::Playlist(std::string name)
{
	Playlist::name = name;
}

std::string Playlist::getName()
{
	return Playlist::name;
}

unsigned int Playlist::getDuration() const noexcept
{
	return Playlist::duration;
}

std::string Playlist::formatDuration() const noexcept
{
	std::string res = "";
	res += std::to_string(Playlist::duration / 60);
	res += ":";
	if (Playlist::duration % 60 < 10)
		res += "0";
	res += std::to_string(Playlist::duration % 60);
	return res;
}
