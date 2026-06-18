#include <iostream>

// Function to calculate the sum of digits at even and odd positions
void calculateSum(int num, int& evenSum, int& oddSum) {
    evenSum = 0;
    oddSum = 0;
    int position = 1;

    // Iterate through each digit in the number
    while (num > 0) {
        int digit = num % 10;
        if (position % 2 == 0) {
            evenSum += digit;
        }
        else {
            oddSum += digit;
        }
        num /= 10;
        position++;
    }
}

// Function to print numbers in the range [100, 999] with equal sums of digits at even and odd positions
void printNumbers() {
    for (int num = 100; num <= 999; num++) {
        int evenSum, oddSum;
        calculateSum(num, evenSum, oddSum);
        if (evenSum == oddSum) {
            std::cout << num << " ";
        }
    }
    std::cout << std::endl;
}

int main() {
    std::cout << "Numbers in the range [100, 999] with equal sums of digits at even and odd positions:" << std::endl;
    printNumbers();
    return 0;
}
