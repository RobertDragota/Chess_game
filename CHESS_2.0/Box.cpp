//
// Created by robert12 on 10/16/23.
//

#include "Box.h"
void Box::ChangeStatus(string &&new_status) {
    status = new_status;
}

void Box::ChangeStatus(string &new_status) {
    status = new_status;
}

string Box::getStatus() {
    return status;
}

void Box::ChangeSubStatus(string &&new_sub_status) {
    sub_status = new_sub_status;
}

void Box::ChangeSubStatus(string &new_sub_status) {
    sub_status = new_sub_status;
}

string Box::getSubStatus() {
    return sub_status;
}

void Box::originalColor() {
    this->setBrush(color);
}
