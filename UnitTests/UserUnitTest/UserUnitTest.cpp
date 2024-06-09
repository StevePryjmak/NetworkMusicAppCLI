#include "gtest/gtest.h"
#include <stdexcept>
#include <Networking/server/UserLib/User.h>
#include "stdlib.h"
#include <iostream>
#include <sstream>

TEST (UserTestConstructor, TypicalConstructor) {
    User u("name", "login", "password");
    EXPECT_EQ(u.my_profile(), "My profile:\nusername: name\nlogin: login\n");
}

TEST (UserTestConstructor, ConstructorWithSymbols) {
    User u("Name Name", "login2", "password!1");
    EXPECT_EQ(u.my_profile(), "My profile:\nusername: Name Name\nlogin: login2\n");
}

TEST (UserTestGetOption, GetOptionConstructorMap) {
    User u("name", "login", "password");
    std::string res ="";
    res += "1. My profile\n2. Show Playlists\n3. Favorites\n4. Become an Artist\n5. Log Out\n";
    res += "6. Generate Random Playlist(Input number of Songs\n";
    res += "7. Delete Playlist (Input playlist name)\n8. Add Favorite Song (Input song name)\n";
    res += "9. Create Playlist (Input playlist name)\n10. Add Song to Playlist (Input playlist name and song name)\n";
    res += "11. Show Songs from Database\n12. Help\n";
    EXPECT_EQ(u.get_option(), res);
}

TEST (UserTestGetOption, GetOptionPlaylistMap) {
    User u("name", "login", "password");
    u.show_playlists();
    std::string res ="0. Back to main menu\n";
    EXPECT_EQ(u.get_option(), res);
}

TEST(UserTestOutput, ShowPlaylistsOutput) {
    User u("name", "login", "password");
    std::vector<Playlist> pl;
    Song s1(12u, "a", "a", "a", 213u, 1999u);
    Song s2(13u, "b", "b", "b", 213u, 1999u);
    Playlist p("play"), p2("play2");
    p.addToPlaylist(s1);
    p.addToPlaylist(s2);
    p2.addToPlaylist(s2);
    p2.addToPlaylist(s1);
    pl.push_back(p);
    pl.push_back(p2);
    u.load_playlists(pl);
    u.show_playlists();
    EXPECT_EQ(u.output, "Playlists:\n");
}

TEST(UserTestOutput, HelpOutput) {
    User u("name", "login", "password");
    std::string res = "Help:\n";
    res += "To use a command enter number of the command and an argument if needed\nIf the argument has more than one word put it in \"\"\n";
    res += "1. Shows your profile info\n2. Shows your playlist and allows further actions on playlist\n";
    res += "3. Shows your favorite songs\n4. Allows you to become an artist. Changes will be applied after logging out.\n";
    res += "5. Logs you out and saves changes\n6. Generates random playlist. Requires number of songs\n";
    res += "7. Deletes Playlist. Requires name of the playlist\n8. Adds song to favorites. Requires song name\n";
    res += "9. Creates empty playlist. Requires playlist name\n10. Adds song to playlist. Requires playlist name and then song\n";
    res += "11. Shows list of songs in the database\n";
    u.help();
    EXPECT_EQ(u.output, res);
}