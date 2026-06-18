#include <iostream>

class Complex {
private:
    double real;
    double imaginary;

public:
    // Default constructor
    Complex() {
        real = 0.0;
        imaginary = 0.0;
    }

    // Parameterized constructor
    Complex(double r, double i) {
        real = r;
        imaginary = i;
    }

    // Getter and setter methods for real and imaginary parts
    void setReal(double r) {
        real = r;
    }

    double getReal() {
        return real;
    }

    void setImaginary(double i) {
        imaginary = i;
    }

    double getImaginary() {
        return imaginary;
    }

    // Display the complex number
    void display() {
        std::cout << real << (imaginary >= 0 ? "+" : "") << imaginary << "i" << std::endl;
    }

    // Add two complex numbers
    Complex addComplex(Complex& c1) {
        Complex result;
        result.real = real + c1.real;
        result.imaginary = imaginary + c1.imaginary;
        return result;
    }

    // Subtract two complex numbers
    Complex subComplex(Complex& c1) {
        Complex result;
        result.real = real - c1.real;
        result.imaginary = imaginary - c1.imaginary;
        return result;
    }

    // Multiply two complex numbers
    Complex mulComplex(Complex& c1) {
        Complex result;
        result.real = (real * c1.real) - (imaginary * c1.imaginary);
        result.imaginary = (real * c1.imaginary) + (imaginary * c1.real);
        return result;
    }
};

int main() {
    // Example 1: Use Parameterized Constructor
    Complex c1(3, 2);
    Complex c2(1, 1);
    std::cout << "Example 1:" << std::endl;
    std::cout << "Use Parameterized Constructor to assign the values" << std::endl;
    std::cout << "C1 = ";
    c1.display();
    std::cout << "C2 = ";
    c2.display();
    Complex addition = c1.addComplex(c2);
    std::cout << "Addition = ";
    addition.display();
    Complex subtraction = c1.subComplex(c2);
    std::cout << "Subtraction = ";
    subtraction.display();
    Complex multiplication = c1.mulComplex(c2);
    std::cout << "Multiplication = ";
    multiplication.display();

    // Example 2: Use setters to assign the values
    Complex c3, c4;
    c3.setReal(4);
    c3.setImaginary(-5);
    c4.setReal(-7);
    c4.setImaginary(2);
    std::cout << "\nExample 2:" << std::endl;
    std::cout << "Use setters to assign the values" << std::endl;
    std::cout << "C1 = ";
    c3.display();
    std::cout << "C2 = ";
    c4.display();
    addition = c3.addComplex(c4);
    std::cout << "Addition = ";
    addition.display();
    subtraction = c3.subComplex(c4);
    std::cout << "Subtraction = ";
    subtraction.display();
    multiplication = c3.mulComplex(c4);
    std::cout << "Multiplication = ";
    multiplication.display();

    return 0;
}
