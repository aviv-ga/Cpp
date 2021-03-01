//
// Created by avivg on 1/2/18.
//

#ifndef CPP_EX2_ROOK_H
#define CPP_EX2_ROOK_H


#include <ostream>
#include "ChessPiece.h"

/**
 * Definition of class Rook which is a type of a chess piece which is used in chess game.
 * This class inherits from ChessPiece.
 */
class Rook : public ChessPiece
{
public:

    /**
     * Constructor.
     */
    Rook(unsigned int x, unsigned int y, unsigned int c): ChessPiece(x, y, c, ROOK){};

    /**
    * Checks whether moving a ChessPiece of this type to given coordinates,
    * is legal on given chessBoard.
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


#endif //CPP_EX2_ROOK_H
