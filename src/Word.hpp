#pragma once
#include <string>
#include <utility>

struct Word {
    std::string word;
    std::string pos;
    std::string vibe;
    int severity  = 0;

    Word() = default;

    Word(std::string w, std::string p, std::string v, int s) :
        word(std::move(w)), pos(std::move(p)), vibe(std::move(v)), severity(s) {}
};