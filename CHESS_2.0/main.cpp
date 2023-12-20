#include <QApplication>

#include "Board.h"
#include "Game.h"
#include "GUI.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto CHESS_BOARD = new Board();
    auto boardSideLeft=new BoardSide();
    auto boardSideRight=new BoardSide();
    Game *CHESS = new Game(*CHESS_BOARD,boardSideLeft,boardSideRight);
    GUI *gui = new GUI(CHESS);

    gui->show();
    return QApplication::exec();
}
