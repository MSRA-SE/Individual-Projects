#include "stdafx.h"
#include "CppUnitTest.h"
#include "..\pi\SmallNum.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(PLUS1)
		{
			int tmp1[3] = { 0, 1234, 5678 }, tmp2[3] = { 0, 2345, 6789 };
			SmallNum a(tmp1, 3), b(tmp2, 3);
			a = a + b;
			Assert::AreEqual(0, a[0]);
			Assert::AreEqual(3580, a[1]);
			Assert::AreEqual(2467, a[2]);

		}
		TEST_METHOD(PLUS2)
		{
			int tmp1[3] = { 0, 9876, 5432 }, tmp2[2] = { 0, 2345 };
			SmallNum a(tmp1, 3), b(tmp2, 2);
			a = a + b;
			Assert::AreEqual(1, a[0]);
			Assert::AreEqual(2221, a[1]);
			Assert::AreEqual(5432, a[2]);

		}
		TEST_METHOD(MINUS1)
		{
			int tmp1[3] = { 1, 0, 123 }, tmp2[2] = { 0, 345 };
			SmallNum a(tmp1, 3), b(tmp2, 2);
			a = a - b;
			Assert::AreEqual(0, a[0]);
			Assert::AreEqual(9655, a[1]);
			Assert::AreEqual(123, a[2]);

		}
		TEST_METHOD(MINUS2)
		{
			int tmp1[3] = { 1, 0, 0 }, tmp2[3] = { 0, 345, 789 };
			SmallNum a(tmp1, 3), b(tmp2, 3);
			a = a - b;
			Assert::AreEqual(0, a[0]);
			Assert::AreEqual(9654, a[1]);
			Assert::AreEqual(9211, a[2]);

		}
		TEST_METHOD(MINUS3)
		{
			int tmp1[3] = { 2, 0, 0 }, tmp2[3] = { 0, 0, 1 };
			SmallNum a(tmp1, 3), b(tmp2, 3);
			a = a - b;
			Assert::AreEqual(1, a[0]);
			Assert::AreEqual(9999, a[1]);
			Assert::AreEqual(9999, a[2]);

		}
		TEST_METHOD(MUL1)
		{
			int tmp1[3] = { 2, 1234, 5678 };
			SmallNum a(tmp1, 3);
			a = a * 11;
			Assert::AreEqual(23, a[0]);
			Assert::AreEqual(3580, a[1]);
			Assert::AreEqual(2458, a[2]);
		}
		TEST_METHOD(DIV1)
		{
			int tmp1[3] = { 1, 0, 0 };
			SmallNum a(tmp1, 3);
			a = a / 100000;
			Assert::AreEqual(0, a[0]);
			Assert::AreEqual(0, a[1]);
			Assert::AreEqual(1000, a[2]);
		}
		TEST_METHOD(DIV2)
		{
			int tmp1[3] = { 1, 0, 0 };
			SmallNum a(tmp1, 3);
			a = a / 7;
			Assert::AreEqual(0, a[0]);
			Assert::AreEqual(1428, a[1]);
			Assert::AreEqual(5714, a[2]);
		}
		TEST_METHOD(ARCTAN1)
		{
			
			SmallNum a = SmallNum::arctan(1, 5);
			Assert::AreEqual(0, a[0]);
			Assert::AreEqual(1973, a[1]);
			Assert::AreEqual(9555, a[2]);
			Assert::AreEqual(9849, a[3]);

		}
		TEST_METHOD(ARCTAN2)
		{

			SmallNum a = SmallNum::arctan(1, 239);
			Assert::AreEqual(0, a[0]);
			Assert::AreEqual(41, a[1]);
			Assert::AreEqual(8407, a[2]);
			Assert::AreEqual(6002, a[3]);

		}
	};
}