/**author: Thomas Centa

interface for the Board */

#include "Board.h"
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

Board::Board(){
	//number of mines is same as in expert mode: 99
	numMines = 99;
	//create a sorted array, then randomize to determine position of mines
	vector<int> rvector(480,0);
	for (int i = 0; i < 480; i++){
		rvector[i] = i;
		mineVector.push_back(0);
	}
	//delete elements around 254, the starting position	
	rvector.erase(rvector.begin() + 283, rvector.begin() + 286);
	rvector.erase(rvector.begin() + 253, rvector.begin() + 256);
	rvector.erase(rvector.begin() + 223, rvector.begin() + 226);

	//randomize!
	random_shuffle(rvector.begin(), rvector.end());
	for (int i = 0; i < 99; i++){
		int boardSpot = rvector[i];
		mineVector[boardSpot] = -2;
		// now adjust mine values around added mine.
		//start with the corners
		if (boardSpot == 0){
			if (mineVector[boardSpot + 1] != -2){
				mineVector[boardSpot + 1] += 1;
			}
			if (mineVector[boardSpot + 30] != -2){
				mineVector[boardSpot + 30] += 1;
			}
			if (mineVector[boardSpot + 31] != -2){
				mineVector[boardSpot + 31] += 1;
			}
		}
		else if (boardSpot == 29){
			if (mineVector[boardSpot - 1] != -2){
				mineVector[boardSpot - 1] += 1;
			}
			if (mineVector[boardSpot + 30] != -2){
				mineVector[boardSpot + 30] += 1;
			}
			if (mineVector[boardSpot + 29] != -2){
				mineVector[boardSpot + 29] += 1;
			}
		}
		else if (boardSpot == 450){
			if (mineVector[boardSpot - 30] != -2){
				mineVector[boardSpot - 30] += 1;
			}
			if (mineVector[boardSpot + 1] != -2){
				mineVector[boardSpot + 1] += 1;
			}
			if (mineVector[boardSpot - 29] != -2){
				mineVector[boardSpot - 29] += 1;
			}
		}
		else if (boardSpot == 479){
			if (mineVector[boardSpot - 30] != -2){
				mineVector[boardSpot - 30] += 1;
			}
			if (mineVector[boardSpot - 1] != -2){
				mineVector[boardSpot - 1] += 1;
			}
			if (mineVector[boardSpot - 31] != -2){
				mineVector[boardSpot - 31] += 1;
			}
		}
		// now do the same with the sides. starting with the left side
		else if (boardSpot % 30 == 0){
			vector<int> mods;
			mods.push_back(-30);
			mods.push_back(-29);
			mods.push_back(1);
			mods.push_back(30);
			mods.push_back(31);
			for (int i = 0; i < mods.size(); i++){
				if (mineVector[boardSpot + mods[i]] != -2){
					mineVector[boardSpot + mods[i]] += 1;
				}
			}
		}
		//top side
		else if (boardSpot < 30){
			vector<int> mods;
			mods.push_back(-1);
			mods.push_back(29);
			mods.push_back(1);
			mods.push_back(30);
			mods.push_back(31);
			for (int i = 0; i < mods.size(); i++){
				if (mineVector[boardSpot + mods[i]] != -2){
					mineVector[boardSpot + mods[i]] += 1;
				}
			}
		}
		//right side
		else if (boardSpot % 30 == 29){
			vector<int> mods;
			mods.push_back(-31);
			mods.push_back(-30);
			mods.push_back(-1);
			mods.push_back(30);
			mods.push_back(29);
			for (int i = 0; i < mods.size(); i++){
				if (mineVector[boardSpot + mods[i]] != -2){
					mineVector[boardSpot + mods[i]] += 1;
				}
			}
		}
		//bottom side
		else if (boardSpot > 449){
			vector<int> mods;
			mods.push_back(-29);
			mods.push_back(-30);
			mods.push_back(-31);
			mods.push_back(1);
			mods.push_back(-1);
			for (int i = 0; i < mods.size(); i++){
				if (mineVector[boardSpot + mods[i]] != -2){
					mineVector[boardSpot + mods[i]] += 1;
				}
			}
		}
		//now for the middle pieces
		else{
			vector<int> mods;
			mods.push_back(-29);
			mods.push_back(-30);
			mods.push_back(-31);
			mods.push_back(1);
			mods.push_back(-1);
			mods.push_back(29);
			mods.push_back(30);
			mods.push_back(31);
			for (int i = 0; i < mods.size(); i++){
				if (mineVector[boardSpot + mods[i]] != -2){
					mineVector[boardSpot + mods[i]] += 1;
				}
			}
		}
	}
	//that completes the set up of the board
}

