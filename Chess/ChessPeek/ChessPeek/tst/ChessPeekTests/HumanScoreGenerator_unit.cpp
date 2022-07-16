#include <ChessPeek/HumanScoreGenerator.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

TEST(HumanScoreGeneratorTest, GetHumanScoreWorks) {
    Board board(BoardOrientation::BlackUpWhiteDown);
    BoardWithContext boardWithContext(PieceColor::White, board);
    HumanScoreGenerator humanScoreGenerator(boardWithContext, 52, -127);

    EXPECT_EQ(0x00015483U, humanScoreGenerator.getHumanScore({{{6, 7}, {5, 5}}, 52, 0}));
    EXPECT_EQ(0x00013512U, humanScoreGenerator.getHumanScore({{{3, 6}, {3, 4}}, 52, 0}));
    EXPECT_EQ(0x00013522U, humanScoreGenerator.getHumanScore({{{4, 6}, {4, 4}}, 49, 0}));
    EXPECT_EQ(0x000134E2U, humanScoreGenerator.getHumanScore({{{2, 6}, {2, 4}}, 39, 0}));
    EXPECT_EQ(0x00013452U, humanScoreGenerator.getHumanScore({{{6, 6}, {6, 5}}, 31, 0}));
    EXPECT_EQ(0x00013492U, humanScoreGenerator.getHumanScore({{{4, 6}, {4, 5}}, 25, 0}));
    EXPECT_EQ(0x00013452U, humanScoreGenerator.getHumanScore({{{2, 6}, {2, 5}}, 21, 0}));
    EXPECT_EQ(0x00013402U, humanScoreGenerator.getHumanScore({{{1, 6}, {1, 5}}, 10, 0}));
    EXPECT_EQ(0x00013402U, humanScoreGenerator.getHumanScore({{{7, 6}, {7, 5}}, 3, 0}));
    EXPECT_EQ(0x00013392U, humanScoreGenerator.getHumanScore({{{0, 6}, {0, 5}}, -1, 0}));
    EXPECT_EQ(0x00013482U, humanScoreGenerator.getHumanScore({{{3, 6}, {3, 5}}, -2, 0}));
    EXPECT_EQ(0x00015453U, humanScoreGenerator.getHumanScore({{{1, 7}, {2, 5}}, -6, 0}));
    EXPECT_EQ(0x00013422U, humanScoreGenerator.getHumanScore({{{0, 6}, {0, 4}}, -6, 0}));
    EXPECT_EQ(0x00013492U, humanScoreGenerator.getHumanScore({{{1, 6}, {1, 4}}, -22, 0}));
    EXPECT_EQ(0x00013512U, humanScoreGenerator.getHumanScore({{{5, 6}, {5, 4}}, -25, 0}));
    EXPECT_EQ(0x00003492U, humanScoreGenerator.getHumanScore({{{7, 6}, {7, 4}}, -52, 0}));
    EXPECT_EQ(0x00005393U, humanScoreGenerator.getHumanScore({{{1, 7}, {0, 5}}, -52, 0}));
    EXPECT_EQ(0x00003482U, humanScoreGenerator.getHumanScore({{{5, 6}, {5, 5}}, -57, 0}));
    EXPECT_EQ(0x00005403U, humanScoreGenerator.getHumanScore({{{6, 7}, {7, 5}}, -61, 0}));
    EXPECT_EQ(0x000034E2U, humanScoreGenerator.getHumanScore({{{6, 6}, {6, 4}}, -127, 0}));
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
