//
// Created by avivg on 1/2/18.
//

#ifndef CPP_EX2_CHESSGAME_H
#define CPP_EX2_CHESSGAME_H


#include "ChessBoard.h"

/**
 * Static Class that represents a game of chess.
 */
class ChessGame
{
public:
    
    /**
    * Runs the chess game.
    * @return
    */
    static int run();

private:
    ChessGame() = default;

    /**
    * Gets player names from the standard input mechanism.
    */
    static void _getPlayerNames();

    /**
    * Gets a string representing a move from the user, using the standard input.
    * Format of move is "A1A5", where first 2 chars indicate the position of the wanted piece to be moved,
    * and the third and the forth chars for its destination.
    * @param pName Name of the player to make the move.
    * @param move String in which the move is saved.
    */
    static void _getMove(const std::string &, std::string &);

     /**
     * Runs the move logic.
     * @param move String that represents the move.
     * @param curC Colour code of the current player.
     * @return true if move succeeded, false otherwise.
     */
    static bool _move(std::string, unsigned int, bool);

    /** Pointer to the board of the game. */
    static ChessBoard* _board;
    /** Strings which represent player's names. */
    static std::string _pW, _pB;

};


#endif //CPP_EX2_CHESSGAME_H
