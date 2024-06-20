#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "TreeNode.h"
#include <iostream>
#include <stdexcept>
#include <functional>

template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    // Private methods for recursive implementations
    void insertRecursive(TreeNode<T>*& node, T value);
    TreeNode<T>* findMin(TreeNode<T>* node);
    TreeNode<T>* removeRecursive(TreeNode<T>*& node, T value);
    TreeNode<T>* findRecursive(TreeNode<T>* node, T value);
    void printInorder(TreeNode<T>* node);
    void destroy(TreeNode<T>* node);
    void printTree(TreeNode<T>* node, int indent);

public:
    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(); }

    void insert(T value);
    void remove(T value);
    TreeNode<T>* find(T value);
    void printTree();
    void clear();

    // Traversal methods
    void printPreorder();
    void printPreorder(TreeNode<T>* node);
    void printPostorder();
    void printPostorder(TreeNode<T>* node);
    void printInorder();
    void printReverseInorder();
    void printReverseInorder(TreeNode<T>* node);
    void printReversePreorder();
    void printReversePreorder(TreeNode<T>* node);
    void printReversePostorder();
    void printReversePostorder(TreeNode<T>* node);

    // Other methods
    template <typename U>
    BinarySearchTree<U> map(std::function<U(T)> func) const;

    template <typename U>
    U reduce(std::function<U(U, T)> func, U initialValue) const;

    BinarySearchTree<T> where(std::function<bool(const T&)> predicate) const;
};

#include "BinarySearchTree.cpp"

#endif // BINARYSEARCHTREE_H
