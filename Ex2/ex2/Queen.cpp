//
// Created by avivg on 1/2/18.
//

#include "Queen.h"
#include <cmath>

/**
 * Output operator helper
 */
std::ostream &Queen::_doStream(std::ostream &os)const
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
bool Queen::checkMove(unsigned int x, unsigned int y, ChessBoard* board)
{
    ChessPiece* piece;
    bool moved = false;
    if(fabs((double)x - (double)_row) == fabs((double)y - (double)_col))
    {
        moved = true;
        unsigned int diff = (unsigned int)fabs((double)_row - (double)x);
        for(unsigned int i = 1; i < diff; i++)
        {
            if(_row > x && _col > y)
            {
                piece = board->checkSpot(_row - i, _col - i);
            }
            else if(_row > x && _col < y)
            {
                piece = board->checkSpot(_row - i, _col + i);
            }
            else if(_row < x && _col < y)
            {
                piece = board->checkSpot(_row + i, _col + i);
            }
            else
            {
                piece = board->checkSpot(_row + i, _col - i);
            }

            if(piece)
            {
                return false;
            }
        }
    }

    if((_row == x) ^ (_col == y))
    {
        moved = true;
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
    }
    return moved;
}


std::string Queen::whiteOnBlue = "\33[37;46m\u265B\33[0m";
std::string Queen::whiteOnGreen = "\33[37;42m\u265B\33[0m";
std::string Queen::blackOnBlue = "\33[30;46m\u265B\33[0m";
std::string Queen::blackOnGreen = "\33[30;42m\u265B\33[0m";