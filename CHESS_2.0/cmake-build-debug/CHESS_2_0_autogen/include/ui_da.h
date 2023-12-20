/********************************************************************************
** Form generated from reading UI file 'da.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DA_H
#define UI_DA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_da
{
public:

    void setupUi(QWidget *da)
    {
        if (da->objectName().isEmpty())
            da->setObjectName("da");
        da->resize(400, 300);

        retranslateUi(da);

        QMetaObject::connectSlotsByName(da);
    } // setupUi

    void retranslateUi(QWidget *da)
    {
        da->setWindowTitle(QCoreApplication::translate("da", "da", nullptr));
    } // retranslateUi

};

namespace Ui {
    class da: public Ui_da {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DA_H
