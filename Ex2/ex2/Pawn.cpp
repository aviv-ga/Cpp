//
// Created by avivg on 1/2/18.
//

#include "Pawn.h"


/**
 * Checks if i move to given coordinates is valid.
 * @return true if valid, false otherwise.
 */
bool Pawn::checkMove(unsigned int x, unsigned int y, ChessBoard* board)
{
    ChessPiece *piece;
    if(_colour == BLACK)
    {
        if(_col == y)
        {
            piece = board->checkSpot(_row - 1, _col);
            if(piece)
            {
                return false;
            }

            if(_row == x + 1)
            {
                return true;
            }
            else if (_row == x + 2 && !_hasMoved)
            {
                return (board->checkSpot(x, y) == nullptr);
            }
            return false;
        }
        else if(_row == x + 1 && (_col == y + 1 || _col == y - 1))
        {
            return (board->checkSpot(x, y) != nullptr);
        }
        return false;
    }
    else
    {
        if (_col == y)
        {
            piece = board->checkSpot(_row + 1, _col);
            if (piece)
            {
                return false;
            }
            if (_row == x - 1)
            {
                return true;
            }
            else if (_row == x - 2 && !_hasMoved)
            {
                return (board->checkSpot(x, y) == nullptr);
            }
            return false;
        }
        else if(_row == x - 1 && (_col == y + 1 || _col == y - 1))
        {
            return (board->checkSpot(x, y) != nullptr);
        }
        return false;
    }
}

/**
 * Output operator helper
 */
std::ostream& Pawn::_doStream(std::ostream &os) const
{
    ((_row + _col) % 2 == 0) ?
    ((_colour == BLACK) ? os << blackOnGreen: os << whiteOnGreen):
    ((_colour == BLACK) ? os << blackOnBlue: os << whiteOnBlue);
    return os;
}
std::string Pawn::whiteOnBlue = "\33[37;46m\u265F\33[0m";
std::string Pawn::whiteOnGreen = "\33[37;42m\u265F\33[0m";
std::string Pawn::blackOnBlue = "\33[30;46m\u265F\33[0m";
std::string Pawn::blackOnGreen = "\33[30;42m\u265F\33[0m";