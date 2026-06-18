#include <iostream>

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

class Fraction {
private:
    int numerator;
    int denominator;

public:
    // Default Constructor
    Fraction() : numerator(0), denominator(1) {}

    // Parameterized Constructor
    Fraction(int num, int denom) : numerator(num), denominator(denom) {
        // Simplify the fraction
        int divisor = gcd(numerator, denominator);
        numerator /= divisor;
        denominator /= divisor;
    }

    // Equality operator (==)
    bool operator==(const Fraction& other) const {
        return (numerator == other.numerator) && (denominator == other.denominator);
    }

    // Greater than operator (>)
    bool operator>(const Fraction& other) const {
        return (numerator * other.denominator) > (other.numerator * denominator);
    }

    // Less than operator (<)
    bool operator<(const Fraction& other) const {
        return (numerator * other.denominator) < (other.numerator * denominator);
    }

    // Input stream operator (>>)
    friend std::istream& operator>>(std::istream& is, Fraction& fraction) {
        char slash;
        is >> fraction.numerator >> slash >> fraction.denominator;
        return is;
    }

    // Output stream operator (<<)
    friend std::ostream& operator<<(std::ostream& os, const Fraction& fraction) {
        os << fraction.numerator << "/" << fraction.denominator;
        return os;
    }

    // Addition operator (+)
    Fraction operator+(const Fraction& other) const {
        int num = numerator * other.denominator + other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    // Subtraction operator (-)
    Fraction operator-(const Fraction& other) const {
        int num = numerator * other.denominator - other.numerator * denominator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }

    // Multiplication operator (*)
    Fraction operator*(const Fraction& other) const {
        int num = numerator * other.numerator;
        int denom = denominator * other.denominator;
        return Fraction(num, denom);
    }
};

int main() {
    Fraction f1(1, 2);
    Fraction f2(2, 3);

    std::cout << "f1: " << f1 << std::endl;
    std::cout << "f2: " << f2 << std::endl;

    Fraction sum = f1 + f2;
    std::cout << "Sum: " << sum << std::endl;

    Fraction difference = f1 - f2;
    std::cout << "Difference: " << difference << std::endl;

    Fraction product = f1 * f2;
    std::cout << "Product: " << product << std::endl;

    return 0;
}
