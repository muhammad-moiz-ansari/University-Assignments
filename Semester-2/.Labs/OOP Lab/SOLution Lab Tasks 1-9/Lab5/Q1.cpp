#include <iostream>

// Define the Complex structure
struct Complex {
    int real;
    int imaginary;

    // Member function to add two complex numbers
    Complex addComplex(Complex c1, Complex& c2) {
        Complex result;
        result.real = c1.real + c2.real;
        result.imaginary = c1.imaginary + c2.imaginary;
        return result;
    }
};

int main() {
    // Create two Complex objects
    Complex c1 = { 5, 3 };
    Complex c2 = { 4, 2 };

    // Call the addComplex function
    Complex result = c1.addComplex(c1, c2);

    // Output the result
    std::cout << "Sum: " << result.real << " + " << result.imaginary << "i" << std::endl;

    return 0;
}
