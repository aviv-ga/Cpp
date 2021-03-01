//
// Created by avivg on 1/2/18.
//

#ifndef CPP_EX2_CHESSPIECE_H
#define CPP_EX2_CHESSPIECE_H


#include <ostream>
#include "ChessBoard.h"
class ChessBoard;

/**
 * Definition of class ChessPiece which is base class of all pieces in chess game.
 * Father class of Queen, King, Pawn, Rook, Bishop and Knight.
 */
class ChessPiece
{
public:
    /** Indicate Black colour of a chessPiece. */
    static const int BLACK = 0;
    /** Indicate white colour of a chessPiece. */
    static const int WHITE = 1;

    /**
     * Type's of the chesspiece's in chess game.
     */
    enum type
    {
        PAWN,
        ROOK,
        KNIGHT,
        BISHOP,
        QUEEN,
        KING
    };

    /**
     * Consturctor of ChessPiece.
     * @param row init
     * @param col init
     * @param c init
     * @param type init
     */
    ChessPiece(unsigned int row, unsigned int col, unsigned int c, unsigned int type):
             _row(row), _col(col), _colour(c), _type(type), _hasMoved(false) {};

    /**
     * Destructor
     */
    virtual ~ChessPiece() = default;

    /**
    * Move the object to the given destination.
    * @param x the coloumn destination
    * @param y the row destination
    * @param board pointer to game board.
    * @return true if move was successfully made, false otherwise.
    */
    bool move(unsigned int, unsigned int, ChessBoard*) ;

    /**
     * Checks if a move to given coordinates is valid.
     */
    virtual bool checkMove(unsigned int, unsigned int, ChessBoard*) = 0;

    /**
     * Output operator helper.
     */
    virtual std::ostream& _doStream(std::ostream &) const = 0;

    /**
    * Put the object to the given output stream.
    * @param os an output stream.
    * @param piece the ChessPiece to put.
    * @return the output stream.
    */
    friend std::ostream &operator<<(std::ostream &os, const ChessPiece &piece);

    /**
    * set object's row field.
    * @param row the new row.
    */
    void setRow(unsigned int row);

    /**
    * set object's coloumn field.
    * @param col the new coloumn
    */
    void setCol(unsigned int col);

    /**
     * @return current row.
    */
    unsigned int getRow() const;

    /**
    * @return current coloumn
    */
    unsigned int getCol() const;

    /**
    * @return object's colour
    */
    unsigned int getColour() const;

    /**
    * @return the type of the object.
    */
    unsigned int getType() const;

    /**
    * @return true if piece was moved before, false otherwise.
    */
    bool hasMoved() const;


protected:
    /** Object's row */
    unsigned int _row;
    /** Object's column */
    unsigned int _col;
    /** Object's colour */
    unsigned int _colour;
    /** Object's type */
    unsigned int _type;
    /** true if object was moved before, false otherwise. */
    bool _hasMoved;
};


#endif //CPP_EX2_CHESSPIECE_H
