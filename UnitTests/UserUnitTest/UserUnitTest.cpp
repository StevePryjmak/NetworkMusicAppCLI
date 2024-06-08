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
    res += "1. My_profile\n2. Show Playlists\n3. Favorites\n4. Become an Artist\n5. Log Out\n";
    res += "6. Generate Random Playlist(Input number of Songs and Genre(not required))\n";
    res += "7. Delete Playlist (Input playlist name)\n8. Add Favorite Song (Input song name)\n";
    res += "9. Create Playlist (Input playlist name)\n10. Add Song to Playlist (Input playlist name and song name)\n";
    EXPECT_EQ(u.get_option(), res);
}

TEST (UserTestGetOption, GetOptionPlaylistMap) {
    User u("name", "login", "password");
    u.show_playlists();
    std::string res ="0. Back to main menu\n";
    EXPECT_EQ(u.get_option(), res);
}