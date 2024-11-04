#include <QApplication>
#include "chinachessboard.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ChinaChessBoard ccb;
    ccb.setFixedSize(600, 550);
    ccb.setWindowTitle("象棋");
    ccb.show();
    return QApplication::exec();
}
