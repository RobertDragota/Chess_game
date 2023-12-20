//
// Created by robert12 on 10/16/23.
//

#ifndef CHESS_2_0_BOARD_H
#define CHESS_2_0_BOARD_H

#include <QGraphicsProxyWidget>
#include <QApplication>
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QDrag>
#include <QObject>
#include <QMimeData>
#include <QDragEnterEvent>
#include<list>
#include <vector>
#include <QPushButton>
#include <ostream>
#include "Box.h"
#include "Rook.h"
#include "Pawn.h"
#include "Horse.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"

using std::vector;
using std::list;
class Board :public QGraphicsScene{
Q_OBJECT
public:
    Board();

    void drawBoxes();

    void addPieces();

    vector<vector<Box *>> &getChessBoard();

    list<Piece *> &getWhiteTeam();

    list<Piece *> &getBlackTeam();

    Piece *getBlackKing();

    Piece *getWhiteKing();

    void RemovePiecefromTeam(Piece *PIECE, list<Piece *> &TEAM);

    void resetBoard();

private:

    QPushButton *button = new QPushButton("Restart Game!");
    QGraphicsProxyWidget *buttonProxy = new QGraphicsProxyWidget();
    list<Piece *> white_team;
    list<Piece *> black_team;
    King* whiteKing;
    King* blackKing;
    string team, path;
    vector<vector<Box *>> Board_game;

    void connect();
};


#endif //CHESS_2_0_BOARD_H
