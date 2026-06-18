#include <iostream>
#include "../Lab Task 3/Project1/Header.h"
#include <gtest/gtest.h>

// Question2
TEST(TransposeMatrixTest, SquareMatrix)
{
    int rows = 3;
    int columns = 3;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[columns];
        for (int j = 0; j < columns; ++j)
        {
            matrix[i][j] = i * columns + j; // Populate with sequential values
        }
    }

    // Calculate the transpose
    transposeMatrix(matrix, rows, columns);

    // Check the result
    EXPECT_EQ(matrix[0][0], 0);
    EXPECT_EQ(matrix[0][1], 3);
    EXPECT_EQ(matrix[0][2], 6);
    // Add more assertions for other elements if needed...

    // Deallocate memory for the original matrix
    // for (int i = 0; i < rows; ++i) {
    //     delete[] matrix[i];
    // }
    // delete[] matrix;
}

// Question 3
TEST(RowColumnSumTest, SquareMatrix)
{
    int rows = 3;
    int columns = 3;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[columns];
        for (int j = 0; j < columns; ++j)
        {
            matrix[i][j] = i * columns + j; // Populate with sequential values
        }
    }

    // Arrays to store row and column sums
    int* rowSums = new int[rows];
    int* columnSums = new int[columns];

    // Calculate row and column sums
    calculateRowColumnSums(matrix, rows, columns, rowSums, columnSums);

    // Check the results
    EXPECT_EQ(rowSums[0], 3);
    EXPECT_EQ(rowSums[1], 12);
    EXPECT_EQ(rowSums[2], 21);

    EXPECT_EQ(columnSums[0], 9);
    EXPECT_EQ(columnSums[1], 12);
    EXPECT_EQ(columnSums[2], 15);

    // Deallocate memory
    // for (int i = 0; i < rows; ++i) {
    //     delete[] matrix[i];
    // }
    // delete[] matrix;

    // delete[] rowSums;
    // delete[] columnSums;
}

// Question 4
TEST(FindMaxElementTest, SquareMatrix)
{
    int rows = 3;
    int columns = 3;

    int** matrix = new int* [rows];
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = new int[columns];
        for (int j = 0; j < columns; ++j)
        {
            matrix[i][j] = i * columns + j; // Populate with sequential values
        }
    }

    // Find the maximum element
    int maxElement = findMaxElement(matrix, rows, columns);

    // Check the result
    EXPECT_EQ(maxElement, 8); // In a 3x3 matrix, 8 is the maximum element

    // Deallocate memory
    // for (int i = 0; i < rows; ++i) {
    //     delete[] matrix[i];
    // }
    // delete[] matrix;
}


// Question 5
TEST(SetZeroesTest, ExampleMatrix)
{
    int m = 3;
    int n = 4;
    int** matrix = new int* [m]
        {
            new int[4] {1, 2, 3, 0},
                new int[4] {4, 5, 0, 2},
                new int[4] { 0, 3, 1, 5 }
        };

    setZeroes(matrix, m, n);

    // Check if the matrix has been modified as expected
    EXPECT_EQ(matrix[0][0], 0);
    EXPECT_EQ(matrix[0][1], 0);
    EXPECT_EQ(matrix[0][2], 0);
    EXPECT_EQ(matrix[0][3], 0);
    EXPECT_EQ(matrix[1][0], 0);
    EXPECT_EQ(matrix[1][1], 0);
    EXPECT_EQ(matrix[1][2], 0);
    EXPECT_EQ(matrix[1][3], 0);
    EXPECT_EQ(matrix[2][0], 0);
    EXPECT_EQ(matrix[2][1], 0);
    EXPECT_EQ(matrix[2][2], 0);
    EXPECT_EQ(matrix[2][3], 0);

    // Deallocate memory
    // for (int i = 0; i < m; ++i) {
    //     delete[] matrix[i];
    // }
    // delete[] matrix;
}

// int main(int argc, char** argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }
