//
// Created by robert12 on 10/16/23.
//

#include "Horse.h"

void Horse::Moves(int X, int Y) {
    DeleteMovablePos();
    //DeleteOpCoords();
    vector<pair<int, int>> directions = {{2,  1},
                                         {1,  2},
                                         {-2, 1},
                                         {1,  -2},
                                         {-2, -1},
                                         {-1, -2},
                                         {2,  -1},
                                         {-1, 2}};
    for (const auto &[dx, dy]: directions) {
        int newX = X + dx;
        int newY = Y + dy;
        if (validPos(newX, newY))
                AddMovablePos({newX, newY});
    }
}


int Horse::Check() {
    bool flag=false;
    std::for_each(movable_pos.begin(), movable_pos.end(), [&](const auto &it) -> void {
        if (isOpponent(it.first,it.second) && dynamic_cast<King *>(chessBoard[it.first][it.second]->childItems().first()) ==
            opponentKing) {
            // Is check directly to the King
            flag=true;
        }
    });
    if(flag)
        return 1;
return 0;
}