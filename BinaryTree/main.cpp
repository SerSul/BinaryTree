#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <functional>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

// Шаблон класса для узла бинарного дерева
template <typename T>
class TreeNode {
public:
    T data;
    TreeNode<T>* left;
    TreeNode<T>* right;

    TreeNode(T value) : data(value), left(nullptr), right(nullptr) {}
};

// Шаблон класса бинарного дерева поиска
template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    // Вспомогательные функции для рекурсивных операций
    void insertRecursive(TreeNode<T>*& node, T value) {
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

    TreeNode<T>* findMin(TreeNode<T>* node) {
        if (node == nullptr) return nullptr;
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    TreeNode<T>* removeRecursive(TreeNode<T>*& node, T value) {
        if (node == nullptr) return nullptr;

        if (value < node->data) {
            node->left = removeRecursive(node->left, value);
        }
        else if (value > node->data) {
            node->right = removeRecursive(node->right, value);
        }
        else {
            // Найден узел для удаления
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
                // Узел имеет два потомка
                TreeNode<T>* temp = findMin(node->right);
                node->data = temp->data;
                node->right = removeRecursive(node->right, temp->data);
            }
        }
        return node;
    }

    TreeNode<T>* findRecursive(TreeNode<T>* node, T value) {
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

    void printInorder(TreeNode<T>* node) {
        if (node != nullptr) {
            printInorder(node->left);
            std::cout << node->data << " ";
            printInorder(node->right);
        }
    }

    void destroy(TreeNode<T>* node) {
        if (node != nullptr) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    void printTree(TreeNode<T>* node, int indent) {
        if (node != nullptr) {
            printTree(node->right, indent + 1);
            for (int i = 0; i < indent; ++i) {
                std::cout << "  ";
            }
            std::cout << "+--" << node->data << std::endl;
            printTree(node->left, indent + 1);
        }
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(T value) {
        insertRecursive(root, value);
    }

    void remove(T value) {
        root = removeRecursive(root, value);
    }

    TreeNode<T>* find(T value) {
        return findRecursive(root, value);
    }

    // Метод для вывода дерева в формате слева направо с отступами
    void printTree() {
        printTree(root, 0);
    }

    void clear() {
        destroy(root);
        root = nullptr;
    }

    ~BinarySearchTree() {
        clear();
    }

    // Map
    template <typename U>
    BinarySearchTree<U> map(std::function<U(T)> func) const {
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

    // Reduce
    template <typename U>
    U reduce(std::function<U(U, T)> func, U initialValue) const {
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

    // Where
    BinarySearchTree<T> where(std::function<bool(const T&)> predicate) const {
        BinarySearchTree<T> filteredTree;

        std::function<void(TreeNode<T>*, TreeNode<T>*&)> filterFunc = [&](TreeNode<T>* node, TreeNode<T>*& newNode) {
            if (node) {
                if (predicate(node->data)) {
                    newNode = new TreeNode<T>(node->data);
                    filterFunc(node->left, newNode->left);
                    filterFunc(node->right, newNode->right);
                }
                else {
                    filterFunc(node->left, newNode);
                    filterFunc(node->right, newNode);
                }
            }
            else {
                newNode = nullptr;
            }
            };

        filterFunc(root, filteredTree.root);

        return filteredTree;
    }
};

int main() {
    setlocale(LC_ALL, "ru");
    BinarySearchTree<int> tree;

    int choice;
    while (true) {
        std::cout << "Меню:" << std::endl;
        std::cout << "1. Добавить элемент" << std::endl;
        std::cout << "2. Удалить элемент" << std::endl;
        std::cout << "3. Найти элемент" << std::endl;
        std::cout << "4. Вывести дерево" << std::endl;
        std::cout << "5. Очистить дерево" << std::endl;
        std::cout << "6. Map" << std::endl;
        std::cout << "7. Where" << std::endl;
        std::cout << "8. Reduce" << std::endl;
        std::cout << "9. Выход" << std::endl;
        std::cout << "Выберите пункт меню: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            std::cout << "Введите значение для добавления: ";
            std::cin >> value;
            tree.insert(value);
            break;
        }
        case 2: {
            int value;
            std::cout << "Введите значение для удаления: ";
            std::cin >> value;
            tree.remove(value);
            break;
        }
        case 3: {
            int value;
            std::cout << "Введите значение для поиска: ";
            std::cin >> value;
            TreeNode<int>* node = tree.find(value);
            if (node) {
                std::cout << "Элемент найден: " << node->data << std::endl;
            }
            else {
                std::cout << "Элемент не найден" << std::endl;
            }
            break;
        }
        case 4: {
            tree.printTree();
            break;
        }
        case 5: {
            tree.clear();
            break;
        }
        case 6: {
            // Map
            std::string funcStr;
            std::function<int(int)> func = [funcStr](int x) {
                return x * 2; 
                };
            BinarySearchTree<int> newTree = tree.map(func);
            newTree.printTree();
            break;
        }
        case 7: {
            // Where

            std::string predicateStr;
            std::function<bool(const int&)> predicate = [predicateStr](const int& x) {
                return x > 5; // пример
                };
            BinarySearchTree<int> filteredTree = tree.where(predicate);
            filteredTree.printTree();
            break;
        }
        case 8: {
            // Reduce
            std::string funcStr;
            std::function<int(int, int)> func = [funcStr](int x, int y) {
                return x + y; // пример
                };
            int initialValue;

            std::cin >> initialValue;
            int result = tree.reduce(func, initialValue);
            std::cout << "Результат reduce: " << result << std::endl;
            break;
        }
        case 9: {
            return 0;
        }
        default: {
            std::cout << "Неверный выбор" << std::endl;
        }
        }
    }

    return 0;
}