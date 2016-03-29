#include "stdafx.h"
#include "CppUnitTest.h"
#include "C://Users/Thomas/documents/Visual Studio 2013/Projects/minesweeper/Project1/SubspaceList.h"
#include "C://Users/Thomas/documents/Visual Studio 2013/Projects/minesweeper/Project1/SubspaceList.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(testConstructor)
		{
			SubspaceList test = SubspaceList(5);
		}

	};
}