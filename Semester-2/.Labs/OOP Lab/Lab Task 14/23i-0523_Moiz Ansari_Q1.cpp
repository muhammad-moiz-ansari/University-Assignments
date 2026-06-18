#include <iostream>
#include "23i-0523_Moiz Ansari_Q1.h"
using namespace std;

int main()
{
	int sdvr = 0, sdev = 0;

	cout << "Enter salary of driver and developer: \n";
	cin >> sdvr >> sdev;
	cout << endl;

	Employee* emp = new Driver(sdvr);

	cout << "Driver Employee Number: " << emp->getEmpNum() << endl
		<< "Driver Salary: " << emp->getSalary() << endl;

	emp = new Developer(sdev);

	cout << "Developer Employee Number: " << emp->getEmpNum() << endl
		<< "Developer Salary: " << emp->getSalary() << endl;


	return 0;
}
