#include <iostream>

// Recursive function to print the pattern
void printPattern(int n) {
    // Base case: if n is less than 1, return
    if (n < 1) {
        return;
    }

    // Print stars for the current line
    for (int i = 0; i < n; ++i) {
        std::cout << "* ";
    }
    std::cout << std::endl;

    // Recursive call to print the pattern for n-1
    printPattern(n - 1);

    // Print stars for the current line again after recursion
    for (int i = 0; i < n; ++i) {
        std::cout << "* ";
    }
    std::cout << std::endl;
}

int main() {
    int input;
    std::cout << "Enter a number: ";
    std::cin >> input;

    // Call the recursive function to print the pattern
    printPattern(input);

    return 0;
}
