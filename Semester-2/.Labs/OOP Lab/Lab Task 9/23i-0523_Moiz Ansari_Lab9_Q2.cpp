#include <iostream>
#include "23i-0523_Moiz Ansari_Q2.h"
using namespace std;

int main()
{
	Fraction a(1, 2), b(3 , 4), c, d(a), e(b);

	cin >> c;
	cout << endl << a << b << c;

	cout << (a == b) << endl << (a<b) << endl << (a>b) << endl;

	a + b;
	cout << "a = " << a;

	d - b;
	cout << "d = " << d;

	a * c;
	cout << "a = " << a;
}