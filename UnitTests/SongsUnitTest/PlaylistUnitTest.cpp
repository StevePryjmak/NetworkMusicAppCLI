#include "gtest/gtest.h"
#include <stdexcept>
#include <Networking/server/SongLib/Song.h>
#include <Networking/server/SongLib/Playlist.h>

TEST(PlaylistTestConstructor, EmptyPlaylist) {
	Playlist p("MyPlaylist");
	EXPECT_EQ(p.getName(), "MyPlaylist");
	EXPECT_EQ(p.getDuration(), 0);
	EXPECT_EQ(p.formatDuration(), "0:00");
}

TEST(PlaylistTestConstructor, CurrentAssignment) {
	Playlist p("MyPlaylist");
	p.play();
	p.skip();
	EXPECT_EQ(p.getCurrent().getName(), "unknown");
}

TEST(PlaylistTestAddToPlaylist, AddToPlaylistOneSong) {
	Playlist p("MyPlaylist");
	EXPECT_EQ(p.getName(), "MyPlaylist");
	EXPECT_EQ(p.getDuration(), 0);
	EXPECT_EQ(p.formatDuration(), "0:00");
	Song s(1, "Black Celebration", "Depeche Mode", "Synth pop", 297, 1986);
	p.addToPlaylist(s);
	EXPECT_EQ(p.getDuration(), 297);
	EXPECT_EQ(p.formatDuration(), "4:57");
	auto i = p.begin();
	EXPECT_EQ((*i).getDescription(), "Black Celebration | Depeche Mode | 4:57");
}

TEST(PlaylistTestAddToPlaylist, AddToPlaylistMoreSongs) {
	Playlist p("MyPlaylist");
	EXPECT_EQ(p.getName(), "MyPlaylist");
	EXPECT_EQ(p.getDuration(), 0);
	EXPECT_EQ(p.formatDuration(), "0:00");
	Song s(1, "Black Celebration", "Depeche Mode", "Synth pop", 297, 1986);
	p.addToPlaylist(s);
	EXPECT_EQ(p.getDuration(), 297);
	EXPECT_EQ(p.formatDuration(), "4:57");
	Song s1(2, "The Last Imagination", "Dark Tranquillity", "Death metal", 227);
	Song s2(3, "The Sun Always Shines On T.V.", "a-ha", "Synth pop", 302, 1985);
	p.addToPlaylist(s1);
	EXPECT_EQ(p.getDuration(), 524);
	EXPECT_EQ(p.formatDuration(), "8:44");
	p.addToPlaylist(s2);
	EXPECT_EQ(p.getDuration(), 826);
	EXPECT_EQ(p.formatDuration(), "13:46");

	auto i = p.begin();
	EXPECT_EQ((*i).getDescription(), "Black Celebration | Depeche Mode | 4:57");
	EXPECT_EQ((*(++i)).getDescription(), "The Last Imagination | Dark Tranquillity | 3:47");
	EXPECT_EQ((*(++i)).getDescription(), "The Sun Always Shines On T.V. | a-ha | 5:02");
}

TEST(PlaylistTestAddToPlaylist, OneSongCurrentAssignment) {
	Playlist p("MyPlaylist");
	EXPECT_EQ(p.getName(), "MyPlaylist");
	EXPECT_EQ(p.getDuration(), 0);
	EXPECT_EQ(p.formatDuration(), "0:00");
	Song s(1, "Black Celebration", "Depeche Mode", "Synth pop", 297, 1986);
	p.addToPlaylist(s);
	EXPECT_EQ(p.getCurrent().getName(), "Black Celebration");
	p.play();
	p.skip();
	EXPECT_EQ(p.getCurrent().getName(), "Black Celebration");
}

TEST(PlaylistGetPlaylist, PlaylistEmpty) {
	Playlist p("MyPlaylist");
	EXPECT_EQ(p.getPlaylist(), "");
}

TEST(PlaylistGetPlaylist, PlaylistNotEmpty) {
	Playlist p("MyPlaylist");
	EXPECT_EQ(p.getName(), "MyPlaylist");
	EXPECT_EQ(p.getDuration(), 0);
	EXPECT_EQ(p.formatDuration(), "0:00");
	Song s(1, "Black Celebration", "Depeche Mode", "Synth pop", 297, 1986);
	Song s1(2, "The Last Imagination", "Dark Tranquillity", "Death metal", 227);
	p.addToPlaylist(s);
	p.addToPlaylist(s1);
	EXPECT_EQ(p.getPlaylist(), "1. Black Celebration | Depeche Mode | 4:57\n2. The Last Imagination | Dark Tranquillity | 3:47\n");
}

