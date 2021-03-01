//
// Created by avivg on 1/2/18.
//

#include <iostream>
#include "King.h"

std::string King::whiteOnBlue = "\33[37;46m\u265A\33[0m";
std::string King::whiteOnGreen = "\33[37;42m\u265A\33[0m";
std::string King::blackOnBlue = "\33[30;46m\u265A\33[0m";
std::string King::blackOnGreen = "\33[30;42m\u265A\33[0m";


/**
 * Checks if i move to given coordinates is valid.
 * @return true if valid, false otherwise.
 */
bool King::checkMove(unsigned int x, unsigned int y, ChessBoard* board)
{
    if (board->checkThreat(x, y, _colour))
    {
       return false;
    }
    if(_row == x)
    {
        return (_col == y - 1 || _col == y + 1);
    }
    if(_row == x - 1)
    {
        return (_col == y - 1 || _col == y + 1 || _col == y);
    }
    if(_row == x + 1)
    {
        return (_col == y - 1 || _col == y + 1 || _col == y);
    }
    return false;
}

/**
 * Output operator helper
 */
std::ostream& King::_doStream(std::ostream &os) const
{
    ((_row + _col) % 2 == 0) ?
    ((_colour == BLACK) ? os << blackOnGreen : os << whiteOnGreen) :
    ((_colour == BLACK) ? os << blackOnBlue : os << whiteOnBlue);
    return os;
}

