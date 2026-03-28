//A base class for the RB Tree and Hash Table to inherit from
#pragma once
#include <string>

class WordStructure {
public:
    virtual std::string get(std::string pos, std::string vibe, int severity) = 0;
    virtual ~WordStructure() = default;
};
