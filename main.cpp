#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include "algorhythm.h"

using namespace std;

//Gets user's input for a custom puzzle
vector<string> customPuzzle(string &input) 
{
	//cin.ignore(256, ' '); could potentially work if properly implemented but becomes more complicated with bigger puzzles
    getline(cin, input);
    remove(input.begin(), input.end(), ' '); //seamlessly removes all whitespace from input
    vector<string> matrix;
    for (int i = 0; i < 3; i++) //maxRows acts as the number of rows/columns in an 8-puzzle and should be able to be adjusted for 15 and 24 puzzles
    {
        matrix.push_back(string(1, input.at(i)));
    }
    return matrix;
}

/* THE GENERAL SEARCH ALGORITHM
 * function general-search(problem, QUEUEING-FUNCTION)
 * nodes = MAKE-QUEUE(MAKE-NODE(problem.INITIAL-STATE))
 * loop do
 * if EMPTY(nodes) then return "failure"
 * 		node = REMOVE-FRONT(nodes)
 * if problem.GOAL-TEST(node.STATE)succeeds then return node
 * 		node = QUEUEING-FUNCTION(nodes, EXPAND(node, problem.OPERATORS))
 * end
*/

int main() 
{
    vector<vector<string> > numberSequence; //vector of vectors acting as rows and columns
    string input;
    bool validInput = false;
    
    while (!validInput) 
    {
        cout << "Enter 1 for default puzzle, 2 for custom puzzle: " << endl;
        cin >> input;
        if (input == "1") 
        {
            numberSequence = { {"1", "2", "0"},
                       {"4", "5", "3"},
                       {"7", "8", "6"} };
            validInput = true;
        }
        else if (input == "2") 
        {
            cin.ignore();
            cout << "Enter your puzzle, use zero to represent the blank/empty space." << endl;
            cout << "Please enter only valid 8-puzzles (there should only be 3 single-digit entries per row)." << endl;
            cout << "Hit Enter/Return after inputting sequence of numbers:" << endl;
            cout << "Enter the first row of numbers with a space in betweeen each number: " << endl;
            numberSequence.push_back(customPuzzle(input));
            cout << "Enter the second row of numbers with a space in betweeen each number: " << endl;
            numberSequence.push_back(customPuzzle(input));
            cout << "Enter the third row of numbers with a space in betweeen each number: " << endl;
            numberSequence.push_back(customPuzzle(input));
            
            validInput = true;
        }
        else 
        {
            cout << "Invalid input, please input '1' or '2' to begin." << endl;
        }
    }

    int algorithm; //this determines the queueing function from the psuedocode
    cout << "Select an algorithm by entering the associated number: (1) for Uniform Cost Search, " << endl;
    cout << "(2) for the Manhattan Distance Heuristic, or (3) for the Misplaced Tile Heuristic" << endl; //I changed these from the example to be in alphabetical order
    cin >> algorithm;
    
    //decide between making multiple if statements depending on selected algorithm or separate helper function

    slidePuzzle my_puzzle(numberSequence);
    priority_queue <slidePuzzle> nodes; //should sort each node
    map<string, bool> tracker; //used to record each iteration of puzzle to check for repeats
    nodes.push(my_puzzle); //creates the data structure of nodes
    
    int queueSize = nodes.size();
    int nodesExpanded = 0;
    
    while(!nodes.empty()) //enter loop and ask if nodes is empty
    {
        if (queueSize < nodes.size()) //updates queueSize
        {
            queueSize = nodes.size();
        }
        
        slidePuzzle currentNode = nodes.top();
        nodes.pop(); // pop off the head off nodes
        
        if (isGoal(currentNode)) //ask if its the goal state, if yes enter if statement and were done 
        {
            cout << "Solution found! " << endl;
            currentNode.printPuzzle();
            cout << "Solution depth was " << currentNode.costToState << endl;
            cout << "Number of nodes expanded: " << nodesExpanded << endl;
            cout << "Max queue size: " << queueSize << endl;
            
            return 0;
        }
        
        cout << "The best state to is expand with a g(n) = " << currentNode.costToState << " and h(n) = " << currentNode.heuristic << " is... " << endl;
        
        
        currentNode.printPuzzle();
        expand(currentNode, nodes, tracker, algorithm);// EXPAND function: creates children based off of currentNode and selected algorithm ;if not goal state, creates all of current nodes children
        nodesExpanded++; //updates nodesExpanded and returns to top of the loop
        
    }
    
    cout << "No solution could be found." << endl;
    cout << "Number of nodes expanded: " << nodesExpanded << endl;
    cout << "Max queue size: " << queueSize << endl;
    return 0;
}
