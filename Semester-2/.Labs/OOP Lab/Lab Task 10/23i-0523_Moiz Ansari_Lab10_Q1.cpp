#include <iostream>
#include "23i-0523_Moiz Ansari_Q1.h"
using namespace std;

int main()
{
	Line L(1, 5, 10, 15);
	Point M;
	float Slope = 0, Length = 0;

	Slope = L.findSlope();
	Length = L.findLength();
	M = L.findMidPoint();

	cout << "Slope = " << Slope << endl
		<< "Length = " << Length << endl
		<< "Mid-Point = " << M << endl;
}