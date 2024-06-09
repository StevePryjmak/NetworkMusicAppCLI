#include "gtest/gtest.h"
#include <Networking/server/DatabaseLib/database.h>

void clear_directories()
{
    std::filesystem::remove_all("public");
    std::filesystem::remove_all("users");
    std::filesystem::remove("id.txt");
    createDirectories();
}

TEST(SongTest, saveLoadDelete) {
    clear_directories();
    SongDataInterface sdi;
    unsigned int id = 1;
	std::string name = "a a";
	std::string artist = "b b";
	std::string genre = "c c";
	unsigned int duration = 2;
	unsigned int year = 3;
    Song s1 = Song(id, name, artist, genre, duration, year);
    EXPECT_NO_THROW(sdi.saveSong(s1));
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

TEST(SongTest, getRandom) {
    clear_directories();
    SongDataInterface sdi;
    unsigned int id = 1;
	std::string name = "Ostatnie slowa mieszka I";
	std::string artist = "b b";
	std::string genre = "c c";
	unsigned int duration = 8;
	unsigned int year = 992;
    Song s1 = Song(id, name, artist, genre, duration, year);
    Song s2 = Song(2, "notACreativeName", artist, genre, duration, year);
    sdi.saveSong(s1);
    sdi.saveSong(s2);
    unsigned int random = sdi.getRandomSongId();
    EXPECT_TRUE(random == 1 || random == 2);
    sdi.deleteSong(1);
    random = sdi.getRandomSongId();
    EXPECT_TRUE(random == 2);
}

TEST(SongTest, IdIncrement) {
    clear_directories();
    SongDataInterface sdi;
    unsigned int id = sdi.getNextIdAndIncrement();
    EXPECT_EQ(id, 1);
    id = sdi.getNextIdAndIncrement();
    EXPECT_EQ(id, 2);
    SongDataInterface sdi2;
    id = sdi2.getNextIdAndIncrement();
    EXPECT_EQ(id, 3);
}

TEST(SongTest, getEmptyId) {
    clear_directories();
    SongDataInterface sdi;
    unsigned int id = sdi.getNextIdAndIncrement();
	std::string name = "a a";
	std::string artist = "b b";
	std::string genre = "c c";
	unsigned int duration = 2;
	unsigned int year = 3;
    EXPECT_EQ(id, 1);
    Song s1 = Song(id, name, artist, genre, duration, year);
    sdi.saveSong(s1);
    id = sdi.getNextIdAndIncrement();
    EXPECT_EQ(id, 2);
    s1 = Song(id, name, artist, genre, duration, year);
    sdi.saveSong(s1);
    EXPECT_EQ(sdi.getEmptyId(), 3);
    EXPECT_NO_THROW(sdi.deleteSong(2));
    EXPECT_EQ(sdi.getEmptyId(), 2);

}

TEST(UserTest, saveDelete) {
    clear_directories();
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
    clear_directories();
    std::string pass = "abc";
    std::string login = "testuser";
    std::string name = "name";
    unsigned int accessLevel = 0;
    UserDataInterface udi;
    EXPECT_NO_THROW(udi.addUser(name, login, pass, accessLevel));
    udi.changeAccessLevel(login,3);
    std::ifstream file1("users/testuser/credentials.txt");
    std::string pass2;
    file1>>pass2;
    std::string name2;
    file1>>name2;
    unsigned int al;
    file1>>al;
    file1.close();
    EXPECT_EQ(al, 3);
    udi.changeAccessLevel(login,1);
    std::ifstream file2("users/testuser/credentials.txt");
    file2>>pass2;
    file2>>name2;
    file2>>al;
    EXPECT_EQ(al, 1);
    file2.close();
}

TEST(UserTest, validateUserData) {
    clear_directories();
    std::string pass = "abc";
    std::string login = "testuser";
    std::string name = "name";
    unsigned int accessLevel = 0;
    UserDataInterface udi;
    EXPECT_NO_THROW(udi.addUser(name, login, pass, accessLevel));
    EXPECT_TRUE(udi.validUserData(login, pass));
    EXPECT_FALSE(udi.validUserData(login, "letmein"));
    EXPECT_FALSE(udi.validUserData("testuser2", pass));
    EXPECT_FALSE(udi.validUserData("admin", "admin"));
}

TEST(PlaylistTest, saveLoadDelete) {
    clear_directories();
    std::filesystem::create_directories("users/testuser/userPlaylists");
    std::string login = "testuser";
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

TEST(PlaylistTest, getPlaylistsNames) {
    clear_directories();
    std::filesystem::create_directories("users/testuser/userPlaylists");
    std::string login = "testuser";
    PlaylistDataInterface pdi;
    unsigned int id = 1;
	std::string name = "a";
	std::string artist = "b";
	std::string genre = "c";
	unsigned int duration = 2;
	unsigned int year = 3;
    Playlist pl1 = Playlist("a 1");
    Playlist pl2 = Playlist("a 2");
    Playlist pl3 = Playlist("a 3");
    EXPECT_NO_THROW(pdi.savePlaylist(pl1, login));
    EXPECT_NO_THROW(pdi.savePlaylist(pl2, login));
    EXPECT_NO_THROW(pdi.savePlaylist(pl3, login));
    std::vector<std::string> pls = pdi.getPlalistsNames(login);
    EXPECT_EQ(pls[0], "a 1");
    EXPECT_EQ(pls[1], "a 2");
    EXPECT_EQ(pls[2], "a 3");
}
