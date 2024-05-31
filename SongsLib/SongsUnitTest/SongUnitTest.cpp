#include "gtest/gtest.h"
#include <stdexcept>
#include "..\SongsLib\Song.h"
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
