//
// Created by avivg on 1/2/18.
//

#include <cmath>
#include "Bishop.h"
#include "ChessBoard.h"

/**
 * Checks if i move to given coordinates is valid.
 * @return true if valid, false otherwise.
 */
bool Bishop::checkMove(unsigned int x, unsigned int y, ChessBoard* board)
{
    if (fabs((double)x - (double)_row) != fabs((double)y - (double)_col))
    {
        return false;
    }
    unsigned int diff = (unsigned int) fabs((double)_row - (double)x);
    ChessPiece *piece;
    for (unsigned int i = 1; i < diff; i++)
    {
        if (_row > x && _col > y)
        {
            piece = board->checkSpot(_row - i, _col - i);
        }
        else if (_row > x && _col < y)
        {
            piece = board->checkSpot(_row - i, _col + i);
        }
        else if (_row < x && _col < y)
        {
            piece = board->checkSpot(_row + i, _col + i);
        }
        else
        {
            piece = board->checkSpot(_row + i, _col - i);
        }
        if (piece)
        {
            return false;
        }
    }
    return true;
}

/**
 * Output operator helper
 */
std::ostream &Bishop::_doStream(std::ostream &os) const
{
    ((_row + _col) % 2 == 0) ?
    ((_colour == BLACK) ? os << blackOnGreen: os << whiteOnGreen):
    ((_colour == BLACK) ? os << blackOnBlue: os << whiteOnBlue);
    return os;
}
std::string Bishop::whiteOnBlue = "\33[37;46m\u265D\33[0m";
std::string Bishop::whiteOnGreen = "\33[37;42m\u265D\33[0m";
std::string Bishop::blackOnBlue = "\33[30;46m\u265D\33[0m";
std::string Bishop::blackOnGreen = "\33[30;42m\u265D\33[0m";
