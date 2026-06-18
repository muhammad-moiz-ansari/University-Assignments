#include <iostream>

// Function to reverse the elements of an array within a specified range
void reverse(int* arr, int start, int end) {
    while (start < end) {
        // Swap elements at start and end indices
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        // Move start index towards end and end index towards start
        start++;
        end--;
    }
}

// Function to rotate the array to the right by 'n' times
void rotateArray(int* arr, int sizeofArray, int n, int m) {
    // Calculate the size of each part
    int partSize = sizeofArray / m;

    // Rotate each part individually
    for (int i = 0; i < m; ++i) {
        int start = i * partSize;
        int end = start + partSize - 1;

        // Reverse the current part
        reverse(arr, start, end);

        // Rotate the reversed part by 'n' times
        reverse(arr, start, start + n - 1);
        reverse(arr, start + n, end);
    }
}

int main() {
    int arr[] = { 1, 2, 3, 4, 5, 6 };
    int size = sizeof(arr) / sizeof(arr[0]);
    int n = 2; // Number of shifts
    int m = 2; // Number of parts

    // Call rotateArray function
    rotateArray(arr, size, n, m);

    // Output the rotated array
    std::cout << "Rotated Array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
