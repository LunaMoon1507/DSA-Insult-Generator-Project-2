#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <random>
#include "HashTable.hpp"
#include "Word.hpp"
#include "Tree.hpp"

void insertData(HashTable* hash, RBTree* tree, std::string fileName) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: .csv failed to open.\n";
    }
    std::string line;
    getline(file, line); // skip header
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string word, pos, vibe, severityStr;

        getline(ss, word, ',');
        getline(ss, pos, ',');
        getline(ss, vibe, ',');
        getline(ss, severityStr, ',');

        Word *entry = new Word();
        entry->word = word;
        entry->pos = pos;
        entry->vibe = vibe;
        try {
            entry->severity = stoi(severityStr);
        } catch (...) {
            entry->severity = 1;
        }

        hash->insert(entry);
        tree->insert(entry);
        delete entry;
    }
}

std::string sentence1Hash(HashTable* hash, std::string vibe, int severity) {
    std::string newSentence = "You’re a "
        + hash->get("adjective",vibe,severity) + " "
        + hash->get("noun",vibe,severity) + " and an "
        + hash->get("adjective",vibe,severity) + " "
        + hash->get("adjective",vibe,severity) + " "
        + hash->get("noun",vibe,severity)
        + ", and worst of all a "
        + hash->get("adjective","CSmajor",severity)
        + " CS major!";
    return newSentence;
}

std::string sentence2Hash(HashTable* hash, std::string vibe, int severity) {
    std::string newSentence = "Imagine being a "
        + hash->get("adjective",vibe,severity) + " "
        + hash->get("noun",vibe,severity) + ", you "
        + hash->get("adjective",vibe,severity) + " "
        + hash->get("adjective",vibe,severity) + " "
        + hash->get("noun",vibe,severity)
        + " of a "
        + hash->get("noun","CSmajor",severity) + "!";
    return newSentence;
}

std::string sentence3Hash(HashTable* hash, std::string vibe, int severity) {
    std::string newSentence = "You should "
        + hash->get("verb",vibe,severity) + " in a "
        + hash->get("noun",vibe,severity) + " and an "
        + hash->get("adjective",vibe,severity) + " "
        + hash->get("noun",vibe,severity) + ", you "
        + hash->get("adjective",vibe,severity) + " "
        + hash->get("noun","CSmajor",severity) + "!";
    return newSentence;
}

std::string sentence4Hash(HashTable* hash, std::string vibe, int severity) {
    std::string newSentence = "You’re just a "
        + hash->get("adjective",vibe,severity) + " "
        + hash->get("adjective",vibe,severity) + " "
        + hash->get("noun",vibe,severity) + " of a "
        + hash->get("adjective","CSmajor",severity)
        + " CS major, so stop "
        + hash->get("verb",vibe,severity) + " and be a quiet "
        + hash->get("noun","CSmajor",severity) + ".";
    return newSentence;
}

/*
std::string sentence1Tree(RBTree* tree, std::string vibe, int severity) {
    std::string newSentence = "You’re just a "
        + tree->get("adjective",vibe,severity) + " "
        + tree->get("adjective",vibe,severity) + " "
        + tree->get("noun",vibe,severity) + " of a "
        + tree->get("adjective","CSmajor",severity)
        + " CS major, so stop "
        + tree->get("verb",vibe,severity) + " and be a quiet "
        + tree->get("noun","CSmajor",severity) + ".";
    return newSentence;
}

std::string sentence2Tree(RBTree* tree, std::string vibe, int severity) {
    std::string newSentence = "You’re just a "
        + tree->get("adjective",vibe,severity) + " "
        + tree->get("adjective",vibe,severity) + " "
        + tree->get("noun",vibe,severity) + " of a "
        + tree->get("adjective","CSmajor",severity)
        + " CS major, so stop "
        + tree->get("verb",vibe,severity) + " and be a quiet "
        + tree->get("noun","CSmajor",severity) + ".";
    return newSentence;
}

std::string sentence3Tree(RBTree* tree, std::string vibe, int severity) {
    std::string newSentence = "You’re just a "
        + tree->get("adjective",vibe,severity) + " "
        + tree->get("adjective",vibe,severity) + " "
        + tree->get("noun",vibe,severity) + " of a "
        + tree->get("adjective","CSmajor",severity)
        + " CS major, so stop "
        + tree->get("verb",vibe,severity) + " and be a quiet "
        + tree->get("noun","CSmajor",severity) + ".";
    return newSentence;
}

std::string sentence4Tree(RBTree* tree, std::string vibe, int severity) {
    std::string newSentence = "You’re just a "
        + tree->get("adjective",vibe,severity) + " "
        + tree->get("adjective",vibe,severity) + " "
        + tree->get("noun",vibe,severity) + " of a "
        + tree->get("adjective","CSmajor",severity)
        + " CS major, so stop "
        + tree->get("verb",vibe,severity) + " and be a quiet "
        + tree->get("noun","CSmajor",severity) + ".";
    return newSentence;
}
*/

