//
// Created by heiyt_R9000P on 24-11-4.
//

#ifndef CHINACHESS_2_STACK_H
#define CHINACHESS_2_STACK_H

class Node {
public:
    Node *nextNode{};
    Node(int id, int be_id, int row, int col):id(id),be_id(be_id),row(row),col(col){}
    [[nodiscard]] int getID() const{return id;}
    [[nodiscard]] int getBeID() const{return be_id;}
    [[nodiscard]] int getRow() const{return row;}
    [[nodiscard]] int getCol() const{return col;}
private:
    int id;
    int be_id;
    int row;
    int col;
};

class ChessStack {
public:
    ChessStack() {
        root = new Node(-1, 0, 0, 0);
    }
    void add(Node *&node) {
        node->nextNode = root->nextNode;
        root->nextNode = node;
    }
    void pop(Node *&node) {
        node = root->nextNode;
        root->nextNode = node->nextNode;
    }
    bool isEmpty() {
        if (root->nextNode == nullptr) {
            return true;
        } else {
            return false;
        }
    }
private:
    Node *root;
};

#endif //CHINACHESS_2_STACK_H
