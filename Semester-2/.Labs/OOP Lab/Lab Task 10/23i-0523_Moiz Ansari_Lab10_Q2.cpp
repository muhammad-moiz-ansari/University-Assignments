#include <iostream>
#include "23i-0523_Moiz Ansari_Q2.h"
using namespace std;

int main()
{
	string uni_n, dept_n;
	int uni_s, dept_id;
	cout << "Enter Uni Name & Size: ";
	cin >> uni_n >> uni_s;

	University uni1(uni_n, uni_s, NULL);

	cout << "Enter Dept Name & ID: ";
	cin >> dept_n;

	uni1.addDepartment(dept_n, 30, NULL);
	uni1.Display();

	uni1.updateDepartment(30, "Computer Science");
	uni1.Display();
}