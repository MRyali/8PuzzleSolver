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

using namespace std;

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
        // priority queue to hold our states
        priority_queue<SquareTile*> que;

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
        // create children nodes during each Expansion
        void makeChildren1(SquareTile*, vector<vector<int>>);
        void makeChildren2(SquareTile*, vector<vector<int>>);
        void makeChildren3(SquareTile*, vector<vector<int>>);
        void makeChildren4(SquareTile*, vector<vector<int>>);
        // function to check if a state is a repeat
        bool isNotRepeatState(vector<vector<int>>);
        // function to check if a state is the goalTemp
        bool checkGoal(vector<vector<int>>);
        // function will display the puzzle in a grid format
        void printPuzzle(SquareTile*);
        // function that runs search algorithms
        void runAlgorithm(int a);
        // print function to test and fiind seg fault
        void printTest(SquareTile*, string);
        // function to make move if the missing is in index zero of 3x3 grid
        void IndexZero(SquareTile*);
        // function to make move if the missing is in index one of 3x3 grid
        void IndexOne(SquareTile*);
        // function to make move if the missing is in index two of 3x3 grid
        void IndexTwo(SquareTile*);
        // function to make move if the missing is in index three of 3x3 grid
        void IndexThree(SquareTile*);
        // function to make move if the missing is in index four of 3x3 grid
        void IndexFour(SquareTile*);
        // function to make move if the missing is in index five of 3x3 grid
        void IndexFive(SquareTile*);
        // function to make move if the missing is in index six of 3x3 grid
        void IndexSix(SquareTile*);
        // function to make move if the missing is in index seven of 3x3 grid
        void IndexSeven(SquareTile*);
        // function to make move if the missing is in index eight of 3x3 grid
        void IndexEight(SquareTile*);








        /* More Functions to come => Still need the following
            * Use the selected algorithm -------> Done
            * 4 possible movement => up, down, left, right -------> Done
            * Expansion of Node for children -------> Done
            * Make the puzzle tree root to allow for decision tree and its Expansion -------> Done
            * Calculation of number of nodes (max in queue and total) -------> Done
            * Repeat comparison -------> Done
            * Goal comparison -------> Done
            * Current state display -------> Done
            * Valid puzzle check (when user enters custom puzzle) -------> Done
            * etc. (may need more but this is it for now)
         */

         /**********************************************

         Need to figure out how to reorder the priority queue so that the best move
         from each expansion will be selected and not all possible nodes.

         ************************************************/

};

#endif /* puzzleSolver_hpp */
