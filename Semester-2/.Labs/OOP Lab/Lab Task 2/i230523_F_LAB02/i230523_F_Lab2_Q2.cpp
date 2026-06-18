#include <iostream>

// Function to calculate grades
char* calculateGrades(int arr[], int size) {
    // Allocate memory for grades array
    char* grades = new char[size];

    // Loop through the array and assign grades based on marks
    for (int i = 0; i < size; ++i) {
        if (arr[i] >= 90 && arr[i] <= 100)
            grades[i] = 'A';
        else if (arr[i] >= 80 && arr[i] < 90)
            grades[i] = 'B';
        else if (arr[i] >= 70 && arr[i] < 80)
            grades[i] = 'C';
        else if (arr[i] >= 60 && arr[i] < 70)
            grades[i] = 'D';
        else if (arr[i] >= 0 && arr[i] < 60)
            grades[i] = 'F';
        else
            grades[i] = 'X'; // Invalid mark
    }

    return grades;
}

int main() {
    int size;
    std::cout << "Enter the size of the array: ";
    std::cin >> size;

    // Allocate memory for dynamic array
    int* marks = new int[size];

    std::cout << "Enter marks (0-100):" << std::endl;
    // Input marks from the user
    for (int i = 0; i < size; ++i) {
        std::cout << "Enter mark " << i + 1 << ": ";
        std::cin >> marks[i];
    }

    // Call the calculateGrades function
    char* grades = calculateGrades(marks, size);

    // Output grades
    std::cout << "Grades:" << std::endl;
    for (int i = 0; i < size; ++i) {
        std::cout << "Mark " << marks[i] << " : Grade " << grades[i] << std::endl;
    }

    // Free dynamically allocated memory
    delete[] marks;
    delete[] grades;

    return 0;
}
