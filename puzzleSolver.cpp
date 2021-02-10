//
//  puzzleSolver.cpp
//  MRyali_8PuzzleSolver
//
//  Created by Mayur Ryali on 2/8/21.
//

#include "puzzleSolver.hpp"

// class construcotr initializes root to NULL
ProblemSolver::ProblemSolver() {
    root = NULL;
}

// makes the root node and initial tree for eventual solutionPath
// use of priority queue: https://www.geeksforgeeks.org/priority-queue-in-cpp-stl/
void PuzzleSolver::makeTreeRoot (int a) {
    // create a SquareTile object
    SquareTile* squareT = new SquareTile;
    //set all of the nodes to null to initialize tree
    squareT->parentNode = NULL;
    squareT->childNode1 = NULL;
    squareT->childNode2 = NULL;
    squareT->childNode3 = NULL;
    squareT->childNode4 = NULL;
    // set all values to zero to initialize
    squareT->heuristicVal = 0;
    squareT->movementCost = 0;
    //goal state is initalized to false since we are not at goal state yet
    isGoal = false;
    // total nodes expanded and max nodes in queue are both zero since we havent expanded yet
    totalNodes = 0;
    maxNodes = 0;

    if (a == 1) { // User chose to use deafult 8 puzzle
        squareT->eightPuzzle = makeDefaultPuzzle();
        root = squareT;
        // push the root node into our priority queue
        que.push(root);
        // store the puzzle to compare for repeats later
        repeatStates.push_back(root->eightPuzzle);
    }
    else if (a == 2) { // User chose to use custom 8 puzzle
        squareT->eightPuzzle = makeCustomPuzzle();
        root = squareT;
        // push the root node into our priority queue
        que.push(root);
        // store the puzzle to compare for repeats later
        repeatStates.push_back(root->eightPuzzle);
    }
    else { // invalid choice
        cout << "Invalid entry. Program Exited." << endl;
        return;
    }
}

// Val Calculation algorithm: https://www.geeksforgeeks.org/a-search-algorithm/
int PuzzleSolver::heuristicVal (vector<vector<int>> puzzle) {
    int heuristicVal = 0;

    vector<vector<int>> goalPuzzle makeGoal();

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
        heuristicVal = 0; // default heuristic is zero
    }
    return heuristicVal;
}

vector<vector<int>> PuzzleSolver::makeDefaultPuzzle() {
    vector<vector<int>> defaultPuzzle;

    // vectors for each row of the 2D puzzle
    vector<int> v1, v2, v3;

    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);

    v2.push_back(4);
    v2.push_back(0);
    v2.push_back(6);

    v3.push_back(7);
    v3.push_back(8);
    v3.push_back(5);

    // populate the goal puzzle
    defaultPuzzle.push_back(v1);
    defaultPuzzle.push_back(v2);
    defaultPuzzle.push_back(v3);

    return defaultPuzzle;
}

vector<vector<int>> PuzzleSolver::makeCustomPuzzle() {
    // contain user's input for rows
    int a, b, c;
    // vectors for each row of the 2D puzzle
    vector<int> v1, v2, v3;
    // vector for custom puzzleType
    vector<vector<int>> customPuzzle;

    cout << "Please enter row 1 of your puzzle using space in between number: " << endl;
    cin >> a >> b >> c;
    cout << endl;

    v1.push_back(a);
    v1.push_back(b);
    v1.push_back(c);

    cout << "Please enter row 2 of your puzzle using space in between number: " << endl;
    cin >> a >> b >> c;
    cout << endl;

    v2.push_back(a);
    v2.push_back(b);
    v2.push_back(c);

    cout << "Please enter row 3 of your puzzle using space in between number: " << endl;
    cin >> a >> b >> c;
    cout << endl;

    v3.push_back(a);
    v3.push_back(b);
    v3.push_back(c);

    customPuzzle.push_back(v1);
    customPuzzle.push_back(v2);
    customPuzzle.push_back(v3);

    return customPuzzle;
}