int main()
{
    int choice = 0;
    int severity = 0;
    std::string vibe;
    int whileLoop;
    bool stillGenerate = true;

    // Loading .csv data into hash table and timing it
    std::cout << "\nLoading data..." << std::endl;
    auto startTime = std::chrono::high_resolution_clock::now();
    HashTable *hash = new HashTable();
    RBTree *tree = new RBTree();
    insertData(hash,tree,"../databases/wordnet-db-3.csv");
    insertData(hash,tree,"../databases/professional-db.csv");
    insertData(hash,tree,"../databases/explicit-db-cleaned.csv");
    insertData(hash,tree,"../databases/brainrot-db.csv");
    insertData(hash,tree,"../databases/CSmajor-database.csv");
    auto endTime = std::chrono::high_resolution_clock::now();
    auto durationTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
    std::cout << "(Took " << durationTime.count() << " milliseconds)" << std::endl;

    // Text interface
    std::cout << "\nWelcome to the CS Major insult generator!" << std::endl;

    while(stillGenerate){
        std::cout << "\nWhat vibe would you like your insult to have?\n(1) Random\n(2) Explicit\n(3) Brainrot\n(4) Professional" << std::endl;
        std::cout << "Choice: ";
        std::cin >> choice;

        if(std::cin.fail() || choice < 1 || choice > 4){ // checks for valid input, 1-4 only
            std::cout << "\nPlease choose a number 1-4!\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        switch (choice){ // mode selection
            case 1:
                std::cout << "You have chosen Random Mode :|\n" << std::endl;
                vibe = "Random";
                break;

            case 2:
                std::cout << "You have chosen Explicit Mode o_o\n" << std::endl;
                vibe = "Explicit";
                break;
            case 3:
                std::cout << "You have chosen Brainrot Mode!!\n" << std::endl;
                vibe = "Brainrot";
                break;
            case 4:
                std::cout << "You have chosen Professional Mode.\n" << std::endl;
                vibe = "Professional";
                break;
            default: break;
        }

        std::cout << "What severity would you like your insult to have?\n(1) Mild\n(2) Moderate\n(3) Severe\n(4) Brutal" << std::endl;
        std::cout << "Choice: ";
        std::cin >> severity;

        if(std::cin.fail() || severity < 1 || severity > 4){ // same input check; if it's invalid it will restart to first prompt
            std::cout << "Invalid severity! Returning to main menu.\n" << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }
        switch (severity){ // severity selection
            case 1:
                std::cout << "\nYou have chosen a mild insult in " + vibe + " Mode." << std::endl;
                break;
            case 2:
                std::cout << "\nYou have chosen a moderate insult in " + vibe + " Mode..."  << std::endl;
                break;
            case 3:
                std::cout << "\nYou have chosen a severe insult in " + vibe + " Mode!"  << std::endl;
                break;
            case 4:
                std::cout << "\nYou have chosen a brutal insult in " + vibe + " Mode!!!" << std::endl;
                break;
            default:
                std::cout << "\nPlease choose a number 1-4!" << std::endl;
        }

        // Generating a random number [1,4] to choose a sentence structure
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 4);
        int randomNum = dist(gen);

        // Creating insult string with Hash Table
        std::cout << "\nGenerating insults..." << std::endl;
        std::string sentence;
        startTime = std::chrono::high_resolution_clock::now();
        switch (randomNum) {
            case 1:
                sentence = sentence1Hash(hash,vibe,severity);
                break;
            case 2:
                sentence = sentence2Hash(hash,vibe,severity);
                break;
            case 3:
                sentence = sentence3Hash(hash,vibe,severity);
                break;
            case 4:
                sentence = sentence4Hash(hash,vibe,severity);
                break;
            default:
                sentence = "";
                break;
        }
        endTime = std::chrono::high_resolution_clock::now();
        durationTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        std::cout << "Hash Table Insult: " << sentence << std::endl;
        std::cout << "(Took " << durationTime.count() << " milliseconds)" << std::endl;

        // Creating insult string with RB Tree
        // TODO: implement sentence generation for RB tree!
        startTime = std::chrono::high_resolution_clock::now();
        /*
        switch (randomNum) {
            case 1:
                sentence = sentence1Tree(tree,vibe,severity);
                break;
            case 2:
                sentence = sentence2Tree(tree,vibe,severity);
                break;
            case 3:
                sentence = sentence3Tree(tree,vibe,severity);
                break;
            case 4:
                sentence = sentence4Tree(tree,vibe,severity);
                break;
            default:
                sentence = "";
                break;
        } */
        endTime = std::chrono::high_resolution_clock::now();
        durationTime = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
        std::cout << "Red Black Tree Insult: " << sentence << std::endl;
        std::cout << "(Took " << durationTime.count() << " milliseconds)" << std::endl;

        // Main menu loop
        std::cout << "\nWould you like to insult again, or exit?\n 1. Generate another insult\n 2. Exit" << std::endl;
        std::cout << "Choice: ";
        std::cin >> whileLoop;

        if (whileLoop == 1){
            continue;
        }
        else {
            // std::cout << "\nPlease choose 1 or 2!" << std::endl;
            stillGenerate = false;
            std::cout << "\nExiting program..." << std::endl;
        }
    }
    std::cout << "\nGoodbye, see you next time!\n(CS Major Insult Generator is not liable for any damages caused by using this program)" << std::endl;
    return 0;
}
