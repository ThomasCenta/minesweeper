/**author: Thomas Centa

interface for the list of subspaces */

#ifndef SUBSPACELIST_H
#define SUBSPACELIST_H
#include <vector>
#include "Subspace.h"

using namespace std;

class SubspaceList{

public:
	//default constructor. Instantiates list
	SubspaceList();
	//constructor with specified size
	SubspaceList(int boardSize);
	//destructor
	~SubspaceList();
	//this will add a subspace based on an element from the board
	void addSubspace(int spot, Board* getTheSpotFrom);
	//remove element. this will happen when a spot is marked as a mine or cleared
	void removeElement(int spot, bool mineSpot);
	//this will see if it can be determined whether or not a spot has to have a mine or not. There will be two vectors. the first vector will have 0 if it does not have a mine, and 1 if it does have a mine. 
	//The second position will contain the spot numbers relating to the numbers in the first vector
	vector< vector<int> > checkSolutions();
	//this will calculate solutions for all subspaces using subspaces around it.
	void calculateLocalSolutions();
	//this will return the spot with the lowest probability of having a mine, given the current subspace solutions
	int lowestProbability();
	//this will add subspaces using a vector of spots and a mineNumber
	void addSubspace(vector<int> spots, int mineCount);


private:

	//this will take in a vector of spots, find all solutions in that space, and return a vector containing the number of times a mine was placed in each space
	vector<int> solutionsQuantity(vector<int> spots, vector<int> marked);
	//this will take in a vector of spots, find all solutions in that space, and return a queue for all of the solutions found in that space
	queue< vector<int> > solutionsSpecific(vector<int> spots, vector<int> marked);
	//this will return the set of all adjacent spots to a subspace
	vector<int> nearbySpots(Subspace* thisOne);
	

	//this is a vector which has pointers to subspaces in each element if those subspaces contain the mine corresponding to that element
	vector< vector<Subspace*> > subspaceOrdering;
	//this will store the subspace pointers. makes deleting them easier
	vector < Subspace* > vectorOfSubspaces;

};

#endif