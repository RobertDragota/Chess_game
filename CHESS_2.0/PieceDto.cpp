//
// Created by robert12 on 11/23/23.
//

#include "PieceDto.h"

PieceDto::PieceDto(string imagePath_, string pieceTeam_, Box *pieceBox_) :QGraphicsPixmapItem(
        QPixmap::fromImage(QImage(QString::fromStdString(imagePath_))).scaled(80, 80)),imagePath(imagePath_),pieceTeam(pieceTeam_),pieceBox(pieceBox_){
    this->setParentItem(pieceBox_);
    this->setPos(pieceBox_->rect().x() + (pieceBox_->rect().width() - 80) / 2,
                 pieceBox_->rect().y() + (pieceBox_->rect().height() - 80) / 2);
}

const string &PieceDto::getPieceTeam() const {
return pieceTeam;
}

const string &PieceDto::getImagePath() const {
    return imagePath;
}
