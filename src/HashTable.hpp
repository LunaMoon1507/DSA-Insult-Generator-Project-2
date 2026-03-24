#include "Word.cpp"
#include <vector>
#include <string>

struct HashTable {
    std::vector<std::vector<Word*>> hash_table;

    HashTable() : hash_table(256, std::vector<Word*>(0)) {}
    ~HashTable();
    int hash(int POS, int vibe, int severity);
    void insert(Word* data);
    std::string get(std::string POS, std::string vibe, std::string mode, int severity);

    //these lines help decode the string values in the word object to ints
    int decodePOS(std::string str);
    int decodeVibe(std::string str);
};