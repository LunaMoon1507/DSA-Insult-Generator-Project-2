# CS Major Insult Generator

## Overview

This project is a C++ application that generates randomized “insults” using words stored in multiple CSV datasets. It demonstrates the use and performance comparison of two data structures:
* Hash Table
* Red-Black Tree

Both structures store the same dataset and implement a shared interface (WordStructure) that allows interchangeable use for generating output.

## Features
Loads multiple CSV datasets containing words and metadata with the following classifications:

“Vibe”:
* Random
* Professional
* Brainrot

Supports severity levels:
* Mild
* Moderate
* Severe
* Brutal

## File Structure
```
src/
  main.cpp
  HashTable.cpp / HashTable.hpp
  Tree.cpp / Tree.hpp
  WordStructure.hpp
  Word.hpp

databases/
  wordnet-db-3.csv
  professional-db.csv
  explicit-db-cleaned.csv
  brainrot-db.csv
  CSmajor-database.csv
```

## Requirements
* C++17 or later
* CMake (if using CLion or command line build)
* Standard libraries:
```
<iostream>
<vector>
<fstream>
<sstream>
<chrono>
<random>
```

## How to Build

**Using CLion (Recommended)**
	1.	Open the project folder in CLion
	2.	Let CMake configure automatically
	3.	Click Build → Build Project

**Using Command Line (CMake)**
From the project root: 
```
mkdir build
cd build
cmake ..
make
```

## How to Run

**Important:**

The program expects CSV files to be located at:

```../databases/```

relative to the executable.

If running from build/, ensure:
```
project-root/
  build/
  databases/
```

Run the program: ./DSA_Insult_Generator_Project_2

## Authors
Kira Luna Nichtawitz (GitHub: LunaMoon1507), Ben Kindem (GitHub: bkindem), Vera Zheng (GitHub: verazh07)

## Disclaimer
This project is intended for educational purposes. Generated content is not meant to be taken seriously.
