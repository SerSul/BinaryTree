#include "BinarySearchTree.h"
#include <cassert>
#include <functional>

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

        filteredNode = filteredTree.find(3);
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

    void runAllTests() {
        testInsertFind();
        testRemove();
        testMap();
        testWhere();
        testReduce();
        std::cout << "All tests passed!\n";
    }
};