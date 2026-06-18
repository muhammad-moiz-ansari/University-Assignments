#include <iostream>
#include "23i-0523_Moiz Ansari_Q3.h"
using namespace std;

int main()
{
	int id = 0;
	string name = "";
	int h = 0;
	int s = 0;
	string p = "";

	Manager ali;
	cout << "\nEnter Employee Details:\n";
	cout << "Employee ID: ";
	cin >> id;
	cout << "Employee Name: ";
	cin >> name;
	cout << "Hours Worked: ";
	cin >> h;
	cout << "Position: ";
	cin >> p;

	ali.setEmpID(id);
	ali.setEmpName(name);
	ali.setHours(h);
	ali.setPosition(p);
	ali.calculateSalary();

	ali.Print_detail();

	return 0;
}