void PuzzleSolver::boardMoves(SquareTile* curr) {
    // location of zero in the puzzle
    int index = 0;

    vector<vector<int>> t1;
    vector<vector<int>> t2;
    vector<vector<int>> t3;
    vector<vector<int>> t4;

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        if (eightPuzzle.at(i).at(j) == 0) {
          index = (j + 1) + (3 * i);
        }
      }
    }

    if (index == 5) { // middle => 4 possible moves
        t1 = swapDown(index, curr->eightPuzzle);
        t2 = swapUp(index, curr->eightPuzzle);
        t3 = swapLeft(index, curr->eightPuzzle);
        t4 = swapRight(index, curr->eightPuzzle);

        makeChildren1(curr, t1);
        makeChildren2(curr, t2);
        makeChildren3(curr, t3);
        makeChildren4(curr, t4);

    }
    else if (index % 2 == 1) { //corners => 2 possible moves
        if (index == 1) {
            t1 = swapDown(index, curr->eightPuzzle);
            t2 = swapRight(index, curr->eightPuzzle);

            makeChildren1(curr, t1);
            makeChildren2(curr, t2);
        }
        else if (index == 3) {
            t1 = swapDown(index, curr->eightPuzzle);
            t2 = swapLeft(index, curr->eightPuzzle);

            makeChildren1(curr, t1);
            makeChildren2(curr, t2);
        }
        else if (index == 7) {
            t1 = swapUp(index, curr->eightPuzzle);
            t2 = swapRight(index, curr->eightPuzzle);

            makeChildren1(curr, t1);
            makeChildren2(curr, t2);
        }
        else if (index == 9) {
            t1 = swapUp(index, curr->eightPuzzle);
            t2 = swapLeft(index, curr->eightPuzzle);

            makeChildren1(curr, t1);
            makeChildren2(curr, t2);
        }
    }
    else if (index % 2 == 0) { // middle edge => 3 possible moves
        if (index == 2) {
            t1 = swapDown(index, curr->eightPuzzle);
            t2 = swapRight(index, curr->eightPuzzle);
            t3 = swapLeft(index, curr->eightPuzzle);

            makeChildren1(curr, t1);
            makeChildren2(curr, t2);
            makeChildren3(curr, t3);
        }
        else if (index == 4) {
            t1 = swapDown(index, curr->eightPuzzle);
            t2 = swapRight(index, curr->eightPuzzle);
            t3 = swapUp(index, curr->eightPuzzle);

            makeChildren1(curr, t1);
            makeChildren2(curr, t2);
            makeChildren3(curr, t3);
        }
        else if (index == 6) {
            t1 = swapDown(index, curr->eightPuzzle);
            t2 = swapUp(index, curr->eightPuzzle);
            t3 = swapLeft(index, curr->eightPuzzle);

            makeChildren1(curr, t1);
            makeChildren2(curr, t2);
            makeChildren3(curr, t3);
        }
        else if (index == 8) {
            t1 = swapRight(index, curr->eightPuzzle);
            t2 = swapUp(index, curr->eightPuzzle);
            t3 = swapLeft(index, curr->eightPuzzle);

            makeChildren1(curr, t1);
            makeChildren2(curr, t2);
            makeChildren3(curr, t3);
        }
    }
    else {
      cout << "No zero found. Error." << endl;
      return;
    }
}

// we have four possible moves for the puzzle => down, up, left, swapRight
// swap function for vector: https://www.geeksforgeeks.org/difference-between-stdswap-and-stdvectorswap/
vector<vector<int>> PuzzleSolver::swapDown(int index, vector<vector<int>> eightPuzzle) {
    vector<vector<int>> temp;
    temp = eightPuzzle;
    if (index == 1) {
        swap(temp.at(0).at(0), temp.at(1).at(0));
    }
    else if (index == 2) {
        swap(temp.at(0).at(1), temp.at(1).at(1));
    }
    else if (index == 3) {
        swap(temp.at(0).at(2), temp.at(1).at(2));
    }
    else if (index == 4) {
        swap(temp.at(1).at(0), temp.at(2).at(0));
    }
    else if (index == 5) {
        swap(temp.at(1).at(1), temp.at(2).at(1));
    }
    else if (index == 6) {
        swap(temp.at(1).at(2), temp.at(2).at(2));
    }
    return temp;
}


