/**author: Thomas Centa

interface for the Board */

#ifndef BOARD_H
#define BOARD_H
#include <vector>

using namespace std;


class Board{
public:
	/*Default Constructor. Makes an an expert board with all spots exposed
		fill each spot with 0-7 corresponding to the number of mines around that spot, or -2 for a mine
		leaves the center 3x3 square with no mines on it
	*/
	Board();

	/* Optional constructor to produce a covered board for an expert board
		has -1 in every spot except the center spot of 254 which is 0 (no mines around it)
	*/
	Board(bool cover);

	/*change the value of a square
		@param e
			the spot in this to change
		@param n
			the value to change the spot to
		@updates this
		@requires 0 <= e < 480 (the board size)
		@ensures
			this = #this[0, e) * n * this(e, 480)
	*/
	void changeElement(const int e, const int n);
	
	/*returns the number of mines not exposed on the board
		@returns the number of mines not exposed on the board
		@ensures the number returned is 99 - number of -2s on the board
	*/
	int getMines();
	
	/*reduces the number of mines by 1
		@updates this
		@ensures this.numMines = #this.numMines - 1
	*/
	void reduceMines();

	/*gets the element on the board at spot e
		@param e
			the spot to get the element on
		@requires 0 <= e < 480
		@returns the element at position e
		@ensures the number returned is -2 if its a mine, -1 if unknown, 0-7 if known and not a mine
	*/
	int getElement(const int e);

	/* counts the number of unknown spots next to the element e
		@param e
			the element to be searched around
		@requires 0 <= e < 480
		@returns a vector of all elements surrounnding e with -1 as an element
		@ensures 0 <= |return vector| <= 8
	*/
	vector<int> countUnknown(const int e);

	/*count the number of marked mines around a space
		@param e
			the element to be searched around
			@requires 0 <= e < 480
			@returns the number of elements marked as -2 around e
			@ensures 0 <= return value <= 8
	*/
	int countMarked(const int e);

	/*returns a copy of the list of elements
	*/
	vector<int> getList();


private:

	/*this stores the element of each position
	index i in mineVector corresponds to the spot row: floor(i / 30) and column: i % 30
	a -2 in that spot is a mine, -1 is an unknown spot, 0-7 is known, not a mine, and 
		corresponds to the number of mines around the element
	*/
	vector<int> mineVector;

	/*This is the number of mines that are still covered on the board
		so this would be 99 minus number of -2s in mineVector
	*/
	int numMines;
};

#endif