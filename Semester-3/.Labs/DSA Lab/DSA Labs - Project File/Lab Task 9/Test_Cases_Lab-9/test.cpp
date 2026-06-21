#include "pch.h"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 9\Lab-9 Project File\23i-0523_Moiz Ansari_Lab9_Q1.cpp"
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 9\Lab-9 Project File\23i-0523_Moiz Ansari_Lab9_Q2.cpp"
#include <string>

//***************** Q1 Test cases *****************
//Maze

// Test case 1: Simple path to the destination
TEST(MazeSolverTest, SimplePath) {
    int n = 4, m = 4;
    int** maze = new int* [n];
    for (int i = 0; i < n; ++i) {
        maze[i] = new int[m];
    }

    int mazeData[4][4] = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            maze[i][j] = mazeData[i][j];
        }
    }

    bool result = isReachable(maze, n, m, 3, 3);  // Checking if rat can reach (3, 3)
    EXPECT_TRUE(result);  // Should return true because there's a valid path

    // Clean up dynamic memory
    for (int i = 0; i < n; ++i) {
        delete[] maze[i];
    }
    delete[] maze;
}

// Test case 2: No path to the destination
TEST(MazeSolverTest, NoPath) {
    int n = 4, m = 4;
    int** maze = new int* [n];
    for (int i = 0; i < n; ++i) {
        maze[i] = new int[m];
    }

    int mazeData[4][4] = {
        {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 0, 0, 0},
        {1, 1, 1, 0}
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            maze[i][j] = mazeData[i][j];
        }
    }

    bool result = isReachable(maze, n, m, 3, 3);  // Checking if rat can reach (3, 3)
    EXPECT_FALSE(result);  // Should return false because there's no valid path

    // Clean up dynamic memory
    for (int i = 0; i < n; ++i) {
        delete[] maze[i];
    }
    delete[] maze;
}

// Test case 3: Start and destination are the same
TEST(MazeSolverTest, StartEqualsDestination) {
    int n = 3, m = 3;
    int** maze = new int* [n];
    for (int i = 0; i < n; ++i) {
        maze[i] = new int[m];
    }

    int mazeData[3][3] = {
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            maze[i][j] = mazeData[i][j];
        }
    }

    bool result = isReachable(maze, n, m, 0, 0);  // Rat is already at the destination
    EXPECT_TRUE(result);  // Should return true since start equals destination

    // Clean up dynamic memory
    for (int i = 0; i < n; ++i) {
        delete[] maze[i];
    }
    delete[] maze;
}

// Test case 4: Fully blocked maze
TEST(MazeSolverTest, FullyBlockedMaze) {
    int n = 3, m = 3;
    int** maze = new int* [n];
    for (int i = 0; i < n; ++i) {
        maze[i] = new int[m];
    }

    int mazeData[3][3] = {
        {1, 0, 0},
        {0, 0, 0},
        {0, 0, 0}
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            maze[i][j] = mazeData[i][j];
        }
    }

    bool result = isReachable(maze, n, m, 2, 2);  // Checking if rat can reach (2, 2)
    EXPECT_FALSE(result);  // Should return false because the maze is blocked

    // Clean up dynamic memory
    for (int i = 0; i < n; ++i) {
        delete[] maze[i];
    }
    delete[] maze;
}

// Test case 5: Large maze with multiple paths
TEST(MazeSolverTest, LargeMazeMultiplePaths) {
    int n = 5, m = 5;
    int** maze = new int* [n];
    for (int i = 0; i < n; ++i) {
        maze[i] = new int[m];
    }

    int mazeData[5][5] = {
        {1, 1, 1, 0, 0},
        {0, 0, 1, 1, 1},
        {1, 1, 0, 0, 1},
        {1, 0, 0, 1, 1},
        {1, 1, 1, 1, 1}
    };

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            maze[i][j] = mazeData[i][j];
        }
    }

    bool result = isReachable(maze, n, m, 4, 4);  // Check if rat can reach (4, 4)
    EXPECT_TRUE(result);  // Should return true because there's a valid path

    // Clean up dynamic memory
    for (int i = 0; i < n; ++i) {
        delete[] maze[i];
    }
    delete[] maze;
}

//***************** Q2 Test cases *****************
//Simple stack
// Test case 1: Valid sequence of brackets
TEST(IsValidTest, ValidBrackets) {
    std::string input = "(){}[]";
    EXPECT_TRUE(isValid(input));  // Expected result is true for valid brackets
}

// Test case 2: Invalid sequence due to incorrect closing order
TEST(IsValidTest, InvalidBrackets_Order) {
    std::string input = "({[)]}";
    EXPECT_FALSE(isValid(input));  // Expected result is false for incorrect order of closing brackets
}

// Test case 3: Single unmatched opening bracket
TEST(IsValidTest, SingleUnmatchedOpeningBracket) {
    std::string input = "(";
    EXPECT_FALSE(isValid(input));  // Expected result is false since the opening bracket has no matching closing bracket
}

// Test case 4: Single unmatched closing bracket
TEST(IsValidTest, SingleUnmatchedClosingBracket) {
    std::string input = ")";
    EXPECT_FALSE(isValid(input));  // Expected result is false since there's no matching opening bracket for the closing bracket
}

// Test case 5: Nested valid brackets
TEST(IsValidTest, NestedValidBrackets) {
    std::string input = "{[()]}";
    EXPECT_TRUE(isValid(input));  // Expected result is true for correctly nested brackets
}

// Test case 6: Empty string (which is trivially valid)
TEST(IsValidTest, EmptyString) {
    std::string input = "";
    EXPECT_TRUE(isValid(input));  // Expected result is true since there are no brackets, which means the string is valid
}

// Test case 7: Complex valid bracket structure
TEST(IsValidTest, ComplexValidBrackets) {
    std::string input = "(({{[[]]}}))";
    EXPECT_TRUE(isValid(input));  // Expected result is true for a complex but valid structure
}

// Test case 8: String with non-bracket characters that should be ignored
TEST(IsValidTest, NonBracketCharacters) {
    std::string input = "(a + b) * {x - y} + [z]";
    EXPECT_TRUE(isValid(input));  // Non-bracket characters should be ignored, so the expected result is true
}

// Test case 9: Brackets without matching pairs
TEST(IsValidTest, UnmatchedBrackets) {
    std::string input = "[{]";
    EXPECT_FALSE(isValid(input));  // Expected result is false since there are unmatched brackets
}

