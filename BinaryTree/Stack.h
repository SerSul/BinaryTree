#ifndef STACK_H
#define STACK_H

#include <iostream>

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& data) : data(data), next(nullptr) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    void push(const T& data) {
        Node* newNode = new Node(data);
        newNode->next = topNode;
        topNode = newNode;
    }

    void pop() {
        if (topNode) {
            Node* temp = topNode;
            topNode = topNode->next;
            delete temp;
        }
    }

    T top() const {
        if (topNode) {
            return topNode->data;
        }
        throw std::runtime_error("Stack is empty");
    }

    bool empty() const {
        return topNode == nullptr;
    }

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }
};

#endif
