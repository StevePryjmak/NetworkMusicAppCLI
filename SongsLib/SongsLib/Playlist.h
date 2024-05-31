#pragma once
#include "Song.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <stdlib.h>

class Playlist
{
private:
	std::vector<Song> playlist;
	std::string name;
public:
	class PlaylistIterator {
		std::vector<Song>::const_iterator curr;
		bool shuffle;
		Playlist * pl;
	public:
		PlaylistIterator& operator++() {
			if (curr == pl->playlist.end())
				throw std::range_error("Index out of range");
			if (not shuffle)
				curr++;
			else {
				curr = (pl->playlist.begin() + (rand() % pl->playlist.size()));
			}
			return *this;
		}
		Song operator*() {
			if (curr == pl->playlist.end())
				throw std::range_error("Index out of range");
			return *curr;
		}
		PlaylistIterator operator++(int) {
			PlaylistIterator tmp = *this;
			++(*this);
			return tmp;
		}
		PlaylistIterator& operator+=(int a) {
			while (a--) {
				++(*this);
			}
			return *this;
		}
		PlaylistIterator operator+(int a) {
			PlaylistIterator tmp = *this;
			tmp += a;
			return tmp;
		}
		void shufflePlaylist() {
			PlaylistIterator::shuffle = true;
		}
		//bool operator==(PlaylistIterator const& i) const noexcept;
		//bool operator!=(PlaylistIterator const& i) const noexcept;
		friend Playlist;
		private:
		PlaylistIterator(std::vector<Song>::const_iterator curr, Playlist * playlist, bool shuffle=false) {
			PlaylistIterator::curr = curr;
			PlaylistIterator::pl = playlist;
			PlaylistIterator::shuffle = shuffle;
		}

	};
private:
	unsigned int duration = 0;
	PlaylistIterator current;
public:
	PlaylistIterator begin();
	PlaylistIterator end();
	void addToPlaylist(Song song) noexcept;
	PlaylistIterator deleteFromPlaylist(PlaylistIterator i);
};

