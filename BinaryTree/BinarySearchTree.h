#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "TreeNode.h"
#include <iostream>
#include <stdexcept>
#include <functional>
#include <String>

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

    void insert(T value);
    void remove(T value);
    TreeNode<T>* find(T value);
    void printTree();
    void clear();

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

    template <typename U>
    BinarySearchTree<U> map(std::function<U(T)> func) const;

    template <typename U>
    U reduce(std::function<U(U, T)> func, U initialValue) const;

    BinarySearchTree<T> where(std::function<bool(const T&)> predicate) const;

    BinarySearchTree<T> merge(const BinarySearchTree<T>& other) const;

    BinarySearchTree<T> extractSubtree(T value);
    bool containsSubtree(const BinarySearchTree<T>& subtree);


    //балансировка
    void rotateLeft(TreeNode<T>*& node);
    void rotateRight(TreeNode<T>*& node);
    int height(TreeNode<T>* node);
    int getBalance(TreeNode<T>* node);
    void balance(TreeNode<T>*& node);

    //прошивка
    void threadInorder(TreeNode<T>* node);
    void threadCustom(TreeNode<T>* node, std::function<void(TreeNode<T>*)> traversal);

    //Сохранение и чтение из строки
    std::string toStringInorder(TreeNode<T>* node);
    std::string toStringCustom(TreeNode<T>* node, const std::string& format);
    TreeNode<T>* fromStringInorder(const std::string& data, int& index);
    TreeNode<T>* fromStringCustom(const std::string& data, int& index, const std::string& format);



};

#include "BinarySearchTree.cpp"

#endif // BINARYSEARCHTREE_H
