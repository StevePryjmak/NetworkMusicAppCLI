#include "gtest/gtest.h"
#include <stdexcept>
#include <Networking/server/SongLib/Song.h>
#include "stdlib.h"

TEST(SongTestConstructor, TypicalConstructor) {
	Song s(1, "Black Celebration", "Depeche Mode", "Synth pop", 297, 1986);
	EXPECT_EQ(s.getName(), "Black Celebration");
	EXPECT_EQ(s.getArtist(), "Depeche Mode");
	EXPECT_EQ(s.getGenre(), "Synth pop");
	EXPECT_EQ(s.getDuration(), 297);
	EXPECT_EQ(s.formatDuration(), "4:57");
	EXPECT_EQ(s.getYear(), 1986);
}

TEST(SongTestConstructor, ConstructorWOYear) {
	Song s(1, "The Last Imagination", "Dark Tranquillity", "Death metal", 227);
	EXPECT_EQ(s.getName(), "The Last Imagination");
	EXPECT_EQ(s.getArtist(), "Dark Tranquillity");
	EXPECT_EQ(s.getGenre(), "Death metal");
	EXPECT_EQ(s.getDuration(), 227);
	EXPECT_EQ(s.formatDuration(), "3:47");
	EXPECT_EQ(s.getYear(), 2024);
}

TEST(SongTestConstructor, ConstructorNameNotGiven) {
	EXPECT_THROW(Song(0, "", "a", "a", 222, 222), std::invalid_argument);
}

TEST(SongTestConstructor, ConstructorArtistNotGiven) {
	EXPECT_THROW(Song(0, "a", "", "a", 222, 222), std::invalid_argument);
}

TEST(SongTestDescription, TypicalDescription) {
	Song s(1, "The Sun Always Shines On T.V.", "a-ha", "Synth pop", 302, 1985);
	EXPECT_EQ(s.getName(), "The Sun Always Shines On T.V.");
	EXPECT_EQ(s.getArtist(), "a-ha");
	EXPECT_EQ(s.getGenre(), "Synth pop");
	EXPECT_EQ(s.getDuration(), 302);
	EXPECT_EQ(s.formatDuration(), "5:02");
	EXPECT_EQ(s.getYear(), 1985);
	EXPECT_EQ(s.getDescription(), "The Sun Always Shines On T.V. | a-ha | 5:02");
}

TEST(SongTestLyrics, LyricsGetDefaultLyrics) {
	Song s(1, "The Sun Always Shines On T.V.", "a-ha", "Synth pop", 302, 1985);
	EXPECT_EQ(s.getLyrics(), "Sorry, we don't know the lyrics.");
}

TEST(SongTestLyrics, LyricsAddLyrics) {
	Song s(1, "The Sun Always Shines On T.V.", "a-ha", "Synth pop", 302, 1985);
	EXPECT_EQ(s.getLyrics(), "Sorry, we don't know the lyrics.");
	s.addLyrics("Believe me, the sun always shines on T.V.");
	EXPECT_EQ(s.getLyrics(), "Believe me, the sun always shines on T.V.");
	s.addLyrics("Hold me close to your heart.");
	EXPECT_EQ(s.getLyrics(), "Hold me close to your heart.");
}
