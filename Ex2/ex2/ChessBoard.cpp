//
// Created by avivg on 1/2/18.
//

#include <cmath>
#include "ChessBoard.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

#define LEGEND "ABCDEFGH"
//#define BLACK 0
//#define WHITE 1

ChessBoard* ChessBoard::_boardSingleton = nullptr;

/**
 * Returns the singleton instance of the board.
 */
ChessBoard* ChessBoard::getBoard()
{
    if(!_boardSingleton)
    {
        _boardSingleton = new ChessBoard();
    }
    return _boardSingleton;
}

/**
 * Deletes the singleton instance of board.
 */
void ChessBoard::deleteBoard()
{
    if(_boardSingleton)
    {
        delete _boardSingleton;
        _boardSingleton = nullptr;
    }
}

/**
 * Constructor.
 */
ChessBoard::ChessBoard()
{
    blackChessPieces = new ChessPiece *[16];
    whiteChessPieces = new ChessPiece *[16];

    for(unsigned int i = 1; i <= 8; i++)
    {
        blackChessPieces[i-1] = new Pawn(7, i, BLACK);
        whiteChessPieces[i-1] = new Pawn(2, i, WHITE);
    }
    for(unsigned int i = 1; i <= 2; i++)
    {
        blackChessPieces[i + 7] = new Rook(8, i + (6 * (unsigned int)floor(i / 2)), BLACK);
        whiteChessPieces[i + 7] = new Rook(1, i + (6 * (unsigned int)floor(i / 2)), WHITE);
    }

    for(unsigned int i = 1; i <= 2; i++)
    {
        blackChessPieces[i + 9] = new Knight(8, (2 * i) + (3 * (unsigned int)floor(i / 2)), BLACK);
        whiteChessPieces[i + 9] = new Knight(1, (2 * i) + (3 * (unsigned int)floor(i / 2)), WHITE);
    }

    for(unsigned int i = 1; i <= 2; i++)
    {
        blackChessPieces[i + 11] = new Bishop(8, (3 * i), BLACK);
        whiteChessPieces[i + 11] = new Bishop(1, (3 * i), WHITE);
    }

    blackChessPieces[14] = new Queen(8, 4, BLACK);
    whiteChessPieces[14] = new Queen(1, 4, WHITE);

    blackChessPieces[15] = new King(8, 5, BLACK);
    whiteChessPieces[15] = new King(1, 5, WHITE);
}

/**
 * Destructor.
 */
ChessBoard::~ChessBoard()
{
    for(int i = 0; i < 16; i++)
    {
        if(whiteChessPieces[i])
        {
            delete whiteChessPieces[i];
        }
        if(blackChessPieces[i])
        {
            delete blackChessPieces[i];
        }
    }
    delete [] whiteChessPieces;
    delete [] blackChessPieces;
}

/**
 * Puts a printable version of the board to a given output stream.
 */
std::ostream &operator<<(std::ostream &os, const ChessBoard* board)
{
    os << "  " << LEGEND << std::endl << std::endl;
    for(unsigned int row = 8; row >= 1; row--)
    {
        os << row << " ";
        for(unsigned int col = 1; col <= 8; col++)
        {
            ChessPiece* temp = board->checkSpot(row, col);
            (temp) ? (os << *temp): (((row + col) % 2 == 0) ? os << "\33[37;42m \33[0m": os << "\33[37;46m \33[0m");
        }
        os << " " << row << std::endl;
    }
    os << std::endl << "  " << LEGEND << std::endl << std::endl;
    return os;
}

/**
 * Checks if a spot gith given coordinates on the board is vacated or not.
 * @return Pointer to ChessPiece object that occupies the spot, nullptr if spot is vacated.
 */
