//
//  puzzleSolver.hpp
//  MRyali_8PuzzleSolver
//
//  Created by Mayur Ryali on 2/8/21.
//

#ifndef puzzleSolver_hpp
#define puzzleSolver_hpp

#include <stdio.h>
#include <vector>
#include <queue>
#include <list>
#include <cmath>

using namespace std;

struct SquareTile {
    // Each tile (1 parent) has 4 possible moves => 4 children
    SquareTile* parentNode;
    SquareTile* childNode1;
    SquareTile* childNode2;
    SquareTile* childNode3;
    SquareTile* childNode4;
    //heuristic val for each expansion
    int heuristicVal;
    // movement cost for each expansion
    int movementCost;
};

class PuzzleSolver {
    private:
				// Used to see what algorithm the user selects at the beginning
				int algorithmNum;
				// This is our root node (aka the initial state)
        SquareTile* root;
				// This is our goal node (aka the goal state)
        SquareTile* goal;
				// Used to count how many nodes we expand to reach our goal states for analysis
				int totalNodes;
				// Used to count the maximum number of nodes in our priority queue for analysis
				int maxNodes;
				// Used to check if the current state is the goal states
				bool isGoal;
				// This is a vector of the states already traversed states to avoid repeats
				vector<vector<vector<int>>> repeatStates;
				// This is a list containg the final solution path from initial state to goal state
				list<SquareTile*> solutionPath;
		public:
				int heuristicVal(vector<vector<int>>);

				/* More Functions to come => Still need the following
				 * USe the selected algorithm
				 * 4 possible movement => up, down, left, right
				 * Expansion of Node for children
				 * Make the puzzle tree root to allow for decision tree and its Expansion
				 * Calculation of number of nodes (max in queue and total)
				 * Repeat comparison
				 * Goal comparison
				 * Current state display
				 * Solution display
				 * Valid puzzle check (when user enters custom puzzle)
				 * etc. (may need more but this is it for now)
				*/

};

#endif /* puzzleSolver_hpp */
