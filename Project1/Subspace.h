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
	//default constructor. Just instantiates a vector for the subspace and sets numMines = 0 and checkedLocally = false
	Subspace();

	/*Constructor using a vector of spots and number of mines in the subspace
		sets unknownSpots to spots
		numMines to mineCount
		checkedLocally to false
		guaranteedSolution to false
	*/
	Subspace(int mineCount, vector<int> spots);

	/*removes spot from the subspace only if the spot is in the subspace. reduces numMines by 1 if it is mineSpot
		@param spot
			the spot to remove from this
		@param mineSpot
			true if the spot removed is a mine, alse otherwise
		@requires spot is in this
		@updates this
		@ensures #this = this * spot
			if mineSpot, numMines is reduced by 1
	*/
	void remove(int spot, bool mineSpot);

	/* returns the number of unknown spots in this
		@returns |unknownSpots|
	*/
	int size();

	//returns the number of mines in this subspace
	int numberOfMines();

	//sets checkedLocally
	void setChecked(bool value);

	//returns checkedLocally
	bool hasBeenChecked();

	//returns whether or not this subsapce has been checked for a guaranteed solution
	bool checkedForGuaranteedSolution();

	//this will search for a guaranteed solution in the subspace. There will be two vectors:
	//the first vector will have 0 if it does not have a mine, and 1 if it does have a mine. 
	//The second position will contain the spot numbers relating to the numbers in the first vector
	vector< vector<int> > findGuaranteedSolution();

	//this will set the value of guaranteedSpot to the input checked
	void setCheckedForGuaranteedSolution(bool checked);

	//reports if subspace contains the given spot
	bool contains(int spot);

	//this will return the vector of unknown spots
	vector<int> getSpots();

	//returns true if the two subsets are the same subset
	bool equals(Subspace* thisOne);

	//sets solutions of this to the given solutions
	void setSolutions(vector<int> solutions);

	//this will return the spot with lowest probability in this subspace. The first element in the array will be the probability and the second the spot number
	/*
		requires that at least one solution has been found for the subspace
	*/
	double * lowestProbability();
	
	


private:

	//this is the vector of the unknown squares in the subspace. Does not contain surrounding known spots
	vector<int> unknownSpots;

	//this is the number of mines that are supposed to be in the subspace
	int numMines;

	//this is a boolean to mark whether or not a solution has been found using local subspaces
	bool checkedLocally;

	//this is a boolean to mark whether or not this subspace has been checked for a guaranteed solution
	bool guaranteedSolution;

	//this will store the frequency of the spots in solutions
	//The last element in solutions is the total number of solutions found.
	//for all 0 <= i < |solutions| - 1, solutions[i] = number of solutions with a mine in unknownSpots[i]
	vector<int> solutions;
};

#endif