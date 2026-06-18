#include <iostream>

// Recursive function to calculate Fibonacci number at index n
int fibonacci(int n) {
    // Base case: if n is 0 or 1, return n
    if (n == 0 || n == 1) {
        return n;
    }

    // Recursive call to calculate Fibonacci number at index n-1 and n-2
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    // Test cases
    int index1 = 4;
    int index2 = 6;

    // Calculate Fibonacci numbers for the given indices
    int result1 = fibonacci(index1);
    int result2 = fibonacci(index2);

    // Output the results
    std::cout << "fibonacci(" << index1 << ") = " << result1 << std::endl;
    std::cout << "fibonacci(" << index2 << ") = " << result2 << std::endl;

    return 0;
}
