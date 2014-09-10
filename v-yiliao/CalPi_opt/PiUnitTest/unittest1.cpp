#include "stdafx.h"
#include "CppUnitTest.h"
#include "Header.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PiUnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Test_add)
		{
			
			std::vector<int> a, b, ans;
			a.push_back(0);
			a.push_back(MOD - 1);
			b.push_back(0);
			b.push_back(2);
			ans.push_back(1);
			ans.push_back(1);
			add(a, b, 0);
			int len = min((int)a.size(), (int)ans.size());
			for (int i = 0; i < len; i++)
			{
				Assert::AreEqual(a[i], ans[i]);
			}
		}

		TEST_METHOD(Test_multiply)
		{

			std::vector<int> a, ans;
			a.push_back(0);
			a.push_back(MOD - 15);
			int b = 29;
			ans.push_back(28);
			ans.push_back(999999565);
			multiply(a, b, 0);
			int len = min((int)a.size(), (int)ans.size());
			for (int i = 0; i < len; i++)
			{
				Assert::AreEqual(a[i], ans[i]);
			}
		}

		TEST_METHOD(Test_divide)
		{

			std::vector<int> a, ans;
			a.push_back(0);
			a.push_back(100000000);
			int b = 3;
			ans.push_back(0);
			ans.push_back(33333333);
			ans.push_back(333333333);
			divide(a, b, 0, 3);
			int len = min((int)a.size(), (int)ans.size());
			for (int i = 0; i < len; i++)
			{
				Assert::AreEqual(a[i], ans[i]);
			}
		}

		TEST_METHOD(Test_check)
		{

			std::vector<int> a;
			a.push_back(0);
			a.push_back(0);
			a.push_back(0);
			a.push_back(1);
			int pos = check(a, 0);
			Assert::AreEqual(pos, 3);
		}

		TEST_METHOD(Test_updateLength)
		{

			int n = 10000, MAXN;
			updateLength(n, MAXN);
			Assert::AreEqual(MAXN, 1114);
		}
	};
}