Board::Board(bool cover){
	//numMines is still 99
	numMines = 99;
	//simply returns a board of -1's (covered)
	for (int i = 0; i < 480; i++){
		if (i != 254){
			mineVector.push_back(-1);

		}
		else{
			//leave the center space a 0
			mineVector.push_back(0);
		}
	}
}

void Board::changeElement(const int e, const int n){
	mineVector[e] = n;
}

int Board::getElement(const int e){
	return mineVector[e];
}

int Board::getMines(){
	return numMines;
}

void Board::reduceMines(){
	numMines = numMines - 1;
}

vector<int> Board::countUnknown(const int boardSpot){
	vector<int> count;
	if (boardSpot == 0){
		if (mineVector[boardSpot + 1] == -1){
			count.push_back(boardSpot + 1);
		}
		if (mineVector[boardSpot + 30] == -1){
			count.push_back(boardSpot + 30);
		}
		if (mineVector[boardSpot + 31] == -1){
			count.push_back(boardSpot + 31);
		}
	}
	else if (boardSpot == 29){
		if (mineVector[boardSpot - 1] == -1){
			count.push_back(boardSpot - 1);
		}
		if (mineVector[boardSpot + 30] == -1){
			count.push_back(boardSpot + 30);
		}
		if (mineVector[boardSpot + 29] == -1){
			count.push_back(boardSpot + 29);
		}
	}
	else if (boardSpot == 450){
		if (mineVector[boardSpot - 30] == -1){
			count.push_back(boardSpot - 30);
		}
		if (mineVector[boardSpot + 1] == -1){
			count.push_back(boardSpot + 1);
		}
		if (mineVector[boardSpot - 29] == -1){
			count.push_back(boardSpot - 29);
		}
	}
	else if (boardSpot == 479){
		if (mineVector[boardSpot - 30] == -1){
			count.push_back(boardSpot - 30);
		}
		if (mineVector[boardSpot - 1] == -1){
			count.push_back(boardSpot - 1);
		}
		if (mineVector[boardSpot - 31] == -1){
			count.push_back(boardSpot - 31);
		}
	}
	// now do the same with the sides. starting with the left side
	else if (boardSpot % 30 == 0){
		vector<int> mods;
		mods.push_back(-30);
		mods.push_back(-29);
		mods.push_back(1);
		mods.push_back(30);
		mods.push_back(31);
		for (int i = 0; i < mods.size(); i++){
			if (mineVector[boardSpot + mods[i]] == -1){
				count.push_back(boardSpot + mods[i]);
			}
		}
	}
	//top side
	else if (boardSpot < 30){
		vector<int> mods;
		mods.push_back(-1);
		mods.push_back(29);
		mods.push_back(1);
		mods.push_back(30);
		mods.push_back(31);
		for (int i = 0; i < mods.size(); i++){
			if (mineVector[boardSpot + mods[i]] == -1){
				count.push_back(boardSpot + mods[i]);
			}
		}
	}
	//right side
	else if (boardSpot % 30 == 29){
		vector<int> mods;
		mods.push_back(-31);
		mods.push_back(-30);
		mods.push_back(-1);
		mods.push_back(30);
		mods.push_back(29);
		for (int i = 0; i < mods.size(); i++){
			if (mineVector[boardSpot + mods[i]] == -1){
				count.push_back(boardSpot + mods[i]);
			}
		}
	}
	//bottom side
	else if (boardSpot > 449){
		vector<int> mods;
		mods.push_back(-29);
		mods.push_back(-30);
		mods.push_back(-31);
		mods.push_back(1);
		mods.push_back(-1);
		for (int i = 0; i < mods.size(); i++){
			if (mineVector[boardSpot + mods[i]] == -1){
				count.push_back(boardSpot + mods[i]);
			}
		}
	}
	//now for the middle pieces
	else{
		vector<int> mods;
		mods.push_back(-29);
		mods.push_back(-30);
		mods.push_back(-31);
		mods.push_back(1);
		mods.push_back(-1);
		mods.push_back(29);
		mods.push_back(30);
		mods.push_back(31);
		for (int i = 0; i < mods.size(); i++){
			if (mineVector[boardSpot + mods[i]] == -1){
				count.push_back(boardSpot + mods[i]);
			}
		}
	}
	return count;
}

