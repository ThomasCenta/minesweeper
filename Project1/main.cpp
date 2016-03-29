/**author: Thomas Centa

*/

#include "Board.h"
#include "SubspaceList.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

/*
	This will return true if the game was won, false if lost
*/
bool runGameType1(int boardSize){
	Board master;
	Board played(true);

	//make the subspaceList
	SubspaceList subspaces = SubspaceList(boardSize);
	subspaces.addSubspace(254, &played);

	bool lost = false;
	//now let the games BEGIN!
	while (!lost && played.getMines() > 0){
		subspaces.calculateLocalSolutions();
		vector< vector<int> > guaranteedSolutions = subspaces.checkSolutions();
		//store whether or not a solution has been found
		bool solutionFound = false;
		for (int i = 0; i < guaranteedSolutions[1].size(); i++){
			solutionFound = true;
			if (guaranteedSolutions[0][i] == 1){
				//if this is called then something is wrong with these guaranteed solutions
				if (master.getElement(guaranteedSolutions[1][i]) != -2){
					lost = true;
					continue;
				}
				else{
					subspaces.removeElement(guaranteedSolutions[1][i], true);
					played.changeElement(guaranteedSolutions[1][i], -2);
					played.reduceMines();
				}
			}
			else if (guaranteedSolutions[0][i] == 0){
				int revealedNumber = master.getElement(guaranteedSolutions[1][i]);
				//if this is called then something is wrong with these guaranteed solutions
				if (revealedNumber == -2){
					lost = true;
					continue;
				}
				else{
					subspaces.removeElement(guaranteedSolutions[1][i], false);
					played.changeElement(guaranteedSolutions[1][i], revealedNumber);
					subspaces.addSubspace(guaranteedSolutions[1][i], &played);
				}
			}
		}
		//if no solution was found, then it's guessin' time. Gonna click on the spot with lowest probability
		int checkNext = subspaces.lowestProbability();
		if (master.getElement(checkNext) == -2){
			lost = true; 
			continue;
		}
		else{
			subspaces.removeElement(checkNext, false);
			played.changeElement(checkNext, master.getElement(checkNext));
			subspaces.addSubspace(checkNext, &played);
		}
	}
	return !lost;


}




int main(){
	//This will only use the expert board with 99 mines and a width of 30 and height 15.
	/*cout << "How many games would you like to play? ";
	int numGames;
	cin >> numGames;
	cout << "\n";         
	*/

	bool won = runGameType1(480);



	bool timeWaster;
	cout << "done viewing ? ";
	cin >> timeWaster;
	return 0;
}