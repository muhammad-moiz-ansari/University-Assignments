#include <iostream>
#include <cmath>

class Point {
private:
    int x;
    int y;

public:
    // Default constructor
    Point() {
        x = 0;
        y = 0;
    }

    // Parameterized constructor
    Point(int a, int b) {
        x = a;
        y = b;
    }

    // Getter and setter methods for x and y coordinates
    int getx() {
        return x;
    }

    int gety() {
        return y;
    }

    void setx(int a) {
        x = a;
    }

    void sety(int b) {
        y = b;
    }

    // Display function to display the x and y coordinates
    void display() {
        std::cout << "(" << x << ", " << y << ")";
    }
};

class Line {
private:
    Point P1;
    Point P2;

public:
    // Parameterized constructor
    Line(Point& p1, Point& p2) {
        P1 = p1;
        P2 = p2;
    }

    // Alternative parameterized constructor
    Line(int x1, int y1, int x2, int y2) : P1(x1, y1), P2(x2, y2) {}

    // Getter methods for endpoints P1 and P2
    Point getP1() {
        return P1;
    }

    Point getP2() {
        return P2;
    }

    // Function to calculate the slope of the line
    double getSlope() {
        int x1 = P1.getx();
        int y1 = P1.gety();
        int x2 = P2.getx();
        int y2 = P2.gety();

        if (x2 - x1 == 0) {
            return INFINITY; // Vertical line, slope is undefined
        }
        else {
            return static_cast<double>(y2 - y1) / (x2 - x1);
        }
    }

    // Function to display the endpoints of the line
    void displayLine() {
        std::cout << "P1 = ";
        P1.display();
        std::cout << ", P2 = ";
        P2.display();
        std::cout << std::endl;
    }
};

int main() {
    // Example 1
    Point p1(1, 2), p2(5, 11);
    Line line1(p1, p2);
    std::cout << "Example 1:" << std::endl;
    std::cout << "- ";
    line1.displayLine();
    std::cout << "- Slope= " << line1.getSlope() << std::endl;

    // Example 2
    Point p3(3, -4), p4(-9, -7);
    Line line2(p3, p4);
    std::cout << "\nExample 2:" << std::endl;
    std::cout << "- ";
    line2.displayLine();
    std::cout << "- Slope= " << line2.getSlope() << std::endl;

    return 0;
}
