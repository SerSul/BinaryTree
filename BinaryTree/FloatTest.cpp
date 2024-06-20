#include "FloatTest.h"

void FloatTest::testFind() {
    BinarySearchTree<float> tree;

    tree.insert(3.5f);
    tree.insert(1.2f);
    tree.insert(4.8f);
    tree.insert(2.9f);
    tree.insert(5.1f);

    TreeNode<float>* node = tree.find(2.9f);
    assert(node != nullptr);
    assert(node->data == 2.9f);
}

void FloatTest::testRemove() {
    BinarySearchTree<float> tree;

    tree.insert(3.5f);
    tree.insert(1.2f);
    tree.insert(4.8f);
    tree.insert(2.9f);
    tree.insert(5.1f);

    tree.remove(4.8f);
    TreeNode<float>* node = tree.find(4.8f);
    assert(node == nullptr);
}

void FloatTest::testMap() {
    BinarySearchTree<float> tree;

    tree.insert(3.5f);
    tree.insert(1.2f);
    tree.insert(4.8f);
    tree.insert(2.9f);
    tree.insert(5.1f);

    std::function<float(float)> func = [](float x) {
        return x * 2.0f;
        };
    BinarySearchTree<float> newTree = tree.map(func);
    TreeNode<float>* newNode = newTree.find(5.2f); // 2.6f * 2.0f
    assert(newNode != nullptr);
    assert(newNode->data == 5.8f); // исправлено значение на 5.8f, так как 2.9f * 2.0f = 5.8f
}

void FloatTest::testWhere() {
    BinarySearchTree<float> tree;

    tree.insert(3.5f);
    tree.insert(1.2f);
    tree.insert(4.8f);
    tree.insert(2.9f);
    tree.insert(5.1f);

    std::function<bool(const float&)> predicate = [](const float& x) {
        return x > 3.0f;
        };
    BinarySearchTree<float> filteredTree = tree.where(predicate);
    TreeNode<float>* filteredNode = filteredTree.find(4.8f);
    assert(filteredNode != nullptr);
    assert(filteredNode->data == 4.8f);
}

void FloatTest::testReduce() {
    BinarySearchTree<float> tree;

    tree.insert(3.5f);
    tree.insert(1.2f);
    tree.insert(2.9f);
    tree.insert(5.1f);

    std::function<float(float, float)> func2 = [](float x, float y) {
        return x + y;
        };
    float initialValue = 0.0f;
    float result = tree.reduce(func2, initialValue);
    assert(result == 12.7f); // 3.5f + 1.2f + 2.9f + 5.1f
}
