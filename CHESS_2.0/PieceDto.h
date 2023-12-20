//
// Created by robert12 on 11/23/23.
//

#ifndef CHESS_2_0_PIECEDTO_H
#define CHESS_2_0_PIECEDTO_H


#include <QGraphicsPixmapItem>
#include "Box.h"
class PieceDto : public QGraphicsPixmapItem{
private:
    Box *pieceBox;
    std::string pieceTeam;
    std::string imagePath;
public:
    PieceDto(std::string imagePath_, std::string pieceTeam_, Box *pieceBox_);

    const string &getPieceTeam() const;

    const string &getImagePath() const;
};



#endif //CHESS_2_0_PIECEDTO_H
