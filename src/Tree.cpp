#include "Tree.hpp"

RBTree::RBTree() : treeSize(0) {
    justInsertedNode = nullptr;
    Word emptyWord = {"", "", "", 0};
    nil = new Node(emptyWord);
    nil->color = BLACK;
    nil->left = nullptr;
    nil->right = nullptr;
    nil->parent = nullptr;
    root = nil;
}

RBTree::~RBTree() {
    destructorHelper(this->root);
    delete nil;
}

void RBTree::insert(Word* newWord) {
    justInsertedNode = nullptr;
    root = insertHelper(root, *newWord, nullptr);
    fixInsert(justInsertedNode);
    treeSize++;
}

void RBTree::inOrderTraversal(Node* node) {
    if (node == nil) {
        return;
    }
    inOrderTraversal(node->left);
    std::cout << node->data.severity << " ";
    inOrderTraversal(node->right);
}

void RBTree::printInOrder() {
    inOrderTraversal(root);
    std::cout << std::endl;
}

std::string RBTree::get(std::string pos, std::string vibe, int severity) {
    std::vector<Word> candidates = vectorOfWords(pos, vibe, severity);
    if (candidates.empty()) {
        Word emptyWord = {"", "", "", 0};
        return " ";
    }
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, candidates.size() - 1);
    int randomIndex = dis(gen);

    return candidates[randomIndex].word;
}

// gets all words with desired severity level and position in sentence
std::vector<Word> RBTree::vectorOfWords(std::string& pos, std::string& vibe, int severity) {
    std::vector<Word> words;
    int currentSeverity = severity;
    while (words.size() < 3 && currentSeverity != 0) { // loops until vector has at least 3 words
        auto it = lowerBoundSeverity(currentSeverity);
        auto treeEnd = end();
        while (it != treeEnd && it->severity == currentSeverity) { // only loops within the desired severity section
            if (it->pos == pos && it->vibe == vibe) {
                words.push_back(*it);
            }
            ++it;
        }
        currentSeverity--; // if vector has less than 3 words, it checks all the words in a severity level 1 lower than the current
    }
    return words;
}

Node* RBTree::insertHelper(Node* node, const Word& data, Node* parent) { // insertion helper for insert function, done recursively
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

void RBTree::rotateLeft(Node* x) {
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

void RBTree::rotateRight(Node* y) {
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

void RBTree::fixInsert(Node* k) { //balances the RB tree
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

void RBTree::destructorHelper(Node* node) {
    if (node == nil) return;
    destructorHelper(node->left);
    destructorHelper(node->right);
    delete node;
}
