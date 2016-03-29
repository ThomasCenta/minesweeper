/**author: Thomas Centa

interface for the Board */

#ifndef BOARD_H
#define BOARD_H
#include <vector>

using namespace std;


class Board{
public:
	//default constructor. makes board, no mines covered. -2 if a mine. 0-7 for known square values
	Board();
	//another constructor to make a covered board. Unknown squares are written as -1. 
	//The bool is just there to distinguish the constructors.
	Board(bool cover);
	//dont need a copy constructor because shallow copies will suffice.
	//change the value of a square
	void changeElement(const int e, const int n);
	//get numMines
	int getMines();
	//reduce the number of mines
	void reduceMines();
	//get element value from board
	int getElement(const int e);
	//count the number of unknown squares around a space.
	vector<int> countUnknown(const int e);
	//count the number of marked mines around a space
	int countMarked(const int e);
	//get the list of the positions of the board
	vector<int> getList();


private:

	vector<int> mineVector;
	int numMines;
};

#endif