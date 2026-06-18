#include "pch.h"
#include "../Asgn 1/Submission.cpp"
#include "gtest/gtest.h"
#include <cstring>
using namespace std;

//-------------------Question No 1-----------------
TEST(Question_1a, BinaryCheckInstructor) {

	ASSERT_EQ(0, strcmp("0", BaseConverter(0, 2)));
	ASSERT_EQ(0, strcmp("1", BaseConverter(1, 2)));
	ASSERT_EQ(0, strcmp("10", BaseConverter(2, 2)));
	ASSERT_EQ(0, strcmp("11", BaseConverter(3, 2)));
	ASSERT_EQ(0, strcmp("100", BaseConverter(4, 2)));
	ASSERT_EQ(0, strcmp("101", BaseConverter(5, 2)));
	ASSERT_EQ(0, strcmp("110", BaseConverter(6, 2)));
	ASSERT_EQ(0, strcmp("111", BaseConverter(7, 2)));
	ASSERT_EQ(0, strcmp("1000", BaseConverter(8, 2)));
	ASSERT_EQ(0, strcmp("1001", BaseConverter(9, 2)));
	ASSERT_EQ(0, strcmp("1010", BaseConverter(10, 2)));
	ASSERT_EQ(0, strcmp("1011", BaseConverter(11, 2)));
	ASSERT_EQ(0, strcmp("1100", BaseConverter(12, 2)));
	ASSERT_EQ(0, strcmp("1101", BaseConverter(13, 2)));
	ASSERT_EQ(0, strcmp("1110", BaseConverter(14, 2)));
	ASSERT_EQ(0, strcmp("1111", BaseConverter(15, 2)));
	ASSERT_EQ(0, strcmp("10000", BaseConverter(16, 2)));
	ASSERT_EQ(0, strcmp("10001", BaseConverter(17, 2)));
	ASSERT_EQ(0, strcmp("10010", BaseConverter(18, 2)));
	ASSERT_EQ(0, strcmp("10011", BaseConverter(19, 2)));
}

TEST(Question_1b, FloatNumberCheckForBaseTwo) {
	ASSERT_EQ(0, strcmp("0", BaseConverter(0.0, 2)));
	ASSERT_EQ(0, strcmp("0.1", BaseConverter(0.5, 2)));
	ASSERT_EQ(0, strcmp("0.01", BaseConverter(0.25, 2)));
	ASSERT_EQ(0, strcmp("0.11", BaseConverter(0.75, 2)));
	ASSERT_EQ(0, strcmp("0.001", BaseConverter(0.125, 2)));
	ASSERT_EQ(0, strcmp("0.101", BaseConverter(0.625, 2)));
	ASSERT_EQ(0, strcmp("0.011", BaseConverter(0.375, 2)));
	ASSERT_EQ(0, strcmp("0.111", BaseConverter(0.875, 2)));
	ASSERT_EQ(0, strcmp("0.0001", BaseConverter(0.0625, 2)));
	ASSERT_EQ(0, strcmp("0.1001", BaseConverter(0.5625, 2)));
	ASSERT_EQ(0, strcmp("0.0101", BaseConverter(0.3125, 2)));
	ASSERT_EQ(0, strcmp("0.1101", BaseConverter(0.8125, 2)));
	ASSERT_EQ(0, strcmp("0.0011", BaseConverter(0.1875, 2)));
	ASSERT_EQ(0, strcmp("0.1011", BaseConverter(0.6875, 2)));
	ASSERT_EQ(0, strcmp("0.0111", BaseConverter(0.4375, 2)));
	ASSERT_EQ(0, strcmp("0.1111", BaseConverter(0.9375, 2)));
	ASSERT_EQ(0, strcmp("0.00001", BaseConverter(0.03125, 2)));
	ASSERT_EQ(0, strcmp("0.10001", BaseConverter(0.53125, 2)));
	ASSERT_EQ(0, strcmp("0.01001", BaseConverter(0.28125, 2)));
	ASSERT_EQ(0, strcmp("0.11001", BaseConverter(0.78125, 2)));
	ASSERT_EQ(0, strcmp("0.00101", BaseConverter(0.15625, 2)));
	ASSERT_EQ(0, strcmp("0.10101", BaseConverter(0.65625, 2)));
	ASSERT_EQ(0, strcmp("0.01101", BaseConverter(0.40625, 2)));
	ASSERT_EQ(0, strcmp("0.11101", BaseConverter(0.90625, 2)));
	ASSERT_EQ(0, strcmp("0.00011", BaseConverter(0.09375, 2)));
	ASSERT_EQ(0, strcmp("0.10011", BaseConverter(0.59375, 2)));
	ASSERT_EQ(0, strcmp("0.01011", BaseConverter(0.34375, 2)));
}

