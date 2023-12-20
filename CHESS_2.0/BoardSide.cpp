//
// Created by robert12 on 11/21/23.
//

#include "BoardSide.h"

BoardSide::BoardSide() : status("free") {
    this->setScene(graphicsScene);
    drawBoxesForDeaths();
}

void BoardSide::drawBoxesForDeaths() {

    class Box *box;
    auto color = QColor(205,133,63);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 2; j++) {
            box = new class Box(100 * j, 100 * i, 100, 100,"free","",color);
            box->setBrush(color);
            graphicsScene->addItem(box);
            boxes.emplace_back(box);
        }

    }

}

Box *BoardSide::getNextFreeBox()  {
   for(const auto & it:boxes){
       if(it->childItems().empty())
           return it;
   }
}

void BoardSide::ResetBoardSide() {
    for(const auto & it:boxes){
        if(!it->childItems().empty())
        {
            delete it->childItems().first();
        }

    }
}


