#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <iostream>
#include <stdexcept>
#include <functional>
#include <string>
#include "Stack.h"
#include "TreeNode.h"


template <typename T>
struct TreeNode {
    T data;
    TreeNode* left;
    TreeNode* right;
    int height;

    TreeNode(T value)
        : data(value), left(nullptr), right(nullptr), height(1) {}
};

template <typename T>
class BinarySearchTree {
private:

    TreeNode<T>* root;
    
    void insertRecursive(TreeNode<T>*& node, T value);
    TreeNode<T>* findMin(TreeNode<T>* node);
    TreeNode<T>* removeRecursive(TreeNode<T>*& node, T value);
    TreeNode<T>* findRecursive(TreeNode<T>* node, T value);
    TreeNode<T>* extractSubtreeRecursive(TreeNode<T>*& node, T value);
    bool containsSubtreeRecursive(TreeNode<T>* mainTree, TreeNode<T>* subtree);
    void printInorder(TreeNode<T>* node);
    void destroy(TreeNode<T>* node);
    void printTree(TreeNode<T>* node, int indent);


public:

    BinarySearchTree() : root(nullptr) {}
    ~BinarySearchTree() { clear(); }

    TreeNode<T>* getRoot() { return this.root; };
    // Публичные функции для работы с деревом
    void insert(T value);
    void remove(T value);
    TreeNode<T>* find(T value);
    void printTree();
    void clear();

    // Функции для печати дерева в различных порядках
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


    // Функции для трансформации дерева
    template <typename U>
    BinarySearchTree<U> map(std::function<U(T)> func) const;

    template <typename U>
    U reduce(std::function<U(U, T)> func, U initialValue) const;

    BinarySearchTree<T> where(std::function<bool(const T&)> predicate) const;

    BinarySearchTree<T> merge(const BinarySearchTree<T>& other) ;



    // Функции для работы с поддеревьями
    BinarySearchTree<T> extractSubtree(T value);
    bool containsSubtree(const BinarySearchTree<T>& subtree);

    // Балансировка дерева
    void rotateLeft(TreeNode<T>*& node);
    void rotateRight(TreeNode<T>*& node);
    int height(TreeNode<T>* node);
    int getBalance(TreeNode<T>* node);
    void balance(TreeNode<T>*& node);

};

#include "BinarySearchTree.cpp"

#endif // BINARYSEARCHTREE_H