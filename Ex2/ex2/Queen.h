//
// Created by avivg on 1/2/18.
//

#ifndef CPP_EX2_QUEEN_H
#define CPP_EX2_QUEEN_H


#include "ChessPiece.h"

/**
 * Definition of class Queen which is a type of a chess piece which is used in chess game.
 * This class inherits from ChessPiece.
 */
class Queen : public ChessPiece
{
public:

    /**
     * Constructor.
     */
    Queen(unsigned int x, unsigned int y, unsigned int c): ChessPiece(x, y, c, QUEEN){};

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


#endif //CPP_EX2_QUEEN_H
