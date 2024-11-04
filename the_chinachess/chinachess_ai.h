//
// Created by heiyt_R9000P on 24-10-29.
//

#ifndef CHINACHESS_2_CHINACHESS_AI_H
#define CHINACHESS_2_CHINACHESS_AI_H

#include "chinachess.h"

struct MinimaxResult {
    int value; // 节点的评分值
    int id;    // 节点的 ID
    int row;
    int col;
};

void ai_Tree(ChinaChess chinaChess, int &id, int &row, int &col);

#endif //CHINACHESS_2_CHINACHESS_AI_H