vector<vector<int>> PuzzleSolver::swapUp(int index, vector<vector<int>> eightPuzzle) {
    vector<vector<int>> temp;
    temp = eightPuzzle;
    if (index == 4) {
        swap(temp.at(1).at(0), temp.at(0).at(0));
    }
    else if (index == 5) {
        swap(temp.at(1).at(1), temp.at(0).at(1));
    }
    else if (index == 6) {
        swap(temp.at(1).at(2), temp.at(0).at(2));
    }
    else if (index == 7) {
        swap(temp.at(2).at(0), temp.at(1).at(0));
    }
    else if (index == 8) {
        swap(temp.at(2).at(1), temp.at(1).at(1));
    }
    else if (index == 9) {
        swap(temp.at(2).at(1), temp.at(1).at(2));
    }
    return temp;
}

vector<vector<int>> PuzzleSolver::swapLeft(int index, vector<vector<int>> eightPuzzle) {
    vector<vector<int>> temp;
    temp = eightPuzzle;
    if (index == 2) {
        swap(temp.at(0).at(1), temp.at(0).at(0));
    }
    if (index == 3) {
        swap(temp.at(0).at(2), temp.at(0).at(1));
    }
    else if (index == 5) {
        swap(temp.at(1).at(1), temp.at(1).at(0));
    }
    else if (index == 6) {
        swap(temp.at(1).at(2), temp.at(1).at(1));
    }
    else if (index == 8) {
        swap(temp.at(2).at(1), temp.at(2).at(0));
    }
    else if (index == 9) {
        swap(temp.at(2).at(2), temp.at(2).at(1));
    }
    return temp;
}

vector<vector<int>> PuzzleSolver::swapRight(int index, vector<vector<int>> eightPuzzle) {
    vector<vector<int>> temp;
    temp = eightPuzzle;
    if (index == 1) {
        swap(temp.at(0).at(0), temp.at(0).at(1));
    }
    if (index == 2) {
        swap(temp.at(0).at(1), temp.at(0).at(2));
    }
    else if (index == 4) {
        swap(temp.at(1).at(0), temp.at(1).at(1));
    }
    if (index == 5) {
        swap(temp.at(1).at(1), temp.at(1).at(2));
    }
    if (index == 7) {
        swap(temp.at(2).at(0), temp.at(2).at(1));
    }
    else if (index == 8) {
        swap(temp.at(2).at(1), temp.at(2).at(2));
    }
    return temp;
}

/* when we make each child in each expansion we need to check the following:
 * Was the goal already reached?
 * Is the child the goal?
 * is the child a duplicate?
 * If it is a no to all of the questions then we continue making children and asking the questions.
 */
void makeChildren1(SquareTile* curr, vector<vector<int>> vec) {
    // temp SquareTile
    SquareTile* temp = new SquareTile;

    // if goal state has already been found then we do nothing
    if (isGoal) {
        return;
    }
    // if goal is not reached check if state is a repeat and if child is the goal
    if (!isRepeatState(vec)) {
        // calculate heuristic and movement cost
        temp->eightPuzzle = vec;
        temp->heuristicVal = heuristicVal(vec);
        temp->movementCost = curr->movementCost + 1;

        // add to checked states
        repeatStates.push_back(vec);

        // expansion
        curr->childNode1 = temp;
        curr->childNode1->parentNode = curr;
        que.push(curr->childNode1);

        // calculate total nodes and max nodes in priority_queue
        totalNodes += 1;
        maxNodes = que.size();

        if (checkGoal(curr->eightPuzzle)) {
            isGoal = true;
            // set goal node as the child that is the goal state
            goal = curr->childNode1;
            // exit once we found the goal
            return;
        }

    }
    else { // repeat so we "delete" child
        curr->childNode1 = NULL;
    }
}

