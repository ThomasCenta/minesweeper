#include "stdafx.h"
#include "CppUnitTest.h"
#include "C://Users/Thomas/documents/Visual Studio 2013/Projects/minesweeper/Project1/Subspace.h"
#include "C://Users/Thomas/documents/Visual Studio 2013/Projects/minesweeper/Project1/Subspace.cpp"
#include <iostream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		bool vectorsCombinatoriallyEqual(vector<int> vector1, vector<int> vector2){
			bool equal = true;
			if (vector1.size() != vector2.size()){
				equal = false;
			}
			else{
				for (int i = 0; i < vector1.size(); i++){
					bool found = false;
					for (int j = 0; vector2.size(); j++){
						if (vector2[j] == vector1[i]){
							found = true;
							break;
						}
					}
					if (!found){
						equal = false;
						break;
					}
				}
			}
			return equal;
		}

		int find(vector<int> vector, int value){
			for (int i = 0; i < vector.size(); i++){
				if (vector[i] == value){
					return i;
				}
			}
			return -1;
		}

		TEST_METHOD(constructor1)
		{
			int numMines = 0;
			int spotList[] = { 0, 1, 2, 3, 4 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}
			Subspace test = Subspace(numMines, spots);

			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMines);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spots, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestConstructor2)
		{
			int numMines = 3;
			int spotList[] = { 0 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}
			Subspace test = Subspace(numMines, spots);

			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMines);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spots, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}


		TEST_METHOD(TestRemoveLeavingEmptyNonMineSpot)
		{
			int numMines = 3;
			int spotList[] = { 0 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			//empty in this case
			vector<int> spotsAfterFunctionCall;

			Subspace test = Subspace(numMines, spots);

			test.remove(0, false);
			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			//these should remain false
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestRemoveNonMineSpot1)
		{
			int numMines = 0;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 4, 5 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);

			test.remove(3, false);
			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}


		TEST_METHOD(TestRemoveNonMineSpot2)
		{
			int numMines = 5;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 3, 4 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);

			test.remove(5, false);
			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestRemoveMineSpotLeavingEmpty)
		{
			int numMines = 5;
			int spotList[] = { 0 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines - 1;

			vector<int> spotsAfterFunctionCall;

			Subspace test = Subspace(numMines, spots);

			test.remove(0, true);
			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestRemoveMineSpot1)
		{
			int numMines = 5;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines - 1;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 3, 4 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);

			test.remove(5, true);
			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		};

		TEST_METHOD(TestRemoveMineSpot2)
		{
			int numMines = 0;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines - 1;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 4, 5 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);

			test.remove(3, true);
			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestRemoveOnCheckedSubsets1)
		{
			int numMines = 0;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines - 1;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 4, 5 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);


			test.remove(3, true);
			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestRemoveOnCheckedSubsets2)
		{
			int numMines = 0;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines - 1;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 3, 4 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);
			test.setChecked(true);


			test.remove(5, true);
			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestRemoveOnCheckedSubsets3)
		{
			int numMines = 4;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 3, 4 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);
			test.setChecked(true);


			test.remove(5, false);
			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestSizeOnNonEmptySubset1)
		{
			int numMines = 4;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);

			vector<int> result = test.getSpots();

			int size = test.size();

			Assert::AreEqual(size, (int) spotsAfterFunctionCall.size());
			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestSizeOnNonEmptySubset2)
		{
			int numMines = 4;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setChecked(true);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			int size = test.size();

			Assert::AreEqual(size, (int) spotsAfterFunctionCall.size());
			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsTrue(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}


		TEST_METHOD(TestSizeOnEmptySubset1)
		{
			int numMines = 4;

			vector<int> spots;


			int numMinesAfterFunctionCall = numMines;

			vector<int> spotsAfterFunctionCall;

			Subspace test = Subspace(numMines, spots);


			test.remove(5, false);
			vector<int> result = test.getSpots();

			int size = test.size();

			Assert::AreEqual(size, (int) spotsAfterFunctionCall.size());
			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestSizeOnEmptySubset2)
		{
			int numMines = 4;
			vector<int> spots;

			int numMinesAfterFunctionCall = numMines;

			vector<int> spotsAfterFunctionCall;

			Subspace test = Subspace(numMines, spots);
			test.setChecked(true);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			int size = test.size();

			Assert::AreEqual(size, (int) spotsAfterFunctionCall.size());
			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsTrue(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}


		//Ugh Im done checking getters and setters.

		TEST_METHOD(TestFindGuaranteedSolutionOnNoSolution1)
		{
			int numMines = 4;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);


			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();


			Assert::AreEqual(0, (int) solutions[0].size());
			Assert::AreEqual(0, (int) solutions[1].size());
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestFindGuaranteedSolutionOnNoSolution2)
		{
			int numMines = 1;
			int spotList[] = { 0, 1 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();


			Assert::AreEqual(0, (int) solutions[0].size());
			Assert::AreEqual(0, (int) solutions[1].size());
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestFindGuaranteedSolutionWithSolution1)
		{
			int numMines = 1;
			int spotList[] = { 0 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();

			int spotsWithMines[] = { 0 };

			for (int i = 0; i < sizeof(spotsWithMines) / sizeof(*spotsWithMines); i++){
				int spotLocation = find(solutions[1], spotsWithMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 1);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}


		TEST_METHOD(TestFindGuaranteedSolutionWithSolution2)
		{
			int numMines = 3;
			int spotList[] = { 0, 1, 2 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();

			int spotsWithMines[] = { 0, 1, 2 };

			for (int i = 0; i < sizeof(spotsWithMines) / sizeof(*spotsWithMines); i++){
				int spotLocation = find(solutions[1], spotsWithMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 1);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestFindGuaranteedSolutionWithSolution3)
		{
			int numMines = 0;
			int spotList[] = { 0, 1, 2 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();

			int spotsWithoutMines[] = { 0, 1, 2 };

			for (int i = 0; i < sizeof(spotsWithoutMines) / sizeof(*spotsWithoutMines); i++){
				int spotLocation = find(solutions[1], spotsWithoutMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 0);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}


		TEST_METHOD(TestFindGuaranteedSolutionWithSolution4)
		{
			int numMines = 0;
			int spotList[] = { 0 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();

			int spotsWithoutMines[] = { 0 };

			for (int i = 0; i < sizeof(spotsWithoutMines) / sizeof(*spotsWithoutMines); i++){
				int spotLocation = find(solutions[1], spotsWithoutMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 0);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}

		
		TEST_METHOD(TestFindGuaranteedSolutionWithSolution5)
		{
			int numMines = 2;
			int spotList[] = { 0, 1, 2 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			//add solutions
			vector<int> premadeSolutions;
			premadeSolutions.push_back(0);
			premadeSolutions.push_back(2);
			premadeSolutions.push_back(4);
			premadeSolutions.push_back(4);
			test.setSolutions(premadeSolutions);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();

			int spotsWithoutMines[] = { 0 };

			int spotsWithMines[] = { 2 };

			for (int i = 0; i < sizeof(spotsWithoutMines) / sizeof(*spotsWithoutMines); i++){
				int spotLocation = find(solutions[1], spotsWithoutMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 0);
			}

			for (int i = 0; i < sizeof(spotsWithMines) / sizeof(*spotsWithMines); i++){
				int spotLocation = find(solutions[1], spotsWithMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 1);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}

		
		TEST_METHOD(TestFindGuaranteedSolutionWithSolution6)
		{
			int numMines = 2;
			int spotList[] = { 0, 1, 2 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			//add solutions
			vector<int> premadeSolutions;
			premadeSolutions.push_back(4);
			premadeSolutions.push_back(4);
			premadeSolutions.push_back(4);
			premadeSolutions.push_back(4);
			test.setSolutions(premadeSolutions);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();


			int spotsWithMines[] = { 0, 1, 2 };


			for (int i = 0; i < sizeof(spotsWithMines) / sizeof(*spotsWithMines); i++){
				int spotLocation = find(solutions[1], spotsWithMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 1);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestFindGuaranteedSolutionWithSolution7)
		{
			int numMines = 2;
			int spotList[] = { 0, 1, 2 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			//add solutions
			vector<int> premadeSolutions;
			premadeSolutions.push_back(0);
			premadeSolutions.push_back(0);
			premadeSolutions.push_back(0);
			premadeSolutions.push_back(4);
			test.setSolutions(premadeSolutions);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();

			int spotsWithoutMines[] = { 0, 1, 2 };


			for (int i = 0; i < sizeof(spotsWithoutMines) / sizeof(*spotsWithoutMines); i++){
				int spotLocation = find(solutions[1], spotsWithoutMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 0);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}

		TEST_METHOD(TestFindGuaranteedSolutionWithoutSolution)
		{
			int numMines = 2;
			int spotList[] = { 0, 1, 2 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2 };
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			//add solutions
			vector<int> premadeSolutions;
			premadeSolutions.push_back(1);
			premadeSolutions.push_back(2);
			premadeSolutions.push_back(3);
			premadeSolutions.push_back(4);
			test.setSolutions(premadeSolutions);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();


			Assert::AreEqual(0, (int) solutions[0].size());
			Assert::AreEqual(0, (int) solutions[1].size());
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		}

	};
}