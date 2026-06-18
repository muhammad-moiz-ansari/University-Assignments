#include <iostream>

int* sortArray(int* arr, int size) {
    // Initialize pointers for the start and end of the array
    int* start = arr;
    int* end = arr + size - 1;

    while (start < end) {
        // Move start pointer until it points to an even number
        while (*start % 2 != 0 && start < end) {
            start++;
        }
        // Move end pointer until it points to an odd number
        while (*end % 2 == 0 && start < end) {
            end--;
        }
        // Swap the odd and even numbers
        if (start < end) {
            int temp = *start;
            *start = *end;
            *end = temp;
        }
    }
    return arr;
}

int main() {
    int arr[] = { 6, 3, 1, 2, 7, 5, 9, 4 };
    int size = sizeof(arr) / sizeof(arr[0]);

    // Call sortArray function
    int* sortedArr = sortArray(arr, size);

    // Output the sorted array
    std::cout << "Sorted Array: ";
    for (int i = 0; i < size; ++i) {
        std::cout << sortedArr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}
