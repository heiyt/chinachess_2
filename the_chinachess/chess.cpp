//
// Created by heiyt_R9000P on 24-10-29.
//

#include "chess.h"

int Chess::getID() const {
    return id;
}
int Chess::getRow() const {
    return row;
}
int Chess::getCol() const {
    return col;
}
void Chess::setRow(int r) {
    if (is_died) {
        r = -1;
    } else if (r > 10 || r < 1) {
        return;
    }
    row = r;
}
void Chess::setCol(int c) {
    if (is_died) {
        c = -1;
    } else if (c > 9 || c < 1) {
        return;
    }
    col = c;
}
Player Chess::getPlayer() const {
    return player;
}
ChessType Chess::getChessType() const {
    return chessType;
}
void Chess::set_is_died(bool d){
    is_died = d;
}
bool Chess::get_is_died() const {
    return is_died;
}


