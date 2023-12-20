//
// Created by robert12 on 10/16/23.
//

#ifndef CHESS_2_0_KING_H
#define CHESS_2_0_KING_H
#include "Piece.h"
#include <list>
#include <utility>

using std::list;
using std::pair;

class King:public Piece {
private:
    list<Piece *> &opponents;

public:
    explicit King(string& imagePath_, string& pieceTeam_, vector<vector<Box *>> &chessBoard_, Box *pieceBox_,list<Piece*>& _opponents, int X, int Y, bool movable_):opponents(_opponents),
    Piece(imagePath_, pieceTeam_, chessBoard_, pieceBox_, X, Y, movable_){

    }
    bool SafePos();
    void UnblockMates(list<Piece *> &mates);
    void Moves(int X, int Y) override ;

    int Check() override ;
};


#endif //CHESS_2_0_KING_H
