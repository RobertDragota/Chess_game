//
// Created by robert12 on 10/16/23.
//

#ifndef CHESS_2_0_QUEEN_H
#define CHESS_2_0_QUEEN_H


#include <list>
#include <utility>
#include "King.h"
class Queen :public Piece{
private:
    King* opponentKing;
public:
    explicit Queen(string& imagePath_, string& pieceTeam_, vector<vector<Box *>> &chessBoard_, Box *pieceBox_,King* _opponentKing, int X, int Y, bool movable_):opponentKing(_opponentKing),
    Piece(imagePath_, pieceTeam_, chessBoard_, pieceBox_, X, Y, movable_){

    }

    int Check() override;
    void Moves(int X,int Y)override;

};


#endif //CHESS_2_0_QUEEN_H
