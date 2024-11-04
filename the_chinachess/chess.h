//
// Created by heiyt_R9000P on 24-10-29.
//

#ifndef CHESS_H
#define CHESS_H

enum Player {
    RED_PLAYER,
    BLACK_PLAYER
};

enum ChessType {
    BING,
    PAO,
    CHE,
    MA,
    XIANG,
    SHI,
    JIANG
};

class Chess {
public:
    Chess(int id, int r, int c, Player p, ChessType ct)
            : id(id), row(r), col(c), player(p), chessType(ct), is_died(false) {}
    [[nodiscard]] int getID() const;
    [[nodiscard]] int getRow() const;
    [[nodiscard]] int getCol() const;
    void setRow(int r);
    void setCol(int c);
    [[nodiscard]] Player getPlayer() const;
    [[nodiscard]] ChessType getChessType() const;
    void set_is_died(bool d);
    [[nodiscard]] bool get_is_died() const;
private:
    int id;
    int row;
    int col;
    Player player;
    ChessType chessType;
    bool is_died = false;
};

#endif
