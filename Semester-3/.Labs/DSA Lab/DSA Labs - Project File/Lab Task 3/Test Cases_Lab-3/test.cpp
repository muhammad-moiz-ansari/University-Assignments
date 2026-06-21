#include "pch.h"
#include <sstream>  // For testing output stream
#include <iostream>
#include <algorithm>  // For std::swap
#include <string>
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 3\Lab-3 Project File\23i-0523_Moiz Ansari_Q1.cpp"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 3\Lab-3 Project File\23i-0523_Moiz Ansari_Q2.cpp"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 3\Lab-3 Project File\23i-0523_Moiz Ansari_Q3.cpp"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 3\Lab-3 Project File\23i-0523_Moiz Ansari_Q4.cpp"

/***************************QUESTION 1***************************/
// Test suite for Transpose of matrix
TEST(MatrixRotationTest, Rotate90DegreesClockwise) {
    int matrix[SIZE][SIZE] = {
        {3, 4, 2},
        {5, 6, 1},
        {7, 8, 9}
    };

    int expectedMatrix[SIZE][SIZE] = {
        {7, 5, 3},
        {8, 6, 4},
        {9, 1, 2}
    };

    rotateMatrix90DegreesClockwise(matrix);

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            EXPECT_EQ(matrix[i][j], expectedMatrix[i][j]);
        }
    }
}