void makeChildren2(SquareTile* curr, vector<vector<int>> vec) {
    // temp SquareTile
    SquareTile* temp = new SquareTile;

    // if goal state has already been found then we do nothing
    if (isGoal) {
        return;
    }
    // if goal is not reached check if state is a repeat and if child is the goal
    if (!isRepeatState(vec)) {
        // calculate heuristic and movement cost
        temp->eightPuzzle = vec;
        temp->heuristicVal = heuristicVal(vec);
        temp->movementCost = curr->movementCost + 1;

        // add to checked states
        repeatStates.push_back(vec);

        // expansion
        curr->childNode2 = temp;
        curr->childNode2->parentNode = curr;
        que.push(curr->childNode2);

        // calculate total nodes and max nodes in priority_queue
        totalNodes += 1;
        maxNodes = que.size();

        if (checkGoal(curr->eightPuzzle)) {
            isGoal = true;
            // set goal node as the child that is the goal state
            goal = curr->childNode2;
            // exit once we found the goal
            return;
        }

    }
    else {
        curr->childNode2 = NULL;
    }
}

void makeChildren3(SquareTile* curr, vector<vector<int>> vec) {
    // temp SquareTile
    SquareTile* temp = new SquareTile;

    // if goal state has already been found then we do nothing
    if (isGoal) {
        return;
    }
    // if goal is not reached check if state is a repeat and if child is the goal
    if (!isRepeatState(vec)) {
        // calculate heuristic and movement cost
        temp->eightPuzzle = vec;
        temp->heuristicVal = heuristicVal(vec);
        temp->movementCost = curr->movementCost + 1;

        // add to checked states
        repeatStates.push_back(vec);

        // expansion
        curr->childNode3 = temp;
        curr->childNode3->parentNode = curr;
        que.push(curr->childNode3);

        // calculate total nodes and max nodes in priority_queue
        totalNodes += 1;
        maxNodes = que.size();

        if (checkGoal(curr->eightPuzzle)) {
            isGoal = true;
            // set goal node as the child that is the goal state
            goal = curr->childNode3;
            // exit once we found the goal
            return;
        }

    }
    else {
        curr->childNode3 = NULL;
    }
}

void makeChildren4(SquareTile* curr, vector<vector<int>> vec) {
    // temp SquareTile
    SquareTile* temp = new SquareTile;

    // if goal state has already been found then we do nothing
    if (isGoal) {
        return;
    }
    // if goal is not reached check if state is a repeat and if child is the goal
    if (!isRepeatState(vec)) {
        // calculate heuristic and movement cost
        temp->eightPuzzle = vec;
        temp->heuristicVal = heuristicVal(vec);
        temp->movementCost = curr->movementCost + 1;

        // add to checked states
        repeatStates.push_back(vec);

        // expansion
        curr->childNode4 = temp;
        curr->childNode4->parentNode = curr;
        que.push(curr->childNode4);

        // calculate total nodes and max nodes in priority_queue
        totalNodes += 1;
        maxNodes = que.size();

        if (checkGoal(curr->eightPuzzle)) {
            isGoal = true;
            // set goal node as the child that is the goal state
            goal = curr->childNode4;
            // exit once we found the goal
            return;
        }

    }
    else {
        curr->childNode4 = NULL;
    }
}

// checks if a puzzle is the goal puzzle
bool checkGoal(vector<vector<int>> eightPuzzle) {
    vector<vector<int>> goalTemp = makeGoal();

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (eightPuzzle.at(i).at(j) != goalTemp.at(i).at(j)) {
                return false;
            }
        }
    }
    return true;
}

// checks if this state has already been traversed through
bool isRepeatState(vector<vector<int>> eightPuzzle) {
    for (int i = 0; i < repeatStates.size(); i++) {
        if (repeatStates.at(i) == eightPuzzle) {
            return false;
        }
    }
    return true;
}

vector<vector<int>> makeGoal() {
    vector<vector<int>> goalPuzzle;

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

    return goalPuzzle;
}
