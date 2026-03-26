// RB tree implementation to store Words
#pragma once
#include <iostream>
#include <string>
#include "Word.hpp"

enum Color { RED, BLACK };

struct Node { // Node that contains the word struct within it
    Word data;
    Color color;
    Node *left, *right, *parent;

    explicit Node(const Word& w) : data(w), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RBTree {
private:
    Node* root;
    Node* nil;
    size_t treeSize;
    Node* justInsertedNode;

    // insertion helper for insert function, done recursively
    Node* insertHelper(Node* node, const Word& data, Node* parent);

    void rotateLeft(Node* x);
    void rotateRight(Node* y);

    // balances the RB tree
    void fixInsert(Node* k);

    void destructorHelper(Node* node);

public:
    class Iterator {
    private:
        Node* current;
        Node* nil;

    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = Word;
        using difference_type = std::ptrdiff_t;
        using pointer = Word*;
        using reference = Word&;

        Iterator(Node* node, Node* nil) : current(node), nil(nil) {}
        Word& operator*() const {
            return current->data;
        }
        Word* operator->() const {
            return &(current->data);
        }
        Iterator& operator++() {
            if (current == nil) {
                return *this;
            }
            if (current->right != nil) { // finds next node in an in order traversal
                current = current->right;
                while (current->left != nil) {
                    current = current->left;
                }
            }
            else {
                Node* p = current->parent;
                while (p != nullptr && current == p->right) {
                    current = p;
                    p = p->parent;
                }
                current = (p == nullptr) ? nil : p;
            }
            return *this;
        }
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };

    Iterator begin() const { //finds the first node in an in order traversal in the tree
        Node* temp = root;
        if (temp == nil) {
            return Iterator(nil, nil);
        }
        while (temp->left != nil) {
            temp = temp->left;
        }
        return Iterator(temp, nil);
    }

    Iterator end() const {
        return Iterator(nil, nil);
    }

    RBTree();
    ~RBTree();

    void insert(Word newWord);
    void inOrderTraversal(Node* node);
    void printInOrder();
};
