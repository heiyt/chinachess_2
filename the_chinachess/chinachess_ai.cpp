//
// Created by heiyt_R9000P on 24-10-29.
//

#include "chinachess_ai.h"
#include "../the_MinMaxTree/MinMaxTree.h"

// ai的部分
// 重要性，依次为 兵 炮 车 马 象 士 将
int vital_chess[7] = {10, 30, 50, 30, 20, 10, 10000};

//附加值矩阵
int location_score_BING[11][10] =
        {{0, 0,  0,  0,  0,  0,  0,  0,  0,  0},
         {0, 0,  0,  0,  0,  0,  0,  0,  0,  0},
         {0, 0,  0,  0,  0,  0,  0,  0,  0,  0},
         {0, 0,  0,  0,  0,  0,  0,  0,  0,  0},
         {0, -2, 0,  -2, 0,  6,  0,  -2, 0,  -2},
         {0, 3,  0,  4,  0,  7,  0,  4,  0,  3},
         {0, 10, 18, 22, 35, 40, 35, 22, 18, 10},
         {0, 20, 27, 30, 40, 42, 40, 30, 27, 20},
         {0, 20, 30, 30, 55, 55, 55, 45, 30, 20},
         {0, 20, 30, 50, 65, 70, 65, 50, 30, 20},
         {0, 0,  0,  0,  2,  4,  2,  0,  0,  0},
        };
int location_score_PAO[11][10] =
        {{0, 0,  0, 0, 0,  0,  0,  0, 0, 0},
         {0, 0,  0, 1, 3,  3,  3,  1, 0, 0},
         {0, 0,  1, 2, 2,  2,  2,  2, 1, 0},
         {0, 1,  0, 4, 3,  5,  3,  4, 0, 1},
         {0, 0,  0, 0, 0,  0,  0,  0, 0, 0},
         {0, -1, 0, 3, 0,  4,  0,  3, 0, -1},
         {0, 0,  0, 0, 0,  4,  0,  0, 0, 0},
         {0, 0,  3, 3, 2,  4,  2,  3, 3, 0},
         {0, 1,  1, 0, -5, -4, -5, 0, 1, 1},
         {0, 2,  2, 0, -4, -7, -4, 0, 2, 2},
         {0, 4,  4, 0, -5, -6, -5, 0, 4, 4}
        };
int location_score_SHI[11][10] =
        {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 3, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        };
