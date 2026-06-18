#include <iostream>

class Polynomial {
private:
    int coeffX2; // Coefficient of X^2
    int coeffX;  // Coefficient of X
    double constTerm; // Constant term

public:
    // Default Constructor
    Polynomial() : coeffX2(0), coeffX(0), constTerm(0.0) {}

    // Parameterized Constructor
    Polynomial(int a, int b, double c) : coeffX2(a), coeffX(b), constTerm(c) {}

    // Function to set coefficients
    void setCoefficients(int a, int b, double c) {
        coeffX2 = a;
        coeffX = b;
        constTerm = c;
    }

    // Function to get coefficient of X^2
    int getCoeffX2() const {
        return coeffX2;
    }

    // Function to get coefficient of X
    int getCoeffX() const {
        return coeffX;
    }

    // Function to get constant term
    double getConstTerm() const {
        return constTerm;
    }

    // Overload addition operator
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        result.coeffX2 = coeffX2 + other.coeffX2;
        result.coeffX = coeffX + other.coeffX;
        result.constTerm = constTerm + other.constTerm;
        return result;
    }

    // Overload subtraction operator
    Polynomial operator-(const Polynomial& other) const {
        Polynomial result;
        result.coeffX2 = coeffX2 - other.coeffX2;
        result.coeffX = coeffX - other.coeffX;
        result.constTerm = constTerm - other.constTerm;
        return result;
    }

    // Overload output operator <<
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
        os << poly.coeffX2 << "x^2 + " << poly.coeffX << "x + " << poly.constTerm;
        return os;
    }
};

int main() {
    // Create two Polynomial objects
    Polynomial P1(2, 1, -1); // 2x^2 + x - 1
    Polynomial P2(5, -7, 3); // 5x^2 - 7x + 3

    std::cout << "P1: " << P1 << std::endl;
    std::cout << "P2: " << P2 << std::endl;

    // Perform addition
    Polynomial sum = P1 + P2;
    std::cout << "Sum: " << sum << std::endl;

    // Perform subtraction
    Polynomial diff = P1 - P2;
    std::cout << "Difference: " << diff << std::endl;

    return 0;
}
