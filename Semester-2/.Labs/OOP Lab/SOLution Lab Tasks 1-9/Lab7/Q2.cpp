#include <iostream>

class Circle {
private:
    int radius;
    static int countOfCircles;

public:
    // Default constructor
    Circle() {
        radius = 0;
        countOfCircles++;
    }

    // Parameterized constructor
    Circle(int r) {
        radius = r;
        countOfCircles++;
    }

    // Destructor
    ~Circle() {
        countOfCircles--;
    }

    // Getter and setter methods
    int getRadius() const {
        return radius;
    }

    void setRadius(int r) {
        radius = r;
    }

    // Static member function for countOfCircles
    static int getCountOfCircles() {
        return countOfCircles;
    }

    // Function to compute area of circle
    double getArea() const {
        return 3.14 * radius * radius;
    }

    // Function to compute perimeter of circle
    double getPerimeter() const {
        return 2 * 3.14 * radius;
    }
};

int Circle::countOfCircles = 0;

int main() {
    std::cout << "CountOfCircles = " << Circle::getCountOfCircles() << std::endl;

    // Example 1
    std::cout << "Example 1:" << std::endl;
    Circle* circle1 = new Circle(6);
    std::cout << "- Radius = " << circle1->getRadius() << std::endl;
    std::cout << "- Area = " << circle1->getArea() << std::endl;
    std::cout << "- Perimeter = " << circle1->getPerimeter() << std::endl;

    // Example 2
    std::cout << "\nExample 2:" << std::endl;
    Circle* circle2 = new Circle();
    circle2->setRadius(10);
    std::cout << "- Radius = " << circle2->getRadius() << std::endl;
    std::cout << "- Area = " << circle2->getArea() << std::endl;
    std::cout << "- Perimeter = " << circle2->getPerimeter() << std::endl;

    // Example 3
    std::cout << "\nExample 3:" << std::endl;
    Circle* circle3 = new Circle(12.5);
    std::cout << "- Radius = " << circle3->getRadius() << std::endl;
    std::cout << "- Area = " << circle3->getArea() << std::endl;
    std::cout << "- Perimeter = " << circle3->getPerimeter() << std::endl;

    std::cout << "\nCountOfCircles = " << Circle::getCountOfCircles() << std::endl;

    // Deallocate memory and delete all objects
    delete circle1;
    delete circle2;
    delete circle3;

    std::cout << "CountOfCircles = " << Circle::getCountOfCircles() << std::endl;

    return 0;
}
