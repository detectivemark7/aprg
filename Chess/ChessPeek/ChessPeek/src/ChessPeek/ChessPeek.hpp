#pragma once

#include <ChessPeek/ChessPeekCalculationDetails.hpp>
#include <ChessPeek/ChessPeekConfiguration.hpp>
#include <ChessPeek/ChessPieceRetriever.hpp>
#include <ChessUtilities/Board/Board.hpp>
#include <ChessUtilities/ChessEngineControllerWithUci.hpp>
#include <ChessUtilities/ChessEngineHandler.hpp>
#include <Common/Time/AlbaLocalTimer.hpp>
#include <ScreenMonitoring/AlbaLocalScreenMonitoring.hpp>

namespace alba {

namespace chess {

class ChessPeek {
public:
    using ChessCellBitValueMatrix = matrix::AlbaMatrix<uint64_t>;
    using EngineCalculationDetails = CalculationDetails;

    struct ChessBoardDetails {
        unsigned int pieceCount;
        unsigned int whiteCountInUpperHalf;
        unsigned int blackCountInUpperHalf;
        unsigned int whiteCountInLowerHalf;
        unsigned int blackCountInLowerHalf;
        unsigned int numberOfWhiteKings;
        unsigned int numberOfBlackKings;
        Coordinate whiteKingCoordinate;
        Coordinate blackKingCoordinate;
    };

    ChessPeek();

    void runForever();
    void runOneIteration();

    void checkScreenAndSaveDetails();
    void startEngineAnalysisOfNewPosition();
    void calculationMonitoringCallBackForEngine(EngineCalculationDetails const& engineCalculationDetails);

private:
    void initialize();

    void saveChessBoardAndItsDetails();
    void setChessBoardCountDetails(Coordinate const& chessCoordinate, Piece const& chessPiece);
    void setChessBoardKingDetailsIfNeeded(Coordinate const& chessCoordinate, Piece const& chessPiece);
    void updatePlayerColorAndOrientation();
    void updatePlayerColorIfChessDotComPuzzle();
    void updatePlayerColorIfLichessStream();
    void updatePlayerColorAndOrientationFromChessBoardDetails();
    void setPlayerColorAndResetEngineIfNeeded(PieceColor const newColor);
    void setOrientationDependingOnLowerHalfColor(PieceColor const lowerHalfColor);
    void saveCalculationDetails(EngineCalculationDetails const& engineCalculationDetails);

    void displayCalculationDetailsBasedFromTimer();
    void displayCalculationDetailsIfNotDisplayedYet();
    void printCalculationDetails();

    bool shouldAnalyzeBoard(Board::PieceMatrix const& previousPieceMatrix) const;
    bool didBoardChange(Board::PieceMatrix const& previousPieceMatrix) const;
    bool canAnalyzeBoard() const;
    bool areKingsValid() const;
    bool isOpponentsKingOnCheck() const;
    Coordinate getOpponentsKingCoordinate() const;

    ChessPeekConfiguration m_configuration;
    AlbaLocalScreenMonitoring m_screenMonitoring;
    ChessPieceRetriever m_pieceRetriever;
    ChessEngineHandler m_chessEngineHandler;
    ChessEngineControllerWithUci m_chessEngineController;
    AlbaLocalTimer m_displayTimer;
    ChessPeekCalculationDetails m_calculationDetails;
    Board m_chessBoard;
    ChessBoardDetails m_chessBoardDetails;
    PieceColor m_playerColor;
    bool m_isEngineNewlyReseted;
    bool m_hasPendingPrintAction;
};

}  // namespace chess

}  // namespace alba
