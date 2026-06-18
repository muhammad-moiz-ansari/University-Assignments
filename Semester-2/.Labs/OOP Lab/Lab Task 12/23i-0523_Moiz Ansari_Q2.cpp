#include <iostream>
#include "23i-0523_Moiz Ansari_Q2.h"
using namespace std;

int main()
{
	string* facstr = new string[4]{ "HOD", "Lecturer", "LD","TA" };
	string* depstr = new string[4]{ "CS", "AI", "DS","CybSC" };
	int f, d;

	cout << "Choose one of the following:\n";
	cout << "1. HOD\n"
		<< "2. Lecturer\n"
		<< "3. LD\n"
		<< "4. TA\n";
	while (1)
	{
		cin >> f;
		if (f >= 1 && f <= 4)
			break;
		else
			cout << "\nChoose between 1 & 4: ";
	}

	cout << "Choose one of the following:\n";
	cout << "1. CS\n"
		<< "2. AI\n"
		<< "3. DS\n"
		<< "4. CybSc\n";
	while (1)
	{
		cin >> d;
		if (d >= 1 && d <= 4)
			break;
		else
			cout << "\nChoose between 1 & 4: ";
	}

	float grossp = 0, houser = 0, medall = 0;
	cout << "Enter Gross Pay: ";
	cin >> grossp;

	cout << "Enter House Rent: ";
	cin >> houser;

	cout << "Enter Medical Allowance: ";
	cin >> medall;

	Employee* emp = new Faculty(f, d, 1, grossp, houser, medall, 0);

	emp->calcSalary();

	return 0;
}