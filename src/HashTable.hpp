#include <vector>
#include <string>
#include <random>
#include "Word.hpp"

struct HashTable {
    std::vector<std::vector<Word*>> hash_table;

    HashTable() : hash_table(80, std::vector<Word*>(0)) {}
    ~HashTable();
    int hash(int POS, int vibe, int severity);
    bool insert(Word* data);
    std::string get(std::string POS, std::string vibe, int severity);
    //std::string getRandom(std::string POS);

    // these lines help decode the string values in the word object to ints
    int decodePOS(std::string str);
    int decodeVibe(std::string str);
};