int location_score_XIANG[11][10] =
        {{0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
         {0, -2, 0, 0, 0, 3, 0, 0, 0, -2},
         {0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0,  0, 0, 0, 0, 0, 0, 0, 0},
         {0, 0,  0, 0, 0, 0, 0, 0, 0, 0}
        };

int location_score_JIANG[11][10] =
        {{0, 0, 0, 0, 0,  0,  0,  0, 0, 0},
         {0, 0, 0, 0, 1,  5,  1,  0, 0, 0},
         {0, 0, 0, 0, -8, -8, -8, 0, 0, 0},
         {0, 0, 0, 0, -9, -9, -9, 0, 0, 0},
         {0, 0, 0, 0, 0,  0,  0,  0, 0, 0},
         {0, 0, 0, 0, 0,  0,  0,  0, 0, 0},
         {0, 0, 0, 0, 0,  0,  0,  0, 0, 0},
         {0, 0, 0, 0, 0,  0,  0,  0, 0, 0},
         {0, 0, 0, 0, 0,  0,  0,  0, 0, 0},
         {0, 0, 0, 0, 0,  0,  0,  0, 0, 0},
         {0, 0, 0, 0, 0,  0,  0,  0, 0, 0}
        };
int location_score_CHE[11][10] =
        {{0, 0,  0,  0,  0,  0,  0,  0,  0,  0},
         {0, -6, 6,  4,  12, 0,  12, 4,  6,  -6},
         {0, 5,  8,  6,  12, 0,  12, 6,  8,  5},
         {0, -2, 8,  4,  12, 12, 12, 4,  8,  -2},
         {0, 4,  9,  4,  12, 14, 12, 4,  9,  4},
         {0, 8,  12, 12, 14, 15, 14, 12, 12, 8},
         {0, 8,  11, 11, 14, 15, 14, 11, 11, 8},
         {0, 6,  13, 13, 16, 16, 16, 13, 13, 6},
         {0, 6,  8,  7,  14, 16, 14, 7,  8,  6},
         {0, 6,  12, 9,  16, 33, 16, 9,  12, 6},
         {0, 6,  8,  7,  13, 14, 13, 7,  8,  6}
        };

int location_score_MA[11][10] =
        {{0, 0,  0,  0,  0,  0,   0,  0,  0,  0},
         {0, 0,  -3, 2,  0,  2,   0,  2,  -3, 0},
         {0, -3, 2,  4,  5,  -10, 5,  4,  2,  -3},
         {0, 5,  4,  6,  7,  4,   7,  6,  4,  5},
         {0, 4,  6,  10, 7,  10,  7,  10, 6,  4},
         {0, 2,  10, 13, 14, 15,  14, 13, 10, 2},
         {0, 2,  12, 11, 15, 16,  15, 11, 12, 2},
         {0, 5,  20, 12, 19, 12,  19, 12, 20, 5},
         {0, 4,  10, 11, 15, 11,  15, 11, 10, 4},
         {0, 2,  8,  15, 9,  6,   9,  15, 8,  2},
         {0, 2,  2,  2,  8,  2,   8,  2,  2,  2}
        };

int cal(ChinaChess chinaChess, Player player) {
    int scores = 0;
    int scores2 = 0;
    for (auto chess : chinaChess.chesses) {
        if (chess.getPlayer() == player && (!chess.get_is_died())) {
            switch (chess.getChessType()) {
                case MA:
                    scores += (location_score_MA[chess.getRow()][chess.getCol()] + vital_chess[3]);
                    break;
                case BING:
                    scores += (location_score_BING[chess.getRow()][chess.getCol()] + vital_chess[0]);
                    break;
                case PAO:
                    scores += (location_score_PAO[chess.getRow()][chess.getCol()] + vital_chess[1]);
                    break;
                case CHE:
                    scores += (location_score_CHE[chess.getRow()][chess.getCol()] + vital_chess[2]);
                    break;
                case XIANG:
                    scores += (location_score_XIANG[chess.getRow()][chess.getCol()] + vital_chess[4]);
                    break;
                case SHI:
                    scores += (location_score_SHI[chess.getRow()][chess.getCol()] + vital_chess[5]);
                    break;
                case JIANG:
                    scores += (location_score_JIANG[chess.getRow()][chess.getCol()] + vital_chess[6]);
                    break;
            }
        }
        if (chess.getPlayer() != player && (!chess.get_is_died())) {
            switch (chess.getChessType()) {
                case MA:
                    scores2 += (location_score_MA[11-chess.getRow()][10-chess.getCol()] + vital_chess[3]);break;
                case BING:
                    scores2 += (location_score_BING[11-chess.getRow()][10-chess.getCol()] + vital_chess[0]);break;
                case PAO:
                    scores2 += (location_score_PAO[11-chess.getRow()][10-chess.getCol()] + vital_chess[1]);break;
                case CHE:
                    scores2 += (location_score_CHE[11-chess.getRow()][10-chess.getCol()] + vital_chess[2]);break;
                case XIANG:
                    scores2 += (location_score_XIANG[11-chess.getRow()][10-chess.getCol()] + vital_chess[4]);break;
                case SHI:
                    scores2 += (location_score_SHI[11-chess.getRow()][10-chess.getCol()] + vital_chess[5]);break;
                case JIANG:
                    scores2 += (location_score_JIANG[11-chess.getRow()][10-chess.getCol()] + vital_chess[6]);break;
            }
        }
    }
    return scores - scores2;
}

int getWayOfChess(ChinaChess chinaChess, Chess chess, int row[], int col[]) {
    int numOfWay = 0;
    if (chess.get_is_died()) {
        return 0;
    }
    for (int i = 1; i <= 10; i++) {
        for (int j = 1; j <= 9; j++) {
            if (chinaChess.china_chess_board[i][j] == -1) {
                if (chinaChess.canMove(chess, i, j)) {
                    row[numOfWay] = i;
                    col[numOfWay] = j;
                    numOfWay++;
                }
            } else {
                Chess beChess = chinaChess.chesses[chinaChess.china_chess_board[i][j]];
                if (chinaChess.canEat(chess, beChess) && beChess.getPlayer() != chess.getPlayer()) {
                    row[numOfWay] = i;
                    col[numOfWay] = j;
                    numOfWay++;
                }
            }
        }
    }
    return numOfWay;
}

void chinaChessSetTree(ChinaChess &chinaChess, std::shared_ptr<TreeNode> node, int depth) {
    if (depth == 0) {
        return;
    }
    for (int i = 0; i < 32; i++) {
        if (!chinaChess.chesses[i].get_is_died()) {
            if (!(depth % 2 == 0 && chinaChess.chesses[i].getPlayer() == BLACK_PLAYER) &&
                !(depth % 2 == 1 && chinaChess.chesses[i].getPlayer() == RED_PLAYER)) {
                continue;
            }
            int rows[90] = {0}, cols[90] = {0};
            int numOfWay = getWayOfChess(chinaChess, chinaChess.chesses[i], rows, cols);
            if (numOfWay != 0) {
                for (int x = 0; x < numOfWay; x++) {
                    int p;
                    if (chinaChess.china_chess_board[rows[x]][cols[x]] == -1) {
                        int j_row = chinaChess.chesses[i].getRow();
                        int j_col = chinaChess.chesses[i].getCol();
                        chinaChess.moveChess(chinaChess.chesses[i], rows[x], cols[x]);
                        p = cal(chinaChess, BLACK_PLAYER);
                        // 添加到树里面
                        auto newNode = std::make_shared<TreeNode>(i, rows[x], cols[x], p);
                        node->addChild(newNode);
                        chinaChessSetTree(chinaChess, newNode, depth - 1);

                        chinaChess.moveChess(chinaChess.chesses[i], j_row, j_col);
                    } else {
                        int be_id = chinaChess.china_chess_board[rows[x]][cols[x]];
                        int j_row = chinaChess.chesses[i].getRow();
                        int j_col = chinaChess.chesses[i].getCol();
                        chinaChess.eatChess(chinaChess.chesses[chinaChess.china_chess_board[rows[x]][cols[x]]]);
                        chinaChess.moveChess(chinaChess.chesses[i], rows[x], cols[x]);
                        p = cal(chinaChess, BLACK_PLAYER);
                        // 添加到树里面
                        auto newNode = std::make_shared<TreeNode>(i, rows[x], cols[x], p);
                        node->addChild(newNode);
                        chinaChessSetTree(chinaChess, newNode, depth - 1);

                        chinaChess.moveChess(chinaChess.chesses[i], j_row, j_col);
                        chinaChess.china_chess_board[rows[x]][cols[x]] = be_id;
                        chinaChess.chesses[be_id].set_is_died(false);
                        chinaChess.chesses[be_id].setRow(rows[x]);
                        chinaChess.chesses[be_id].setCol(cols[x]);
                    }
                }
            }
        }
    }
}

MinimaxResult minimax(std::shared_ptr<TreeNode> node, int depth, bool isMaximizingPlayer) {
    // 终止条件：到达叶节点或深度为0
    if (node == nullptr || depth == 1) {
        return { node ? node->getPoint() : -99999, node ? node->getID() : -1,
                 node ? node->getRow() : -1, node ? node->getCol() : -1 }; // 返回叶节点的点数值和ID
    }
    if (isMaximizingPlayer) {
        MinimaxResult bestResult = { -99999, -1, -1, -1 }; // 初始值为负无穷
        const auto& children = node->getChildren(); // 获取所有子节点
        for (std::shared_ptr<TreeNode> child : children) {
            MinimaxResult eval = minimax(child, depth - 1, false); // 切换为极小化
            if (eval.value > bestResult.value) {
                bestResult.value = eval.value;
                bestResult.id = child->getID(); // 记录最佳子节点的ID
                bestResult.row = child->getRow();
                bestResult.col = child->getCol();
            }
        }
        return bestResult;
    } else {
        MinimaxResult bestResult = { 99999, -1, -1, -1 }; // 初始值为正无穷
        const auto& children = node->getChildren(); // 获取所有子节点
        for (std::shared_ptr<TreeNode> child : children) {
            MinimaxResult eval = minimax(child, depth - 1, true); // 切换为极大化
            if (eval.value < bestResult.value) {
                bestResult.value = eval.value;
                bestResult.id = child->getID(); // 记录最佳子节点的ID
                bestResult.row = child->getRow();
                bestResult.col = child->getCol();
            }
        }
        return bestResult;
    }
}

void ai_Tree(ChinaChess chinaChess, int &id, int &row, int &col) {
    MinimaxResult minimaxResult{};
    auto root = std::make_shared<TreeNode>(0, 0, 0, 0);
    chinaChessSetTree(chinaChess, root, 4);
    minimaxResult = minimax(root,4, true);
    id = minimaxResult.id;
    row = minimaxResult.row;
    col = minimaxResult.col;
}
