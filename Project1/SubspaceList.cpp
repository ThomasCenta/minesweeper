/**author: Thomas Centa

interface for the Board */

#include "SubspaceList.h"

using namespace std;

SubspaceList::SubspaceList(){
	//this one should never be called
}

SubspaceList::SubspaceList(int boardSize){
	//just instantiate the subspaceOrdering vector based on the size
	for (int i = 0; i < boardSize; i++){
		vector<Subspace*> addThis;
		subspaceOrdering.push_back(addThis);
	}
}

SubspaceList::~SubspaceList(){
	while(vectorOfSubspaces.size() > 0){
		vectorOfSubspaces.pop_back();
	}
}

void SubspaceList::addSubspace(int spot, Board* getTheSpotFrom){
	int mineCount = (*getTheSpotFrom).getElement(spot) - (*getTheSpotFrom).countMarked(spot);
	vector<int> mines = (*getTheSpotFrom).countUnknown(spot);
	Subspace* toBeAdded = new Subspace(mineCount, mines);
	vectorOfSubspaces.push_back(toBeAdded);
	for (int i = 0; i < mines.size(); i++){
		subspaceOrdering[mines[i]].push_back(toBeAdded);
	}

}

void SubspaceList::addSubspace(vector<int> spots, int mineCount){
	Subspace* toBeAdded = new Subspace(mineCount, spots);
	vectorOfSubspaces.push_back(toBeAdded);
	for (int i = 0; i < spots.size(); i++){
		subspaceOrdering[spots[i]].push_back(toBeAdded);
	}
}


void SubspaceList::removeElement(int spot, bool mineSpot){
	for (int i = 0; i < subspaceOrdering[spot].size(); i++){
		(*subspaceOrdering[spot][i]).remove(spot, mineSpot);
		(*subspaceOrdering[spot][i]).setChecked(false);
		(*subspaceOrdering[spot][i]).setCheckedForGuaranteedSolution(false);
		if ((*subspaceOrdering[spot][i]).size() == 0){
			//I'm not going to delete them here because I don't want to deal with nulls
			subspaceOrdering[spot].erase(subspaceOrdering[spot].begin() + i);
		}
	}
}

vector<int> SubspaceList::solutionsQuantity(vector<int> spots, vector<int> marked){
	//marked will keep track of the spots that are marked
	//let the last element in the vector be the number of solutions found
	vector<int> solutions (spots.size() + 1, 0);
	if (marked.size() >= spots.size()){
		solutions = marked;
		//add a 1 to indicate it found a solution
		marked.push_back(1);
	}
	else{
		bool addMine = true;
		bool addEmptySpace = true;
		for (int i = 0; i < subspaceOrdering[spots[marked.size()]].size(); i++){
			if ((*subspaceOrdering[spots[marked.size()]][i]).size() <= (*subspaceOrdering[spots[marked.size()]][i]).numberOfMines()){
				addEmptySpace = false;
			}
			if ((*subspaceOrdering[spots[marked.size()]][i]).numberOfMines() == 0){
				addMine = false;
			}
		}
		//add mine then empty space then do recursion
		if (addMine){
			marked.push_back(1);
			vector<int> solns = this->solutionsQuantity(spots, marked);
			for (int i = 0; i < solutions.size(); i++){
				solutions[i] = solutions[i] + solns[i];
			}
			marked.pop_back();
		}
		if (addEmptySpace){
			marked.push_back(0);
			vector<int> solns = this->solutionsQuantity(spots, marked);
			for (int i = 0; i < solutions.size(); i++){
				solutions[i] = solutions[i] + solns[i];
			}
			marked.pop_back();
		}
	}
	return solutions;
}

vector<int> SubspaceList::nearbySpots(Subspace* thisOne){
	vector<int> spots = (*thisOne).getSpots();
	//this first elements in the returned value will be spots
	vector<int> growingSpots = spots;
	int size = spots.size();
	for (int i = 0; i < size; i++){
		for (int j = 0; j < subspaceOrdering[spots[i]].size(); i++){
			Subspace* nearbySubspace = subspaceOrdering[spots[i]][j];
			vector<int> addSpots = (*nearbySubspace).getSpots();
			for (int k = 0; k < addSpots.size(); k++){
				bool alreadyHave = false;
				for (int l = 0; !alreadyHave && l < spots.size(); l++){
					if (spots[l] == addSpots[k]){
						alreadyHave = true;
					}
				}
				if (!alreadyHave){
					spots.push_back(addSpots[k]);
				}
			}
		}
	}
	return growingSpots;
}


void SubspaceList::calculateLocalSolutions(){
	for (int i = 0; i < subspaceOrdering.size(); i++){
		for (int j = 0; i < this->subspaceOrdering[i].size(); i++){
			if (!(*(this->subspaceOrdering[i][j])).hasBeenChecked()){
				(*(this->subspaceOrdering[i][j])).setChecked(true);
				vector<int> toCheckSpots = nearbySpots(subspaceOrdering[i][j]);
				vector<int> marked;
				vector<int> solutions = solutionsQuantity(toCheckSpots, marked);
				vector<int> subspaceSolutions;
				for (int i = 0; i < (*(this->subspaceOrdering[i][j])).size(); i++){
					subspaceSolutions.push_back(solutions[i]);
				}
				subspaceSolutions.push_back(solutions[solutions.size() - 1]);
				(*(this->subspaceOrdering[i][j])).setSolutions(subspaceSolutions);
			}
		}
	}
}


vector< vector<int> > SubspaceList::checkSolutions(){
	vector< vector<int> > toReturn;
	vector<int> add;
	vector<int> add2;
	toReturn.push_back(add);
	toReturn.push_back(add2);
	int i = 0;
	while (i < vectorOfSubspaces.size()){
		Subspace* next = vectorOfSubspaces[i];
		//subspace pointers could have been made NULL at other points in the code
		if ((*next).size() == 0){
			vectorOfSubspaces.erase(vectorOfSubspaces.begin() + i);
			delete next;
			continue;
		}
		if (!(*next).checkedForGuaranteedSolution()){
			vector< vector<int> > theseSolutions = (*next).findGuaranteedSolution();
			for (int j = 0; j < theseSolutions[1].size(); j++){
				bool alreadyFound = false;
				for (int k = 0; k < toReturn[1].size(); k++){
					if (theseSolutions[1][j] == toReturn[1][k]){
						alreadyFound = true;
					}
				}
				if (!alreadyFound){
					toReturn[0].push_back(theseSolutions[0][j]);
					toReturn[1].push_back(theseSolutions[1][j]);
				}
			}
		}
		i++;
	}
	return toReturn;
}

int SubspaceList::lowestProbability(){
	double toReturn[2] = { 1, -1 };
	int i = 0;
	while (i < vectorOfSubspaces.size()){
		Subspace* next = vectorOfSubspaces[i];
		//subspace pointers could have been made NULL at other points in the code
		if ((*next).size() == 0){
			vectorOfSubspaces.erase(vectorOfSubspaces.begin() + i);
			delete next;
			continue;
		}
		double * check = (*(vectorOfSubspaces[i])).lowestProbability();
		if (check[0] < toReturn[0]){
			toReturn[0] = check[0];
			toReturn[1] = check[1];
		}
		i++;
	}
	return toReturn[1];
}
