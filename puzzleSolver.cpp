//
//  puzzleSolver.cpp
//  MRyali_8PuzzleSolver
//
//  Created by Mayur Ryali on 2/8/21.
//

#include "puzzleSolver.hpp"

// Val Calculation algorithm: https://www.geeksforgeeks.org/a-search-algorithm/
int heuristicVal (vector<vector<int>> puzzle) {
    int heuristicVal = 0;
    
    vector<vector<int>> goalPuzzle;
    
    /*If you have an array then sizeof(array) returns the number of bytes the array
     * occupies.Since each element can take more than 1 byte of space, you have to
     * divide the result with the size of one element (sizeof(array[0])). This
     * gives you number of elements in the array
     */
    
    // vectors for each row of the 2D puzzle
    vector<int> v1, v2, v3;
    
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    
    v2.push_back(4);
    v2.push_back(5);
    v2.push_back(6);
    
    v3.push_back(7);
    v3.push_back(8);
    v3.push_back(0);
    
    // populate the goal puzzle
    goalPuzzle.push_back(v1);
    goalPuzzle.push_back(v2);
    goalPuzzle.push_back(v3);
    
    // Uniform Cost Search (BFS) where heuristic is zero
    if (algorithmNum == 1) {
        heuristicVal = 0;
    }
    // A* with Misplaced Tile Heuristic where heuristic is number of misplaced tiles
    else if (algorithmNum == 2) {
        for (int i = 0; i < 3; i++) { //rows
            for (int j = 0; j < 3; j++) { //colums
                if (puzzle.at(i).at(j) != goalPuzzle.at(i).at(j)) {
                    heuristicVal++; // number of misplaced tiles
                }
            }
        }
    }
    // A* with Manhattan Distance Heuristic"
    else if (algorithmNum == 3) {
        for (int i = 0; i < 3; i++) { //rows of current
            for (int j = 0; j < 3; j++) { //colums of current
                for (int k = 0; k < 3; k++) { //rows of goal
                    for (int l = 0; l < 3; l++) { //colums of goal
                        if (puzzle.at(i).at(j) == goalPuzzle.at(k).at(l)) { // abs (current_cell.x – goal.x) + abs (current_cell.y – goal.y)
                            heuristicVal += abs(i - k) + abs(j-l);
                        }
                    }
                }
            }
        }
    }
    else {
        heuristicVal = 0;
    }
    return heuristicVal;
}
