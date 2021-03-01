//
// Created by avivg on 1/2/18.
//

#include "Knight.h"

/**
 * Checks if i move to given coordinates is valid.
 * @return true if valid, false otherwise.
 */
bool Knight::checkMove(unsigned int x, unsigned int y, ChessBoard* board)
{
    if (!board)
    {
        return false;
    }
    if(_row == x + 2 || _row == x - 2)
    {
        if(_col == y -1 || _col == y + 1)
        {
            return true;
        }
    }
    if(_row == x - 1 || _row == x + 1)
    {
        if(_col == y - 2 || _col == y + 2)
        {
            return true;
        }
    }
    return false;
}

/**
 * Output operator helper
 */
std::ostream &Knight::_doStream(std::ostream &os) const
{
    ((_row + _col) % 2 == 0) ?
    ((_colour == BLACK) ? os << blackOnGreen: os << whiteOnGreen):
    ((_colour == BLACK) ? os << blackOnBlue: os << whiteOnBlue);
    return os;
}
std::string Knight::whiteOnBlue = "\33[37;46m\u265E\33[0m";
std::string Knight::whiteOnGreen = "\33[37;42m\u265E\33[0m";
std::string Knight::blackOnBlue = "\33[30;46m\u265E\33[0m";
std::string Knight::blackOnGreen = "\33[30;42m\u265E\33[0m";