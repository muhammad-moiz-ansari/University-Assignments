#include <iostream>
#include "23i-0523_Moiz Ansari_Q1.h"
using namespace std;

int main()
{
	Money M1(12, 95);
	Money M2, M3, M4, M6;
	cin >> M2;

	cout << "M1:\n";
	cout<<M1;
	cout << "M2:\n";
	cout<<M2;

	M3 = M1 + M2;
	cout << "M1 + M2:\n";
	cout<<M3;

	M4 = M1 - M2;
	cout << "M1 - M2:\n";
	cout << M4;

	Money M5(2, 10);
	cout << "M5:\n" << M5;

	M6 = M5++;
	cout << "M5:\n" << M5;
	cout << "M6:\n" << M6;

	cout << "M1 != M2" <<endl << (M1 != M2);



	return 0;
}