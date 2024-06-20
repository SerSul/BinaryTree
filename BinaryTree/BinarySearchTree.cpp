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
BinarySearchTree<T> BinarySearchTree<T>::merge(const BinarySearchTree<T>& other) {
    BinarySearchTree<T> mergedTree;

    Stack<TreeNode<T>*> stack1, stack2;
    TreeNode<T>* current1 = root;
    TreeNode<T>* current2 = other.root;

    while (current1 != nullptr || !stack1.empty() || current2 != nullptr || !stack2.empty()) {
        while (current1 != nullptr) {
            stack1.push(current1);
            current1 = current1->left;
        }

        while (current2 != nullptr) {
            stack2.push(current2);
            current2 = current2->left;
        }

        if (!stack1.empty() && !stack2.empty()) {
            current1 = stack1.top();
            current2 = stack2.top();

            if (current1->data < current2->data) {
                mergedTree.insert(current1->data);
                stack1.pop();
                current1 = current1->right;
                current2 = nullptr;
            }
            else {
                mergedTree.insert(current2->data);
                stack2.pop();
                current2 = current2->right;
                current1 = nullptr;
            }
        }
        else if (!stack1.empty()) {
            current1 = stack1.top();
            mergedTree.insert(current1->data);
            stack1.pop();
            current1 = current1->right;
        }
        else if (!stack2.empty()) {
            current2 = stack2.top();
            mergedTree.insert(current2->data);
            stack2.pop();
            current2 = current2->right;
        }
    }

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
        return true;
    }
    if (mainTree == nullptr) {
        return false;
    }

    if (areIdentical(mainTree, subtree)) {
        return true;
    }
    return containsSubtreeRecursive(mainTree->left, subtree) || containsSubtreeRecursive(mainTree->right, subtree);
}

template <typename T>
bool BinarySearchTree<T>::areIdentical(TreeNode<T>* tree1, TreeNode<T>* tree2) {
    if (tree1 == nullptr && tree2 == nullptr) {
        return true;
    }
    if (tree1 == nullptr || tree2 == nullptr) {
        return false;
    }
    return tree1->data == tree2->data &&
        areIdentical(tree1->left, tree2->left) &&
        areIdentical(tree1->right, tree2->right);
}


template <typename T>
bool BinarySearchTree<T>::containsSubtree(const BinarySearchTree<T>& subtree)  {
    return containsSubtreeRecursive(root, subtree.root);
}

template <typename T>
int BinarySearchTree<T>::height(TreeNode<T>* node) {
    return node ? node->height : 0;
}

template <typename T>
int BinarySearchTree<T>::getBalance(TreeNode<T>* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::balance(TreeNode<T>* node) {
    int balanceFactor = getBalance(node);

    if (balanceFactor > 1) {
        if (getBalance(node->left) < 0)
            node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balanceFactor < -1) {
        if (getBalance(node->right) > 0)
            node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::rotateLeft(TreeNode<T>* y) {
    TreeNode<T>* x = y->right;
    TreeNode<T>* T2 = x->left;

    x->left = y;
    y->right = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::rotateRight(TreeNode<T>* y) {
    TreeNode<T>* x = y->left;
    TreeNode<T>* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}





#endif // BINARYSEARCHTREE_TPP
