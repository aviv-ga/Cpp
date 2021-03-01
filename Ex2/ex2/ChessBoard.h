//
// Created by avivg on 1/2/18.
//

#ifndef CPP_EX2_CHESSBOARD_H
#define CPP_EX2_CHESSBOARD_H


#include <ostream>
#include "ChessPiece.h"

/** forward declaration of ChessPiece */
class ChessPiece;

/**
 * Class that represents a chess board in the ChessGame.
 */

class ChessBoard
{
public:

    /**
     * Singleton ChessBoard object getter.
     * @return
     */
    static ChessBoard* getBoard();

    /**
     * Singleton destruct function of ChessBoard object.
     */
    static void deleteBoard();

    /**
    * Puts the ChessBoard object to the standard output stream.
    * @param os Output stream.
    * @param board Chessboard object to put.
    * @return given stream.
    */
    friend std::ostream &operator<<(std::ostream &os, const ChessBoard* board);

    /**
    * Tries to perform a move on the board.
    * @param fromRow Row of the piece to move.
    * @param fromCol Column of the piece to move.
    * @param toRow Destination row.
    * @param toCol Destination column.
    * @param c Colour code of the player that performs the move.
    * @return true if a move was successfully completed, false otherwise.
    */
    bool move(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

    /**
    * Checks whether the king of given colour is in check.
    * @param c Colour code.
    * @return true if in check, false otherwise.
    */
    bool checkCheck(unsigned int);

    /**
    * Checks whether a spot with given coordinates is under threat.
    * @param x Row of the spot to check.
    * @param y Column of the spot to check.
    * @param c Colour code of the player that wants to know if threatened.
    * @return true if spot is under threat, false otherwise.
    */
    bool checkThreat(unsigned int, unsigned int, unsigned int);

    /**
    * Checks whether the king of a given colour is in checkmate.
    * @param c Colour code.
    * @return true if in checkmate, false otherwise.
    */
    bool checkCheckMate(unsigned int);

    /**
    * Checks whether given coordinates are in the board boundaries.
    * @param x Row.
    * @param y Column.
    * @return
    */
    bool checkLegalPos(unsigned int, unsigned int);

    /**
    * Attempts to perform a small castling of ChessPieces of a given colour.
    * @param c Colour code.
    * @return true if castling was successfully completed, false otherwise.
    */
    bool smallCastling(unsigned int c);

    /**
    * Attempts to perform a big castling of ChessPieces of a given colour.
    * @param c Colour code.
    * @return true if castling was successfully completed, false otherwise.
    */
    bool bigCastling(unsigned int c);

    /**
    * Checks if the spot with the given coordinates is occupied or not.
    * @param row
    * @param col
    * @param p points to the index of the ChessPiece, if found.
    * @return ChessPiece object in the given coordinates, nullptr if spot is vacated.
    */
    ChessPiece* checkSpot(unsigned int, unsigned int, unsigned int* = nullptr) const;

    /**
    * Returns the king ChessPiece object of a given colour.
    * @param c Colour code
    * @return ChessPiece object of the king.
    */
    ChessPiece* getKing(unsigned int);

    /**
    * Performs promotion of Pawns of a given colour, if necessary.
    * @param c Colour code.
    */
    void P2Q(unsigned int);

private:
    /**
    * ChessBoard object constructor.
    */
    ChessBoard();
    /**
     * ChessBoard object Destructor
     */
    ~ChessBoard();
    /**
     * Copy constructor. Made private in order to avoid more than one instance.
     */
    ChessBoard(ChessBoard& board) = default;
    /**
     * Equals operator. Made private in order to avoid more than one instance.
     */
    ChessBoard& operator=(ChessBoard&) = default;

    static ChessBoard* _boardSingleton;
    /** Pointer to a list of pointers of ChessPiece objects. Black Pieces of the game.*/
    ChessPiece **blackChessPieces;
    /** Pointer to a list of pointers of ChessPiece objects. White Pieces of the game.*/
    ChessPiece **whiteChessPieces;
    static unsigned int const WHITE = 1;
    static unsigned int const BLACK = 0;

};


#endif //CPP_EX2_CHESSBOARD_H
