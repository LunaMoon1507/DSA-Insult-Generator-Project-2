#include <iostream>
#include "Word.cpp"
#include "Tree.cpp"
#include "HashTable.cpp"

int main() {
    std::cout << "\nWelcome to the CS Major insult generator!" << std::endl;
    Word w;
    w.word = "hello";
    w.pos = "noun";
    w.severity = 1;
    w.vibe = "friendly";
    return 0;
}
