//
// Created by robert12 on 11/9/23.
//

#include "Game.h"

Game::Game(Board &_chessBoard, BoardSide *boardSideLeft_, BoardSide *boardSideRight_) : chessBoard(&_chessBoard),
                                                                                        boardSideLeft(boardSideLeft_),
                                                                                        boardSideRight(boardSideRight_),
                                                                                        box(nullptr) {
    this->setScene(&_chessBoard);
    this->setMinimumSize(800, 840);
    turn = true;
    check = 0;
}

void Game::RepaintToOriginalColor() {
    auto board = chessBoard->getChessBoard();
    std::for_each(board.begin(), board.end(), [&](const auto &row) -> void {
        std::for_each(row.begin(), row.end(), [&](class Box *it) -> void {
            it->originalColor();
        });
    });
}

void Game::SetDraggingPos(class Box *_box, QMouseEvent *event) {
    dragStartPosition = event->pos();
    box = _box;
    box->setBrush(QBrush(Qt::green));
    mime_type = QString::fromStdString(
            dynamic_cast<Piece *>(box->childItems().front())->getImagePath());
}

void Game::SearchPiece(class Box *_box, QMouseEvent *event, Piece *piece, list<Piece *> &mates) {
    auto found = std::find(mates.begin(), mates.end(), piece);
    King *king = dynamic_cast<King *>(piece);
    if (found != mates.end()) {
        if (piece->isMovable()) {
            if (king) {
                king->SafePos();
            } else {
                if ((check == 1 || check == 2) && !piece->getOpponentsPos().empty())
                    piece->intersectLists();
                else
                    piece->Moves(piece->getPieceX(), piece->getPieceY());
            }
            piece->colorPath();
            SetDraggingPos(_box, event);
        }
    }

}

void Game::mousePressEvent(QMouseEvent *event) {
    if (event->button() & Qt::LeftButton) {
        RepaintToOriginalColor();
        dragStartPosition.setX(0);
        dragStartPosition.setY(0);
        auto board = chessBoard->getChessBoard();
        std::for_each(board.begin(), board.end(),
                      [&](std::vector<class Box *> &row) -> void {
                          std::for_each(row.begin(), row.end(), [&](class Box *col) -> void {
                              if (col->getStatus() != "free")
                                  if (col->contains(mapToScene(event->position().toPoint()))) {
                                      auto piece = dynamic_cast<Piece *>(col->childItems().front());
                                      turn ? SearchPiece(col, event, piece, chessBoard->getWhiteTeam()) : SearchPiece(
                                              col, event, piece, chessBoard->getBlackTeam());
                                      return;
                                  }
                          });
                      });
    }
}

void Game::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton && !dragStartPosition.isNull()) {
        int distance = (event->pos() - dragStartPosition).manhattanLength();
        if (distance >= QApplication::startDragDistance()) {
            QPointF cursorOffset = dynamic_cast<Piece *>(box->childItems().front())->boundingRect().center();
            auto mimeData = new QMimeData;
            mimeData->setData(mime_type, QByteArray());
            auto drag = new QDrag(this);
            drag->setHotSpot(cursorOffset.toPoint());
            drag->setMimeData(mimeData);
            drag->setPixmap(dynamic_cast<Piece *>(box->childItems().front())->pixmap());
            drag->exec();
            dragStartPosition = QPoint();
        }
    }
}