int Board::countMarked(const int boardSpot){
	int count = 0;
	if (boardSpot == 0){
		if (mineVector[boardSpot + 1] == -2){
			count += 1;
		}
		if (mineVector[boardSpot + 30] == -2){
			count += 1;
		}
		if (mineVector[boardSpot + 31] == -2){
			count += 1;
		}
	}
	else if (boardSpot == 29){
		if (mineVector[boardSpot - 1] == -2){
			count += 1;
		}
		if (mineVector[boardSpot + 30] == -2){
			count += 1;
		}
		if (mineVector[boardSpot + 29] == -2){
			count += 1;
		}
	}
	else if (boardSpot == 450){
		if (mineVector[boardSpot - 30] == -2){
			count += 1;
		}
		if (mineVector[boardSpot + 1] == -2){
			count += 1;
		}
		if (mineVector[boardSpot - 29] == -2){
			count += 1;
		}
	}
	else if (boardSpot == 479){
		if (mineVector[boardSpot - 30] == -2){
			count += 1;
		}
		if (mineVector[boardSpot - 1] == -2){
			count += 1;
		}
		if (mineVector[boardSpot - 31] == -2){
			count += 1;
		}
	}
	// now do the same with the sides. starting with the left side
	else if (boardSpot % 30 == 0){
		vector<int> mods;
		mods.push_back(-30);
		mods.push_back(-29);
		mods.push_back(1);
		mods.push_back(30);
		mods.push_back(31);
		for (int i = 0; i < mods.size(); i++){
			if (mineVector[boardSpot + mods[i]] == -2){
				count += 1;
			}
		}
	}
	//top side
	else if (boardSpot < 30){
		vector<int> mods;
		mods.push_back(-1);
		mods.push_back(29);
		mods.push_back(1);
		mods.push_back(30);
		mods.push_back(31);
		for (int i = 0; i < mods.size(); i++){
			if (mineVector[boardSpot + mods[i]] == -2){
				count += 1;
			}
		}
	}
	//right side
	else if (boardSpot % 30 == 29){
		vector<int> mods;
		mods.push_back(-31);
		mods.push_back(-30);
		mods.push_back(-1);
		mods.push_back(30);
		mods.push_back(29);
		for (int i = 0; i < mods.size(); i++){
			if (mineVector[boardSpot + mods[i]] == -2){
				count += 1;
			}
		}
	}
	//bottom side
	else if (boardSpot > 449){
		vector<int> mods;
		mods.push_back(-29);
		mods.push_back(-30);
		mods.push_back(-31);
		mods.push_back(1);
		mods.push_back(-1);
		for (int i = 0; i < mods.size(); i++){
			if (mineVector[boardSpot + mods[i]] == -2){
				count += 1;
			}
		}
	}
	//now for the middle pieces
	else{
		vector<int> mods;
		mods.push_back(-29);
		mods.push_back(-30);
		mods.push_back(-31);
		mods.push_back(1);
		mods.push_back(-1);
		mods.push_back(29);
		mods.push_back(30);
		mods.push_back(31);
		for (int i = 0; i < mods.size(); i++){
			if (mineVector[boardSpot + mods[i]] == -2){
				count += 1;
			}
		}
	}
	return count;
}

vector<int> Board::getList(){
	return mineVector;
}