#include <ChessPeek/SequenceOfMovesAnalyzer.hpp>

#include <gtest/gtest.h>

using namespace std;

namespace alba {

namespace chess {

namespace ChessPeek {

TEST(SequenceOfMovesAnalyzerTest, CheckMoveAndCommitMoveWorks) {
    BoardWithContext boardWithContext(PieceColor::White, BoardOrientation::BlackUpWhiteDown);
    SequenceOfMovesAnalyzer analyzer(boardWithContext);

    analyzer.analyzeMove({{3, 6}, {3, 4}});
    EXPECT_EQ(PieceColor::White, analyzer.getCurrentMoveColor());

    analyzer.commitMove();
    EXPECT_EQ(PieceColor::White, analyzer.getCurrentMoveColor());
    Board::PieceMatrix expectedMatrix(
        8U, 8U,
        {0xC, 0xA, 0xB, 0xD, 0xE, 0xB, 0xA, 0xC, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
         0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
         0x0, 0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x0, 0x1, 0x1, 0x1, 0x1, 0x4, 0x2, 0x3, 0x5, 0x6, 0x3, 0x2, 0x4});
    EXPECT_EQ(expectedMatrix, analyzer.getCurrentBoard().getPieceMatrix());
}

TEST(SequenceOfMovesAnalyzerTest, CanPreMoveWorksOnRecapture) {
    BoardWithContext boardWithContext(PieceColor::White, BoardOrientation::BlackUpWhiteDown);
    SequenceOfMovesAnalyzer analyzer(boardWithContext);
    analyzer.analyzeMove({{4, 6}, {4, 4}});
    analyzer.commitMove();
    analyzer.analyzeMove({{3, 1}, {3, 3}});
    analyzer.commitMove();
    analyzer.analyzeMove({{4, 4}, {3, 3}});
    analyzer.commitMove();

    analyzer.analyzeMove({{3, 0}, {3, 3}});
    EXPECT_TRUE(analyzer.canPreMove());
}

TEST(SequenceOfMovesAnalyzerTest, CanPreMoveWorksOnCheckWithOneWayOfEscape) {
    Board board(
        BoardOrientation::BlackUpWhiteDown,
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xE, 0x0, 0x4, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
         0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x5, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
         0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0});
    BoardWithContext boardWithContext(PieceColor::White, board);
    SequenceOfMovesAnalyzer analyzer(boardWithContext);
    analyzer.analyzeMove({{5, 3}, {5, 1}});
    analyzer.commitMove();
    analyzer.analyzeMove({{6, 0}, {7, 0}});
    analyzer.commitMove();

    analyzer.analyzeMove({{5, 1}, {6, 1}});
    EXPECT_TRUE(analyzer.canPreMove());
}

TEST(SequenceOfMovesAnalyzerTest, CanPreMoveWorksOnCheckWithOneWayToBlock) {
    Board board(
        BoardOrientation::BlackUpWhiteDown,
        {0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0xE, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
         0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xC, 0x0, 0x0, 0x0,
         0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6, 0x0, 0x0, 0x0, 0x0, 0x5, 0x0, 0x0});
    BoardWithContext boardWithContext(PieceColor::White, board);
    SequenceOfMovesAnalyzer analyzer(boardWithContext);
    analyzer.analyzeMove({{5, 7}, {7, 7}});
    analyzer.commitMove();
    analyzer.analyzeMove({{0, 5}, {7, 5}});
    analyzer.commitMove();

    analyzer.analyzeMove({{7, 7}, {7, 5}});
    EXPECT_TRUE(analyzer.canPreMove());
}

}  // namespace ChessPeek

}  // namespace chess

}  // namespace alba
