//
// Created by heiyt_R9000P on 24-10-29.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChinaChessBoard.h" resolved

#include "chinachessboard.h"
#include "ui_ChinaChessBoard.h"

ChinaChessBoard::ChinaChessBoard(QWidget *parent) :
        QDialog(parent), ui(new Ui::ChinaChessBoard) {
    ui->setupUi(this);
    button = new QPushButton("悔棋", this);
    button->setGeometry(520, 450, 50, 40);
    connect(button, &QPushButton::clicked, this, &ChinaChessBoard::onButtonClicked);
}
ChinaChessBoard::~ChinaChessBoard() {
    delete ui;
}

void ChinaChessBoard::paintEvent(QPaintEvent *event) {
    // 画棋盘
    QPainter board_painter(this);
    for (int i = 0; i < 10; i++) {
        board_painter.drawLine(50, 50 * i + 50, 450, 50 * i + 50);
    }
    for (int i = 0; i < 9; i++) {
        board_painter.drawLine(50 * i + 50, 50, 50 * i + 50, 250);
    }
    for (int i = 0; i < 9; i++) {
        board_painter.drawLine(50 * i + 50, 300, 50 * i + 50, 500);
    }
    board_painter.drawLine(50, 250, 50, 300);
    board_painter.drawLine(450, 250, 450, 300);
    // 四条斜线
    board_painter.drawLine(200, 50, 300, 150);
    board_painter.drawLine(300, 50, 200, 150);
    board_painter.drawLine(200, 400, 300, 500);
    board_painter.drawLine(300, 400, 200, 500);
    // 画棋子
    for (const auto & chess : chinaChess.chesses) {
        drawChess(board_painter,chess);
    }
}
void ChinaChessBoard::drawChess(QPainter &chess_painter,Chess chess) {
    if (chess.get_is_died()) {
        return;
    }
    int x,y;
    cr2xy(chess.getCol(), chess.getRow(), x, y);
    QString chess_name;
    QPen ppp;
    QRect rect = QRect(x - 23, y - 23, 46, 46);
    ppp.setWidth(3);
    if(chess.getPlayer() == RED_PLAYER) {
        ppp.setColor(Qt::red);
    } else {
        ppp.setColor(Qt::black);
    }
    chess_painter.setBrush(QBrush(Qt::yellow));
    chess_painter.setPen(ppp);
    chess_painter.drawEllipse(x - 23, y - 23, 46, 46);
    switch (chess.getChessType()) {
        case BING:chess_name = "兵";break;
        case PAO:chess_name = "炮";break;
        case CHE:chess_name = "车";break;
        case MA:chess_name = "马";break;
        case XIANG:chess_name = "象";break;
        case SHI:chess_name = "士";break;
        case JIANG:chess_name = "将";break;
    }
    chess_painter.setFont(QFont("宋体", 20, QFont::Bold));
    chess_painter.drawText(rect, chess_name, QTextOption(Qt::AlignCenter));
}
void ChinaChessBoard::xy2cr(int x, int y, int &col, int &row) {
    col = x / 50;
    row = y / 50;
}
void ChinaChessBoard::cr2xy(int col, int row, int &x, int &y) {
    x = col * 50;
    y = row * 50;
}
void ChinaChessBoard::mousePressEvent(QMouseEvent *event) {
    if(event->button() != Qt::LeftButton) {
        return;
    }
    int row = 0, col = 0, id = 0;
    if (isClickOnChess(event->pos(), row, col, id)) {
        clickOnChess(chinaChess.chesses[id], row, col);
    } else {
        clickonBoard(row, col);
    }
}
bool ChinaChessBoard::isClickOnChess(QPoint qPoint, int &row, int &col, int &id) {
    int qx, qy;
    qx = qPoint.x();
    qy = qPoint.y();
    xy2cr(qx, qy, col, row);
    if (qx % 50 > 25) {
        col = col + 1;
    }
    if (qy % 50 > 25) {
        row = row + 1;
    }
    if (chinaChess.china_chess_board[row][col] != -1) {
        id = chinaChess.china_chess_board[row][col];
        return true;
    }
    return false;
}
void ChinaChessBoard::clickOnChess(Chess &chess, int row, int col) {
    qDebug() << "棋子";
    if (chinaChess.getNowPlayer() == RED_PLAYER) {
        if (chess.getPlayer() == RED_PLAYER) {
            selected_id = chess.getID();
            qDebug() << "选中" << chess.getID();
            return;
        }
        if (chess.getPlayer() == BLACK_PLAYER) {
            if (selected_id == -1) {
                return;
            }
            if (chinaChess.canEat(chinaChess.chesses[selected_id],chess)) {

                // stack操作
                Node *n1 = new Node(selected_id, chinaChess.china_chess_board[row][col],
                                    chinaChess.chesses[selected_id].getRow(),
                                    chinaChess.chesses[selected_id].getCol());
                chessStack->add(n1);

                // 吃掉棋子
                chinaChess.eatChess(chess);
                chinaChess.moveChess(chinaChess.chesses[selected_id], row, col);

                // 切换玩家
                Player p;
                if (chinaChess.isWin(p)) {
                    qDebug() << p << "获胜";
                }
                selected_id = -1;
                chinaChess.setNowPlayer(BLACK_PLAYER);
                repaint();
                // 进行ai走棋
                QEventLoop loop;
                ai_run();
                loop.exec();
            }
        }
    }
    // 双人模式
//    if (chinaChess.getNowPlayer() == BLACK_PLAYER) {
//        if (chess.getPlayer() == BLACK_PLAYER) {
//            selected_id = chess.getID();
//            qDebug() << "选中" << chess.getID();
//            return;
//        }
//        if (chess.getPlayer() == RED_PLAYER) {
//            if (selected_id == -1) {
//                return;
//            }
//            if (chinaChess.canEat(chinaChess.chesses[selected_id],chess)) {
//                chinaChess.eatChess(chess);
//                chinaChess.moveChess(chinaChess.chesses[selected_id], row, col);
//                // 切换玩家
//                Player p;
//                if (chinaChess.isWin(p)) {
//                    qDebug() << p << "获胜";
//                }
//                selected_id = -1;
//                chinaChess.setNowPlayer(RED_PLAYER);
//                update();
//            }
//        }
//    }
}
void ChinaChessBoard::clickonBoard(int row, int col) {
    qDebug() << "棋盘";
    if (chinaChess.getNowPlayer() == RED_PLAYER) {
        if (selected_id != -1 && chinaChess.canMove(chinaChess.chesses[selected_id], row, col)) {

            // stack操作
            Node *n2 = new Node(selected_id, -1,
                                chinaChess.chesses[selected_id].getRow(),
                                chinaChess.chesses[selected_id].getCol());
            chessStack->add(n2);

            // 移动棋子
            chinaChess.moveChess(chinaChess.chesses[selected_id], row, col);

            // 切换玩家
            selected_id = -1;
            chinaChess.setNowPlayer(BLACK_PLAYER);
            repaint();
            // 进行ai走棋
            QEventLoop loop;
            ai_run();
            loop.exec();
        }
    }
    // 双人模式
//    if (chinaChess.getNowPlayer() == BLACK_PLAYER) {
//        if (selected_id != -1 && chinaChess.canMove(chinaChess.chesses[selected_id], row, col)) {
//            chinaChess.moveChess(chinaChess.chesses[selected_id], row, col);
//            // 切换玩家
//            selected_id = -1;
//            chinaChess.setNowPlayer(RED_PLAYER);
//            update();
//        }
//    }
}

