#include <iostream>
#include "23i-0523_Moiz Ansari_Q1.h"
using namespace std;

int main()
{
	Distance D1(15, 8);
	Distance D2(10, 7);
	Distance D3(D1);
	Distance D4(D2);
	Distance D5(D1);
	Distance D6(D2);

	Distance Addition;
	Addition = D3.addDistance(D4);
	D5.subDistance(D6);

	cout << "Sum: ";
	Addition.Display();

	cout << "Diff: ";
	D6.Display();

	return 0;
}