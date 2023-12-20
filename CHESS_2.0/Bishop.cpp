//
// Created by robert12 on 10/16/23.
//

#include "Bishop.h"

void Bishop::Moves(int X, int Y) {
    DeleteMovablePos();
    // DeleteOpCoords();
    vector<pair<int, int>> directions = {{1,  1},
                                         {-1, -1},
                                         {-1, 1},
                                         {1,  -1}};
    for (const auto &[dx, dy]: directions) {
        for (int i = 1; i <= 7; i++) {
            int newX = X + i * dx;
            int newY = Y + i * dy;
            if (validPos(newX, newY)) {
                if (isOpponent(newX, newY)) {
                    AddMovablePos({newX, newY});
                    break;
                } else
                    AddMovablePos({newX, newY});
            } else
                break;

        }
    }
}

int Bishop::Check() {
    bool flag = false;
    int delta_X = opponentKing->getPieceX() - this->getPieceX();
    int delta_Y = opponentKing->getPieceY() - this->getPieceY();
    int startX, stopX;
    int startY, stopY;
    int deltaXSign = (delta_X > 0) ? 1 : (delta_X < 0) ? -1 : 0;
    int deltaYSign = (delta_Y > 0) ? 1 : (delta_Y < 0) ? -1 : 0;
    startX = this->getPieceX() + deltaXSign;
    startY = this->getPieceY() + deltaYSign;
    stopX = opponentKing->getPieceX();
    stopY = opponentKing->getPieceY();


    if (abs(delta_X) != abs(delta_Y))
            return 0;


    std::for_each(movable_pos.begin(), movable_pos.end(), [&](const auto &it) -> void {
        if (isOpponent(it.first, it.second) &&
            dynamic_cast<King *>(chessBoard[it.first][it.second]->childItems().first()) ==
            opponentKing) {
            // Is check directly to the King
            flag = true;
        }
    });
    if (flag) {
        stopX += deltaXSign;
        stopY += deltaYSign;
        if(inside(stopX,stopY))
            chessBoard.at(stopX).at(stopY)->ChangeSubStatus(pieceTeam);
        return 1;
    }


    return CheckForOthers(startX, stopX, startY, stopY, deltaXSign, deltaYSign);


}