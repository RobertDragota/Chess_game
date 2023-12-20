//
// Created by robert12 on 11/21/23.
//

#ifndef CHESS_2_0_BOARDSIDE_H
#define CHESS_2_0_BOARDSIDE_H


#include "Box.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QColor>
#include <string>
#include <vector>
class BoardSide: public QGraphicsView {
private:
    std::string status;
    std::vector<class Box*>boxes;
    QGraphicsScene *graphicsScene=new QGraphicsScene;
public:
    BoardSide();

    void drawBoxesForDeaths();
    void ResetBoardSide();

     class Box* getNextFreeBox();

    ~BoardSide() {
        delete graphicsScene;
    }
;
};


#endif //CHESS_2_0_BOARDSIDE_H
