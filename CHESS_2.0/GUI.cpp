//
// Created by robert12 on 10/5/23.
//

#include "GUI.h"

GUI::GUI(Game *Chess_) : Chess(Chess_), centralWidget(new QWidget(this)) {
    init();
    connect();
}

void GUI::init() {
    this->setCentralWidget(centralWidget);
    main_layout = new QVBoxLayout(centralWidget);
    QFont font;
    font.setPointSize(20);
    font.setBold(true);
    Game_Status->setFont(font);
    Game_Status->setAlignment(Qt::AlignCenter);
    Game_Status->setTextFormat(Qt::RichText);
    RestartButton->setFixedSize(60, 30);
    L1->addWidget(Game_Status);
    L2->addWidget(Chess->getBoardSideLeft());
    L2->addWidget(Chess);
    L2->addWidget(Chess->getBoardSideRight());
    L3->addWidget(RestartButton);
    main_layout->addLayout(L1);
    main_layout->addLayout(L2);
    main_layout->addLayout(L3);
    main_layout->addLayout(L4);

}

void GUI::connect() {
    QObject::connect(Chess, &Game::GameStat, this, &GUI::Get_Game_Stat);
    QObject::connect(RestartButton, &QPushButton::clicked, [&]() -> void {
        Chess->RestartGame();
    });
}


