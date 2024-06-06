#include "gtest/gtest.h"
#include <Networking/server/DatabaseLib/database.h>

TEST(SongTest, saveLoadDelete) {
    std::filesystem::create_directories("public/songs");
    std::filesystem::remove("public/songs/1.txt");
    SongDataInterface sdi;
    unsigned int id = 1;
	std::string name = "a a";
	std::string artist = "b b";
	std::string genre = "c c";
	unsigned int duration = 2;
	unsigned int year = 3;
    Song s1 = Song(id, name, artist, genre, duration, year);
    sdi.saveSong(s1);
    Song s2 = sdi.loadSong(1);
    EXPECT_EQ(s2.getId(), id);
    EXPECT_EQ(s2.getName(), name);
    EXPECT_EQ(s2.getArtist(), artist);
    EXPECT_EQ(s2.getGenre(), genre);
    EXPECT_EQ(s2.getDuration(), duration);
    EXPECT_EQ(s2.getYear(), year);
    sdi.deleteSong(1);
    EXPECT_THROW(sdi.loadSong(1), std::runtime_error);
}

TEST(UserTest, saveDelete) {
    std::filesystem::remove_all("users/testuser");
    std::filesystem::create_directories("users");
    std::string pass = "abc";
    std::string login = "testuser";
    std::string name = "name";
    unsigned int accessLevel = 0;
    UserDataInterface udi;
    EXPECT_NO_THROW(udi.addUser(name, login, pass, accessLevel));
    std::ifstream file("users/testuser/credentials.txt");
    std::string pass2;
    file>>pass2;
    std::string name2;
    file>>name2;
    unsigned int al;
    file>>al;
    file.close();
    EXPECT_EQ(pass, pass2);
    EXPECT_EQ(name, name2);
    EXPECT_EQ(al, accessLevel);
    EXPECT_NO_THROW(udi.deleteUser("testuser"));
}

TEST(UserTest, changeAccessLevel) {
    EXPECT_TRUE(true);
}

TEST(PlaylistTest, saveLoadDelete) {
    std::string login = "testuser";
    std::filesystem::create_directories("public/songs");
    std::filesystem::create_directories("users/testuser/userPlaylists");
    PlaylistDataInterface pdi;
    unsigned int id = 1;
	std::string name = "a";
	std::string artist = "b";
	std::string genre = "c";
	unsigned int duration = 2;
	unsigned int year = 3;
    Song s1 = Song(id, name, artist, genre, duration, year);
    pdi.saveSong(s1);
    Playlist pl = Playlist("a a");
    pl.addToPlaylist(s1);
    EXPECT_NO_THROW(pdi.savePlaylist(pl, login));
    Playlist pl2 = pdi.loadPlaylist("a a", login);
    EXPECT_EQ(pl2.getName(), pl.getName());
    EXPECT_EQ(pl2.getPlaylist(), pl.getPlaylist());
    EXPECT_NO_THROW(pdi.deletePlaylist("a a", login));
    EXPECT_THROW(pdi.loadPlaylist("a a", login), std::runtime_error);
}