TEST(PlaylistTestAddToPlaylist, AddSongCurrentTest) {
	Playlist p("MyPlaylist");
	EXPECT_EQ(p.getName(), "MyPlaylist");
	EXPECT_EQ(p.getDuration(), 0);
	EXPECT_EQ(p.formatDuration(), "0:00");
	Song s(1, "Black Celebration", "Depeche Mode", "Synth pop", 297, 1986);
	Song s1(2, "The Last Imagination", "Dark Tranquillity", "Death metal", 227);
	Song s2(3, "The Sun Always Shines On T.V.", "a-ha", "Synth pop", 302, 1985);
	//EXPECT_THROW(p.getCurrent(), std::range_error);
	p.addToPlaylist(s);
	EXPECT_EQ(p.getCurrent().getDescription(), "Black Celebration | Depeche Mode | 4:57");
	p.addToPlaylist(s1);
	p.skip();
	EXPECT_EQ(p.getCurrent().getDescription(), "The Last Imagination | Dark Tranquillity | 3:47");
}

TEST(PlaylistTestDeleteFromPlaylist, DeleteFromBegginingOfPlaylistByIterator) {
	Playlist p("MyPlaylist");
	Song s(1, "Black Celebration", "Depeche Mode", "Synth pop", 297, 1986);
	Song s1(2, "The Last Imagination", "Dark Tranquillity", "Death metal", 227);
	Song s2(3, "The Sun Always Shines On T.V.", "a-ha", "Synth pop", 302, 1985);
	p.addToPlaylist(s);
	p.addToPlaylist(s1);
	p.addToPlaylist(s2);
	EXPECT_EQ(p.getDuration(), 826);
	EXPECT_EQ(p.formatDuration(), "13:46");
	p.deleteFromPlaylist(p.begin());
	auto i = p.begin();
	EXPECT_EQ((*i).getDescription(), "The Last Imagination | Dark Tranquillity | 3:47");
	EXPECT_EQ(p.getDuration(), 529);
	EXPECT_EQ(p.formatDuration(), "8:49");
}

TEST(PlaylistTestDeleteFromPlaylist, DeleteByIteartorTypical) {
	Playlist p("MyPlaylist");
	Song s(1, "Black Celebration", "Depeche Mode", "Synth pop", 297, 1986);
	Song s1(2, "The Last Imagination", "Dark Tranquillity", "Death metal", 227);
	Song s2(3, "The Sun Always Shines On T.V.", "a-ha", "Synth pop", 302, 1985);
	p.addToPlaylist(s);
	p.addToPlaylist(s1);
	p.addToPlaylist(s2);
	EXPECT_EQ(p.getDuration(), 826);
	EXPECT_EQ(p.formatDuration(), "13:46");
	p.deleteFromPlaylist(p.begin()+1);
	auto i = p.begin();
	EXPECT_EQ((*i).getDescription(), "Black Celebration | Depeche Mode | 4:57");
	EXPECT_EQ((*(++i)).getDescription(), "The Sun Always Shines On T.V. | a-ha | 5:02");
	EXPECT_EQ(p.getDuration(), 599);
	EXPECT_EQ(p.formatDuration(), "9:59");
}

TEST(PlaylistTestDeleteSong, DeleteSongCurrentChanges) {
	Playlist p("MyPlaylist");
	Song s(1, "Black Celebration", "Depeche Mode", "Synth pop", 297, 1986);
	Song s1(2, "The Last Imagination", "Dark Tranquillity", "Death metal", 227);
	Song s2(3, "The Sun Always Shines On T.V.", "a-ha", "Synth pop", 302, 1985);
	p.addToPlaylist(s);
	p.addToPlaylist(s1);
	p.addToPlaylist(s2);
	p.deleteSong(1);
	EXPECT_EQ(p.getCurrent().getDescription(), "The Last Imagination | Dark Tranquillity | 3:47");
	p.skip();
	EXPECT_EQ(p.getCurrent().getDescription(), "The Sun Always Shines On T.V. | a-ha | 5:02");
}

TEST(PlaylistTestPlaySkip, PlaySkipTypical) {
	Playlist p("MyPlaylist");
	Song s(1, "Black Celebration", "Depeche Mode", "Synth pop", 297, 1986);
	Song s1(2, "The Last Imagination", "Dark Tranquillity", "Death metal", 227);
	Song s2(3, "The Sun Always Shines On T.V.", "a-ha", "Synth pop", 302, 1985);
	p.addToPlaylist(s);
	p.addToPlaylist(s1);
	p.addToPlaylist(s2);
	EXPECT_EQ(p.getCurrent().getName(), "Black Celebration");
	p.skip();
	EXPECT_EQ(p.getCurrent().getName(), "The Last Imagination");
	p.play();
	EXPECT_EQ(p.getCurrent().getName(), "The Last Imagination");
	p.skip();
	p.skip();
	p.play();
	EXPECT_EQ(p.getCurrent().getName(), "Black Celebration");
}