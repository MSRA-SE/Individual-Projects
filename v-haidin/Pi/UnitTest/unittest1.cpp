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
			// TODO: Your test code here
            Assert a;
            a.IsTrue(unit_test("../Pi/pi.txt", "../Pi/Data.txt"));
		}

	};
}