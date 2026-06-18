#include <iostream>
#include "23i-0523_Moiz Ansari_Q3.h"
using namespace std;

int main()
{
	int x1, y1,
		x2, y2;

	cout << "Enter x & y for Point 1: ";
	cin >> x1 >> y1;
	
	cout << "Enter x & y for Point 1: ";
	cin >> x2 >> y2;

	Point P1(x1, y1), P2;

	P2.setx(x2);
	P2.sety(y2);

	Line L(x1, y1, x2, y2);

	cout << endl;
	L.displayLine();

	double Slope;

	Slope = L.getSlope();

	cout << "Slope = " << Slope << endl;

	return 0;
}