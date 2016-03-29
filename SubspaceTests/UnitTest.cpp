#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace SubspaceTests
{
	[TestClass]
	public ref class UnitTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		/// <summary>
		///Gets or sets the test context which provides
		///information about and functionality for the current test run.
		///</summary>
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		//
		//You can use the following additional attributes as you write your tests:
		//
		//Use ClassInitialize to run code before running the first test in the class
		//[ClassInitialize()]
		//static void MyClassInitialize(TestContext^ testContext) {};
		//
		//Use ClassCleanup to run code after all tests in a class have run
		//[ClassCleanup()]
		//static void MyClassCleanup() {};
		//
		//Use TestInitialize to run code before running each test
		//[TestInitialize()]
		//void MyTestInitialize() {};
		//
		//Use TestCleanup to run code after each test has run
		//[TestCleanup()]
		//void MyTestCleanup() {};
		//
		#pragma endregion 

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


		[TestMethod]
		void TestConstructor1()
		{
			int numMines = 0;
			int spotList[] = { 0, 1, 2, 3, 4 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}
			Subspace test = Subspace(numMines, spots);

			vector<int> result = test.getSpots();

			Assert::AreEqual(test.numberOfMines(),numMines);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spots, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		};

		[TestMethod]
		void TestConstructor2()
		{
			int numMines = 3;
			int spotList[] = { 0};
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
		};

		[TestMethod]
		void TestRemoveLeavingEmptyNonMineSpot()
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
		};

		[TestMethod]
		void TestRemoveNonMineSpot1()
		{
			int numMines = 0;
			int spotList[] = { 0 , 1, 2, 3, 4, 5};
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
		};


		[TestMethod]
		void TestRemoveNonMineSpot2()
		{
			int numMines = 5;
			int spotList[] = { 0, 1, 2, 3, 4, 5};
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 3, 4};
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
		};

		[TestMethod]
		void TestRemoveMineSpotLeavingEmpty()
		{
			int numMines = 5;
			int spotList[] = { 0};
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
		};

		[TestMethod]
		void TestRemoveMineSpot1()
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

		[TestMethod]
		void TestRemoveMineSpot2()
		{
			int numMines = 0;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines - 1;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 4 , 5};
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
		};

		[TestMethod]
		void TestRemoveOnCheckedSubsets1()
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
		};

		[TestMethod]
		void TestRemoveOnCheckedSubsets2()
		{
			int numMines = 0;
			int spotList[] = { 0, 1, 2, 3, 4, 5 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines - 1;

			int spotListAfterFunctionCall[] = { 0, 1, 2, 3, 4};
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
		};

		[TestMethod]
		void TestRemoveOnCheckedSubsets3()
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
		};


		[TestMethod]
		void TestSizeOnNonEmptySubset1()
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
			
			Assert::AreEqual(size, spotsAfterFunctionCall.size());
			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		};

		[TestMethod]
		void TestSizeOnNonEmptySubset2()
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

			Assert::AreEqual(size, spotsAfterFunctionCall.size());
			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsTrue(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		};


		[TestMethod]
		void TestSizeOnEmptySubset1()
		{
			int numMines = 4;
			
			vector<int> spots;


			int numMinesAfterFunctionCall = numMines;

			vector<int> spotsAfterFunctionCall;

			Subspace test = Subspace(numMines, spots);


			test.remove(5, false);
			vector<int> result = test.getSpots();

			int size = test.size();

			Assert::AreEqual(size, spotsAfterFunctionCall.size());
			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsFalse(test.checkedForGuaranteedSolution());
		};

		[TestMethod]
		void TestSizeOnEmptySubset2()
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

			Assert::AreEqual(size, spotsAfterFunctionCall.size());
			Assert::AreEqual(test.numberOfMines(), numMinesAfterFunctionCall);
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsTrue(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		};


//Ugh Im done checking getters and setters.
		
		[TestMethod]
		void TestFindGuaranteedSolutionOnNoSolution1()
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


			Assert::AreEqual(0, solutions[0].size());
			Assert::AreEqual(0, solutions[1].size());
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		};

		[TestMethod]
		void TestFindGuaranteedSolutionOnNoSolution2()
		{
			int numMines = 1;
			int spotList[] = { 0, 1 };
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0, 1};
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();


			Assert::AreEqual(0, solutions[0].size());
			Assert::AreEqual(0, solutions[1].size());
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		};

		[TestMethod]
		void TestFindGuaranteedSolutionWithSolution1()
		{
			int numMines = 1;
			int spotList[] = { 0};
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0};
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
				Assert::IsFalse( spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 1);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		};

		[TestMethod]
		void TestFindGuaranteedSolutionWithSolution2()
		{
			int numMines = 3;
			int spotList[] = { 0 , 1, 2};
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0 , 1, 2};
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();

			int spotsWithMines[] = { 0 , 1, 2};

			for (int i = 0; i < sizeof(spotsWithMines) / sizeof(*spotsWithMines); i++){
				int spotLocation = find(solutions[1], spotsWithMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 1);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		};

		[TestMethod]
		void TestFindGuaranteedSolutionWithSolution3()
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
		};


		[TestMethod]
		void TestFindGuaranteedSolutionWithSolution4()
		{
			int numMines = 0;
			int spotList[] = { 0};
			vector<int> spots;
			for (int i = 0; i < (sizeof(spotList) / sizeof(*spotList)); i++){
				spots.push_back(spotList[i]);
			}

			int numMinesAfterFunctionCall = numMines;

			int spotListAfterFunctionCall[] = { 0};
			vector<int> spotsAfterFunctionCall;
			for (int i = 0; i < (sizeof(spotListAfterFunctionCall) / sizeof(*spotListAfterFunctionCall)); i++){
				spotsAfterFunctionCall.push_back(spotListAfterFunctionCall[i]);
			}

			Subspace test = Subspace(numMines, spots);
			test.setCheckedForGuaranteedSolution(true);

			vector<int> result = test.getSpots();

			vector< vector<int> > solutions = test.findGuaranteedSolution();

			int spotsWithoutMines[] = { 0};

			for (int i = 0; i < sizeof(spotsWithoutMines) / sizeof(*spotsWithoutMines); i++){
				int spotLocation = find(solutions[1], spotsWithoutMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 0);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		};

		[TestMethod]
		void TestFindGuaranteedSolutionWithSolution5()
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

			int spotsWithoutMines[] = { 0};

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
		};

		[TestMethod]
		void TestFindGuaranteedSolutionWithSolution6()
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
		};
		
		[TestMethod]
		void TestFindGuaranteedSolutionWithSolution7()
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

			int spotsWithoutMines[] = { 0 , 1, 2};


			for (int i = 0; i < sizeof(spotsWithoutMines) / sizeof(*spotsWithoutMines); i++){
				int spotLocation = find(solutions[1], spotsWithoutMines[i]);
				Assert::IsFalse(spotLocation == -1);
				Assert::IsTrue(solutions[0][spotLocation] == 0);
			}


			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		};

		[TestMethod]
		void TestFindGuaranteedSolutionWithoutSolution()
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

			
			Assert::AreEqual(0, solutions[0].size());
			Assert::AreEqual(0, solutions[1].size());
			Assert::IsTrue(vectorsCombinatoriallyEqual(spotsAfterFunctionCall, result));
			Assert::IsFalse(test.hasBeenChecked());
			Assert::IsTrue(test.checkedForGuaranteedSolution());
		};

	};
}
