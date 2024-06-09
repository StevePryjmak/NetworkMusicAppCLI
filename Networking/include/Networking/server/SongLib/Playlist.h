#pragma once
#include "Song.h"
#include <vector>
#include <string>
#include <stdexcept>
#include <stdlib.h>
#include <iostream>
#include <map>
#include <functional>

class Playlist
{

protected:
    using FunctionType = std::function<void()>;
    using CommandInfo = std::tuple<std::string, std::string, FunctionType>;
	std::map<std::string, CommandInfo> command_map;
    void initializeCommands() {
        command_map = {
			{"1", {"Show", "Show contents of the playlist", [this]() { show(); }}},
            {"2", {"Play", "Plays the song", [this]() { play(); }}},
			{"3", {"Skip", "Skip the song", [this]() { skip(); }}},
            {"4", {"Shuffle", "Shuffles playlist", [this]() { shuffle(); }}},
            {"5", {"Unshuffle", "Unshuffles playlist", [this]() { unshuffle(); }}},
			//{"5", {"Delete song", "Deletes song", [this]() { unshuffle(); }}},
        };
    }
private:
	std::vector<Song> playlist;
	std::string name;
public:
	class PlaylistIterator {
		std::vector<Song>::const_iterator curr;
		bool shuffle;
		Playlist const * pl;
	public:
		PlaylistIterator& operator++() {
			if (curr == pl->playlist.end())
				throw std::range_error("Index out of range");
			if (!shuffle)
				++curr;
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
		void unshufflePlaylist() {
			PlaylistIterator::shuffle = false;
		}
		bool operator==(PlaylistIterator const& i) const noexcept;
		bool operator!=(PlaylistIterator const& i) const noexcept;
		friend Playlist;
		private:
		PlaylistIterator(std::vector<Song>::const_iterator curr, Playlist const * playlist, bool shuffle=false) {
			PlaylistIterator::curr = curr;
			PlaylistIterator::pl = playlist;
			PlaylistIterator::shuffle = shuffle;
		}

	};
private:
	unsigned int duration = 0;
	PlaylistIterator current = PlaylistIterator(playlist.begin(), this);
public:
	Playlist() {current = begin();};
	Playlist(std::string name);
	std::string getPlaylist() const noexcept;
	std::string getName() const noexcept;
	PlaylistIterator begin() const;
	PlaylistIterator end() const;
	Song getCurrent();
	void addToPlaylist(Song song) noexcept;
	PlaylistIterator deleteFromPlaylist(PlaylistIterator i);
	PlaylistIterator deleteFromPlaylist(unsigned int i);
	unsigned int getDuration() const noexcept;
	std::string formatDuration() const noexcept;
	std::string getDescription() const noexcept;
	void play() noexcept;
	void shuffle() noexcept;
	void unshuffle() noexcept;
	void skip() noexcept;
	void show() const noexcept;
	void deleteSong(unsigned int i);
	//void addSong(Song song) noexcept;

};