TEST(Question_1, FloatNumberCheckForBaseOctak) {

	ASSERT_EQ(0, strcmp("0", BaseConverter(0.0, 8)));
	ASSERT_EQ(0, strcmp("0.4", BaseConverter(0.5, 8)));
	ASSERT_EQ(0, strcmp("0.2", BaseConverter(0.25, 8)));
	ASSERT_EQ(0, strcmp("0.7", BaseConverter(0.875, 8)));
	ASSERT_EQ(0, strcmp("0.34", BaseConverter(0.4375, 8)));
	ASSERT_EQ(0, strcmp("0.74", BaseConverter(0.9375, 8)));
	ASSERT_EQ(0, strcmp("0.02", BaseConverter(0.03125, 8)));
	ASSERT_EQ(0, strcmp("0.32", BaseConverter(0.40625, 8)));
	ASSERT_EQ(0, strcmp("0.72", BaseConverter(0.90625, 8)));
	ASSERT_EQ(0, strcmp("0.06", BaseConverter(0.09375, 8)));
	ASSERT_EQ(0, strcmp("0.46", BaseConverter(0.59375, 8)));
	ASSERT_EQ(0, strcmp("0.26", BaseConverter(0.34375, 8)));

}

TEST(Question_1, FloatNegativeNumbersCheckerMixedBases) {

	// note for the negative numbers, the output will be in 2's complement form
	// the binary on the right side of the dot is the fractional part and will not be in 2's complement form
	// as in actual PC, the fractional part is always positive and observed negative or possible using flag
	ASSERT_EQ(0, strcmp("110.000110011001100110011", BaseConverter(6.1, 2)));
	ASSERT_EQ(0, strcmp("010.000110011001100110011", BaseConverter(-6.1, 2)));

}

TEST(Question_1, NegativeDecimal) {

	ASSERT_EQ(0, strcmp("0.4", BaseConverter(-0.5, 8)));
	ASSERT_EQ(0, strcmp("0.6", BaseConverter(-0.25, 8)));

}

TEST(Question_1, GreaterNumber) {

	ASSERT_EQ(0, strcmp("0.777777777777777777777", BaseConverter(0.999999999999999999999, 8)));
	ASSERT_EQ(0, strcmp("0.999999999999999999999", BaseConverter(0.999999999999999999999, 10)));

	ASSERT_EQ(0, strcmp("1110110001001111101001100011000", BaseConverter(1982321432, 2)));
	ASSERT_EQ(0, strcmp("16611751430", BaseConverter(1982321432, 8)));
	ASSERT_EQ(0, strcmp("7627D318", BaseConverter(1982321432, 16)));

}

TEST(Question_1, GreatNegativeNumber) {
	ASSERT_EQ(0, strcmp("89D82CE8", BaseConverter(-1982321432, 16)));

}

//-------------------Question No 2-----------------

