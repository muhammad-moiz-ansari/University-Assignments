#include <iostream>

class Money {
private:
    int dollars;
    int cents;

public:
    // Default Constructor
    Money() : dollars(0), cents(0) {}

    // Parameterized Constructor
    Money(int dollar, int cent) : dollars(dollar), cents(cent) {}

    // Overload + operator
    Money operator+(const Money& obj) {
        Money result;
        result.dollars = dollars + obj.dollars;
        result.cents = cents + obj.cents;
        if (result.cents >= 100) {
            result.dollars++;
            result.cents -= 100;
        }
        return result;
    }

    // Overload - operator
    Money operator-(const Money& obj) {
        Money result;
        result.dollars = dollars - obj.dollars;
        result.cents = cents - obj.cents;
        if (result.cents < 0) {
            result.dollars--;
            result.cents += 100;
        }
        return result;
    }

    // Overload = operator
    const Money operator=(const Money& obj) {
        dollars = obj.dollars;
        cents = obj.cents;
        return *this;
    }

    // Overload pre increment operator
    Money& operator++() {
        dollars++;
        return *this;
    }

    // Overload post increment operator
    Money operator++(int x) {
        Money temp = *this;
        ++(*this);
        return temp;
    }

    // Overload pre decrement operator
    Money& operator--() {
        dollars--;
        return *this;
    }

    // Overload post decrement operator
    Money operator--(int x) {
        Money temp = *this;
        --(*this);
        return temp;
    }

    // Overload != operator
    bool operator!=(const Money& right) {
        return (dollars != right.dollars || cents != right.cents);
    }

    // Friend function to overload input operator >>
    friend std::istream& operator>>(std::istream& in, Money& obj);

    // Friend function to overload output operator <<
    friend std::ostream& operator<<(std::ostream& out, const Money& obj);
};

// Overload input operator >>
std::istream& operator>>(std::istream& in, Money& obj) {
    std::cout << "Enter dollars: ";
    in >> obj.dollars;
    std::cout << "Enter cents: ";
    in >> obj.cents;
    return in;
}

// Overload output operator <<
std::ostream& operator<<(std::ostream& out, const Money& obj) {
    out << "Dollars: " << obj.dollars << ", Cents: " << obj.cents;
    return out;
}

int main() {
    Money M1(12, 95); // Using parameterized constructor
    Money M2; // Default constructor
    std::cin >> M2; // Using input operator (istream)

    std::cout << "M1: " << M1 << std::endl;
    std::cout << "M2: " << M2 << std::endl;

    Money sum = M1 + M2;
    std::cout << "Sum: " << sum << std::endl;

    Money difference = M1 - M2;
    std::cout << "Difference: " << difference << std::endl;

    Money temp = M1;
    M1 = M2;
    std::cout << "M1 after assignment: " << M1 << std::endl;
    std::cout << "M2 before assignment: " << M2 << std::endl;

    ++M1; // Pre increment
    std::cout << "M1 after pre-increment: " << M1 << std::endl;

    M2++; // Post increment
    std::cout << "M2 after post-increment: " << M2 << std::endl;

    --M1; // Pre decrement
    std::cout << "M1 after pre-decrement: " << M1 << std::endl;

    M2--; // Post decrement
    std::cout << "M2 after post-decrement: " << M2 << std::endl;

    if (M1 != temp) {
        std::cout << "M1 is not equal to temp" << std::endl;
    }

    return 0;
}
