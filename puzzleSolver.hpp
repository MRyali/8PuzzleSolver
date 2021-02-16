//
//  puzzleSolver.hpp
//  MRyali_8PuzzleSolver
//
//  Created by Mayur Ryali on 2/8/21.
//

#ifndef puzzleSolver_hpp
#define puzzleSolver_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

// struct to represent each node (state)
struct SquareTile {
    // Each tile (1 parent) has 4 possible moves => 4 children
    SquareTile* parentNode;
    SquareTile* childNode1;
    SquareTile* childNode2;
    SquareTile* childNode3;
    SquareTile* childNode4;
    // heuristic val for each expansion
    int heuristicVal;
    // movement cost for each expansion
    int movementCost;
    // vector of int vectors that includes a puzzle states
    vector<vector<int>> eightPuzzle;
};

// This struct allows for the priority queue to reorder its elements depending on the values of h and g for each.
// f = g + h
// The best option in each expansion is the one with the lowest f
// Credit (Source 1): http://www.cplusplus.com/forum/general/115634/
// Credit (Source 2):  https://www.geeksforgeeks.org/stl-priority-queue-for-structure-or-class/
struct ReOrderElements {
    bool operator () (SquareTile* t1, SquareTile* t2) {
        if ((t1->movementCost + t1->heuristicVal) > (t2->movementCost + t2->heuristicVal)) { //f = g + h
           return true;
        }
        return false;
    }
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
        // priority queue to hold our states (parents and their children)
        priority_queue<SquareTile*, vector<SquareTile*>, ReOrderElements> que;

    public:
        // class constructor
        PuzzleSolver();
        // calculate the heuristic value depending on selected algorithm
        int heuristicVal(vector<vector<int>>);
        // make root node and set up intial puzzle
        void makeTreeRoot(int);
        // function to make a default puzzle
        vector<vector<int>> makeDefaultPuzzle();
        // function to make a custom puzzle
        vector<vector<int>> makeCustomPuzzle();
        // function to make a goal puzzleType
        vector<vector<int>> makeGoal();
        // function of possible moves
        void boardMoves(SquareTile*);
        // move down
        void swapDown (int, vector<vector<int>>&);
        // move up
        void swapUp (int, vector<vector<int>>&);
        // move left
        void swapLeft (int, vector<vector<int>>&);
        // move right
        void swapRight(int, vector<vector<int>>&);
        // create children nodes during each Expansion => 4 possible children for each parent state
        void makeChildren1(SquareTile*, vector<vector<int>>);
        void makeChildren2(SquareTile*, vector<vector<int>>);
        void makeChildren3(SquareTile*, vector<vector<int>>);
        void makeChildren4(SquareTile*, vector<vector<int>>);
        // function to check if a state is a repeat
        bool isNotRepeatState(vector<vector<int>>);
        // function to check if a state is the goal state
        bool checkGoal(vector<vector<int>>);
        // function will display the puzzle in a grid format with heuristic and movement cost values
        void printPuzzle(SquareTile*);
        // function that runs search algorithms
        void runAlgorithm(int a);
        // print function to test and find errors in code
        void printTest(SquareTile*, string);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexZero(SquareTile*);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexOne(SquareTile*);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexTwo(SquareTile*);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexThree(SquareTile*);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexFour(SquareTile*);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexFive(SquareTile*);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexSix(SquareTile*);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexSeven(SquareTile*);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexEight(SquareTile*);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexNine(SquareTile*);
        // function to make move if the missing is in index zero of 3x3 grid

        /* More Functions to come => Still need the following
            * Use the selected algorithm -------> Done
            * 4 possible movement => up, down, left, right -------> Done
            * Expansion of Node for children -------> Done
            * Make the puzzle tree root to allow for decision tree and its Expansion -------> Done
            * Calculation of number of nodes (max in queue and total) -------> Done
            * Expand the best state with lowest h(n) and g(n) values -------> Done
            * Repeat comparison -------> Done
            * Goal comparison -------> Done
            * Current state display -------> Done
            * Valid puzzle check (when user enters custom puzzle) -------> Done
            * etc. (may need more but this is it for now)
         */
};

#endif /* puzzleSolver_hpp */
