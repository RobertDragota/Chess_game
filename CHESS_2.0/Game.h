//
// Created by robert12 on 11/9/23.
//

#ifndef CHESS_2_0_GAME_H
#define CHESS_2_0_GAME_H

#include "Board.h"
#include <vector>
#include "Box.h"
#include "BoardSide.h"
#include "PieceDto.h"
using std::vector;

class Game : public QGraphicsView {
Q_OBJECT

private:
    class Box *box;
    BoardSide * boardSideLeft;
    BoardSide * boardSideRight;
    Board *chessBoard;
    bool turn;
    int check;
    QPoint dragStartPosition;
    QString mime_type;
public:
    explicit Game(Board &_chessBoard,BoardSide* boardSideLeft_,BoardSide*boardSideRight_);

    BoardSide *getBoardSideLeft() const;

    BoardSide *getBoardSideRight() const;

    void RestartGame();
    bool BlackPawnOnWhiteSide();
    bool WhitePawnOnBlackSide();
protected:
    void mousePressEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void dragEnterEvent(QDragEnterEvent *event) override;

    void dragMoveEvent(QDragMoveEvent *event) override;

    void dropEvent(QDropEvent *event) override;

    void RepaintToOriginalColor();

    void SetDraggingPos(class Box *_box, QMouseEvent *event);

    void SearchPiece(class Box *_box, QMouseEvent *event, Piece *piece, list<Piece *> &mates);

    void UpdateSubStatus();

    void UpdateSubStatusAction(list<Piece *> &pieces, string &&Team);

    bool isCheckAction(list<Piece *> &opponents);

    bool isCheck();

    bool isCheckMate(list<Piece *> &mates);

    void ResetOpCoords();

    void dropPiece(QDropEvent *event);

    void EliminatePiece(Piece *piece);

    void SetNewEnviorment(class Box *sourceBox, class Box *targetBox, Piece *piece, int newX, int newY);

    void SelectUsefullPieces(Piece *opponent, list<Piece *> &mates);

    void CheckScenario(Piece *opponent, list<Piece *> &pieces, string &&checkStatus, string &&checkMateStatus);

    static void CheckForUsefullPieces(list<pair<int, int>> &resultList, King *king, Piece *opponent);


signals:

    void GameStat(string winner);
};


#endif //CHESS_2_0_GAME_H
