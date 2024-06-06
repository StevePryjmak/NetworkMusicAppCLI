#include <Networking/server/SongLib/Playlist.h>

void Playlist::addToPlaylist(Song song) noexcept
{
	Playlist::playlist.push_back(song);
	Playlist::duration += song.getDuration();
}

Playlist::PlaylistIterator Playlist::begin() const
{
	return PlaylistIterator(playlist.begin(), this);
}

Playlist::PlaylistIterator Playlist::deleteFromPlaylist(PlaylistIterator i)
{
	Playlist::duration -= (*i).getDuration();
	std::vector<Song>::const_iterator j = Playlist::playlist.erase(i.curr);
	return PlaylistIterator(j, this, i.shuffle);
}

Playlist::PlaylistIterator Playlist::deleteFromPlaylist(unsigned int i)
{
	PlaylistIterator it = begin() + i;
	return this->deleteFromPlaylist(it);
}

Playlist::PlaylistIterator Playlist::end() const
{
	return PlaylistIterator(playlist.end(), this);
}

Playlist::Playlist(std::string name)
{
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
	while (i != end()) {
		description += (std::to_string(count) + ". ");
		description += (*i).getDescription();
		description += "\n";
		count++;
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
	current = begin();
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
	std::cout << (*current).getDescription() << "\n";
}

void Playlist::show() const noexcept
{
	std::cout << getPlaylist();
}
bool Playlist::PlaylistIterator::operator==(PlaylistIterator const& i) const noexcept
{
	return curr == curr;
}

bool Playlist::PlaylistIterator::operator!=(PlaylistIterator const& i) const noexcept
{
	return curr != curr;
}
