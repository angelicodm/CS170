#ifndef ALGORHYTHM_H
#define ALGORHTYHM_H
#include <iostream>
#include <vector>
#include <queue>
#include <map>

using namespace std;

class slidePuzzle {
    private:
        vector<vector<string> > puzzle;
        int costToState; // g(n)
        int heuristic; // h(n) aka distance to goal state
        pair<int, int> zero; //this tracks the zero/blank space position with <row, column>
    public:
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

        vector<vector<string> > getNode() const //used to get current sequence of numbers
        {
            return this->puzzle;
        }
        
        int getG() const //used to get costToState or g(n) 
        {
            return this->costToState;
        }
        int getH() const //used to get heuristic or h(n)
        {
            return this->heuristic;
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
			
			return dPuzzle;
        }
        slidePuzzle goLeft(slidePuzzle lPuzzle) 
        {
			
			return lPuzzle;
        }
        slidePuzzle goRight(slidePuzzle rPuzzle) 
        {
			
			return rPuzzle;
        }

        void allCosts(const int &algorithm) 
        {
            this->costToState += 1;
            if (algorithm == 1) 
            {
                this->heuristic = 0;
            }
            else if(algorithm == 2) 
            {
                this->heuristic = manhattanDistanceCost();
            }
            else if(algorithm == 3)
            {
                this->heuristic = misplacedTileCost();
            }
        }

        
};

void expand(slidePuzzle currentNode, const int &algorithm) 
{
    
}

bool isGoal(const slidePuzzle &my_puzzle) 
{
	
}

#endif
