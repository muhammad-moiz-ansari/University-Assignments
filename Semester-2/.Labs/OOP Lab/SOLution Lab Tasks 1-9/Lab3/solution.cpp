// Function to calculate transpose of a 2D array using pointers
void transposeMatrix(int** matrix, int rows, int columns) {
    // Create a new matrix for the transpose
    int** transpose = new int*[columns];
    for (int i = 0; i < columns; ++i) {
        transpose[i] = new int[rows];
    }

    // Calculate transpose using pointers
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            transpose[j][i] = matrix[i][j];
        }
    }

    // Copy the transpose back to the original matrix
    for (int i = 0; i < columns; ++i) {
        for (int j = 0; j < rows; ++j) {
            matrix[i][j] = transpose[i][j];
        }
    }

    // Deallocate memory for the transpose matrix
    for (int i = 0; i < columns; ++i) {
        delete[] transpose[i];
    }
    delete[] transpose;
}


// Function to calculate the sum of each row and each column in a 2D array
void calculateRowColumnSums(int** matrix, int rows, int columns, int* rowSums, int* columnSums) {
    // Calculate row sums
    for (int i = 0; i < rows; ++i) {
        rowSums[i] = 0;
        for (int j = 0; j < columns; ++j) {
            rowSums[i] += matrix[i][j];
        }
    }

    // Calculate column sums
    for (int j = 0; j < columns; ++j) {
        columnSums[j] = 0;
        for (int i = 0; i < rows; ++i) {
            columnSums[j] += matrix[i][j];
        }
    }
}


// Function to find the maximum element in a dynamically allocated 2D array
int findMaxElement(int** matrix, int rows, int columns) {
    int maxElement = std::numeric_limits<int>::min(); // Initialize to the minimum possible value

    // Traverse the array using pointers and find the maximum element
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (matrix[i][j] > maxElement) {
                maxElement = matrix[i][j];
            }
        }
    }

    return maxElement;
}



// Function to search for and replace a value in a dynamically allocated 2D array
void searchAndReplace(int** matrix, int rows, int columns, int searchValue, int newValue) {
    // Traverse the array using pointers to search for the value
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            if (matrix[i][j] == searchValue) {
                // Replace the value with the new value
                matrix[i][j] = newValue;
            }
        }
    }
}


// Function to perform matrix multiplication
void multiplyMatrices(int** matrix1, int rows1, int columns1, int** matrix2, int rows2, int columns2, int** resultMatrix) {
    // Check if matrices can be multiplied
    if (columns1 != rows2) {
        std::cerr << "Error: Incompatible matrix dimensions for multiplication!" << std::endl;
        return;
    }

    // Perform matrix multiplication
    for (int i = 0; i < rows1; ++i) {
        for (int j = 0; j < columns2; ++j) {
            resultMatrix[i][j] = 0;
            for (int k = 0; k < columns1; ++k) {
                resultMatrix[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}


// Function to calculate the sum of matrix diagonals
int diagonalSum(int** mat, int size) {
    int sum = 0;

    // Include primary diagonal elements
    for (int i = 0; i < size; ++i) {
        sum += mat[i][i];
    }

    // Include secondary diagonal elements not part of the primary diagonal
    for (int i = 0; i < size; ++i) {
        if (i != size - 1 - i) {
            sum += mat[i][size - 1 - i];
        }
    }

    return sum;
}



// Function to construct a 2D array from a 1D array
int** construct2DArray(int* original, int m, int n) {
    if (m * n != sizeof(original) / sizeof(original[0])) {
        // Impossible to create a valid 2D array
        return nullptr;
    }

    int** result = new int*[m];
    int index = 0;

    for (int i = 0; i < m; ++i) {
        result[i] = new int[n];

        for (int j = 0; j < n; ++j) {
            result[i][j] = original[index++];
        }
    }

    return result;
}


// Function to count the number of negative numbers in a sorted matrix
int countNegatives(int** grid, int m, int n) {
    int count = 0;
    int row = 0;
    int col = n - 1;

    // Start from the top-right corner
    while (row < m && col >= 0) {
        if (grid[row][col] < 0) {
            // If the current element is negative, all elements to the left are also negative
            count += (m - row);
            col--;
        } else {
            // If the current element is non-negative, move down in the current column
            row++;
        }
    }

    return count;
}


// Function to set entire rows and columns to 0's in the matrix if an element is 0
void setZeroes(int** matrix, int m, int n) {
    std::vector<int> zeroRows(m, 0);
    std::vector<int> zeroCols(n, 0);

    // Find the rows and columns with 0 elements
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == 0) {
                zeroRows[i] = 1;
                zeroCols[j] = 1;
            }
        }
    }

    // Set entire rows to 0's
    for (int i = 0; i < m; ++i) {
        if (zeroRows[i] == 1) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = 0;
            }
        }
    }

    // Set entire columns to 0's
    for (int j = 0; j < n; ++j) {
        if (zeroCols[j] == 1) {
            for (int i = 0; i < m; ++i) {
                matrix[i][j] = 0;
            }
        }
    }
}