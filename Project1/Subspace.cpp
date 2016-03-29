/**author: Thomas Centa

interface for the Board */

#include "Subspace.h"


using namespace std;

Subspace::Subspace(){
	numMines = 0;
	checkedLocally = false; 
}

Subspace::Subspace(int mineCount, vector<int> spots){
	unknownSpots = spots;
	checkedLocally = false;
	numMines = mineCount;
	guaranteedSolution = false;

	//THIS WILL ONLY BE FOR FUTURE IMPLEMENTATIONS OF SUBSPACE
	//setSolutions(mineCount, marked, spots.size(), &possibleSolutions);

}

void Subspace::remove(int spot, bool mineSpot){
	for (int i = 0; i < unknownSpots.size(); i++){
		if (unknownSpots[i] == spot){
			unknownSpots.erase(unknownSpots.begin() + i);
			if (mineSpot){
				numMines--;
			}
			checkedLocally = false;
			guaranteedSolution = false;
		}
	}

}

/*
void Subspace::addUnknown(int spot, bool minespot){
	unknownSpots.push_back(spot);
	if (minespot){
		numMines++;
	}
}
*/


int Subspace::size(){
	return unknownSpots.size();
}

int Subspace::numberOfMines(){
	return numMines;
}

void Subspace::setChecked(bool value){
	checkedLocally = value;
}

bool Subspace::hasBeenChecked(){
	return checkedLocally;
}

bool Subspace::checkedForGuaranteedSolution(){
	return guaranteedSolution;
}

void Subspace::setCheckedForGuaranteedSolution(bool checked){
	guaranteedSolution = checked;
}

vector< vector<int> > Subspace::findGuaranteedSolution(){
	vector< vector<int> > guaranteedSpots;
	vector<int> add;
	vector<int> add2;
	guaranteedSpots.push_back(add);
	guaranteedSpots.push_back(add2);
	//if there are as many spots as mines, they must all be mines
	if (numMines == unknownSpots.size()){
		for (int i = 0; i < unknownSpots.size(); i++){
			guaranteedSpots[0].push_back(1);
			guaranteedSpots[1].push_back(unknownSpots[i]);
		}
	}
	//if there are no mines, all the spots must be empty
	else if (numMines == 0){
		for (int i = 0; i < unknownSpots.size(); i++){
			guaranteedSpots[0].push_back(0);
			guaranteedSpots[1].push_back(unknownSpots[i]);
		}
	}
	//I do not want to call this last one if no solutions have been found
	//if the a mine was found in all solutions or none, it is guaranteed to be filled or empty, respectively
	else if (this->solutions.size() > 0){
		for (int i = 0; i < solutions.size() - 1; i++){
			if (solutions[i] == 0){
				guaranteedSpots[0].push_back(0);
				guaranteedSpots[1].push_back(unknownSpots[i]);
			}
			else if (solutions[i] == solutions[solutions.size() - 1]){
				guaranteedSpots[0].push_back(1);
				guaranteedSpots[1].push_back(unknownSpots[i]);
			}
			
		}
	}
	return guaranteedSpots;

}

bool Subspace::contains(int spot){
	for (int i = 0; i < unknownSpots.size(); i++){
		if (unknownSpots[i] == spot){
			return true;
		}
	}
	return false;
}

vector<int> Subspace::getSpots(){
	return unknownSpots;
}

bool Subspace::equals(Subspace* thisOne){
	//im only going to check the unknownSpots, because if thats true, the others follow
	if ((*thisOne).size() != unknownSpots.size()){
		return false;
	}
	for (int i = 0; i < unknownSpots.size(); i++){
		if (!(*thisOne).contains(unknownSpots[i])){
			return false;
		}
	}
	return true;
}

void Subspace::setSolutions(vector<int> newSolutions){
	this->solutions = newSolutions;
}

double * Subspace::lowestProbability(){
	double toReturn[2] = { solutions[0], unknownSpots[0] };
	//go through and find the spot in the least number of solutions
	for (int i = 0; i < solutions.size() - 1; i++){
		if (solutions[i] < toReturn[0]){
			toReturn[0] = solutions[i];
			toReturn[1] = unknownSpots[i];
		}
	}
	toReturn[0] = toReturn[0] * 1.0 / solutions[solutions.size() - 1];
	return toReturn;
}

/*
void setSolutions(int mineCount, vector<int> marked, int numSpaces, queue< vector<int> >* buildingSolutions){
	if (mineCount == numSpaces){
		for (int i = 0; i < numSpaces; i++){
			(marked).push_back(1);
		}
		(*buildingSolutions).push(marked);
	}
	else if (mineCount == 0){
		for (int i = 0; i < numSpaces; i++){
			(marked).push_back(0);
		}
		(*buildingSolutions).push(marked);
	}
	else if (numSpaces == 0){
		(*buildingSolutions).push(marked);
	}
	else{
		for (int i = (marked).size(); i < numSpaces - mineCount; i++){
			(marked).push_back(1);
			setSolutions(mineCount - 1, marked, numSpaces - 1, buildingSolutions);
			(marked).pop_back();
			(marked).push_back(0);
			setSolutions(mineCount, marked, numSpaces, buildingSolutions);
			(marked).pop_back();
		}
	}
}
*/