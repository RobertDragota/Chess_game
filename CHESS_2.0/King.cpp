//
// Created by robert12 on 10/16/23.
//

#include "King.h"
#include "Pawn.h"


void King::UnblockMates(list<Piece *> &mates) {
    std::for_each(mates.begin(), mates.end(), [&](const auto &it) -> void {
        const_cast<Piece *>(it)->unblockPiece();
    });
}

void King::Moves(int X, int Y) {
    DeleteMovablePos();
    vector<pair<int, int>> directions = {{1,  0},
                                         {-1, 0},
                                         {0,  1},
                                         {0,  -1},
                                         {1,  1},
                                         {-1, -1},
                                         {-1, 1},
                                         {1,  -1}};
    std::for_each(directions.begin(), directions.end(), [&](const auto &it) -> void {
        if (validPos(this->getPieceX() + it.first, this->getPieceY() + it.second))
            AddMovablePos({this->getPieceX() + it.first, this->getPieceY() + it.second});
    });
}

int King::Check() {
    return 0;
}

bool King::SafePos() {
    DeleteMovablePos();
   // DeleteOpCoords();
    Moves(this->getPieceX(), this->getPieceY());
    list<pair<int, int>> safe;
    bool safe_flag;
    for (const auto &it: movable_pos) {
        if (chessBoard[it.first][it.second]->getStatus() == "free" &&
            chessBoard[it.first][it.second]->getSubStatus() == this->pieceTeam)
            safe.emplace_back(it);
        if (chessBoard[it.first][it.second]->getStatus() == "hold" &&
            chessBoard[it.first][it.second]->getSubStatus() != this->pieceTeam) {
            chessBoard[it.first][it.second]->ChangeStatus("free");
            safe_flag = true;
            for (const auto &itr: opponents) {

                Pawn *PAWN = dynamic_cast<Pawn *>(itr);
                if (PAWN) {
                    int x = PAWN->getPieceX();
                    int y = PAWN->getPieceY();
                    if (it == (pair<int, int>) {x + 1, y + 1} || it == (pair<int, int>) {x - 1, y - 1}
                        || it == (pair<int, int>) {x + 1, y - 1} ||
                        it == (pair<int, int>) {x - 1, y + 1})
                        safe_flag = false;
                } else {

                    itr->Moves(itr->getPieceX(), itr->getPieceY());
                    auto OpponentMoves = itr->getMovablePos();
                    auto found = std::find(OpponentMoves.begin(), OpponentMoves.end(), it);
                    if (found != OpponentMoves.end())
                        safe_flag = false;
                }
            }
            chessBoard[it.first][it.second]->ChangeStatus("hold");
            if (safe_flag)
                safe.emplace_back(it);
        }
    }

    setMovablePos(safe);
    return !getMovablePos().empty();//daca mai exita pozitii safe atunci jocul continua
}
