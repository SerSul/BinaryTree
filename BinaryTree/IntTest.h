#include "BinarySearchTree.h"
#include <cassert>
#include <functional>
#include <iostream>
#include "TreeNode.h"


class IntBinarySearchTreeTest {
public:
    void testInsertFind() {
        BinarySearchTree<int> tree;

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        TreeNode<int>* node = tree.find(5);
        assert(node != nullptr);
        assert(node->data == 5);

        node = tree.find(2);
        assert(node != nullptr);
        assert(node->data == 2);

        node = tree.find(8);
        assert(node != nullptr);
        assert(node->data == 8);

        // Тесты для случаев, когда узел не найден
        node = tree.find(1);
        assert(node == nullptr);

        node = tree.find(9);
        assert(node == nullptr);
    }

    void testRemove() {
        BinarySearchTree<int> tree;

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        tree.remove(3);
        TreeNode<int>* node = tree.find(3);
        assert(node == nullptr);

        tree.remove(5);
        node = tree.find(5);
        assert(node == nullptr);

        node = tree.find(7);
        assert(node != nullptr);
        assert(node->data == 7);

        // Повторное удаление
        tree.remove(7);
        node = tree.find(7);
        assert(node == nullptr);
    }

    void testMap() {
        BinarySearchTree<int> tree;

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        std::function<int(int)> func = [](int x) {
            return x * 2;
            };
        BinarySearchTree<int> newTree = tree.map(func);

        TreeNode<int>* newNode = newTree.find(6);
        assert(newNode != nullptr);
        assert(newNode->data == 6);

        newNode = newTree.find(10);
        assert(newNode != nullptr);
        assert(newNode->data == 10);

        newNode = newTree.find(14);
        assert(newNode != nullptr);
        assert(newNode->data == 14);

        // Тесты для случаев, когда узел не найден
        newNode = newTree.find(5);
        assert(newNode == nullptr);

        newNode = newTree.find(1);
        assert(newNode == nullptr);
    }

    void testWhere() {
        BinarySearchTree<int> tree;

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        std::function<bool(const int&)> predicate = [](const int& x) {
            return x > 4;
            };
        BinarySearchTree<int> filteredTree = tree.where(predicate);

        TreeNode<int>* filteredNode = filteredTree.find(5);
        assert(filteredNode != nullptr);
        assert(filteredNode->data == 5);

        filteredNode = filteredTree.find(7);
        assert(filteredNode != nullptr);
        assert(filteredNode->data == 7);

        filteredNode = filteredTree.find(8);
        assert(filteredNode != nullptr);
        assert(filteredNode->data == 8);

        // Проверка отсутствия элементов, которые не соответствуют предикату
        filteredNode = filteredTree.find(3);
        assert(filteredNode == nullptr);

        filteredNode = filteredTree.find(2);
        assert(filteredNode == nullptr);
    }

    void testReduce() {
        BinarySearchTree<int> tree;

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        std::function<int(int, int)> func = [](int x, int y) {
            return x + y;
            };
        int initialValue = 0;
        int result = tree.reduce(func, initialValue);
        assert(result == 35);
    }


    void testPrintTree() {
        BinarySearchTree<int> tree;

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        // Печать дерева в различных порядках
        std::cout << "Inorder traversal: ";
        tree.printInorder();
        std::cout << "\n";

        std::cout << "Reverse inorder traversal: ";
        tree.printReverseInorder();
        std::cout << "\n";

        std::cout << "Preorder traversal: ";
        tree.printPreorder();
        std::cout << "\n";

        std::cout << "Reverse preorder traversal: ";
        tree.printReversePreorder();
        std::cout << "\n";

        std::cout << "Postorder traversal: ";
        tree.printPostorder();
        std::cout << "\n";

        std::cout << "Reverse postorder traversal: ";
        tree.printReversePostorder();
        std::cout << "\n";
    }

    void testMerge() {
        BinarySearchTree<int> tree1;

        tree1.insert(5);
        tree1.insert(3);
        tree1.insert(7);

        BinarySearchTree<int> tree2;

        tree2.insert(2);
        tree2.insert(4);
        tree2.insert(6);

        BinarySearchTree<int> mergedTree = tree1.merge(tree2);

        assert(mergedTree.find(2));
        assert(mergedTree.find(3));
        assert(mergedTree.find(4));
        assert(mergedTree.find(5));
        assert(mergedTree.find(6));
        assert(mergedTree.find(7));
    }

    void testExtractSubtree() {
        BinarySearchTree<int> tree;

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        BinarySearchTree<int> subtree = tree.extractSubtree(3);

        assert(subtree.find(3));
        assert(subtree.find(2));
        assert(subtree.find(4));
        assert(!subtree.find(5));
    }

    void testContainsSubtree() {
        BinarySearchTree<int> tree1;

        tree1.insert(5);
        tree1.insert(3);
        tree1.insert(7);

        BinarySearchTree<int> subtree;

        subtree.insert(3);
        subtree.insert(7);

        assert(tree1.containsSubtree(subtree));

        subtree.insert(6);
        assert(!tree1.containsSubtree(subtree));
    }

    

    void testHeight() {
        BinarySearchTree<int> tree;

        tree.insert(5);
        tree.insert(3);
        tree.insert(7);
        tree.insert(2);
        tree.insert(4);
        tree.insert(6);
        tree.insert(8);

        assert(tree.height(tree.find(8)) == 3);

        tree.insert(1);
        assert(tree.height(tree.find(1)) == 4);

        tree.remove(3);
        assert(tree.height(tree.find(3)) == 3);
    }


    void runAllTests() {
        testInsertFind();
        testRemove();
        testMap();
        testWhere();
        testReduce();
        testPrintTree();
        testMerge();
        testExtractSubtree();
        testContainsSubtree();
        testHeight();
        std::cout << "All tests passed!\n";
    }
};
