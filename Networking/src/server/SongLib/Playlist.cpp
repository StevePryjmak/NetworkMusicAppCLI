#include <Networking/server/SongLib/Playlist.h>


void Playlist::addToPlaylist(Song song) noexcept
{
	Playlist::playlist.push_back(song);
	Playlist::duration += song.getDuration();
	current = begin();
}

Playlist::PlaylistIterator Playlist::begin() const
{
	return PlaylistIterator(playlist.cbegin(), this);
}

Playlist::PlaylistIterator Playlist::deleteFromPlaylist(PlaylistIterator i)
{
	Playlist::duration -= (*i).getDuration();
	Playlist::playlist.erase(i.curr);
	return begin();
}

Playlist::PlaylistIterator Playlist::deleteFromPlaylist(unsigned int i)
{
	PlaylistIterator it = begin() + i;
	return this->deleteFromPlaylist(it);
}

Playlist::PlaylistIterator Playlist::end() const
{
	return PlaylistIterator(playlist.cend(), this);
}

Song Playlist::getCurrent()
{
	if (current != end())
    	return *current;
	else
	return Song(0, "", "", "", 0, 0);
}
Playlist::Playlist(std::string name)
{
	current = begin();
	Playlist::name = name;
}

std::string Playlist::getName() const noexcept
{
	return Playlist::name;
}

std::string Playlist::getPlaylist() const noexcept
{
	std::string description = "";
	unsigned int count = 1;
	PlaylistIterator i = begin();
	while (i != Playlist::end()) {
		description += (std::to_string(count) + ". ");
		description += (*i).getDescription();
		description += "\n";
		++i;
		++count;
	}
	return description;
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

std::string Playlist::getDescription() const noexcept
{
	std::string res = getName();
	res += " | ";
	res += formatDuration();
    return res;
}

void Playlist::play() noexcept
{
	if (current == end()){
		std::cout << "Playlist ended\n";
	}
	else
		std::cout << (*current).getDescription() << "\n";
}

void Playlist::shuffle() noexcept
{
	current.shufflePlaylist();
}

void Playlist::unshuffle() noexcept
{
	current.unshufflePlaylist();
}

void Playlist::skip() noexcept
{
	++current;
	if (current == end()){
		current = begin();
		std::cout << "Playlist ended, Starting form beginig\n";
	}
	else
		std::cout << (*current).getDescription() << "\n";
}

void Playlist::show() const noexcept
{
	std::cout << getPlaylist();
}

 void Playlist::deleteSong(unsigned int i)
{
	current = deleteFromPlaylist(i-1);
}

/*void Playlist::addSong(Song song) noexcept
{
	current = addToPlaylist(song);
}*/

bool Playlist::PlaylistIterator::operator==(PlaylistIterator const& i) const noexcept
{
	return curr == i.curr;
}

bool Playlist::PlaylistIterator::operator!=(PlaylistIterator const& i) const noexcept
{
	return curr != i.curr;
}
