#include <iostream>

class Rectangle {
private:
    int length;
    int width;

public:
    // Default constructor
    Rectangle() {
        length = 0;
        width = 0;
    }

    // Parameterized constructor
    Rectangle(int l, int w) {
        length = l;
        width = w;
    }

    // Setter methods
    void setLength(int l) {
        length = l;
    }

    void setWidth(int w) {
        width = w;
    }

    // Getter methods
    int getLength() {
        return length;
    }

    int getWidth() {
        return width;
    }

    // Function to compute the area of the rectangle
    int calArea() {
        return length * width;
    }

    // Function to compute the perimeter of the rectangle
    int calPerimeter() {
        return 2 * (length + width);
    }
};

int main() {
    // Example 1: Use Parameterized Constructor
    Rectangle rect1(2, 5);
    std::cout << "Example 1:" << std::endl;
    std::cout << "Use Parameterized Constructor to assign the values" << std::endl;
    std::cout << "Length = " << rect1.getLength() << ", Width = " << rect1.getWidth() << std::endl;
    std::cout << "Area = " << rect1.calArea() << std::endl;
    std::cout << "Perimeter = " << rect1.calPerimeter() << std::endl;

    // Example 2: Use setters to assign the values
    Rectangle rect2;
    rect2.setLength(14);
    rect2.setWidth(17);
    std::cout << "\nExample 2:" << std::endl;
    std::cout << "Use setters to assign the values" << std::endl;
    std::cout << "Length = " << rect2.getLength() << ", Width = " << rect2.getWidth() << std::endl;
    std::cout << "Area = " << rect2.calArea() << std::endl;
    std::cout << "Perimeter = " << rect2.calPerimeter() << std::endl;

    return 0;
}
