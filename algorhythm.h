#ifndef ALGORHYTHM_H
#define ALGORHTYHM_H
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class slidePuzzle {
    
    public:
		vector<vector<string> > puzzle;
        int costToState; // g(n)
        int heuristic; // h(n) aka distance to goal state
        pair<int, int> zero; //this tracks the zero/blank space position with <row, column>
        slidePuzzle() //default constructor
        {
            costToState = 0; 
            heuristic = 0; 
            zero.first = 0;
            zero.second = 0;
        }

        slidePuzzle(vector<vector<string> > cPuzzle) //custom puzzle from input
        {
            puzzle = cPuzzle;
            costToState = 0;
            heuristic = 0;
            zero = findZero();
        }

        void printPuzzle() 
        {
            for (int i = 0; i < puzzle.size(); i++) //enter row first
            {
                for (int j = 0; j < puzzle.at(i).size(); j++) //then print "columns"
                {
                    cout << puzzle.at(i).at(j) << " ";
                }
                
                cout << endl;
            }
        }

        //the simpler algorithm to calculate cost as we only check whether each individual tile is correct or not
        int misplacedTileCost() 
        {
            int mtCost = 0;
            vector<int> numberSequence;
            for (int i = 0; i < puzzle.size(); ++i) //these nested for loops convert the puzzle into integers for comparison
            {
                for (int j = 0; j < puzzle.at(i).size(); ++j) 
                {
                    numberSequence.push_back(stoi(puzzle.at(i).at(j)));
                }
            }
            for (int i = 0; i < numberSequence.size() - 1; ++i) //this for loop checks whether each entry from numberSequence is in the correct position
            {
                if (numberSequence.at(i) != i + 1) //if current number DNE to correct number for its tile, add to h(n)
                {
                    mtCost++;
                }
            }
            if (numberSequence.at(numberSequence.size() - 1) != 0) //unique case separate from above for loop in that the last tile should be 0
            {
                mtCost++;
            }
            return mtCost;
        }

		//the more complex algorithm to calculate cost
        int manhattanDistanceCost() 
        {
            int currentNum = 1; //compare values in puzzle to this beginning with 1 and so on
            int mdCost = 0;
            int lastPos = puzzle.size() - 1; //used to compare to 0;
            string stringNum;
            
            for(int i = 0; i < puzzle.size(); i++) // iterates through the 'rows'
            {
				for(int j = 0; j < puzzle.size(); j++) //iterates through columns
				{
					stringNum = to_string(currentNum);
					if(puzzle.at(i).at(j) != stringNum) //if the two values don't match then we need to find where it should go/how it should move
					{
						for(int x = 0; x < puzzle.size(); x++)//iterates through rows again
						{
							for(int y = 0; y < puzzle.size(); y++) //iterates through columns
							{
								if(stringNum == puzzle.at(x).at(y)) //at currentNum's position
								{
									mdCost += abs(i - x) + abs(j - y); //in order to find cost of distance, subtract where it should be by where it currently is
									//manhattan distance considers cost of every misplaced tile, which is why it is necessary to add them all together
								}
							}
						}
					}
					
					currentNum++;
				}
			}
			
			//finding the cost for zero is different as it needs to be in the last position for both the row and column
			if(puzzle.at(lastPos).at(lastPos) != "0") //check last position for row and column as thats where it should be
			{
				for(int i = 0; i < puzzle.size(); i++) //iterate through rows
				{
					for(int j = 0; j < puzzle.size(); j++) //iterate through columns
					{
						mdCost += abs(lastPos - i) + abs(lastPos - j);
					}
				}
			}
			
			return mdCost;
		}

        
        pair<int, int> findZero() //used to find position of zero/blank space in matrix
        {
            for (int i = 0; i < puzzle.size(); ++i) 
            {
                for(int j = 0; j < puzzle.at(i).size(); ++j) 
                {
                    if (puzzle.at(i).at(j) == "0") 
                    {
                        pair<int, int> zPosition(i, j);
                        return zPosition;
                    }
                }
            }
        }
        
        slidePuzzle goUp(slidePuzzle uPuzzle) 
        {
			if(uPuzzle.zero.first != 0) //makes sure that zero is not already in top row
            {
                string temp = uPuzzle.puzzle.at(uPuzzle.zero.first - 1).at(uPuzzle.zero.second); //creates a temp for value directly above zero
                uPuzzle.puzzle.at(uPuzzle.zero.first - 1).at(uPuzzle.zero.second) = "0"; //moves 0 up
                uPuzzle.puzzle.at(uPuzzle.zero.first).at(uPuzzle.zero.second) = temp; //moves temp value down
                uPuzzle.zero.first = uPuzzle.zero.first - 1; //updates the recorded position of zero
            }
            
            return uPuzzle;

        }

        slidePuzzle goDown(slidePuzzle dPuzzle) 
        {
			if(dPuzzle.zero.first != dPuzzle.puzzle.size() - 1) //makes sure that zero is not already in the bottom row// NOTE: could be set to 3 but having it as this allows for easier adjustment for bigger puzzles
			{
				string temp = dPuzzle.puzzle.at(dPuzzle.zero.first + 1).at(dPuzzle.zero.second); //creates temp value for value directly BELOW zero
				dPuzzle.puzzle.at(dPuzzle.zero.first + 1).at(dPuzzle.zero.second) = "0"; //moves zero down
				dPuzzle.puzzle.at(dPuzzle.zero.first).at(dPuzzle.zero.second) = temp; //moves temp to where zero was (up)
				dPuzzle.zero.first = dPuzzle.zero.first + 1; //updates the current position of zero
			}
			
			return dPuzzle;
        }
        
        slidePuzzle goLeft(slidePuzzle lPuzzle) 
        {
			if (lPuzzle.zero.second != 0) //makes sure that zero is not already in the leftmost position
            {
                string temp = lPuzzle.puzzle.at(lPuzzle.zero.first).at(lPuzzle.zero.second - 1); //creates temp of value to left of zero
                lPuzzle.puzzle.at(lPuzzle.zero.first).at(lPuzzle.zero.second - 1) = "0"; //moves zero to left
                lPuzzle.puzzle.at(lPuzzle.zero.first).at(lPuzzle.zero.second) = temp; //moves temp to zero's previous position
                lPuzzle.zero.second = lPuzzle.zero.second - 1; //updates current position of zero
            }

			
			return lPuzzle;
        }
        
        slidePuzzle goRight(slidePuzzle rPuzzle) 
        {
			if(rPuzzle.zero.second != rPuzzle.puzzle.size() - 1) //makes sure that zero is not in rightmost position
			{
				string temp = rPuzzle.puzzle.at(rPuzzle.zero.first).at(rPuzzle.zero.second + 1); //creates temp of value to right of zero
				rPuzzle.puzzle.at(rPuzzle.zero.first).at(rPuzzle.zero.second + 1) = "0"; //moves zero to right
				rPuzzle.puzzle.at(rPuzzle.zero.first).at(rPuzzle.zero.second) = temp; //moces temp to zero's previous position
				rPuzzle.zero.second = rPuzzle.zero.second + 1; //updates current position of zero
			}
			
			return rPuzzle;
        }


        void allCosts(const int &algorithm) 
        {
            this->costToState += 1;
            if (algorithm == 1) 
            {
                this->heuristic = 0;
            }
            else if (algorithm == 2) 
            {
                this->heuristic = manhattanDistanceCost();
            }
            else if(algorithm == 3)
            {
                this->heuristic = misplacedTileCost();
            }
        }

        //needed for priority_queue to work 
        bool operator<(const slidePuzzle &lhs) const 
        {
            return !((this->costToState + this->heuristic) < (lhs.costToState + lhs.heuristic)); //prioritizes lowest overall cost [f(n)]
        }
};

