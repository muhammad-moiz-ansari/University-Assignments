#include <iostream>
#include <cmath> // for abs() function

// Function to print spaces
void printSpaces(int num) {
    if (num <= 0)
        return;
    std::cout << " ";
    printSpaces(num - 1);
}

// Function to print stars
void printStars(int num) {
    if (num <= 0)
        return;
    std::cout << "* ";
    printStars(num - 1);
}

// Function to print upper half of diamond
void printUpperHalf(int n, int num) {
    if (n <= 0)
        return;
    printSpaces(num - abs(n));
    printStars(2 * n - 1);
    std::cout << std::endl;
    printUpperHalf(n - 1, num);
}

// Function to print lower half of diamond
void printLowerHalf(int n, int num) {
    if (n <= 1)
        return;
    printSpaces(num - abs(n));
    printStars(2 * n - 1);
    std::cout << std::endl;
    printLowerHalf(n - 1, num);
}

// Function to print diamond pattern
void diamond_pattern(int num) {
    // Print upper half
    printUpperHalf(num / 2 + 1, num);

    // Print middle line
    printStars(num);
    std::cout << std::endl;

    // Print lower half
    printLowerHalf(num / 2, num);
}

int main() {
    int n1 = 13;
    int n2 = 11;
    int n3 = 9;
    int n4 = 7;

    std::cout << "Diamond Pattern for n = 13:" << std::endl;
    diamond_pattern(n1);
    std::cout << std::endl;

    std::cout << "Diamond Pattern for n = 11:" << std::endl;
    diamond_pattern(n2);
    std::cout << std::endl;

    std::cout << "Diamond Pattern for n = 9:" << std::endl;
    diamond_pattern(n3);
    std::cout << std::endl;

    std::cout << "Diamond Pattern for n = 7:" << std::endl;
    diamond_pattern(n4);
    std::cout << std::endl;

    return 0;
}
