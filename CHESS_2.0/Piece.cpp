//
// Created by robert12 on 10/16/23.
//

#include "Piece.h"

Piece::Piece(string &imagePath_, std::string &pieceTeam_, vector<vector<Box *>> &chessBoard_, Box *pieceBox_, int X,
             int Y,
             bool movable_) : QGraphicsPixmapItem(
        QPixmap::fromImage(QImage(QString::fromStdString(imagePath_))).scaled(80, 80)),
                              pieceTeam(pieceTeam_), chessBoard(chessBoard_), pieceBox(pieceBox_), pieceX(X),
                              pieceY(Y), movable(movable_), imagePath(imagePath_) {
    this->setParentItem(pieceBox_);
    this->setPos(pieceBox_->rect().x() + (pieceBox_->rect().width() - 80) / 2,
                 pieceBox_->rect().y() + (pieceBox_->rect().height() - 80) / 2);
    pieceBox_->ChangeStatus("hold");
}

std::string Piece::getPieceTeam() { return pieceTeam; }

std::string Piece::getImagePath() { return imagePath; }

std::list<pair<int, int>> &Piece::getMovablePos() { return movable_pos; }

std::list<pair<int, int>> &Piece::getOpponentsPos() { return opponents_pos; }

int Piece::getPieceX() { return pieceX; }

int Piece::getPieceY() { return pieceY; }

void Piece::setPieceTeam(std::string newPieceTeam) { pieceTeam = std::move(newPieceTeam); }

void Piece::setImagePath(std::string newImagePath) { imagePath = std::move(newImagePath); }

void Piece::setMovablePos(list<pair<int, int>> &new_movable_pos) { movable_pos = new_movable_pos; }

void Piece::setParentBox(Box *parentBox) {
    pieceBox = parentBox;
    this->setParentItem(pieceBox);
}

void Piece::setPosition() {
    this->setPos(pieceBox->rect().x() + (pieceBox->rect().width() - 80) / 2,
                 pieceBox->rect().y() + (pieceBox->rect().height() - 80) / 2);
}

void Piece::setCoordonates(int X, int Y) {
    pieceX = X;
    pieceY = Y;
}

void Piece::unblockPiece() { movable = true; }

void Piece::blockPiece() { movable = false; }

bool Piece::isMovable() { return movable; }


void Piece::AddOpCoords(pair<int, int> _op_coords) {
    opponents_pos.emplace_back(_op_coords);
}

void Piece::AddMovablePos(pair<int, int> _op_coords) {
    movable_pos.emplace_back(_op_coords);
}

void Piece::DeleteOpCoords() {
    opponents_pos.clear();
}

void Piece::DeleteMovablePos() {
    movable_pos.clear();
}

bool Piece::isOpponent(int X, int Y) {
    return !chessBoard[X][Y]->childItems().empty() &&
           dynamic_cast<Piece *>(chessBoard[X][Y]->childItems().front())->getPieceTeam() !=
           pieceTeam;
}

bool Piece::inside(int X, int Y) {
    return X >= 0 && X < 8 && Y >= 0 && Y < 8;
}

bool Piece::validPos(int X, int Y) {
    return inside(X, Y) && (chessBoard[X][Y]->getStatus() == "free" || isOpponent(X, Y));
}

int Piece::CheckForOthers(int startX, int &stopX, int startY, int &stopY, int incrementX, int incrementY) {
    int numberOfOpponents = 0, numberOfMates = 0;
    pair<int, int> opponentCoords;
    while (startX != stopX && startY != stopY) {
        if (isOpponent(startX, startY)) {
            // In this case, there is an opponent between the king and the rook.
            // The opponent has the same color as the king.
            // We count how many opponents we find and store their coordinates to decide whether to block them or not.

            opponentCoords = {startX, startY};
            numberOfOpponents++;
        } else {
            // In this case, the piece is an ally that we will not block.
            // However, we will count how many allies we have on this path.
            if (!chessBoard[startX][startY]->childItems().empty())
                numberOfMates++;
        }
        startX += incrementX;
        startY += incrementY;
    }

    if (numberOfMates == 0 && numberOfOpponents == 1) {
        // In this situation, we should block the opponent to ensure that the opponent king cannot put itself in check.
        // Howerver we will check if the opponent can take the rook
        Piece *opponent = dynamic_cast<Piece *>(chessBoard[opponentCoords.first][opponentCoords.second]->childItems().first());
        opponent->blockPiece();
        //We have to determinate the movable_pos vector to check if this opponent can take the piece or not
        opponent->Moves(opponent->getPieceX(), opponent->getPieceY());
        std::for_each(opponent->getMovablePos().begin(), opponent->getMovablePos().end(), [&](const auto &it) {
            if (it.first == this->getPieceX() && it.second == this->getPieceY())
                //If piece position is present in opponent's movabele_pos vector then we should add piece coords to opponent OppCords vector
            {
                opponent->AddOpCoords({this->getPieceX(), this->getPieceY()});
                opponent->unblockPiece();
            }
        });

        return 2;
    }
    return 0;
}

void Piece::colorPath() {

    std::for_each(movable_pos.begin(), movable_pos.end(), [&](const auto &it) {
        if (chessBoard[it.first][it.second]->childItems().empty())
            chessBoard[it.first][it.second]->setBrush(QColor(244, 164, 96));
        else
            chessBoard[it.first][it.second]->setBrush(QColor(220, 20, 60));
    });
}


std::list<std::pair<int, int>> &Piece::intersectLists() {
    std::list<std::pair<int, int>> intersection;
    Moves(getPieceX(), getPieceY());

   for(const auto& it1:getMovablePos())
       for(const auto &it2:getOpponentsPos())
           if(it1==it2)
               intersection.emplace_back(it1);

    setMovablePos(intersection);
    return getMovablePos();

}

