//
// Created by avivg on 1/2/18.
//
#include <iostream>
#include "ChessGame.h"
#include <sstream>

#define W_P_MSG "Enter white player name:"
#define B_P_MSG "Enter black player name:"
#define CLEAN_SCR "\33[2J"
#define CHECK_MSG "\33[37;41mCheck!\33[0m"
#define ILLEGAL_MOVE "\33[37;41millegal _move\33[0m"
#define SMALL_CASTLING "o-o"
#define BIG_CASTLING "o-o-o"
#define WIN_MSG " won!"
#define ENTER_MOVE ": Please enter your move:"
#define BLACK 0
#define WHITE 1

class ChessBoard;
ChessBoard* ChessGame::_board = ChessBoard::getBoard();
std::string ChessGame::_pW = "";
std::string ChessGame::_pB = "";

/**
 * Runs the chess game.
 * @return
 */
int ChessGame::run()
{
    _getPlayerNames();
    bool check = false;
    std::string curP = _pW;
    unsigned int curC = WHITE;
    std::string input;
    while(true)
    {
        std::cout << CLEAN_SCR << _board;
        if (check)
        {
            std::cout << CHECK_MSG << std::endl;
        }
        _getMove(curP, input);
        if (!_move(input, curC, check))
        {
            std::cout << ILLEGAL_MOVE << std::endl;
            continue;
        }
        if(_board)
        {
            _board->P2Q(curC);
        }

        (_board->checkCheck((curC == WHITE) ? BLACK : WHITE)) ? (check = true) : (check = false);
        if (check)
        {
            if (_board->checkCheckMate((curC == WHITE) ? BLACK : WHITE))
            {
                break;
            }
        }
        if (curC == WHITE)
        {
            curC = BLACK;
            curP = _pB;
        }
        else
        {
            curC = WHITE;
            curP = _pW;
        }
    }
    // end game:
    std::cout << _board << std::endl;
    std::cout << curP << WIN_MSG << std::endl;

    ChessBoard::deleteBoard();
    return 0;
}

/**
 * Gets player names from the standard input mechanism.
 */
void ChessGame::_getPlayerNames()
{
    std::cout << W_P_MSG << std::endl;
    std::cin >> _pW;
    std::cout << B_P_MSG << std::endl;
    std::cin >> _pB;
}

/**
 * Gets a string representing a move from the user, using the standard input.
 * Format of move is "A1A5", where first 2 chars indicate the position of the wanted piece to be moved,
 * and the third and the forth chars for its destination.
 * @param pName Name of the player to make the move.
 * @param move String in which the move is saved.
 */
void ChessGame::_getMove(const std::string &pName, std::string &move)
{
    std::cout << pName << ENTER_MOVE << std::endl;
    std::cin >> move;
}

/**
 * Runs the move logic.
 * @param move String that represents the move.
 * @param curC Colour code of the current player.
 * @return true if move succeeded, false otherwise.
 */
bool ChessGame::_move(std::string move, unsigned int curC, bool check)
{
    if(move == SMALL_CASTLING)
    {
        return _board->smallCastling(curC);
    }
    if(move == BIG_CASTLING)
    {
        return _board->bigCastling(curC);
    }
    if(move.length() != 4)
    {
        return false;
    }
    int inp[4];
    for (int i = 0; i < 4; i++)
    {
        if ((i % 2) == 0)
        {
            inp[i] = ((int)move[i]) - 64;
        }
        else
        {
            inp[i] = ((int)move[i]) - 48;
        }
    }
    for (int input: inp)
    {
        if ((input < 1) || (input > 8))
        {
            return false;
        }
    }
    if (check)
    {
        ChessPiece* king = _board->getKing(curC);
        if (!(king->getRow() == (unsigned int)inp[1] && king->getCol() == (unsigned int)inp[0]))
        {
            return false;
        }
    }
    return (_board->move((unsigned int)inp[1], (unsigned int)inp[0],
                        (unsigned int)inp[3], (unsigned int)inp[2], curC));

}
