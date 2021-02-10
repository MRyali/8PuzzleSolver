//
//  main.cpp
//  MRyali_8PuzzleSolver
//
//  Created by Mayur Ryali on 2/6/21.
//

#include "puzzleSolver.hpp"

#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {

    int puzzleType = 0; //input for custom puzzle or default
    int algorithmNum = 0; //input for desired algorithm

    PuzzleSolver t1;

    cout << "My name is Mayur Ryali and this is my solver for the 8 puzzle." << endl << endl;

    cout << "Choose if you want to use a default puzzle or your own (1 or 2): " << endl;
    cin >> puzzleType;
    cout << endl;

    // make initial puzzle
    t1.makeTreeRoot(puzzleType);

    cout << "Choose one of the following algorithms (1-3): " << endl;
    cout << "1) Uniform Cost Search" << endl;
    cout << "2) A* with Misplaced Tile Heuristic" << endl;
    cout << "3) A* with Manhattan Distance Heuristic" << endl;

    cin >> algorithmNum;

    t1.runAlgorithm(algorithmNum);

    cout << endl;

    return 0;
}
