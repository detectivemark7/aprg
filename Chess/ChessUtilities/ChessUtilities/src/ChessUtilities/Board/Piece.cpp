#include "Piece.hpp"

#include <ChessUtilities/Board/BoardUtilities.hpp>
#include <Common/String/AlbaStringHelper.hpp>

using namespace std;

namespace alba {

namespace chess {

PieceColor Piece::extractColor(uint8_t const value) {
    if (PieceType::Empty == extractType(value)) {
        return PieceColor::Unknown;
    } else {
        return static_cast<PieceColor>((value >> 3 & 0B1) | 0B10);  // put 0B10 to avoid unknown
    }
}

PieceType Piece::extractType(uint8_t const value) { return static_cast<PieceType>(value & 0B111); }

PieceColorAndType Piece::extractColorAndType(uint8_t const value) {
    return static_cast<PieceColorAndType>(value & 0B1111);
}

uint8_t Piece::getValueFromColorAndType(PieceColorAndType const pieceColorAndType) {
    return static_cast<uint8_t>(pieceColorAndType) & 0B1111;
}

uint8_t Piece::getValueFromColorAndType(PieceColor const color, PieceType const type) {
    return ((static_cast<uint8_t>(color) & 0B1) << 3) | (static_cast<uint8_t>(type) & 0B111);
}

Piece::Piece() : m_underlyingValue(0U) {}

Piece::Piece(uint8_t const underlyingValue) : m_underlyingValue(underlyingValue) {}

Piece::Piece(PieceColorAndType const colorAndType) : m_underlyingValue(getValueFromColorAndType(colorAndType)) {}

Piece::Piece(PieceColor const color, PieceType const type) : m_underlyingValue(getValueFromColorAndType(color, type)) {}

bool Piece::operator==(Piece const& piece) const { return m_underlyingValue == piece.m_underlyingValue; }

bool Piece::operator!=(Piece const& piece) const { return !operator==(piece); }

bool Piece::isEmpty() const { return PieceType::Empty == getType(); }

PieceColor Piece::getColor() const { return extractColor(m_underlyingValue); }

PieceType Piece::getType() const { return extractType(m_underlyingValue); }

PieceColorAndType Piece::getColorAndType() const { return extractColorAndType(m_underlyingValue); }

uint8_t Piece::getUnderlyingValue() const { return m_underlyingValue; }

char Piece::getFenCharacter() const {
    return convertToFenCharacter(extractType(m_underlyingValue), extractColor(m_underlyingValue));
}

}  // namespace chess

}  // namespace alba
