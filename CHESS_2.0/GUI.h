//
// Created by robert12 on 10/5/23.
//

#ifndef CHESS_GUI_H
#define CHESS_GUI_H


#include <QMainWindow>
#include "Game.h"
#include <QLabel>
#include "BoardSide.h"
class GUI : public QMainWindow {
Q_OBJECT

private:
    Game *Chess;
    QLabel *Game_Status = new QLabel("White turn");
    QWidget *centralWidget;
    QPushButton *RestartButton = new QPushButton("Restart");
    QVBoxLayout *main_layout;
    QHBoxLayout *L1 = new QHBoxLayout;
    QHBoxLayout *L2 = new QHBoxLayout;
    QHBoxLayout *L3 = new QHBoxLayout;
    QHBoxLayout *L4 = new QHBoxLayout;

    void connect();

public:
    explicit GUI(Game *Chess_);

    void init();
    ~GUI(){
        delete RestartButton;
        delete Game_Status;
        delete L1;
        delete L2;
        delete L3;
        delete L4;
    }
public slots:

    void Get_Game_Stat( string winner) {
        Game_Status->setText(QString::fromStdString(winner));
        this->update();
    }

};


#endif //CHESS_GUI_H