TEST(Question_2, insertOpreations)
{
	int totalPages = 0;
	char*** book;
	char text[] = "Once upon a time in the kingdom of Serenia, there lived a wise and just king named Alexander and his beloved queen, Isabella.";
	makeBook(text, book, totalPages);

	insert(book, totalPages, 1); // As you will 1 page in book after makeBook function. Page# are 1

	char text1[] = "As years passed, King Alexander and Queen Isabella's reign flourished, marked by peace, prosperity, and the enduring bond of love between them.";

	insertText(book, totalPages, 2, 1, 0, text1); // 0 means start of the line.

	char ans[] = "---------- Page 1 ----------\nOnce upon a time in the kingdom of\nSerenia, there lived a wise and just\nking named Alexander and his beloved\nqueen, Isabella.\n---------- Page 2 ----------\nAs years passed, King Alexander and\nQueen Isabella's reign flourished,\nmarked by peace, prosperity, and the\nenduring bond of love between them.";
	cout << "\n\nExpected Output:\n" << ans << endl << "\nYour Output:\n" << toString(book, totalPages) << endl;
	ASSERT_EQ(2, totalPages);
}

TEST(Question_2, deleteOpreations)
{
	int totalPages = 0;
	char*** book;
	char text[] = "Once upon a time in the kingdom of Serenia, there lived a wise and just king named Alexander and his beloved queen, Isabella.";
	makeBook(text, book, totalPages);

	Delete(book, totalPages, 1);
	ASSERT_EQ(0, totalPages);

	char text1[] = "As years passed, King Alexander and Queen Isabella's reign flourished, marked by peace, prosperity, and the enduring bond of love between them.";

	insertText(book, totalPages, 1, 1, 0, text1); // 0 means start of the line.

	Delete(book, totalPages, 1, 2); // second line of page

	char ans2[] = "---------- Page 1 ----------\nAs years passed, King Alexander and\nmarked by peace, prosperity, and the\nenduring bond of love between them.";


	cout << "\n\nExpected Output:\n" << ans2 << endl << "\nYour Output:\n" << toString(book, totalPages) << endl;

	char text2[] = "the";

	DeleteText(book, totalPages, text2);

	char ans3[] = "---------- Page 1 ----------\nAs years passed, King Alexander and\nmarked by peace, prosperity, and\nenduring bond of love between them.";

	cout << "\n\nExpected Output:\n" << ans3 << endl << "\nYour Output:\n" << toString(book, totalPages) << endl;
	ASSERT_EQ(1, totalPages);
}

TEST(Question_2, CutPasteOpreations)
{
	int totalPages = 0;
	char*** book;
	char text[] = "Once upon a time in the kingdom of Serenia, there lived a wise and just king named Alexander and his beloved queen, Isabella.";

	makeBook(text, book, totalPages);

	char* clipboard;

	cut(book, totalPages, 1, 1, 2, 4, 2, 2, clipboard); // This will cut from line 2 of page 1 after 2nd word to line 3 of page 1 till word 2 (first 2 words). 

	char ans[] = "---------- Page 1 ----------\nOnce upon a time in the kingdom of\nSerenia, there Alexander and his beloved\nqueen, Isabella.";

	cout << "\n\nExpected Output:\n" << ans << endl << "\nYour Output:\n" << toString(book, totalPages) << endl;

	paste(book, totalPages, clipboard, 1, 1, 0); // start copying after 2nd word

	char ans2[] = "---------- Page 1 ----------\nlived a wise and just king named Once\nupon a time in the kingdom of Serenia,\nthere Alexander and his beloved queen,\nIsabella.";

	cout << "\n\nExpected Output:\n" << ans2 << endl << "\nYour Output:\n" << toString(book, totalPages) << endl;

	//cut(book, totalPages, 1, 1, 1, 5, 0, 1, clipboard);

	ASSERT_EQ(0, totalPages);
}
TEST(Question_2, CopyPasteOpreations)
{
	int totalPages = 0;
	char*** book;
	char text[] = "Once upon a time in the kingdom of Serenia, there lived a wise and just king named Alexander and his beloved queen, Isabella.";

	makeBook(text, book, totalPages);

	char* clipboard;

	copy(book, totalPages, 1, 1, 2, 4, 2, 2, clipboard); // This will cut from line 2 of page 1 after 2nd word to line 3 of page 1 till word 2 (first 2 words). 

	paste(book, totalPages, clipboard, 1, 1, 0); // start copying after 2nd word

	char ans2[] = "---------- Page 1 ----------\nlived a wise and just king named Once\nupon a time in the kingdom of Serenia,\nthere lived a wise and just king named\nAlexander and his beloved queen,\nIsabella.";

	cout << "\n\nExpected Output:\n" << ans2 << endl << "\nYour Output:\n" << toString(book, totalPages) << endl;

	ASSERT_EQ(1, totalPages);
}

