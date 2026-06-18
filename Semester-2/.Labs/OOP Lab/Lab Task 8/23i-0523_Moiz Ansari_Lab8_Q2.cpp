#include <iostream>
#include "23i-0523_Moiz Ansari_Q2.h"
using namespace std;

int main()
{
	Polynomial P1(2, 1, -1);
	Polynomial P2(5, -7, 3);
	Polynomial P3, P4, P5;
	string p1, p2, p3, p4, p5;

	p1 = string(P1);
	cout << "P1:\n"<<p1<<endl;

	p2 = string(P2);
	cout << "P2:\n" << p2<<endl;

	p3 = string(P1 + P2);
	cout << "P3:\n" << p3 << endl;

	p4 = string(P1 - P2);
	cout << "P4:\n" << p4 << endl;

	int d = 5;
	p5 = string(P1 * d);
	cout << "P5:\n" << p5 << endl;

	cout << "P1 == P2" << endl << (P1 == P2);

	return 0;
}