void ChinaChessBoard::ai_run() {
    // ai部分
    ChinaChess chinaChess1 = chinaChess;
    int id1;
    int row1, col1;

    ai_Tree(chinaChess1, id1, row1, col1);

    if (chinaChess.china_chess_board[row1][col1] != -1) {

        // stack操作
        Node *n1 = new Node(id1, chinaChess.china_chess_board[row1][col1],
                            chinaChess.chesses[id1].getRow(), chinaChess.chesses[id1].getCol());
        chessStack->add(n1);

        // 吃掉棋子
        chinaChess.eatChess(chinaChess.chesses[chinaChess.china_chess_board[row1][col1]]);
        chinaChess.moveChess(chinaChess.chesses[id1], row1, col1);
    } else {

        // stack操作
        Node *n2 = new Node(id1, -1,
                            chinaChess.chesses[id1].getRow(), chinaChess.chesses[id1].getCol());
        chessStack->add(n2);

        // 移动棋子
        chinaChess.moveChess(chinaChess.chesses[id1], row1, col1);
    }

    // 切换玩家
    Player p;
    if (chinaChess.isWin(p)) {
        qDebug() << p << "获胜";
    }
    selected_id = -1;
    chinaChess.setNowPlayer(RED_PLAYER);
    repaint();
}
