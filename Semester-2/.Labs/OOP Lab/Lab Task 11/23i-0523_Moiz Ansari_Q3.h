#pragma once
#include <iostream>
using namespace std;

class Employee
{
protected:
	int EmpID;
	string EmpName;
	int hours;
	int salary;
	string position;

public:
	Employee(int id = 0, string name = "", int h = 0, int s = 0, string p = "")
	{
		EmpID = id;
		EmpName = name;
		hours = h;
		salary = s;
		position = p;
	}
	//Setters:
	void setEmpID(int id)
	{
		EmpID=id;
	}
	void setEmpName(string n)
	{
		EmpName=n;
	}
	void setHours(int h)
	{
		hours=h;
	}
	void setSalary(int s)
	{
		salary=s;
	}
	void setPosition(string p)
	{
		position=p;
	}
	//Getters:
	int getEmpID()
	{
		return EmpID;
	}
	string getEmpName()
	{
		return EmpName;
	}
	int getHours()
	{
		return hours;
	}
	int getSalary()
	{
		return salary;
	}
	string getPosition()
	{
		return position;
	}
};
class Manager: public Employee
{
protected:
	int work_hr_rate=2000;

public:
	void calculateSalary()
	{
		salary = hours * work_hr_rate;
	}
	void Print_detail()
	{
		cout << "\nEmployee Details:\n"
			<< "Employee ID: " << EmpID << endl
			<< "Employee Name: " << EmpName << endl
			<< "Hours Worked: " << hours << endl
			<< "Salary: " << salary << endl
			<< "Position: " << position << endl;
	}
};
	
class TeamLead : public Employee
{
protected:
	int work_hr_rate=2200;

public:
	void calculateSalary()
	{
		salary = hours * work_hr_rate;
	}
	void Print_detail()
	{ 
		cout << "\nEmployee Details:\n"
			<< "Employee ID: " << EmpID << endl
			<< "Employee Name: " << EmpName << endl
			<< "Hours Worked: " << hours << endl
			<< "Salary: " << salary << endl
			<< "Position: " << position << endl;
	}
};
	
class Developers : public Employee
{
protected:
	int work_hr_rate=1800;

public:
	void calculateSalary()
	{
		salary = hours * work_hr_rate;
	}
	void Print_detail()
	{
		cout << "\nEmployee Details:\n"
			<< "Employee ID: " << EmpID << endl
			<< "Employee Name: " << EmpName << endl
			<< "Hours Worked: " << hours << endl
			<< "Salary: " << salary << endl
			<< "Position: " << position << endl;
	}
};