#include "Playlist.h"

void Playlist::addToPlaylist(Song song) noexcept
{
	Playlist::playlist.push_back(song);
}

Playlist::PlaylistIterator Playlist::begin()
{
	return PlaylistIterator(playlist.begin(), this);
}

Playlist::PlaylistIterator Playlist::deleteFromPlaylist(PlaylistIterator i)
{
	std::vector<Song>::const_iterator j = Playlist::playlist.erase(i.curr);
	return PlaylistIterator(j, this, i.shuffle);
}

Playlist::PlaylistIterator Playlist::end()
{
	return PlaylistIterator(playlist.end(), this);
}
