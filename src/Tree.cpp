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

    Node* insertHelper(Node* node, const Word& data, Node* parent) { // insertion helper for insert function, done recursively
        if (node == nil) {
            Node* newNode = new Node(data);
            newNode->parent = parent;
            newNode->left = nil;
            newNode->right = nil;
            this->justInsertedNode = newNode;
            return newNode;
        }
        if (data.severity < node->data.severity) {
            node->left = insertHelper(node->left, data, node);
        }
        else {
            node->right = insertHelper(node->right, data, node);
        }
        return node;
    }

    void rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nil) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        if (x->right != nil) x->right->parent = y;
        x->parent = y->parent;
        if (y->parent == nullptr) root = x;
        else if (y == y->parent->left) y->parent->left = x;
        else y->parent->right = x;
        x->right = y;
        y->parent = x;
    }

    void fixInsert(Node* k) { //balances the RB tree
        while (k != root && k->parent->color == RED) { // continues loop if parent is red; violates RB tree
            if (k->parent == k->parent->parent->left) {
                Node* uncle = k->parent->parent->right;
                if (uncle->color == RED) { // if the uncle is red, color swap 2 generations up from current node
                    k->parent->color = BLACK;
                    uncle->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) { // left right rotation happening (this is the left rotation part)
                        k = k->parent;
                        rotateLeft(k);
                    }
                    k->parent->color = BLACK; // right rotation and color change
                    k->parent->parent->color = RED;
                    rotateRight(k->parent->parent);
                }
            } else {
                Node* uncle = k->parent->parent->left;
                if (uncle->color == RED) {
                    k->parent->color = BLACK;
                    uncle->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rotateRight(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rotateLeft(k->parent->parent);
                }
            }
        }
        root->color = BLACK;
    }

    void destructorHelper(Node* node) {
        if (node == nil) return;
        destructorHelper(node->left);
        destructorHelper(node->right);
        delete node;
    }

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

    RBTree() : treeSize(0) {
        justInsertedNode = nullptr;
        Word emptyWord = {"", "", "", 0};
        nil = new Node(emptyWord);
        nil->color = BLACK;
        nil->left = nullptr;
        nil->right = nullptr;
        nil->parent = nullptr;
        root = nil;
    }

    ~RBTree() {
        destructorHelper(this->root);
        delete nil;
    }

    void insert(Word newWord) {
        justInsertedNode = nullptr;
        root = insertHelper(root, newWord, nullptr);
        fixInsert(justInsertedNode);
        treeSize++;
    }

    void inOrderTraversal(Node* node) {
        if (node == nil) {
            return;
        }
        inOrderTraversal(node->left);
        std::cout << node->data.severity << " ";
        inOrderTraversal(node->right);
    }

    void printInOrder() {
        inOrderTraversal(root);
        std::cout << std::endl;
    }
};


