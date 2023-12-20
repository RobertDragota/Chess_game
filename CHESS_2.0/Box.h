//
// Created by robert12 on 10/16/23.
//

#ifndef CHESS_2_0_BOX_H
#define CHESS_2_0_BOX_H

#include<QGraphicsView>
#include<QGraphicsItem>
#include<QGraphicsRectItem>
#include<string>
using std::string;
class Box: public QGraphicsRectItem {
private:
    QColor color;
    string status;
    string sub_status;
public:
    Box(qreal x_, qreal y_, qreal w_, qreal h_, std::string &&stat, std::string &&sub_stat, QColor col)
            : QGraphicsRectItem(x_, y_, w_, h_),
              status(stat), color(col), sub_status(sub_stat) {
        this->setBrush(color);
    }

    Box(const Box &copy) : color(copy.color), status(copy.status), sub_status(copy.sub_status),
                           QGraphicsRectItem(copy.rect().x(), copy.rect().y(), copy.rect().width(),
                                             copy.rect().height()) {
        this->setBrush(color);
    }

    void ChangeStatus(string &&new_status);

    void ChangeStatus(string &new_status);

    void ChangeSubStatus(string &&new_sub_status);

    void ChangeSubStatus(string &new_sub_status);

    void originalColor();

    string getStatus();

    string getSubStatus();


};


#endif //CHESS_2_0_BOX_H
