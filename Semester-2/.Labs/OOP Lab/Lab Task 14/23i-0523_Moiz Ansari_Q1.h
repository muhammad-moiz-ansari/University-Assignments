#pragma once
#include <iostream>
using namespace std;

class Employee
{
protected:
	int Emp_no;
	static int employee_num;

public:
	virtual int getSalary() = 0;
	virtual int getEmpNum() = 0;
};

int Employee::employee_num = 0;

class Driver : public virtual Employee
{
private:
	int salary;

public:
	Driver(int s=30000)
	{
		Emp_no = ++employee_num;
		salary = s;
	}

	int getSalary()
	{
		return salary;
	}

	int getEmpNum()
	{
		return Emp_no;
	}

};

class Developer : public virtual Employee
{
private:
	int salary;

public:
	Developer(int s=100000)
	{
		Emp_no = ++employee_num;
		salary = s;
	}

	int getSalary()
	{
		return salary;
	}

	int getEmpNum()
	{
		return Emp_no;
	}
};
