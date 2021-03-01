//
// Created by avivg on 1/2/18.
//

#ifndef CPP_EX2_PAWN_H
#define CPP_EX2_PAWN_H


#include <ostream>
#include "ChessPiece.h"

/**
 * Definition of class Pawn which is a type of a chess piece which is used in chess game.
 * This class inherits from ChessPiece.
 */
class Pawn: public ChessPiece
{
public:

    /**
     * Constructor.
     */
    Pawn(unsigned int x, unsigned int y, unsigned int c): ChessPiece(x, y, c, PAWN){};

    /**
    * Checks whether moving a ChessPiece of this type to given coordinates,
    * is legal on given chessboard.
    * @return
    */
    bool checkMove(unsigned int, unsigned int, ChessBoard*) override;


private:
    static std::string whiteOnBlue;
    static std::string whiteOnGreen;
    static std::string blackOnBlue;
    static std::string blackOnGreen;
    std::ostream& _doStream(std::ostream &os)const override;
};


#endif //CPP_EX2_PAWN_H
