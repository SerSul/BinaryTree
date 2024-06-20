#ifndef TREENODE_H
#define TREENODE_H

template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    int height; // Добавляем поле height

    TreeNode(T value)
        : data(value), left(nullptr), right(nullptr), height(1) {}
};

#endif // TREENODE_H
