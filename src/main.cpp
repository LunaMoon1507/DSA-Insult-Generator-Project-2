#include <iostream>
#include "Word.cpp"
#include "Tree.cpp"
#include "HashTable.hpp"

int main() {
    std::cout << "\nWelcome to the CS Major insult generator!" << std::endl;

    // Testing out creating a word
    Word w;
    w.word = "hello";
    w.pos = "noun";
    w.severity = 1;
    w.vibe = "friendly";

    // Create menu-driven text interface with input validation here

    return 0;
}

/*
    Example run of the program:

    Welcome to the CS Major insult generator!

    What vibe would you like your insult to have?
    1. Basic
    2. Explicit
    3. Stupid/brainrot
    4. Professional
    Choice: 1

    You've chosen Basic mode.
    What severity would you like your insult to have?
    1. Mild
    2. Moderate
    3. Severe
    4. Brutal
    Choice: 2

    You've chosen a Basic, Moderate severity insult (level 2).
    Generating...

    Insult: "You're a dumb monkey and an excessively greasy gamer, and worst of all a stinking CS major!"
    (took 300 milliseconds)

    Would you like to insult again, or exit?
    1. Generate another insult
    2. Exit
    Choice: 2

    Goodbye, and CS Major Insult Generator is not liable for any programming-related sabotage resulting from your insults to a CS major!
*/