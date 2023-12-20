//
// Created by robert12 on 10/16/23.
//

#include "Board.h"
#include "Rook.h"
Board::Board() {

    drawBoxes();
    team = "white", path = "white_king.png";
    whiteKing = new King(path, team, Board_game, Board_game[0][4], black_team, 0, 4, true);
    team = "black", path = "black_king.png";
    blackKing = new King(path, team, Board_game, Board_game[7][4], white_team, 7, 4, true);
    addPieces();
}


void Board::drawBoxes() {
    vector<Box *> row_boxes;
    Box *box;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            box = (i + j) % 2 == 1 ? new Box(100 * j, 100 * i, 100, 100, "free", "free", QColor(139,69,19))
                                   : new Box(
                            100 * j, 100 * i, 100, 100, "free", "free", QColor(255,222,173));
            this->addItem(box);
            row_boxes.emplace_back(box);
        }
        Board_game.emplace_back(row_boxes);
        row_boxes.clear();
    }
}

void Board::addPieces() {
    team = "white";

    path = "white_rook.png";
    white_team.emplace_back(new Rook(path, team, Board_game, Board_game[0][0], blackKing, 0, 0, true));
    path = "white_horse.png";
    white_team.emplace_back(new Horse(path, team, Board_game, Board_game[0][1], blackKing, 0, 1, true));
    path = "white_bishop.png";
    white_team.emplace_back(new Bishop(path, team, Board_game, Board_game[0][2], blackKing, 0, 2, true));
    path = "white_queen.png";
    white_team.emplace_back(new Queen(path, team, Board_game, Board_game[0][3], blackKing, 0, 3, true));
    path = "white_king.png";
    white_team.emplace_back(whiteKing);
    path = "white_bishop.png";
    white_team.emplace_back(new Bishop(path, team, Board_game, Board_game[0][5], blackKing, 0, 5, true));
    path = "white_horse.png";
    white_team.emplace_back(new Horse(path, team, Board_game, Board_game[0][6], blackKing, 0, 6, true));
    path = "white_rook.png";
    white_team.emplace_back(new Rook(path, team, Board_game, Board_game[0][7], blackKing, 0, 7, true));
    path = "white_pawn.png";
    for (int i = 0; i < 8; i++)
        white_team.emplace_back(new Pawn(path, team, Board_game, Board_game[1][i], blackKing, 1, i, true));


    team = "black";
    path = "black_rook.png";
    black_team.emplace_back(new Rook(path, team, Board_game, Board_game[7][0], whiteKing, 7, 0, true));
    path = "black_horse.png";
    black_team.emplace_back(new Horse(path, team, Board_game, Board_game[7][1], whiteKing, 7, 1, true));
    path = "black_bishop.png";
    black_team.emplace_back(new Bishop(path, team, Board_game, Board_game[7][2], whiteKing, 7, 2, true));
    path = "black_queen.png";
    black_team.emplace_back(new Queen(path, team, Board_game, Board_game[7][3], whiteKing, 7, 3, true));
    path = "black_king.png";
    black_team.emplace_back(blackKing);
    path = "black_bishop.png";
    black_team.emplace_back(new Bishop(path, team, Board_game, Board_game[7][5], whiteKing, 7, 5, true));
    path = "black_horse.png";
    black_team.emplace_back(new Horse(path, team, Board_game, Board_game[7][6], whiteKing, 7, 6, true));
    path = "black_rook.png";
    black_team.emplace_back(new Rook(path, team, Board_game, Board_game[7][7], whiteKing, 7, 7, true));
    path = "black_pawn.png";
    for (int i = 0; i < 8; i++)
        black_team.emplace_back(new Pawn(path, team, Board_game, Board_game[6][i], whiteKing, 6, i, true));

    for (int i = 0; i < 8; i++) {
        Board_game[0][i]->ChangeSubStatus("white");

        Board_game[1][i]->ChangeSubStatus("white");

        Board_game[6][i]->ChangeSubStatus("black");

        Board_game[7][i]->ChangeSubStatus("black");
    }

}

void Board::RemovePiecefromTeam(Piece *PIECE, list<Piece *> &TEAM) {
    auto found = std::find(TEAM.begin(), TEAM.end(), PIECE);
    if (found != TEAM.end())
        TEAM.erase(found);
}

void Board::resetBoard() {

    std::for_each(white_team.begin(), white_team.end(), [&](const auto &it) -> void {
        delete it;
    });
    std::for_each(black_team.begin(), black_team.end(), [&](const auto &it) -> void {
        delete it;
    });

    std::for_each(Board_game.begin(), Board_game.end(), [&](std::vector<Box *> &row) -> void {
        std::for_each(row.begin(), row.end(), [&](Box *it) {
            delete it;
        });
        row.clear();
    });
    white_team.clear();
    black_team.clear();
    Board_game.clear();
    drawBoxes();
    team = "white", path = "white_king.png";
    whiteKing = new King(path, team, Board_game, Board_game[0][4], black_team, 0, 4, true);
    team = "black", path = "black_king.png";
    blackKing = new King(path, team, Board_game, Board_game[7][4], white_team, 7, 4, true);
    addPieces();

}

void Board::connect() {

}

list<Piece *> &Board::getWhiteTeam() { return white_team; }

list<Piece *> &Board::getBlackTeam() { return black_team; }

vector<vector<Box *>> &Board::getChessBoard() { return Board_game; }

Piece *Board::getBlackKing() { return blackKing; }

Piece *Board::getWhiteKing() { return whiteKing; }

