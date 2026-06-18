#include <iostream>
#include "23i-0523_Moiz Ansari_Q1.h"

using namespace std;


int main()
{
	int l, w;

	Rectangle rect;

	cout << "Input Length: ";
	cin >> l;
	rect.setLength(l);

	cout << "Input Width:";
	cin >> w;
	rect.setWidth(w);

	cout << "Length = " << rect.getLength() << endl;

	cout << "Width = " << rect.getWidth() << endl;

	cout << "Area = " << rect.calArea() << endl;

	cout << "Parameter = " << rect.calPerimeter() << endl;
}