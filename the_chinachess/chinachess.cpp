//
// Created by heiyt_R9000P on 24-10-30.
//

#include "chinachess.h"

bool ChinaChess::canMove(Chess chess, int row, int col) {
    // 目标位置要对
    if (row > 10 || row < 1 || col > 9 || col < 1) {
        return false;
    }
    // 根据不同的棋子的不同走棋规则
    switch (chess.getChessType()) {
        case BING:  return canMoveBING(chess,row,col);
        case PAO:   return canMovePAO(chess,row,col);
        case CHE:   return canMoveCHE(chess,row,col);
        case MA:    return canMoveMA(chess,row,col);
        case XIANG: return canMoveXIANG(chess,row,col);
        case SHI:   return canMoveSHI(chess,row,col);
        case JIANG: return canMoveJIANG(chess,row,col);
    }
}
bool ChinaChess::canEat(Chess chess, Chess be_chess) {
    if (chess.getChessType() == PAO) {
        return canMovePAO(chess, be_chess.getRow(), be_chess.getCol());
    }
    if (chess.getChessType() == JIANG) {
        if (isJiangFace() && be_chess.getChessType() == JIANG) {
            return true;
        }
    }
    return canMove(chess, be_chess.getRow(), be_chess.getCol());
}
bool ChinaChess::isJiangFace() {
    if (chesses[30].getCol() != chesses[31].getCol()) {
        return false;
    }
    int gs = 0;
    int c = chesses[30].getCol();
    for (int i = chesses[31].getRow()+1; i < chesses[30].getRow(); i++) {
        if (china_chess_board[i][c] != -1) {
            gs++;
        }
    }
    if (gs == 0) {
        return true;
    }
    return false;
}
bool ChinaChess::canMoveBING(Chess chess, int row, int col) {
    // 兵的规则
    if (chess.getPlayer() == RED_PLAYER) {
        if (abs(row - chess.getRow()) + abs(col - chess.getCol()) == 1 && row <= chess.getRow()) {
            if (row > 5 && row != chess.getRow() - 1) {
                return false;
            }
            return true;
        }
    } else {
        if (abs(row - chess.getRow()) + abs(col - chess.getCol()) == 1 && row >= chess.getRow()) {
            if (row < 6 && row != chess.getRow() + 1) {
                return false;
            }
            return true;
        }
    }
    return false;
}
bool ChinaChess::canMovePAO(Chess chess, int row, int col) {
    if (row < 1 || col < 1 || row > 10 || col > 9) {
        return false;
    }
    if (chess.getRow() != row && chess.getCol() != col) {
        return false;
    }
    int geShu = 0;
    if (chess.getRow() == row && chess.getCol() != col) {
        if (col > chess.getCol()) {
            for (int i = chess.getCol() + 1; i < col; i++) {
                if (china_chess_board[row][i] != -1) {
                    geShu++;
                }
            }
        }
        if (col < chess.getCol()) {
            for (int i = col + 1; i < chess.getCol(); i++) {
                if (china_chess_board[row][i] != -1) {
                    geShu++;
                }
            }
        }
    }
    if (chess.getRow() != row && chess.getCol() == col) {
        if (row > chess.getRow()) {
            for (int i = chess.getRow() + 1; i < row; i++) {
                if (china_chess_board[i][col] != -1) {
                    geShu++;
                }
            }
        }
        if (row < chess.getRow()) {
            for (int i = row + 1; i < chess.getRow(); i++) {
                if (china_chess_board[i][col] != -1) {
                    geShu++;
                }
            }
        }
    }
    if (geShu == 1) {
        if(china_chess_board[row][col] != -1){
            if (chesses[china_chess_board[row][col]].getPlayer() != chess.getPlayer()) {
                return true;
            }
        }
        return false;
    }
    if (geShu == 0) {
        if(china_chess_board[row][col] == -1){
            return true;
        }
        return false;
    } else {
        return false;
    }
}
// 车，相，马 需要通过虚拟的board来指定走棋规则
bool ChinaChess::canMoveCHE(Chess chess, int row, int col) {
    if (chess.getRow() == row && chess.getCol() != col) {
        if (col > chess.getCol()) {
            for (int i = chess.getCol() + 1; i < col; i++) {
                if (china_chess_board[row][i] != -1) {
                    return false;
                }
            }
            return true;
        }
        if (col < chess.getCol()) {
            for (int i = col+1; i < chess.getCol(); i++) {
                if (china_chess_board[row][i] != -1) {
                    return false;
                }
            }
            return true;
        }
    }
    if (chess.getRow() != row && chess.getCol() == col) {
        if (row > chess.getRow()) {
            for (int i = chess.getRow() + 1; i < row; i++) {
                if (china_chess_board[i][col] != -1) {
                    return false;
                }
            }
            return true;
        }
        if (row < chess.getRow()) {
            for (int i = row + 1; i < chess.getRow(); i++) {
                if (china_chess_board[i][col] != -1) {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}
bool ChinaChess::canMoveMA(Chess chess, int row, int col) {
    if (abs(chess.getRow() - row) == 2 && abs(chess.getCol() - col) == 1) {
        if (china_chess_board[(chess.getRow() + row) / 2][chess.getCol()] != -1) {
            return false;
        }
        return true;
    }
    if (abs(chess.getCol() - col) == 2 && abs(chess.getRow() - row) == 1) {
        if (china_chess_board[chess.getRow()][(chess.getCol() + col) / 2] != -1) {
            return false;
        }
        return true;
    }
    return false;
}
bool ChinaChess::canMoveXIANG(Chess chess, int row, int col) {
    if ((chess.getPlayer() == RED_PLAYER && row < 6) || (chess.getPlayer() == BLACK_PLAYER && row > 5)) {
        return false;
    }
    if (abs(chess.getRow() - row) == 2 && abs(chess.getCol() - col) == 2) {
        if (china_chess_board[(chess.getRow() + row) / 2][(chess.getCol() + col) / 2] != -1) {
            return false;
        }
        return true;
    }
    return false;
}
bool ChinaChess::canMoveSHI(Chess chess, int row, int col) {
    if (chess.getPlayer() == RED_PLAYER) {
        if (row < 8 || col < 4 || col > 6) {
            return false;
        }
    } else {
        if (row > 3 || col < 4 || col > 6) {
            return false;
        }
    }
    if (abs(chess.getRow() - row) == 1 && abs(chess.getCol() - col) == 1) {
        return true;
    }
    return false;
}
bool ChinaChess::canMoveJIANG(Chess chess, int row, int col) {
    if (chess.getPlayer() == RED_PLAYER) {
        if (row < 8 || col < 4 || col > 6) {
            return false;
        }
    } else {
        if (row > 3 || col < 4 || col > 6) {
            return false;
        }
    }
    if (abs(chess.getRow() - row) + abs(chess.getCol() - col) == 1) {
        return true;
    }
    return false;
}
bool ChinaChess::isWin(Player &player) {
    if (chesses[30].get_is_died()) {
        player = BLACK_PLAYER;
        return true;
    }
    if (chesses[31].get_is_died()) {
        player = RED_PLAYER;
        return true;
    }
    return false;
}
void ChinaChess::setNowPlayer(Player player) {
    nowPlayer = player;
}
Player ChinaChess::getNowPlayer() const {
    return nowPlayer;
}
void ChinaChess::moveChess(Chess &chess, int row, int col) {
    china_chess_board[chess.getRow()][chess.getCol()] = -1;
    china_chess_board[row][col] = chess.getID();
    chess.setRow(row);
    chess.setCol(col);
}
void ChinaChess::eatChess(Chess &be_chess) {
    china_chess_board[be_chess.getRow()][be_chess.getCol()] = -1;
    be_chess.set_is_died(true);
}

