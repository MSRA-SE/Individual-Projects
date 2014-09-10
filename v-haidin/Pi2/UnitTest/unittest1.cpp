#include "stdafx.h"
#include "CppUnitTest.h"
#include "test.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            Assert::IsTrue(unit_test("../Pi2/pi.txt", "../Pi2/Data.txt"));
		}

	};
}