ChessPiece* ChessBoard::checkSpot(unsigned int row, unsigned int col, unsigned int* p) const
{
    for (unsigned int i = 0; i < 16; i++)
    {
        if (blackChessPieces[i])
        {
            if (row == blackChessPieces[i]->getRow() && col == blackChessPieces[i]->getCol())
            {
                if (p)
                {
                    *p = i;
                }
                return blackChessPieces[i];
            }
        }
    }
    for (unsigned int i = 0; i < 16; i++)
    {
        if (whiteChessPieces[i])
        {
            if (row == whiteChessPieces[i]->getRow() && col == whiteChessPieces[i]->getCol())
            {
                if (p)
                {
                    *p = i + 16;
                }
                return whiteChessPieces[i];
            }
        }
    }
    return nullptr;
}

/**
 * Attempts to perform a move from given coordinates to given coordinates.
 */
bool ChessBoard::move(unsigned int fromRow, unsigned int fromCol, unsigned int toRow, unsigned int toCol, unsigned int c)
{
    unsigned int *p;
    unsigned int x = 32;
    p = &x;
    ChessPiece* piece = checkSpot(fromRow, fromCol);
    if(piece == nullptr || piece->getColour() != c)
    {
        return false;
    }
    ChessPiece* captured = checkSpot(toRow, toCol, p);
    if(captured)
    {
        if(captured->getColour() == piece->getColour())
        {
            return false;
        }
    }
    if (piece->move(toRow, toCol, this))
    {
        if(captured)
        {
            (*p < 16) ? blackChessPieces[*p] = nullptr: whiteChessPieces[*p - 16] = nullptr;
            delete captured;
        }
        return true;
    }
    return false;
}

/**
 * Checks whether a spot on the board is under threat by the opposite colour of the given colour code.
 */
bool ChessBoard::checkThreat(unsigned int x, unsigned int y, unsigned int c)
{
    ChessPiece** chessPieces;
    (c == BLACK) ? chessPieces = whiteChessPieces : chessPieces = blackChessPieces;
    for(int i = 0; i < 16; i++)
    {
        if(chessPieces[i] != nullptr)
        {
            if (chessPieces[i]->checkMove(x, y, this))
            {
                return true;
            }
        }
    }
    return false;
}

/**
 * Checks if the king of a given colour is in check.
 */
bool ChessBoard::checkCheck(unsigned int c)
{
    ChessPiece* king;
    (c == BLACK) ? king = blackChessPieces[15]: king = whiteChessPieces[15];
    return checkThreat(king->getRow(), king->getCol(), c);
}

/**
 * Checks if the king of a given colour is in check mate.
 */
bool ChessBoard::checkCheckMate(unsigned int c)
{
    unsigned int kingX;
    unsigned int kingY;
    bool safe = true;
    (c == BLACK) ? (kingX = blackChessPieces[15]->getRow()): kingX = whiteChessPieces[15]->getRow();
    (c == BLACK) ? (kingY = blackChessPieces[15]->getCol()): kingY = whiteChessPieces[15]->getCol();
    if(checkLegalPos(kingX + 1, kingY))
    {
        if(checkSpot(kingX + 1, kingY) == nullptr)
        {
            safe = !checkThreat(kingX + 1, kingY, c);
        }
    }
    if(checkLegalPos(kingX + 1, kingY + 1))
    {
        if(checkSpot(kingX + 1, kingY + 1) == nullptr)
        {
            safe = !checkThreat(kingX + 1, kingY + 1, c);
        }
    }
    if(checkLegalPos(kingX, kingY + 1))
    {
        if(checkSpot(kingX, kingY + 1) == nullptr)
        {
            safe = !checkThreat(kingX, kingY + 1, c);
        }
    }
    if(checkLegalPos(kingX - 1, kingY))
    {
        if(checkSpot(kingX - 1, kingY) == nullptr)
        {
            safe = !checkThreat(kingX - 1, kingY, c);
        }
    }
    if(checkLegalPos(kingX - 1, kingY - 1))
    {
        if(checkSpot(kingX - 1, kingY - 1) == nullptr)
        {
            safe = !checkThreat(kingX - 1, kingY - 1, c);
        }
    }
    if(checkLegalPos(kingX, kingY - 1))
    {
        if(checkSpot(kingX, kingY - 1) == nullptr)
        {
            safe = !checkThreat(kingX, kingY - 1, c);
        }
    }
    if(checkLegalPos(kingX + 1, kingY - 1))
    {
        if(checkSpot(kingX + 1, kingY - 1) == nullptr)
        {
            safe = !checkThreat(kingX + 1, kingY - 1, c);
        }
    }
    if(checkLegalPos(kingX - 1, kingY + 1))
    {
        if(checkSpot(kingX - 1, kingY + 1) == nullptr)
        {
            safe = !checkThreat(kingX - 1, kingY + 1, c);
        }
    }

    return !safe;
}