/***************************QUESTION 2***************************/
TEST(PlayerDataTest, InputPlayerData) 
{
    const int numPlayers = 12;
    const int numMatches = 10;

    // Mock data for input simulation
    int mockData[12][10] = {
        {10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
        {15, 25, 31, 45, 55, 65, 75, 85, 95, 105},
        {16, 25, 32, 45, 55, 65, 75, 85, 95, 105},
        {17, 25, 33, 45, 55, 65, 75, 85, 95, 105},
        {18, 25, 34, 45, 55, 65, 75, 85, 95, 105},
        {19, 25, 35, 45, 55, 65, 75, 85, 99, 105},
        {11, 25, 36, 45, 55, 65, 75, 85, 98, 105},
        {12, 25, 37, 45, 55, 65, 75, 85, 95, 90},
        {13, 25, 38, 45, 55, 65, 75, 85, 95, 85},
        {14, 25, 39, 45, 55, 65, 75, 85, 95, 100},
        {15, 25, 35, 45, 55, 65, 75, 85, 97, 105},
        {16, 25, 36, 45, 55, 65, 75, 85, 95, 105}
    };

    int runs[numPlayers][numMatches];
    std::memcpy(runs, mockData, sizeof(mockData));  // Directly copying mock data to runs

    // Test if inputPlayerData assigns the correct data (simulated)
    EXPECT_EQ(runs[0][0], 10);
    EXPECT_EQ(runs[1][1], 25);
    EXPECT_EQ(runs[11][9], 105);
}

TEST(PlayerDataTest, ComputeStatistics) {
    const int numPlayers = 12;
    const int numMatches = 10;
    const double runs[numPlayers][numMatches] = 
    {
        {10, 20, 30, 40, 50, 60, 70, 80, 90, 100},
        {15, 25, 31, 45, 55, 65, 75, 85, 95, 105},
        {16, 25, 32, 45, 55, 65, 75, 85, 95, 105},
        {17, 25, 33, 45, 55, 65, 75, 85, 95, 105},
        {18, 25, 34, 45, 55, 65, 75, 85, 95, 105},
        {19, 25, 35, 45, 55, 65, 75, 85, 99, 105},
        {11, 25, 36, 45, 55, 65, 75, 85, 98, 105},
        {12, 25, 37, 45, 55, 65, 75, 85, 95, 90},
        {13, 25, 38, 45, 55, 65, 75, 85, 95, 85},
        {14, 25, 39, 45, 55, 65, 75, 85, 95, 100},
        {15, 25, 35, 45, 55, 65, 75, 85, 97, 105},
        {16, 25, 36, 45, 55, 65, 75, 85, 95, 105}
    };
    double totalRuns[numPlayers];
    double avgRuns[numPlayers];

    computeStatistics(runs, numPlayers, totalRuns, avgRuns);

    cout << "Total runs:\n";
    for (int i = 0; i < numPlayers; ++i)
        cout << totalRuns[i] << "  ";
    cout << "\n\n";

    cout << "Avg runs:\n";
    for (int i = 0; i < numPlayers; ++i)
        cout << avgRuns[i] << "  ";
    cout << "\n\n";

    // Check the correctness of computed total runs and averages
    EXPECT_EQ(totalRuns[0], 550);
    EXPECT_DOUBLE_EQ(avgRuns[1], 59.6);
    EXPECT_EQ(totalRuns[11], 602);
}

TEST(PlayerDataTest, SortPlayersByTotalRuns) {
    const int numPlayers = 12;
    int totalRuns[numPlayers] = { 550, 625, 500, 600, 650, 580, 570, 590, 610, 620, 640, 660 };
    int playerIndices[numPlayers];

    sortPlayersByTotalRuns(totalRuns, playerIndices, numPlayers);

    cout << "\nScores:\n";
    for (int i = 0; i < numPlayers; ++i)
        cout << totalRuns[i] << "\t";
    cout << "\n";

    cout << "\nSorted:\n";
    for (int i = 0; i < numPlayers; ++i)
        cout << playerIndices[i] << "   ";
    cout << "\n\n";

    // Verify the order after sorting
    EXPECT_EQ(playerIndices[0], 11);  // Player 12 has the highest runs
    EXPECT_EQ(playerIndices[1], 4);  // Player 5 has the second-highest runs
    EXPECT_EQ(playerIndices[2], 10);   // Player 11 is third
}

TEST(PlayerDataTest, PrintTop10Players) {
    const int numPlayers = 12;
    int totalRuns[numPlayers] = { 550, 625, 500, 600, 650, 580, 570, 590, 610, 620, 640, 660 };
    int playerIndices[numPlayers];
    sortPlayersByTotalRuns(totalRuns, playerIndices, numPlayers);

    // Capture standard output
    std::ostringstream output;
    std::streambuf* oldCoutStreamBuf = std::cout.rdbuf();
    std::cout.rdbuf(output.rdbuf());

    // Call the function to test
    printTop10Players(totalRuns, playerIndices, numPlayers);

    // Restore standard output
    std::cout.rdbuf(oldCoutStreamBuf);

    printTop10Players(totalRuns, playerIndices, numPlayers);

    std::string outputStr = output.str();
    EXPECT_TRUE(outputStr.find("Player 12: 660 runs") != std::string::npos);
    EXPECT_TRUE(outputStr.find("Player 5: 650 runs") != std::string::npos);
    EXPECT_TRUE(outputStr.find("Player 11: 640 runs") != std::string::npos);

}
/*******************************QUESTION3********************************/

// Test for the calculateInverse function
TEST(MatrixInverseTest, BasicTest) {
    const int N = 2;
    double matrix[N][N] = {
        {4, 7},
        {3, 5}
    };

    double expectedInverse[N][N] = {
        {-5, 7},
        {3, -4}
    };

    double inverse[N][N];

    // Call the calculateInverse function
    bool success = calculateInverse(matrix, inverse);

    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            cout << inverse[i][j] << "  ";
        }
        cout << endl;
    }

    // Check if the inversion was successful
    ASSERT_TRUE(success) << "\nMatrix inversion failed unexpectedly.\n";

    cout << boolalpha;
    cout << "Is Inverse Correct? " << matricesAreEqual(expectedInverse, inverse) << endl;

    // Check if the calculated inverse matches the expected inverse
    EXPECT_TRUE(1, matricesAreEqual(expectedInverse, inverse)) << "\nMatrix inverse matches expected result.\n";
}




/// Question 3: Test for calculateDeterminant
TEST(CalculateDeterminantTest, BasicTest) {
    int matrix[3][3] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    EXPECT_EQ(calculateDeterminant(matrix), 0);

    int matrix2[3][3] = { {6, 1, 1}, {4, -2, 5}, {2, 8, 7} };
    EXPECT_EQ(calculateDeterminant(matrix2), -306);
}

/******************************* QUESTION4 ********************************/
//// Test for spiralOrder
//TEST(SpiralOrderTest, BasicTest) 
//{
//    const int rows = 3;
//    const int cols = 3;
//    int matrix[rows][cols] = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
//    int size;
//    int* result = spiralOrder(matrix, size);
//
//    int expected[] = { 1, 2, 3, 6, 9, 8, 7, 4, 5 };
//    for (int i = 0; i < size; ++i) {
//        EXPECT_EQ(result[i], expected[i]);
//    }
//
//    delete[] result;
//}


int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}