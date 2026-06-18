#include<iostream>
#include "pch.h"
#include "../Lab Task 4/Header.h"
using namespace std;

// question 1
TEST(RecursiveFunction1, CharCount)
{
    char* ptr = "wavelength";
    char c = 'e';
    // Check the result
    EXPECT_EQ(2, getCharCount(ptr, c));
    EXPECT_EQ(2, getCharCount(ptr, c, 0, 0));
    char* ptr1 = "achievement";
    // Check the result
    EXPECT_EQ(3, getCharCount(ptr1, c));
}

// question 2
TEST(RecursiveFunction2, reverse)
{
    string word = "hello";
    string word1 = "programming";

    // Check the result
    EXPECT_EQ("olleh", reverseWord(word, 0, word.length() - 1));

    // Check the result
    EXPECT_EQ("gnimmargorp", reverseWord(word1, 0, word1.length() - 1));
}

// question 3
TEST(RecursiveFunction4, fibonacci)
{
    EXPECT_EQ(3, fibonacci(4));
    EXPECT_EQ(8, fibonacci(6));
    EXPECT_EQ(34, fibonacci(9));
    cout << "\nFibonacci Series: ";
    printFibonacci(6);
}

// question 4
TEST(Pattern1, pattern1)
{
    cout << "Question 4:\n";
    q4(5);
}

// question 5
TEST(Pattern2, pattern2)
{
    cout << "Question 5:\n";
    diamond_pattern(13, 13);
}