/**
 * Checks whether given coordinates describe a legal position on the board.
 */
bool ChessBoard::checkLegalPos(unsigned int x, unsigned int y)
{
    return !((x < 1) || (x > 8)) || ((y < 1) || (y > 8));
}

/**
 * Attempts to perform a small castling move for player of the given colour.
 */
bool ChessBoard::smallCastling(unsigned int c)
{
    ChessPiece** chessPieces;
    (c == BLACK) ? chessPieces = blackChessPieces : chessPieces = whiteChessPieces;
    if (!(chessPieces[8]) || !(chessPieces[15]))
    {
        return false;
    }
    if(chessPieces[8]->hasMoved() || chessPieces[15]->hasMoved())
    {
        return false;
    }
    for(int i = 1; i < 3; i++)
    {
        if(checkThreat(chessPieces[15]->getRow(), chessPieces[15]->getCol() + i, c))
        {
            return false;
        }
        if(checkSpot(chessPieces[15]->getRow(), chessPieces[15]->getCol() + i) != nullptr)
        {
            return false;
        }
    }
    chessPieces[15]->setRow(7);
    chessPieces[8]->setCol(6);
    return true;
}

/**
 * Attempts to perform a big castling move for player of the given colour.
 */
bool ChessBoard::bigCastling(unsigned int c)
{
    ChessPiece** chessPieces;
    (c == BLACK) ? chessPieces = blackChessPieces : chessPieces = whiteChessPieces;
    if (!(chessPieces[9]) || !(chessPieces[15]))
    {
        return false;
    }
    if(chessPieces[9]->hasMoved() || chessPieces[15]->hasMoved())
    {
        return false;
    }
    for(int i = 1; i < 4; i++)
    {
        if(checkThreat(chessPieces[15]->getRow(), chessPieces[15]->getCol() - i, c))
        {
            return false;
        }
        if(checkSpot(chessPieces[15]->getRow(), chessPieces[15]->getCol() - i) != nullptr)
        {
            return false;
        }
    }
    chessPieces[15]->setRow(3);
    chessPieces[9]->setCol(4);
    return true;
}

/**
 * Converts pawns to queens if necessary.
 */
void ChessBoard::P2Q(unsigned int c)
{
    ChessPiece** chessPieces;
    unsigned int line;
    (c == BLACK) ? chessPieces = whiteChessPieces: chessPieces = blackChessPieces;
    (c == BLACK) ? line = 1 : line = 8;
    for (int i = 0; i < 9; i++)
    {
        if(chessPieces[i])
        {
            if((chessPieces[i]->getRow() == line) && (chessPieces[i]->getType() == ChessPiece::PAWN))
            {
                unsigned int newCol = chessPieces[i]->getCol();
                delete chessPieces[i];
                chessPieces[i] = new Queen(line, newCol, c);
            }
        }
    }
}

/**
 * Returns the ChessPiece object of the king of given colour.
 */
ChessPiece* ChessBoard::getKing(unsigned int c)
{
    ChessPiece* king;
    (c == BLACK) ? king = blackChessPieces[15]: king = whiteChessPieces[15];
    return king;
}