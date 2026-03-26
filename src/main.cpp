#include <iostream>
#include <string>
#include "HashTable.hpp"
#include "Word.hpp"
#include "Tree.hpp"

int main()
{
    int choice = 0;
    int severity = 0;
    std::string mode;
    int whileLoop;
    bool stillGenerate = true;

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
                mode = "Random";
                break;

            case 2:
                std::cout << "You have chosen Explicit Mode o_o\n" << std::endl;
                mode = "Explicit";
                break;
            case 3:
                std::cout << "You have chosen Brainrot Mode!!\n" << std::endl;
                mode = "Brainrot";
                break;
            case 4:
                std::cout << "You have chosen Professional Mode.\n" << std::endl;
                mode = "Professional";
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
                std::cout << "\nYou have chosen a mild insult in " + mode + " Mode." << std::endl;
                break;

            case 2:
                std::cout << "\nYou have chosen a moderate insult in " + mode + " Mode..."  << std::endl;
                break;
            case 3:
                std::cout << "\nYou have chosen a severe insult in " + mode + " Mode!"  << std::endl;
                break;
            case 4:
                std::cout << "\nYou have chosen a brutal insult in " + mode + " Mode!!!" << std::endl;
                break;
            default:
                std::cout << "\nPlease choose a number 1-4!" << std::endl;
        }

        std::cout << "\nGenerating..." << std::endl; // the lines will probably be replaced with the actual function
        std::cout << "Insult: " << std::endl; // this one for RB tree
        std::cout << "Insult: " << std::endl; // this one for hash function

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
