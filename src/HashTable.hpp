#include <vector>
#include <random>
#include "Word.hpp"
#include "WordStructure.hpp"

class HashTable : public WordStructure {
private:
    std::vector<std::vector<Word*>> hash_table;
    int hash(int POS, int vibe, int severity);
    // These functions help decode the string values in the word object to ints
    int decodePOS(std::string str);
    int decodeVibe(std::string str);

public:
    HashTable() : hash_table(80, std::vector<Word*>(0)) {}
    ~HashTable();

    bool insert(Word* data);
    std::string get(std::string POS, std::string vibe, int severity);
    //std::string getRandom(std::string POS);
};