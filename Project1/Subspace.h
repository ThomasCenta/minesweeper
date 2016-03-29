/**author: Thomas Centa

interface for the list of subspaces */

#ifndef SUBSPACE_H
#define SUBSPACE_H
#include <queue>
#include <vector>
#include "Board.h"

using namespace std;


class Subspace{
public:
	//default constructor. Just instantiates a vector for the subspace and sets numMines = 0 and checked = false
	//this constructor will probably never be called
	Subspace();
	//Constructor using a spot on a board
	Subspace(int mineCount, vector<int> spots);
	//removes spot from the subspace only if the spot is in the subspace. reduces numMines by 1 if it is mineSpot
	/*
		requires spot is in this subspace
	*/
	void remove(int spot, bool mineSpot);
	//I need a method to add an unknown so I can restore Subspaces
	//void addUnknown(int spot, bool minespot);
	//returns size of this subspace
	int size();
	//returns the number of mines in this subspace
	int numberOfMines();
	//sets checkedLocally
	void setChecked(bool value);
	//returns checkedLocally
	bool hasBeenChecked();
	//reports if there is a spot in subspace with 0% or 100% of having a mine based on the subspaces current known solutions.
	bool checkedForGuaranteedSolution();
	//this will search for a guaranteed solution in the subspace. There will be two vectors. the first vector will have 0 if it does not have a mine, and 1 if it does have a mine. 
	//The second position will contain the spot numbers relating to the numbers in the first vector
	vector< vector<int> > findGuaranteedSolution();
	//this will set the value of guaranteedSpot
	void setCheckedForGuaranteedSolution(bool checked);
	//reports if subspace contains a spot
	bool contains(int spot);
	//this will return the vector of unknown spots
	vector<int> getSpots();
	//returns true if the two subsets are the same subset
	bool equals(Subspace* thisOne);
	//this will be used to update the solutions
	void setSolutions(vector<int> solutions);
	//this will return the spot with lowest probability in this subspace. The first element in the array will be the probability and the second the spot number
	/*
		requires that at least one solution has been found for the subspace
	*/
	double * lowestProbability();
	
	


private:

	//this is the vector of the unknown squares in the subspace
	vector<int> unknownSpots;
	//this is the number of mines that are supposed to be in the subspace
	int numMines;
	//this is a boolean to mark whether or not a solution has been found using local subspaces
	bool checkedLocally;
	//this is a boolean to mark whether or not this subspace has been checked for a guaranteed solution
	bool guaranteedSolution;
	//this will store the frequency of the spots in solutions
	vector<int> solutions;
	

	//this will store the possible solutions. The ith spot in the vector corresponds to the ith spot in the vector unknownSpots
	//will be used in future implementations
	//queue<vector<int> > possibleSolutions;
	//this is a helper function to set the initial solutions of the subspaces
	//Will be used in future implementations
	//void setSolutions(int mineCount, vector<int> marked, int numSpaces, queue<vector<int>> *buildingSolutions);


};

#endif