void Game::dragEnterEvent(QDragEnterEvent *event) {
    if (event->mimeData()->hasFormat(mime_type)) {
        if (event->source() == this) {

            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    }
}

void Game::dragMoveEvent(QDragMoveEvent *event) {
    if (event->mimeData()->hasFormat(
            mime_type)) {
        if (event->source() == this) {

            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    }
}

void Game::UpdateSubStatusAction(list<Piece *> &pieces, string &&Team) {
    list<pair<int, int>> moves;
    std::for_each(pieces.begin(), pieces.end(), [&](Piece *it) -> void {
        dynamic_cast<class Box *>(it->parentItem())->ChangeSubStatus(Team);
        auto pawn = dynamic_cast<Pawn *>(it);
        if (pawn) {
            if (Team == "white") {
                if (pawn->validPos(pawn->getPieceX() + 1, pawn->getPieceY() + 1))
                    chessBoard->getChessBoard()[pawn->getPieceX() + 1][pawn->getPieceY() + 1]->ChangeSubStatus("white");
                if (pawn->validPos(pawn->getPieceX() + 1, pawn->getPieceY() - 1))
                    chessBoard->getChessBoard()[pawn->getPieceX() + 1][pawn->getPieceY() - 1]->ChangeSubStatus("white");
            } else {
                if (pawn->validPos(pawn->getPieceX() - 1, pawn->getPieceY() - 1))
                    chessBoard->getChessBoard()[pawn->getPieceX() - 1][pawn->getPieceY() - 1]->ChangeSubStatus("black");
                if (pawn->validPos(pawn->getPieceX() - 1, pawn->getPieceY() + 1))
                    chessBoard->getChessBoard()[pawn->getPieceX() - 1][pawn->getPieceY() + 1]->ChangeSubStatus("black");
            }

        } else {
            it->Moves(it->getPieceX(), it->getPieceY());
            moves = it->getMovablePos();
            for (const auto &_it: moves)
                chessBoard->getChessBoard()[_it.first][_it.second]->ChangeSubStatus(Team);
        }
    });
}

void Game::UpdateSubStatus() {
    list<pair<int, int>> moves;
    turn ? UpdateSubStatusAction(chessBoard->getWhiteTeam(), "white") : UpdateSubStatusAction(
            chessBoard->getBlackTeam(), "black");
}

bool Game::isCheckAction(list<Piece *> &opponents) {
    bool flag = false;
    std::for_each(opponents.begin(), opponents.end(), [&](Piece *it) -> void {
        // Is check directly to the King
        if (it->Check() == 1)
            check = 1;
        if (it->Check() == 2)
            flag = true;

    });
    if (!check && flag)
        check = 2;

    return check == 1;
}

bool Game::isCheck() {
    return turn ? isCheckAction(chessBoard->getWhiteTeam()) : isCheckAction(chessBoard->getBlackTeam());
}

bool Game::isCheckMate(list<Piece *> &mates) {
    King *king = dynamic_cast<King *>(mates.front()->getPieceTeam() == "white" ? chessBoard->getWhiteKing()
                                                                               : chessBoard->getBlackKing());
    //Check if King has safe position to move on
    if (!king->SafePos()) {// If it doesn't then check is other of his mates is free to move
        king->blockPiece();
        auto found = std::find_if(mates.begin(), mates.end(), [&](Piece *it) -> bool {
            return it->isMovable();
        });
        return !(found != mates.end());// if it was found a free piece that means that is not checkmate
    }
    return false;

}

void Game::ResetOpCoords() {
    auto whiteTeam = chessBoard->getWhiteTeam();
    std::for_each(whiteTeam.begin(), whiteTeam.end(), [&](Piece *it) -> void {
        it->DeleteOpCoords();
    });
    auto blackTeam = chessBoard->getBlackTeam();
    std::for_each(blackTeam.begin(), blackTeam.end(), [&](Piece *it) -> void {
        it->DeleteOpCoords();
    });
}

void Game::EliminatePiece(Piece *piece) {

    piece->parentItem()->childItems().clear();
    chessBoard->RemovePiecefromTeam(piece, turn ? chessBoard->getBlackTeam()
                                                : chessBoard->getWhiteTeam());


    if (piece->getPieceTeam() == "white") {
        new PieceDto(piece->getImagePath(), piece->getPieceTeam(), boardSideLeft->getNextFreeBox());
    } else {
        new PieceDto(piece->getImagePath(), piece->getPieceTeam(), boardSideRight->getNextFreeBox());
    }
    delete piece;
}

void Game::SetNewEnviorment(class Box *sourceBox, class Box *targetBox, Piece *piece, int newX, int newY) {
    sourceBox->ChangeStatus("free");
    targetBox->ChangeStatus("hold");
    piece->setParentBox(targetBox);
    piece->setPosition();
    piece->setCoordonates(newX, newY);
    UpdateSubStatus();
    RepaintToOriginalColor();
    ResetOpCoords();
}

void Game::SelectUsefullPieces(Piece *opponent, list<Piece *> &mates) {
    list<pair<int, int>> moves;
    list<Piece *> kingTeam;
    std::copy_if(mates.begin(), mates.end(), std::back_inserter(kingTeam), [&](Piece *it) -> bool {
        return !dynamic_cast<King *>(it);
    });

    std::for_each(kingTeam.begin(), kingTeam.end(), [&](Piece *it) -> void {
        it->Moves(it->getPieceX(), it->getPieceY());
        moves = it->getMovablePos();
        pair<int, int> op_coord(opponent->getPieceX(), opponent->getPieceY());
        auto found = std::find(moves.begin(), moves.end(), op_coord);
        if (found == moves.end()) {
            it->blockPiece();
        } else {
            it->unblockPiece(), it->AddOpCoords(op_coord);
        }

    });

    auto horse = dynamic_cast<Horse *>(opponent);
    list<pair<int, int>> dangerous_moves;
    auto whiteKing = dynamic_cast<King *>(chessBoard->getWhiteKing());
    auto blackKing = dynamic_cast<King *>(chessBoard->getBlackKing());
    if (!horse) {
        turn ? CheckForUsefullPieces(dangerous_moves, blackKing, opponent) : CheckForUsefullPieces(dangerous_moves,
                                                                                                   whiteKing,
                                                                                                   opponent);

        std::for_each(kingTeam.begin(), kingTeam.end(), [&](Piece *it) -> void {
            it->Moves(it->getPieceX(), it->getPieceY());
            moves = it->getMovablePos();
            std::for_each(moves.begin(), moves.end(), [&](const auto &itr) -> void {
                auto found = std::find(dangerous_moves.begin(), dangerous_moves.end(), itr);
                if (found != dangerous_moves.end())
                    it->unblockPiece(), it->AddOpCoords(*found);
            });
        });


    }
}

void Game::CheckForUsefullPieces(list<pair<int, int>> &resultList, King *king, Piece *opponent) {
    int delta_x = opponent->getPieceX() - king->getPieceX();
    int delta_y = opponent->getPieceY() - king->getPieceY();

    int step_x = (delta_x > 0) ? 1 : (delta_x < 0) ? -1 : 0;
    int step_y = (delta_y > 0) ? 1 : (delta_y < 0) ? -1 : 0;

    int aux_X = king->getPieceX() + step_x;
    int aux_Y = king->getPieceY() + step_y;

    while (aux_X != opponent->getPieceX() || aux_Y != opponent->getPieceY()) {
        resultList.emplace_back(aux_X, aux_Y);
        aux_X += step_x;
        aux_Y += step_y;
    }
}

void Game::CheckScenario(Piece *opponent, list<Piece *> &pieces, string &&checkStatus, string &&checkMateStatus) {
    emit GameStat(checkStatus);
    SelectUsefullPieces(opponent, pieces);
    if (isCheckMate(pieces))
            emit GameStat(checkMateStatus);

}

void Game::dropPiece(QDropEvent *event) {
    list<pair<int, int>> moves;
    Piece *piece = dynamic_cast<Piece *>(box->childItems().front());

    if (dynamic_cast<King *>(piece)) {
    }

    auto board = chessBoard->getChessBoard();
    auto whiteKing = dynamic_cast<King *>(chessBoard->getWhiteKing());
    auto blackKing = dynamic_cast<King *>(chessBoard->getBlackKing());

    for (const auto &it: piece->getMovablePos()) {
        if (board[it.first][it.second]->contains(mapToScene(event->position().toPoint()))) {
            if (board[it.first][it.second]->getStatus() == "hold") {
                auto opponent = dynamic_cast<Piece *>(board[it.first][it.second]->childItems().front());
                EliminatePiece(opponent);
            }
            whiteKing->UnblockMates(chessBoard->getWhiteTeam());
            blackKing->UnblockMates(chessBoard->getBlackTeam());
            SetNewEnviorment(box, board[it.first][it.second], piece, it.first, it.second);

            if (check == 1)
                check = 0;
            if (isCheck() == 1) {
                check = 1;
                turn ? CheckScenario(piece, chessBoard->getBlackTeam(), "Check on Black", "WHITE WIN!") :
                CheckScenario(piece, chessBoard->getWhiteTeam(), "Check on White", "BLACK WIN!");
            }
            turn = !turn;
            if (check == 0 || check == 2)
                turn ? emit GameStat("White turn") : emit GameStat("Black turn");
            break;
        }
    }
}


void Game::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat(
            mime_type)) {
        dropPiece(event);
        chessBoard->update();
        if (event->source() == this) {

            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }
    }
}


void Game::RestartGame() {

    box = nullptr;
    check = 0;
    turn = true;
    chessBoard->resetBoard();
    boardSideLeft->ResetBoardSide();
    boardSideRight->ResetBoardSide();
    emit GameStat("White turn");

}

BoardSide *Game::getBoardSideLeft() const {
    return boardSideLeft;
}

BoardSide *Game::getBoardSideRight() const {
    return boardSideRight;
}

bool Game::BlackPawnOnWhiteSide() {

}

bool Game::WhitePawnOnBlackSide() {

}
