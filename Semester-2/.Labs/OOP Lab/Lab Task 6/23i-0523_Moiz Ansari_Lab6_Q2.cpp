#include <iostream>
#include "23i-0523_Moiz Ansari_Q2.h"

using namespace std;


int main()
{
	double r1, i1,
		r2, i2;

	cout << "Input real and imaginary values for C1: ";
	cin >> r1 >> i1;

	cout << "Input real and imaginary values for C2: ";
	cin >> r2 >> i2;

	Complex C2, add, sub, mul;

	Complex C1(r1, i1);
	
	//C1.setReal(r1);
	//C1.setImaginary(i1);

	C2.setReal(r2);
	C2.setImaginary(i2);

	C1.display();
	C2.display();

	cout << endl;

	add = C1.addComplex(C2);
	sub = C1.subComplex(C2);
	mul = C1.mulComplex(C2);

	cout << "Sum = ";
	add.display();

	cout << "Difference = ";
	sub.display();

	cout << "Product = ";
	mul.display();

	return 0;
}