TEST(Question_2, ConcatenateBooks)
{
	int totalPages1 = 0;
	char*** book1;
	char text[] = "Once upon  a  time in  the  kingdom  of Serenia,  there lived a wise  and just  king named  Alexander and  his beloved  queen, Isabella.";
	makeBook(text, book1, totalPages1);

	removeDoubleSpaces(book1, totalPages1);

	int totalPages2 = 0;
	char*** book2;

	char text1[] = "As years passed, King Alexander and Queen Isabella's reign flourished, marked by peace, prosperity, and the enduring bond of love between them.";

	makeBook(text1, book2, totalPages2);

	int totalPages = 0;
	char*** book;
	concatenateBooks(book1, totalPages1, book2, totalPages2, book, totalPages);

	char ans[] = "---------- Page 1 ----------\nOnce upon a time in the kingdom of\nSerenia, there lived a wise and just\nking named Alexander and his beloved\nqueen, Isabella.\n---------- Page 2 ----------\nAs years passed, King Alexander and\nQueen Isabella's reign flourished,\nmarked by peace, prosperity, and the\nenduring bond of love between them.";
	cout << "\n\nExpected Output:\n" << ans << endl << "\nYour Output:\n" << toString(book, totalPages) << endl;
	ASSERT_EQ(2, totalPages);
}

//-------------------Question No 3-----------------

bool isSafe(int** board, int row, int col, int queens)
{

	for (int i = 0; i < col; ++i)
		if (board[row][i] == 1)
			return false;

	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
		if (board[i][j] == 1)
			return false;

	for (int i = row + 1, j = col - 1; i < queens && j >= 0; ++i, --j)
		if (board[i][j] == 1)
			return false;

	return true;
}

bool isvalid(int**& board, int queens)
{

	for (int i = 0; i < queens; ++i)
		for (int j = 0; j < queens; ++j)
		{
			if (board[i][j] == 1)
				if (!isSafe(board, i, j, queens))
				{
					return false;
				}
		}
	return true;
}

TEST(Question_3, 10queens)
{

	int queens = 10;

	int** board = new int* [queens];
	for (int i = 0; i < queens; ++i)
	{
		board[i] = new int[queens]();
	}

	royalHarmony(board, 0, 0, queens);

	ASSERT_EQ(true, isvalid(board, queens));
}

TEST(Question_3, 6queens)
{

	int queens = 6;

	int** board = new int* [queens];
	for (int i = 0; i < queens; ++i)
	{
		board[i] = new int[queens]();
	}

	royalHarmony(board, 0, 0, queens);

	ASSERT_EQ(true, isvalid(board, queens));
}

TEST(Question_3, 3queens)
{

	int queens = 3;

	int** board = new int* [queens];
	for (int i = 0; i < queens; ++i)
	{
		board[i] = new int[queens]();
	}



	ASSERT_EQ(false, royalHarmony(board, 0, 0, queens));
}
//-------------------Question No 5-----------------

