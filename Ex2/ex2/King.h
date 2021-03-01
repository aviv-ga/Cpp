//
// Created by avivg on 1/2/18.
//

#ifndef CPP_EX2_KING_H
#define CPP_EX2_KING_H


#include <ostream>
#include "ChessPiece.h"

/**
 * Definition of class King which is a type of a chess piece which is used in chess game.
 * This class inherits from ChessPiece.
 */
class King : public ChessPiece
{
public:

    /**
     * Constructor.
     */
    King(unsigned int x, unsigned int y, unsigned int c): ChessPiece(x, y, c, KING){};

    /**
    * Checks whether moving a ChessPiece of this type to given coordinates,
    * is legal on given chessboard.
    * @return
    */
    bool checkMove(unsigned int, unsigned int, ChessBoard*) override;



private:
    std::ostream& _doStream(std::ostream &os)const override;
    static std::string whiteOnBlue;
    static std::string whiteOnGreen;
    static std::string blackOnBlue;
    static std::string blackOnGreen;
};


#endif //CPP_EX2_KING_H
