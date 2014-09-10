#include "stdafx.h"
#include "CppUnitTest.h"
#include "../digitpi/digitpi.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(Testadd1)
		{
			bignum *t1 = new bignum(2, 0, 0);
			t1->setnum(987654321, 0);
			t1->setnum(123456789, 1);
			bignum *t2 = new bignum(2, 0, 0);
			t2->setnum(123456789, 0);
			bignum *t3 = new bignum(3, 0, 0);
			t3->add(t1, t2);
			t3->changelength();
			bignum *ans = new bignum(2, 0, 0);
			ans->setnum(111111110, 0);
			ans->setnum(123456790, 1);
			for (int i = 0; i < 2;i++)
				if (t3->getnumber(i)==ans->getnumber(i))
					Assert::AreEqual(1,1);
				else
					Assert::AreEqual(1, 0);
		}
		TEST_METHOD(Testadd2)
		{
			bignum *t1 = new bignum(2, 0, 1);
			t1->setnum(987654321, 0);
			t1->setnum(123456789, 1);
			bignum *t2 = new bignum(2, 0, 1);
			t2->setnum(123456789, 0);
			bignum *t3 = new bignum(3, 0, 0);
			t3->add(t1, t2);
			t3->changelength();
			bignum *ans = new bignum(2, 0, 0);
			ans->setnum(111111110, 0);
			ans->setnum(123456790, 1);
			for (int i = 0; i < 2; i++)
				if (t3->getnumber(i) == ans->getnumber(i))
					Assert::AreEqual(1, 1);
				else
					Assert::AreEqual(1, 0);
		}
		TEST_METHOD(Testadd3)
		{
			bignum *t1 = new bignum(2, 0, 1);
			t1->setnum(987654321, 0);
			t1->setnum(123456789, 1);
			bignum *t2 = new bignum(2, 0, 0);
			t2->setnum(123456789, 0);
			bignum *t3 = new bignum(3, 0, 0);
			t3->add(t1, t2);
			t3->changelength();
			bignum *ans = new bignum(2, 0, 0);
			ans->setnum(864197532, 0);
			ans->setnum(123456789, 1);
			for (int i = 0; i < 2; i++)
			if (t3->getnumber(i) == ans->getnumber(i))
				Assert::AreEqual(1, 1);
			else
				Assert::AreEqual(1, 0);
		}
		TEST_METHOD(Testmulti1)
		{
			bignum *t1 = new bignum(2, 0, 0);
			t1->setnum(987654321, 0);
			t1->setnum(123456789, 1);
			bignum *t2 = new bignum(2, 0, 0);
			t2->setnum(123456789, 0);
			bignum *t3 = new bignum(4, 0, 0);
			t3->multi(t1, t2);
			t3->changelength();
			bignum *ans = new bignum(3, 0, 0); 
			ans->setnum(112635269, 0);
			ans->setnum(872123152, 1);
			ans->setnum(15241578, 2);
			for (int i = 0; i < 3; i++)
			if (t3->getnumber(i) == ans->getnumber(i))
				Assert::AreEqual(1, 1);
			else
				Assert::AreEqual(1, 0);
		}
		TEST_METHOD(Testmulti2)
		{
			bignum *t1 = new bignum(200000, 0, 0);
			t1->setnum(1111, 0);
			t1->setnum(1111, 199999);
			bignum *t2 = new bignum(200000, 0, 0);
			t2->setnum(1111, 199999);
			bignum *t3 = new bignum(400000, 0, 0);
			t3->multi(t1, t2);
			t3->changelength();
			bignum *ans = new bignum(399999, 0, 0);
			ans->setnum(1234321, 199999);
			ans->setnum(1234321, 399998);
			for (int i = 0; i < 399999; i++)
			if (t3->getnumber(i) == ans->getnumber(i))
				Assert::AreEqual(1, 1);
			else
				Assert::AreEqual(1, 0);
		}

	};
}