/********************************************************************************
** Form generated from reading UI file 'chinachessboard.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHINACHESSBOARD_H
#define UI_CHINACHESSBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_ChinaChessBoard
{
public:

    void setupUi(QDialog *ChinaChessBoard)
    {
        if (ChinaChessBoard->objectName().isEmpty())
            ChinaChessBoard->setObjectName("ChinaChessBoard");
        ChinaChessBoard->resize(400, 300);

        retranslateUi(ChinaChessBoard);

        QMetaObject::connectSlotsByName(ChinaChessBoard);
    } // setupUi

    void retranslateUi(QDialog *ChinaChessBoard)
    {
        ChinaChessBoard->setWindowTitle(QCoreApplication::translate("ChinaChessBoard", "ChinaChessBoard", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChinaChessBoard: public Ui_ChinaChessBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHINACHESSBOARD_H
