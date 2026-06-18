#pragma once
#include <iostream>
using namespace std;

class Person
{
protected:
	string name;
	string address;

public:
	Person(string n = "", string add = "")
	{
		name = n;
		address = add;
	}
	//Setters:
	void setName(string n)
	{
		name = n;
	}
	void setAddress(string add)
	{
		address = add;
	}

	//Getters:
	string getName()
	{
		return name;
	}
	string getAddress()
	{
		return address;
	}
};

class Employee : public Person
{
protected:
	int Employee_number;
	int Hours_worked;

public:
	Employee(int en = 0, int hw = 0)
	{
		Employee_number = en;
		Hours_worked = hw;
	}
	//Setters:
	void setEmployee_number(int en)
	{
		Employee_number = en;
	}
	void setHours_worked(int hw)
	{
		Hours_worked = hw;
	}
	//Getters:
	int getEmployee_number()
	{
		return Employee_number;
	}
	int getHours_worked()
	{
		return Hours_worked;
	}
};

class ProductionWorker : public Employee
{
protected:
	int Shift;
	double Hourly_pay_rate;
	double Salary;

public:
	ProductionWorker(int sh = 0, double hpr = 0, double s = 0)
	{
		Shift = sh;
		Hourly_pay_rate = hpr;
		Salary = s;
	}
	//Setters:
	void setShift(int sh)
	{
		Shift = sh;
	}
	void setHourly_pay_rate(double hpr)
	{
		Hourly_pay_rate = hpr;
	}
	void setSalary(double s)
	{
		Salary = s;
	}
	//Getters:
	int getShift()
	{
		return Shift;
	}
	double getHourly_pay_rate()
	{
		return Hourly_pay_rate;
	}
	double getSalary()
	{
		return Salary;
	}

	//Functions:
	double calculateSalary()
	{
		Salary = Hourly_pay_rate * Hours_worked;
		if (Shift == 2 && Hours_worked>5)
		{
			Salary += 1000;
		}
		return Salary;
	}
	void print_details()
	{
		cout << "\nEmployee Details:\n\n"
			<< "Name: " << name << endl
			<< "Address: " << address << endl
			<< "Employee Number: " << Employee_number << endl
			<< "Hours: " << Hours_worked << endl;
		cout << "Shift: ";
		if (Shift == 1)
			cout << "Day\n";
		else if (Shift == 2)
			cout << "Night\n";
		cout << "Pay Rate: " << Hourly_pay_rate << endl
			<< "Salary: " << Salary << endl;
	}
	void input()
	{
		cout << "\nEnter Employee Details:\n\n";
		cout << "Name: ";
		cin >> name;
		cout << "Address: ";
		cin >> address;
		cout << "Employee Number: ";
		cin >> Employee_number;
		cout << "Hours: ";
		cin >> Hours_worked;
		cout << "For Shift, select one of the following:\n"
			<< "1. Day\n2. Night\n"
			<< "Shift: ";
		while (1)
		{
			cin >> Shift;
			if (Shift == 1 || Shift == 2)
				break;
			else
				cout << "Choose only 1 or 2: ";
		}
		cout << "Pay Rate: ";
		cin >> Hourly_pay_rate;
	}
};