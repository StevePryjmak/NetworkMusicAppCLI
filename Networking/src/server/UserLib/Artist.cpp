#include <Networking/server/UserLib/Artist.h>

void Artist::initialize_commands() {
    User::initialize_commands();
    add_function(13, "Add Song (Input: name, genre, lyryks, duration)", std::function<void(std::string, std::string, std::string, int)>(std::bind(&Artist::add_song, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4)));
    add_function(14, "Delete Song (Input: song name)", std::function<void(std::string)>(std::bind(&Artist::delete_song, this, std::placeholders::_1))); // Change declaratoin later
    add_function(15, "Show My Songs", std::function<void()>(std::bind(&Artist::show_my_songs, this)));
}



Artist::Artist(const std::string& name, const std::string& login, const std::string& password) : User(name, login, password) {
    initialize_commands();
}

void Artist::load_my_songs(Playlist my_songs) {this->my_songs = my_songs;};

void Artist::add_song(std::string name, std::string genre, std::string lyrics, int duratoin) {
    PlaylistDataInterface playlist_db;
    Song song(playlist_db.getEmptyId(),name, this->name, genre, lyrics, duratoin);
    playlist_db.saveSong(song);
    my_songs.addToPlaylist(song);
    playlist_db.savePlaylist(my_songs, login);
    output = "You " + name + " song added.";
}

void Artist::delete_song(std::string song_name) {
    PlaylistDataInterface playlist_db;
    if (playlist_db.songExists(song_name) == false) {
        output = "Song " + song_name + " does not exist.";
        return;
    }
    unsigned int id = playlist_db.getSongId(song_name);
    if(playlist_db.checkIfAutorOfSong(name, id) == false) {
        output = "You are not the author of the song " + song_name + ".";
        return;
    }

    playlist_db.deleteSong(id);
    Playlist new_temp_playlist("My_Songs");
    for(auto song : my_songs) {
        if(song.getName() == song_name) {
            continue;
        }
        new_temp_playlist.addToPlaylist(song);
    }
    my_songs = new_temp_playlist;
    playlist_db.savePlaylist(my_songs, login);
    output = "You " + song_name + " song deleted.";
}

void Artist::show_my_songs()  {
    initialize_songs_map(my_songs);
    add_function(0, "Back to main menu", std::function<void()>(std::bind(&Artist::initialize_commands, this)));
}


void Artist::become_artist() {
    output = "You are already an artist";
}