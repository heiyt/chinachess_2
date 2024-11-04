//
// Created by heiyt_R9000P on 24-10-29.
//

#ifndef CHINACHESS_2_CHINACHESSBOARD_H
#define CHINACHESS_2_CHINACHESSBOARD_H

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QPushButton>
#include "the_chinachess/chinachess.h"
#include "the_chinachess/chinachess_ai.h"
#include "the_Stack/Stack.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ChinaChessBoard; }
QT_END_NAMESPACE

class ChinaChessBoard : public QDialog {
Q_OBJECT

public:
    explicit ChinaChessBoard(QWidget *parent = nullptr);
    ~ChinaChessBoard() override;
private:
    Ui::ChinaChessBoard *ui;
    QPushButton *button;


    ChessStack *chessStack = new ChessStack;

    ChinaChess chinaChess;
    int selected_id = -1;
    void paintEvent(QPaintEvent *event) override;
    static void drawChess(QPainter &chess_painter,Chess chess);
    static void xy2cr(int x, int y, int &col, int &row);
    static void cr2xy(int col, int row, int &x, int &y);
    void mousePressEvent(QMouseEvent *event) override;
    bool isClickOnChess(QPoint qPoint, int &row, int &col, int &id);
    void clickOnChess(Chess &chess, int row, int col);
    void clickonBoard(int row, int col);

    void ai_run();

private slots:
    void onButtonClicked() {
        // 进行悔棋操作
        if (!chessStack->isEmpty()) {
            Node *node1 = nullptr, *node2 = nullptr;
            chessStack->pop(node1);
            chessStack->pop(node2);
            if (chinaChess.chesses[node1->getID()].getPlayer() == BLACK_PLAYER) {
                chinaChess.moveChess(chinaChess.chesses[node1->getID()], node1->getRow(), node1->getCol());
                if (node1->getBeID() != -1) {
                    chinaChess.china_chess_board[chinaChess.chesses[node1->getBeID()].getRow()][chinaChess.chesses[node1->getBeID()].getCol()] = node1->getBeID();
                    chinaChess.chesses[node1->getBeID()].set_is_died(false);
                }
            }
            if (chinaChess.chesses[node2->getID()].getPlayer() == RED_PLAYER) {
                chinaChess.moveChess(chinaChess.chesses[node2->getID()], node2->getRow(), node2->getCol());
                if (node2->getBeID() != -1) {
                    chinaChess.china_chess_board[chinaChess.chesses[node2->getBeID()].getRow()][chinaChess.chesses[node2->getBeID()].getCol()] = node2->getBeID();
                    chinaChess.chesses[node2->getBeID()].set_is_died(false);
                }
            }
            repaint();
        }
    }
};

#endif //CHINACHESS_2_CHINACHESSBOARD_H
