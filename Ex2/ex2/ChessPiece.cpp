//
// Created by avivg on 1/2/18.
//

#include "ChessPiece.h"
#include "ChessBoard.h"

/**
 * Puts a printable version of the ChessPiece to a given output stream.
 */
std::ostream &operator<<(std::ostream &os, const ChessPiece &piece)
{
    piece._doStream(os);
    return os;
}

/**
 * Attempts to move the ChessPiece to a given spot on a given board.
 */
bool ChessPiece::move(unsigned int x, unsigned int y, ChessBoard* board)
{
    if(checkMove(x, y, board))
    {
        unsigned int curX = _row, curY = _col;
        _col = y;
        _row = x;
        if(board->checkCheck(_colour))
        {
            _row = curX;
            _col = curY;
            return false;
        }
        _hasMoved = true;
        return true;
    }
    return false;
}

/**
 * Returns the row of the ChessPiece object.
 */
unsigned int ChessPiece::getRow() const
{
    return _row;
}

/**
 * Returns the column of the ChessPiece object.
 */
unsigned int ChessPiece::getCol() const
{
    return _col;
}

/**
 * Sets the row of the ChessPiece object.
 */
void ChessPiece::setRow(unsigned int row)
{
    _row = row;
}

/**
 * Sets the column of the ChessPiece object.
 */
void ChessPiece::setCol(unsigned int col)
{
    _col = col;
}

/**
 * Returns the colour of the ChessPiece object.
 */
unsigned int ChessPiece::getColour() const
{
    return _colour;
}

/**
 * Returns the type of the ChessPiece object.
 */
unsigned int ChessPiece::getType() const
{
    return _type;
}

/**
 * Returns the hasMoved flag of the ChessPiece object.
 */
bool ChessPiece::hasMoved() const
{
    return _hasMoved;
}