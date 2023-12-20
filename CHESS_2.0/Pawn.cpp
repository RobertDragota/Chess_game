//
// Created by robert12 on 10/27/23.
//

#include "Pawn.h"


void Pawn::Moves(int X, int Y) {
    DeleteMovablePos();
    setMovablePos(this->pieceTeam == "white" ? white_pawn_moves(X, Y) : black_pawn_moves(X, Y));
}

list<pair<int, int>> &Pawn::white_pawn_moves(int x, int y) {

    if (inside(x + 1, y + 1)) {
        if (isOpponent(x + 1, y + 1))
            AddMovablePos({x + 1, y + 1});
    }
    if (inside(x + 1, y - 1)) {
        if (isOpponent(x + 1, y - 1))
            AddMovablePos({x + 1, y - 1});
    }
    if (inside(x + 1, y) && (chessBoard[x + 1][y]->getStatus() == "free")) {
        AddMovablePos({x + 1, y});
        if (x == 1 && inside(x + 2, y) && (chessBoard[x + 2][y]->getStatus() == "free"))
            AddMovablePos({x + 2, y});
    }
    return getMovablePos();
}

list<pair<int, int>> &Pawn::black_pawn_moves(int x, int y) {

    if (inside(x - 1, y - 1)) {
        if (isOpponent(x - 1, y - 1))
            AddMovablePos({x - 1, y - 1});
    }
    if (inside(x - 1, y + 1)) {
        if (isOpponent(x - 1, y + 1))
            AddMovablePos({x - 1, y + 1});
    }
    if (inside(x - 1, y) && (chessBoard[x - 1][y]->getStatus() == "free")) {
        AddMovablePos({x - 1, y});
        if (x == 6 && inside(x - 2, y) && (chessBoard[x - 2][y]->getStatus() == "free"))
            AddMovablePos({x - 2, y});
    }
    return getMovablePos();
}

int Pawn::WhiteCheck() {
    King *king = nullptr;
    if (inside(this->getPieceX() + 1, this->getPieceY() + 1)) {

        if (isOpponent(this->getPieceX() + 1, this->getPieceY() + 1))
            king = dynamic_cast<King *>(chessBoard[this->getPieceX() + 1][this->getPieceY() + 1]->childItems().first());
        if (king)
            return 1;  // Is check directly to the King

    }
    if (inside(this->getPieceX() + 1, this->getPieceY() - 1)) {
        if (isOpponent(this->getPieceX() + 1, this->getPieceY() - 1))
            king = dynamic_cast<King *>(chessBoard[this->getPieceX() + 1][this->getPieceY() - 1]->childItems().front());
        if (king)
            return 1;  // Is check directly to the King
    }
    return 0;
}

int Pawn::BlackCheck() {
    King *king = nullptr;
    if (inside(this->getPieceX() - 1, this->getPieceY() - 1)) {

        if (isOpponent(this->getPieceX() - 1, this->getPieceY() - 1))
            king = dynamic_cast<King *>(chessBoard[this->getPieceX() - 1][this->getPieceY() - 1]->childItems().first());
        if (king)
            return 1;  // Is check directly to the King

    }
    if (inside(this->getPieceX() - 1, this->getPieceY() + 1)) {
        if (isOpponent(this->getPieceX() - 1, this->getPieceY() + 1))
            king = dynamic_cast<King *>(chessBoard[this->getPieceX() - 1][this->getPieceY() + 1]->childItems().front());
        if (king)
            return 1;  // Is check directly to the King
    }
    return 0;
}

int Pawn::Check() {
  //  DeleteOpCoords();
    DeleteMovablePos();
    return this->getPieceTeam() == "white" ? WhiteCheck() : BlackCheck();
}

