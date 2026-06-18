#include <iostream>
#include "23i-0523_Moiz Ansari_Q1.h"
using namespace std;

int main()
{
	cout << "Shape:\n";
	Shape *shape=new Shape("Shape", 0);
	shape->area();
	shape->Display();
	delete shape;

	cout << "\nRectangle:\n";
	shape = new Rectangle("Rectangle", 3.2, 1.2);
	shape->area();
	shape->Display();
	delete shape;

	cout << "\nTriangle:\n";
	shape = new Triangle("Triangle", 2.1, 3.5);
	shape->area();
	shape->Display();
	delete shape;

	cout << "\nCircle:\n";
	shape = new Circle("Circle", 3.2);
	shape->area();
	shape->Display();
	delete shape;

	return 0;
}