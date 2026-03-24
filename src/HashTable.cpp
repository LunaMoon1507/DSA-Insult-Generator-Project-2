#include "HashTable.hpp"
#include <stdexcept>
#include <random>

HashTable::~HashTable() {
    for (int i = 0; i < 64; i++) {
        for (Word* w : hash_table[i]) {
            delete w;
        }
    }
}

int HashTable::hash(int POS, int vibe, int severity) {
    if (POS < 0 || POS > 3 || vibe < 0 || vibe > 3 || severity < 0 || severity > 3 ) {
        throw std::runtime_error("Invalid Values in the Hash"); // eventualy remove but will be amazing for debugging
    }
    return severity * 16 + vibe * 4 + POS;
}

void HashTable::insert(Word* data) {
    int currPOS = decodePOS(data->pos);
    int currVibe = decodeVibe(data->vibe);
    int currSeverity = data->severity;
    int currHash = hash(currPOS, currVibe, currSeverity);
    hash_table[currHash].push_back(data);
}

std::string HashTable::get(std::string POS, std::string vibe, int desiredSeverity) {
    std::random_device rd;
    std::mt19937 gen(rd());
    int desiredPOS = decodePOS(POS);
    int desiredVibe = decodeVibe(vibe);
    int desiredHash = hash(desiredPOS, desiredVibe, desiredSeverity);
    int vecLen = hash_table[desiredHash].size();
    if (vecLen == 0) return ""; // if somehow there is no data in this section
    if (vecLen == 1) return hash_table[desiredHash][0]->word;
    std::uniform_int_distribution<> dist(0, vecLen-1);
    return hash_table[desiredHash][dist(gen)]->word;
}

int HashTable::decodePOS(std::string str) {
    if (str == "noun") return 0;
    if (str == "adjective") return 1;
    if (str == "verb") return 2;
    return 3; //works for all others, even if typo
}

int HashTable::decodeVibe(std::string str) {
    if (str == "Basic") return 0;
    if (str == "Explicit") return 1;
    if (str == "Stupid/brainrot") return 2;
    return 3; // works for professional, but also typos
}