#include "stdafx.h"
#include "CppUnitTest.h"

extern "C"
{
#include "../MyPi/MyPi.h"
#pragma comment(lib,"../Release/MyPi.lib")

}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Add)
		{
			// TODO: Your test code here
			Number a, b, c;
			int L;

			SetLength(2);

			L=NumberNew(&a);
			NumberNew(&b);
			NumberNew(&c);

			a.digit[0] = BASE /2;
			a.digit[1] = BASE /2;

			b.digit[0] = 0;
			b.digit[1] = BASE /2;

			NumberAdd(&a, &b, &c);

			Assert::AreEqual(2, L);
			Assert::AreEqual((u64)BASE / 2 + 1,(u64)c.digit[0]);
			Assert::AreEqual((u64)0, (u64)(c.digit[1]));



			NumberFree(&a);
			NumberFree(&b);
			NumberFree(&c);
		}

		TEST_METHOD(Minus)
		{
			// TODO: Your test code here
			Number a, b, c;
			int L;

			SetLength(2);

			L = NumberNew(&a);
			NumberNew(&b);
			NumberNew(&c);

			a.digit[0] = 2;
			a.digit[1] = 0;

			b.digit[0] = 0;
			b.digit[1] = BASE / 2;

			NumberMinus(&a, &b, &c);

			Assert::AreEqual(2, L);
			Assert::AreEqual((u64)1, (u64)c.digit[0]);
			Assert::AreEqual((u64)BASE / 2, (u64)(c.digit[1]));



			NumberFree(&a);
			NumberFree(&b);
			NumberFree(&c);
		}

		TEST_METHOD(Div)
		{
			// TODO: Your test code here
			Number a, b, c;
			int L;

			SetLength(2);

			L = NumberNew(&a);
			NumberNew(&b);
			NumberNew(&c);

			a.digit[0] = 2;
			a.digit[1] = 0;

			NumberDiv(&a, &c,BASE/8);

			Assert::AreEqual(2, L);
			Assert::AreEqual((u64)0, (u64)c.digit[0]);
			Assert::AreEqual((u64)16, (u64)(c.digit[1]));



			NumberFree(&a);
			NumberFree(&b);
			NumberFree(&c);
		}

		TEST_METHOD(Mul10)
		{
			// TODO: Your test code here
			Number a, b, c;
			int L,T1,T2;

			SetLength(2);

			L = NumberNew(&a);
			NumberNew(&b);
			NumberNew(&c);

			a.digit[0] = BASE / 2;
			a.digit[1] = BASE / 2;

			T1 = NumberMul10(&a, &b);
			T2 = NumberMul10(&b, &a);

			Assert::AreEqual(2, L);
			Assert::AreEqual((u64)5, (u64)T1);
			Assert::AreEqual((u64)0, (u64)T2);



			NumberFree(&a);
			NumberFree(&b);
			NumberFree(&c);
		}

		TEST_METHOD(N2_15)
		{
			// TODO: Your test code here
			Number a, b, c;
			int L, T1, T2;

			SetLength(2);

			L = NumberNew(&a);
			NumberNew(&b);
			NumberNew(&c);

			Number2_15(&a);

			T1 = NumberMul10(&a, &b);
			T2 = NumberMul10(&b, &a);

			Assert::AreEqual(2, L);
			Assert::AreEqual((u64)1, (u64)T1);
			Assert::AreEqual((u64)3, (u64)T2);



			NumberFree(&a);
			NumberFree(&b);
			NumberFree(&c);
		}

	};
}