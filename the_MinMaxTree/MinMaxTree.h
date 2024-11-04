//
// Created by heiyt_R9000P on 24-11-3.
//

#ifndef CHINACHESS_2_MINMAXTREE_H
#define CHINACHESS_2_MINMAXTREE_H

#include <vector>
#include <memory>

class TreeNode {
public:
    // 构造函数
    TreeNode(int id, int row, int col, int point)
            : id(id), row(row), col(col), point(point) {}
    // 获取节点信息的方法
    [[nodiscard]] int getID() const { return id; }
    [[nodiscard]] int getRow() const { return row; }
    [[nodiscard]] int getCol() const { return col; }
    [[nodiscard]] int getPoint() const { return point; }
    // 获取子节点
    [[nodiscard]] const std::vector<std::shared_ptr<TreeNode>>& getChildren() const { return children; }
    // 添加子节点
    void addChild(const std::shared_ptr<TreeNode>&  child) { children.push_back(child); }

private:
    int id;                            // 节点ID
    int row;                           // 节点的行
    int col;                           // 节点的列
    int point;                         // 节点的值或得分
    std::vector<std::shared_ptr<TreeNode>> children; // 子节点使用智能指针存储
};


#endif //CHINACHESS_2_MINMAXTREE_H
