//
// Created by robert12 on 10/27/23.
//


#ifndef CHESS_2_0_PAWN_H
#define CHESS_2_0_PAWN_H

#include <list>
#include <utility>
#include "King.h"


using std::list;
class Pawn :public Piece{
private:
    King* opponentKing;
    list<std::pair<int, int>> &white_pawn_moves(int x, int y);
    list<std::pair<int, int>> &black_pawn_moves(int x, int y);
    int WhiteCheck();
    int BlackCheck();
public:
    explicit Pawn(string& imagePath_, string& pieceTeam_, vector<vector<Box *>> &chessBoard_, Box *pieceBox_,King* _opponentKing, int X, int Y, bool movable_):opponentKing(_opponentKing),
    Piece(imagePath_, pieceTeam_, chessBoard_, pieceBox_, X, Y, movable_){
    }

    int Check() override;
    void Moves(int X,int Y)override;


};

#endif //CHESS_2_0_PAWN_H
