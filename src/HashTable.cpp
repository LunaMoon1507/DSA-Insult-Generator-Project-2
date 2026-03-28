#include "HashTable.hpp"
#include <random>

HashTable::~HashTable() {
    for (int i = 0; i < 80; i++) {
        for (Word* w : hash_table[i]) {
            delete w;
        }
    }
}

int HashTable::hash(int POS, int vibe, int severity) {
    if (POS < 0 || POS > 3 || vibe < 0 || vibe > 4 || severity < 1 || severity > 4 ) {
        return -1;
    }

    return (severity-1) * 20 + vibe * 4 + POS;
}

bool HashTable::insert(Word* data) {
    int currPOS = decodePOS(data->pos);
    int currVibe = decodeVibe(data->vibe);
    int currSeverity = data->severity;
    int currHash = hash(currPOS, currVibe, currSeverity);
    if (currHash == -1) return false;
    hash_table[currHash].push_back(data);
    return true;
}

std::string HashTable::get(std::string POS, std::string vibe, int desiredSeverity) {
    int desiredPOS = decodePOS(POS);
    int desiredVibe = decodeVibe(vibe);
    int desiredHash = hash(desiredPOS, desiredVibe, desiredSeverity);
    if (desiredHash == -1) return "";
    int vecLen = hash_table[desiredHash].size();
    if (vecLen == 0) return ""; // if there is no data in this section
    if (vecLen == 1) return hash_table[desiredHash][0]->word;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, vecLen-1);
    return hash_table[desiredHash][dist(gen)]->word;
}
/*
std::string HashTable::getRandom(std::string POS) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distS(0, 3);
    int desiredPOS = decodePOS(POS);
    if (desiredPOS == -1) return "";
    int desiredVibe = distS(gen);
    int desiredSeverity = distS(gen);
    int desiredHash = hash(desiredPOS, desiredVibe, desiredSeverity);
    int vecLen = hash_table[desiredHash].size();
    if (vecLen == 0) return ""; // if somehow there is no data in this section
    if (vecLen == 1) return hash_table[desiredHash][0]->word;
    std::uniform_int_distribution<int> distL(0, vecLen-1);
    return hash_table[desiredHash][distL(gen)]->word;
}
*/

int HashTable::decodePOS(std::string str) {
    if (str == "noun") return 0;
    if (str == "adjective") return 1;
    if (str == "verb") return 2;
    return 3; // adverb or typos
}

int HashTable::decodeVibe(std::string str) {
    if (str == "brainrot")  return 0;
    if (str == "random")return 1;
    if (str == "CSmajor") return 2;
    if (str == "explicit") return 3;
    return 4; // works for professional, but also typos
}