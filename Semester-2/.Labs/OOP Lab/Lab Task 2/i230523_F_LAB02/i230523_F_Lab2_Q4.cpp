#include <iostream>
#include <cstdlib> // for rand() and srand()
#include <ctime> // for time()

// Function to initialize arrays with random values and store their starting addresses in array of pointers
int* sumArray(int** arr) {
    // Seed the random number generator
    srand(time(nullptr));

    // Define and initialize five arrays of size 6
    int arr1[6], arr2[6], arr3[6], arr4[6], arr5[6];

    // Array of pointers to store starting addresses of the arrays
    arr[0] = arr1;
    arr[1] = arr2;
    arr[2] = arr3;
    arr[3] = arr4;
    arr[4] = arr5;

    // Initialize each array with random values
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 6; ++j) {
            arr[i][j] = rand() % 100; // Generate random numbers in the range 0-99
        }
    }

    // Return pointer to the first array
    return arr1;
}

int main() {
    // Array of pointers
    int* p[5];

    // Call the function to initialize arrays and store their starting addresses
    int* firstArray = sumArray(p);

    // Display sum of each individual array
    for (int i = 0; i < 5; ++i) {
        int sum = 0;
        for (int j = 0; j < 6; ++j) {
            sum += p[i][j];
        }
        std::cout << "Sum of array " << i + 1 << ": " << sum << std::endl;
    }

    return 0;
}
