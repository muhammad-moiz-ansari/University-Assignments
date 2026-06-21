#include "pch.h"
#include "D:\Documents\Semester-3\.Labs\DS Lab\Lab Task 1\i230523_F_Lab 1\23i-0523_Moiz Ansari_Q3.cpp"
#include "D:\Documents\Semester-3\.Labs\DS Lab\Lab Task 1\i230523_F_Lab 1\23i-0523_Moiz Ansari_Q4.cpp"

TEST(Deposite, TestName) 
{
	BankAccount<float> A(1, 500);

	EXPECT_EQ(A.deposite(200), 700);
	EXPECT_TRUE(true);
}

TEST(Withdraw, TestName)
{
	BankAccount<float> A(1, 700);

	EXPECT_EQ(A.withdraw(150.5), 549.5);
	EXPECT_TRUE(true);
}

TEST(Q4, TestName)
{
	Container<float> A(6);

	A.print();

	A.insert(1);
	A.insert(2);
	A.insert(3);
	A.insert(4);
	A.insert(3);
	A.insert(6);
	A.insert(7);

	A.print();

	EXPECT_EQ(A.isFull(), 1);
	EXPECT_TRUE(true);

	EXPECT_EQ(A.search(3), 1);
	EXPECT_TRUE(true);

	A.remove(3);

	A.print();


}