string conversion(vector<vector<string>> currentNode) //turns the entire number sequence into a large single string
{
    string nodeString;
    for (int i = 0; i < currentNode.size(); ++i) {
        for (int j = 0; j < currentNode.at(i).size(); ++j) {
            nodeString.append(currentNode.at(i).at(j));
        }
    }
    return nodeString;
}

void puzzleTracker(map<string, bool> &tracker, slidePuzzle currentNode) //records each number sequence that is encountered/expanded to avoid repeat states
{
	string nodeString = conversion(currentNode.puzzle);
	tracker[nodeString] = true;
}

void expand(slidePuzzle currentNode, priority_queue<slidePuzzle> &nodes, map<string, bool> &tracker, const int &algorithm) 
{
    slidePuzzle puzzleU = currentNode.goUp(currentNode);
    slidePuzzle puzzleD = currentNode.goDown(currentNode);
    slidePuzzle puzzleL = currentNode.goLeft(currentNode);
    slidePuzzle puzzleR = currentNode.goRight(currentNode);
    
    string stringU = conversion(puzzleU.puzzle); //converts number sequence into a single readable string 
    string stringD = conversion(puzzleD.puzzle);
    string stringL = conversion(puzzleL.puzzle);
    string stringR = conversion(puzzleR.puzzle);

    puzzleTracker(tracker, currentNode); //records current number sequence
    
    if (tracker[stringU] == false) //if false then this is a new state
    {
        puzzleU.allCosts(algorithm); //updates cost for specific node
        nodes.push(puzzleU); //adds specific node to the queue
    }
    if (tracker[stringD] == false) //if false then this is a new state
    {
        puzzleD.allCosts(algorithm); //updates cost for specific node
        nodes.push(puzzleD); //adds specific node to the queue
    }
    if (tracker[stringL] == false) //if false then this is a new state
    {
        puzzleL.allCosts(algorithm); //updates cost for specific node
        nodes.push(puzzleL); //adds specific node to the queue
    }
    if (tracker[stringR] == false) //if false then this is a new state
    {
        puzzleR.allCosts(algorithm); //updates cost for specific node
        nodes.push(puzzleR); //adds specific node to the queue
    }
}

bool isGoal(const slidePuzzle &currentNode) 
{
	bool result = false;
    string goal = "123456780";
    string nodeString = conversion(currentNode.puzzle);
    if (goal == nodeString) 
    {
        result = true;
    }
    return result;
}

#endif
