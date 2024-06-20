#ifndef BINARYSEARCHTREE_TPP
#define BINARYSEARCHTREE_TPP

#include "BinarySearchTree.h"

template <typename T>
void BinarySearchTree<T>::insertRecursive(TreeNode<T>*& node, T value) {
    if (node == nullptr) {
        node = new TreeNode<T>(value);
    }
    else {
        if (value < node->data) {
            insertRecursive(node->left, value);
        }
        else if (value > node->data) {
            insertRecursive(node->right, value);
        }
        else {
            throw std::invalid_argument("Дубликаты значений в бинарном дереве поиска не допускаются.");
        }
    }
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::findMin(TreeNode<T>* node) {
    if (node == nullptr) return nullptr;
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::removeRecursive(TreeNode<T>*& node, T value) {
    if (node == nullptr) return nullptr;

    if (value < node->data) {
        node->left = removeRecursive(node->left, value);
    }
    else if (value > node->data) {
        node->right = removeRecursive(node->right, value);
    }
    else {
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
        }
        else if (node->left == nullptr) {
            TreeNode<T>* temp = node;
            node = node->right;
            delete temp;
        }
        else if (node->right == nullptr) {
            TreeNode<T>* temp = node;
            node = node->left;
            delete temp;
        }
        else {
            TreeNode<T>* temp = findMin(node->right);
            node->data = temp->data;
            node->right = removeRecursive(node->right, temp->data);
        }
    }
    return node;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::findRecursive(TreeNode<T>* node, T value) {
    if (node == nullptr) return nullptr;

    if (value < node->data) {
        return findRecursive(node->left, value);
    }
    else if (value > node->data) {
        return findRecursive(node->right, value);
    }
    else {
        return node;
    }
}

template <typename T>
void BinarySearchTree<T>::printInorder(TreeNode<T>* node) {
    if (node != nullptr) {
        printInorder(node->left);
        std::cout << node->data << " ";
        printInorder(node->right);
    }
}

template <typename T>
void BinarySearchTree<T>::destroy(TreeNode<T>* node) {
    if (node != nullptr) {
        destroy(node->left);
        destroy(node->right);
        delete node;
    }
}

template <typename T>
void BinarySearchTree<T>::printTree(TreeNode<T>* node, int indent) {
    if (node != nullptr) {
        printTree(node->right, indent + 1);
        for (int i = 0; i < indent; ++i) {
            std::cout << "  ";
        }
        std::cout << "+--" << node->data << std::endl;
        printTree(node->left, indent + 1);
    }
}

template <typename T>
void BinarySearchTree<T>::insert(T value) {
    insertRecursive(root, value);
}

template <typename T>
void BinarySearchTree<T>::remove(T value) {
    root = removeRecursive(root, value);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::find(T value) {
    return findRecursive(root, value);
}

template <typename T>
void BinarySearchTree<T>::printTree() {
    printTree(root, 0);
}

template <typename T>
void BinarySearchTree<T>::clear() {
    destroy(root);
    root = nullptr;
}

template <typename T>
template <typename U>
BinarySearchTree<U> BinarySearchTree<T>::map(std::function<U(T)> func) const {
    BinarySearchTree<U> newTree;

    std::function<void(TreeNode<T>*, TreeNode<U>*&)> mapFunc = [&](TreeNode<T>* node, TreeNode<U>*& newNode) {
        if (node) {
            U newValue = func(node->data);
            newNode = new TreeNode<U>(newValue);
            mapFunc(node->left, newNode->left);
            mapFunc(node->right, newNode->right);
        }
        else {
            newNode = nullptr;
        }
        };

    mapFunc(root, newTree.root);

    return newTree;
}

template <typename T>
template <typename U>
U BinarySearchTree<T>::reduce(std::function<U(U, T)> func, U initialValue) const {
    std::function<U(TreeNode<T>*, U)> reduceFunc = [&](TreeNode<T>* node, U acc) {
        if (node) {
            acc = func(acc, node->data);
            acc = reduceFunc(node->left, acc);
            acc = reduceFunc(node->right, acc);
        }
        return acc;
        };

    return reduceFunc(root, initialValue);
}

template <typename T>
BinarySearchTree<T> BinarySearchTree<T>::where(std::function<bool(const T&)> predicate) const {
    BinarySearchTree<T> filteredTree;

    std::function<void(TreeNode<T>*)> filterFunc = [&](TreeNode<T>* node) {
        if (node) {
            if (predicate(node->data)) {
                filteredTree.insert(node->data);
            }
            filterFunc(node->left);
            filterFunc(node->right);
        }
    };

    filterFunc(root);
    return filteredTree;
}



template <typename T>
void BinarySearchTree<T>::printPreorder() {
    printPreorder(root);
}

template <typename T>
void BinarySearchTree<T>::printPreorder(TreeNode<T>* node) {
    if (node != nullptr) {
        std::cout << node->data << " ";
        printPreorder(node->left);
        printPreorder(node->right);
    }
}

template <typename T>
void BinarySearchTree<T>::printPostorder() {
    printPostorder(root);
}

template <typename T>
void BinarySearchTree<T>::printPostorder(TreeNode<T>* node) {
    if (node != nullptr) {
        printPostorder(node->left);
        printPostorder(node->right);
        std::cout << node->data << " ";
    }
}

template <typename T>
void BinarySearchTree<T>::printInorder() {
    printInorder(root);
}

template <typename T>
void BinarySearchTree<T>::printReverseInorder() {
    printReverseInorder(root);
}

template <typename T>
void BinarySearchTree<T>::printReverseInorder(TreeNode<T>* node) {
    if (node != nullptr) {
        printReverseInorder(node->right);
        std::cout << node->data << " ";
        printReverseInorder(node->left);
    }
}

template <typename T>
void BinarySearchTree<T>::printReversePreorder() {
    printReversePreorder(root);
}

template <typename T>
void BinarySearchTree<T>::printReversePreorder(TreeNode<T>* node) {
    if (node != nullptr) {
        std::cout << node->data << " ";
        printReversePreorder(node->right);
        printReversePreorder(node->left);
    }
}

template <typename T>
void BinarySearchTree<T>::printReversePostorder() {
    printReversePostorder(root);
}

template <typename T>
void BinarySearchTree<T>::printReversePostorder(TreeNode<T>* node) {
    if (node != nullptr) {
        printReversePostorder(node->left);
        printReversePostorder(node->right);
        std::cout << node->data << " ";
    }
}


template <typename T>
BinarySearchTree<T> BinarySearchTree<T>::merge(const BinarySearchTree<T>& other) const {
    BinarySearchTree<T> mergedTree;

    std::function<void(TreeNode<T>*, TreeNode<T>*, TreeNode<T>*&)> mergeFunc = [&](TreeNode<T>* node1, TreeNode<T>* node2, TreeNode<T>*& mergedNode) {
        if (node1 && node2) {
            mergedNode = new TreeNode<T>(node1->data);
            mergeFunc(node1->left, node2->left, mergedNode->left);
            mergeFunc(node1->right, node2->right, mergedNode->right);
        }
        else if (node1) {
            mergedNode = new TreeNode<T>(node1->data);
            mergeFunc(node1->left, nullptr, mergedNode->left);
            mergeFunc(node1->right, nullptr, mergedNode->right);
        }
        else if (node2) {
            mergedNode = new TreeNode<T>(node2->data);
            mergeFunc(nullptr, node2->left, mergedNode->left);
            mergeFunc(nullptr, node2->right, mergedNode->right);
        }
        };

    mergeFunc(root, other.root, mergedTree.root);

    return mergedTree;
}


template <typename T>
TreeNode<T>* BinarySearchTree<T>::extractSubtreeRecursive(TreeNode<T>*& node, T value) {
    if (node == nullptr) {
        return nullptr;
    }

    TreeNode<T>* extractedSubtree = nullptr;

    if (value < node->data) {
        extractedSubtree = extractSubtreeRecursive(node->left, value);
    }
    else if (value > node->data) {
        extractedSubtree = extractSubtreeRecursive(node->right, value);
    }
    else {
        extractedSubtree = node;
        node = nullptr;
    }

    return extractedSubtree;
}

template <typename T>
BinarySearchTree<T> BinarySearchTree<T>::extractSubtree(T value) {
    BinarySearchTree<T> extractedTree;

    TreeNode<T>* subtreeRoot = extractSubtreeRecursive(root, value);
    extractedTree.root = subtreeRoot;

    return extractedTree;
}


template <typename T>
bool BinarySearchTree<T>::containsSubtreeRecursive(TreeNode<T>* mainTree, TreeNode<T>* subtree) {
    if (subtree == nullptr) {
        return true; // Empty subtree is always found
    }
    if (mainTree == nullptr) {
        return false; // Main tree is empty, subtree cannot be found
    }

    if (mainTree->data == subtree->data &&
        containsSubtreeRecursive(mainTree->left, subtree->left) &&
        containsSubtreeRecursive(mainTree->right, subtree->right)) {
        return true;
    }

    return containsSubtreeRecursive(mainTree->left, subtree) || containsSubtreeRecursive(mainTree->right, subtree);
}


template <typename T>
bool BinarySearchTree<T>::containsSubtree(const BinarySearchTree<T>& subtree)  {
    return containsSubtreeRecursive(root, subtree.root);
}



#endif // BINARYSEARCHTREE_TPP
