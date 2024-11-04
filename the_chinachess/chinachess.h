//
// Created by heiyt_R9000P on 24-10-30.
//

#ifndef CHINACHESS_H
#define CHINACHESS_H

#include "chess.h"
#include "math.h"

class ChinaChess
{
public:
    ChinaChess() : chesses{
            Chess(0,  7,  1, RED_PLAYER,   BING),
            Chess(1,  7,  3, RED_PLAYER,   BING),
            Chess(2,  7,  5, RED_PLAYER,   BING),
            Chess(3,  7,  7, RED_PLAYER,   BING),
            Chess(4,  7,  9, RED_PLAYER,   BING),
            Chess(5,  4,  1, BLACK_PLAYER, BING),
            Chess(6,  4,  3, BLACK_PLAYER, BING),
            Chess(7,  4,  5, BLACK_PLAYER, BING),
            Chess(8,  4,  7, BLACK_PLAYER, BING),
            Chess(9, 4,  9, BLACK_PLAYER, BING),
            Chess(10, 8,  2, RED_PLAYER,   PAO),
            Chess(11, 8,  8, RED_PLAYER,   PAO),
            Chess(12, 3,  2, BLACK_PLAYER, PAO),
            Chess(13, 3,  8, BLACK_PLAYER, PAO),
            Chess(14, 10, 1, RED_PLAYER,   CHE),
            Chess(15, 10, 9, RED_PLAYER,   CHE),
            Chess(16, 1,  1, BLACK_PLAYER, CHE),
            Chess(17, 1,  9, BLACK_PLAYER, CHE),
            Chess(18, 10, 2, RED_PLAYER,   MA),
            Chess(19, 10, 8, RED_PLAYER,   MA),
            Chess(20, 1,  2, BLACK_PLAYER, MA),
            Chess(21, 1,  8, BLACK_PLAYER, MA),
            Chess(22, 10, 3, RED_PLAYER,   XIANG),
            Chess(23, 10, 7, RED_PLAYER,   XIANG),
            Chess(24, 1,  3, BLACK_PLAYER, XIANG),
            Chess(25, 1,  7, BLACK_PLAYER, XIANG),
            Chess(26, 10, 4, RED_PLAYER,   SHI),
            Chess(27, 10, 6, RED_PLAYER,   SHI),
            Chess(28, 1,  4, BLACK_PLAYER, SHI),
            Chess(29, 1,  6, BLACK_PLAYER, SHI),
            Chess(30, 10, 5, RED_PLAYER,   JIANG),
            Chess(31, 1,  5, BLACK_PLAYER, JIANG)
    } {}

    Chess chesses[32];

    // 这个表主要用来进行对于棋子的快速搜索
    int china_chess_board[11][10] = {
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1,},
            {-1, 16, 20, 24, 28, 31, 29, 25, 21, 17},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, 12, -1, -1, -1, -1, -1, 13, -1},
            {-1, 5,  -1, 6,  -1, 7,  -1, 8,  -1, 9},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, 0,  -1, 1,  -1, 2,  -1, 3,  -1, 4},
            {-1, -1, 10, -1, -1, -1, -1, -1, 11, -1},
            {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
            {-1, 14, 18, 22, 26, 30, 27, 23, 19, 15}
    };

    // 判断棋子是否可以移动到 (row,col)
    bool canMove(Chess chess, int row, int col);
    bool canEat(Chess chess, Chess be_chess);
    bool canMoveBING(Chess chess, int row, int col);
    bool canMovePAO(Chess chess, int row, int col);
    bool canMoveCHE(Chess chess, int row, int col);
    bool canMoveMA(Chess chess, int row, int col);
    bool canMoveXIANG(Chess chess, int row, int col);
    bool canMoveSHI(Chess chess, int row, int col);
    bool canMoveJIANG(Chess chess, int row, int col);
    // 两个将是否面对面
    bool isJiangFace();
    // 是否获胜
    bool isWin(Player &player);
    // 将一个棋子移动到位置 (row,col)
    void moveChess(Chess &chess, int row, int col);
    // 吃掉一个棋子
    void eatChess(Chess &be_chess);

    void setNowPlayer(Player player);
    Player getNowPlayer() const;

private:
    // 现在轮到谁下
    Player nowPlayer = RED_PLAYER;

};

#endif