TEST(Q5, first) {

	SavingAccount** saver = new SavingAccount * [100];
	int accountsOpen = 0;

	for (int i = 1; i <= 50; i++)
	{
		OpenCustomerAccount(saver, accountsOpen, "George", 10, i);
	}


	ASSERT_EQ(0, strcmp("George", saver[accountsOpen - 1]->name));
	ASSERT_EQ(50, saver[accountsOpen - 1]->savingBalance);
}

TEST(Q5, second) {

	SavingAccount** saver = new SavingAccount * [100];
	int accountsOpen = 0;

	OpenCustomerAccount(saver, accountsOpen, "Jhon", 10, 10);
	OpenCustomerAccount(saver, accountsOpen, "Ali", 10, 50);


	ASSERT_EQ(0, strcmp("Jhon", saver[accountsOpen - 2]->name));
	ASSERT_EQ(10, saver[accountsOpen - 2]->savingBalance);

	ASSERT_EQ(0, strcmp("Ali", saver[accountsOpen - 1]->name));
	ASSERT_EQ(50, saver[accountsOpen - 1]->savingBalance);
}

TEST(Q5, third) {
	SavingAccount saver;
	saver.name = "Zain";
	saver.annualInterestRate = 10;
	saver.savingBalance = 25;
	saver.accountNum = "SA01";
	modifyInterestRate(&saver, 3);

	ASSERT_EQ(6.25, calculateMonthlyInterest(&saver));
}

TEST(Q5, fourth) {
	SavingAccount** saver = new SavingAccount * [100];
	int accountsOpen = 0;
	for (int i = 0; i < 100; i++)
	{
		OpenCustomerAccount(saver, accountsOpen, "Jhon", 10, i);
	}

	ASSERT_EQ(-1, SearchCustomer(saver, accountsOpen - 1, "110"));
	ASSERT_EQ(98, SearchCustomer(saver, accountsOpen - 1, "98"));
}

TEST(Q5, fifth) {

	SavingAccount** saver = new SavingAccount * [100];
	int accountsOpen = 0;


	for (int i = 0; i < 95; i++)
	{
		OpenCustomerAccount(saver, accountsOpen, "Jhon", 10, i);
	}

	ASSERT_EQ(-1, SearchCustomer(saver, accountsOpen - 1, "101"));
	ASSERT_EQ(90, SearchCustomer(saver, accountsOpen - 1, "90"));
	ASSERT_EQ(95, accountsOpen);

}

TEST(Q5, sixth) {

	SavingAccount s1, s2, s3, s4, s5;
	s1.name = "Moeez";
	s1.annualInterestRate = 10;
	s1.savingBalance = 24;
	s1.accountNum = "SA00";

	s2.name = "Nouman";
	s2.annualInterestRate = 15;
	s2.savingBalance = 30;
	s2.accountNum = "SA01";

	s3.name = "Fariz";
	s3.annualInterestRate = 20;
	s3.savingBalance = 50;
	s3.accountNum = "SA02";

	s4.name = "Luqman";
	s4.annualInterestRate = 10;
	s4.savingBalance = 70;
	s4.accountNum = "SA03";

	s5.name = "Hayat";
	s5.annualInterestRate = 10;
	s5.savingBalance = 80;
	s5.accountNum = "SA04";

	SavingAccount** saver = new SavingAccount * [100];
	int accountsOpen = 5;

	saver[0] = &s1;
	saver[1] = &s2;
	saver[2] = &s3;
	saver[3] = &s4;
	saver[4] = &s5;

	int index = SearchCustomer(saver, accountsOpen - 1, "02");


	ASSERT_EQ(50, saver[index]->savingBalance);
	UpdateAccountBalance(saver, index, "02", 80);
	ASSERT_EQ(80, saver[index]->savingBalance);
}


//-------------------Question No 4-----------------

TEST(Question4, Pattren)
{
	RecursivePattern1(3, 21);

	RecursivePattern1(1, 21);

	RecursivePattern2(11, 11);

	RecursivePattern3(10, 10);
}

int main(int argc, char** argv)
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}