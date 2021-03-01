//
// Created by avivg on 1/2/18.
//

#include "Rook.h"
#include <cmath>

std::string Rook::whiteOnBlue = "\33[37;46m\u265C\33[0m";
std::string Rook::whiteOnGreen = "\33[37;42m\u265C\33[0m";
std::string Rook::blackOnBlue = "\33[30;46m\u265C\33[0m";
std::string Rook::blackOnGreen = "\33[30;42m\u265C\33[0m";

/**
 * Output operator helper
 */
std::ostream &Rook::_doStream(std::ostream &os) const
{
    ((_row + _col) % 2 == 0) ?
    ((_colour == BLACK) ? os << blackOnGreen: os << whiteOnGreen):
    ((_colour == BLACK) ? os << blackOnBlue: os << whiteOnBlue);
    return os;
}

/**
 * Checks if i move to given coordinates is valid.
 * @return true if valid, false otherwise.
 */
bool Rook::checkMove(unsigned int x, unsigned int y, ChessBoard* board)
{
    if(!((_row == x) ^ (_col == y)))
    {
        return false;
    }
    ChessPiece* piece;
    if(_row == x)
    {
        unsigned int range = (unsigned int) fabs((double)_col - (double)y);
        for (unsigned int i = 1; i < range; i++)
        {
            (_col < y) ? piece = board->checkSpot(x, _col + i): piece = board->checkSpot(x, _col - i);
            if(piece)
            {
                return false;
            }
        }
    }
    else
    {
        unsigned int range = (unsigned int) fabs((double)_row - (double)x);
        for (unsigned int i = 1; i < range; i++)
        {
            (_row < x) ? piece = board->checkSpot(_row + i, _col) : piece = board->checkSpot(_row - i, _col);
            if(piece)
            {
                return false;
            }
        }
    }
    return true;
}

