#pragma once
#include <iostream>
using namespace std;

class Person
{
protected:
	char name[10];
	char address[10];

public:
	Person()
	{
		name[0] = '\0';
		address[0] = '\0';
	}
	Person(string n, string add)
	{
		for (int i = 0; i < 10; ++i)
		{
			name[i] = n[i];

			if (name[i] == '\0')
				break;
		}
		for (int i = 0; i < 10; ++i)
		{
			address[i] = add[i];

			if (address[i] == '\0')
				break;
		}
	}
	
};

class Employee:public Person
{
protected:
	int Emp_no;
	float gross_pay;
	float house_rent;
	float medical_allow;
	float net_pay;

public:
	Employee(int empno = 0, float gp = 0, float hr = 0, float ma = 0, float np = 0)
	{
		Emp_no = empno;
		gross_pay = gp;
		house_rent = hr;
		medical_allow = ma;
		net_pay = np;
	}
	virtual void calcSalary()
	{
		net_pay = gross_pay - ((45 / 100) * gross_pay - (5 / 100) * gross_pay);
	}

};

class Faculty:public Employee
{
protected:
	string designation;
	string department;

public:
	const string* facstr = new string[4]{ "HOD", "Lecturer", "LD","TA" };
	const string* depstr = new string[4]{ "CS", "AI", "DS","CybSC" };

	Faculty()
	{
		designation[0] = '\0';
		department[0] = '\0';
	}

	Faculty(int f=0, int d=0, int empno = 0, float gp = 0, float hr = 0, float ma = 0, float np = 0)
	{
		designation = facstr[f - 1];
		department = depstr[d - 1];

		Emp_no = empno;
		gross_pay = gp;
		house_rent = hr;
		medical_allow = ma;
		net_pay = np;
	}
	virtual void calcSalary()
	{
		net_pay = gross_pay - ((45 / (double)100) * gross_pay - (5 / (double)100) * gross_pay);
		
		if (designation == "HOD")
		{
			net_pay += 1.75 * net_pay;
		}
		if (designation == "Lecturer")
		{
			net_pay += 1.25 * net_pay;
		}
		if (designation == "LD")
		{
			net_pay += 0.25 * net_pay;
		}
		if (designation == "TA")
		{
			net_pay += 0.15 * net_pay;
		}

		cout << "\nSalary = Rs. " << net_pay << endl;
	}
};