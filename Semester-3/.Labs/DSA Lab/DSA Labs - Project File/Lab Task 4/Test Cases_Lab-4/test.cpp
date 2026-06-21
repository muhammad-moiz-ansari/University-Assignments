#include<iostream>
#include "pch.h"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 4\Lab-4 Project File\23i-0523_Moiz Ansari_Q1.cpp"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 4\Lab-4 Project File\23i-0523_Moiz Ansari_Q2.cpp"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 4\Lab-4 Project File\23i-0523_Moiz Ansari_Q3.cpp"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 4\Lab-4 Project File\23i-0523_Moiz Ansari_Q4.cpp"

using namespace std;

//question 1
TEST(PuzzleSortTest, SortPuzzleRows) {
    int puzzle[2][8] = {
        {32, 30, 39, 34, 37, 35, 33},
        {50, 48, 54, 59, 47, 49, 52, 51}
    };

    // Expected sorted result
    int expectedPuzzle[2][8] = {
        {30, 32, 33, 34, 35, 37, 39},
        {47, 48, 49, 50, 51, 52, 54, 59}
    };

    // Sort the first row using insertion sort
    selectionSort(puzzle[0], 7);

    for (int i = 0; i < 7; i++) {
        cout << puzzle[0][i] << "  ";
    }
    cout << endl;

    // Sort the third row using bubble sort
    bubbleSort(puzzle[1], 8);

    for (int i = 0; i < 7; i++) {
        cout << puzzle[1][i] << "  ";
    }
    cout << endl;

    // Compare the sorted rows with the expected rows
    for (int i = 0; i < 7; i++) {
        EXPECT_EQ(puzzle[0][i], expectedPuzzle[0][i]);
    }

    for (int i = 0; i < 8; i++) {
        EXPECT_EQ(puzzle[1][i], expectedPuzzle[1][i]);
    }
}

// question 4
TEST(LinearSearchTest, BasicTests) {
    // Test case 1: Target is found in the array
    const int numStrings1 = 5;
    string strings1[numStrings1] = { "apple", "banana", "cherry", "date", "elderberry" };
    int result1 = linearSearchString(strings1, numStrings1, "cherry");
    EXPECT_EQ(result1, 2);  // Expected index is 2

    // Test case 2: Target is not found in the array
    int result2 = linearSearchString(strings1, numStrings1, "fig");
    EXPECT_EQ(result2, -1); // Expected result is -1 since "fig" is not in the array
}
 
// question 3
TEST(FindInsertPositionTest, BasicTests) {
    // Test case 1: Inserting a value into the middle of the array
    const int numElements1 = 6;
    int arr1[numElements1] = { 1, 3, 5, 7, 9, 11 };
    int result1 = findInsertPosition(arr1, numElements1, 6);
    EXPECT_EQ(result1, 3); // 6 should be inserted at index 3 (between 5 and 7)

    // Test case 2: Inserting a value that is smaller than all elements
    int result2 = findInsertPosition(arr1, numElements1, 0);
    EXPECT_EQ(result2, 0); // 0 should be inserted at index 0 (before 1)

    // Test case 3: Inserting a value that is greater than all elements
    int result3 = findInsertPosition(arr1, numElements1, 12);
    EXPECT_EQ(result3, 6); // 12 should be inserted at index 6 (after 11)

    // Test case 4: Inserting a value that is equal to an existing element
    int result4 = findInsertPosition(arr1, numElements1, 9);
    EXPECT_EQ(result4, 4); // 9 is already present at index 4

}