#pragma once
#include <iostream>
using namespace std;

int total = 0;

class Professor
{
	string name;
	int employeeID;
	string designation;

public:
	Professor(string n = "", int e = 0, string des = "")
	{
		name = n;
		employeeID = e;
		designation = des;
	}
	//Setters:
	void setName(string n)
	{
		name = n;
	}
	void setEmployeeID(int emp)
	{
		employeeID = emp;
	}
	void setDesignation(string des)
	{
		designation = des;
	}

	//Getters:
	string getName()
	{
		return name;
	}
	int getEmployeeID()
	{
		return employeeID;
	}
	string getDesignation()
	{
		return designation;
	}
	int getTotal()
	{
		return total;
	}
};
//int Professor::total = 0;

class Department
{
	string name;
	int deptID;
	Professor* professor;

public:
	Department(string n="", int dept=0, Professor* ptr=NULL)
	{
		name = n;
		deptID = dept;
		professor = ptr;
	}
	//Setters:
	void setName(string n)
	{
		name = n;
	}
	void setDeptID(int dept)
	{
		deptID = dept;
	}
	void setProfessor(Professor* ptr)
	{
		professor = ptr;
	}

	//Getters:
	string getName()
	{
		return name;
	}
	int getDeptID()
	{
		return deptID;
	}
	Professor* getProfessor()
	{
		return professor;
	}
};

class University
{
	string name;
	int size;
	int pos;
	Department* department;

public:
	University(string n = "", int s = 0, Department* d = NULL)
	{
		name = n;
		size = s;
		d = new Department[s]();
		pos = 0;
		department = d;
	}
	//Setters:
	void setName(string n)
	{
		name = n;
	}
	void setDepartment(Department* ptr)
	{
		department = ptr;
	}

	//Getters:
	string getName()
	{
		return name;
	}
	Department* getDepartment()
	{
		return department;
	}

	//Department& operator=(Department& dep)
	//{
	//	/*int s = size;

	//	name = uni.name;
	//	size = uni.size;*/
	//	delete department;
	//	department = new Department[size]();

	//	for (int i = 0; i < s; ++i)
	//	{
	//		department[i].setDeptID(dep.getDeptID());
	//		department[i].setName(dep.getName());
	//		department[i].setProfessor(dep.getProfessor());
	//	}
	//	delete[] dep;
	//}

	//Functions:
	bool addDepartment(string n="", int dept=0, Professor* prof=NULL)
	{
		if (pos < size)
		{
			++pos;

			department[pos].setName(n);
			department[pos].setDeptID(dept);
			department[pos].setProfessor(prof);

			return 1;
		}
		else
		{
			cout << "University size exceeded\n";
			return 0;
		}
	}
	bool deleteDepartment(string name)
	{
		bool b = 0;
		for (int i = 0; i < size; ++i)
		{
			if (department[i].getName() == name)
			{
				pos = i;
				b = 1;
				break;
			}
			else
			{
				break;
			}
		}
		if (b == 1)
		{
			department[pos].setDeptID(0);
			department[pos].setName("");
			department[pos].setProfessor(NULL);

			return 1;
		}
		else
		{
			cout << "Department not found.\n";
			return 0;
		}
	}
	bool updateDepartment(int id, string name)
	{
		bool b = 0;
		for (int i = 0; i < size; ++i)
		{
			if (department[i].getDeptID() == id)
			{
				pos = i;
				b = 1;
				break;
			}
			else
			{
				break;
			}
		}
		if (b == 1)
		{
			department[pos].setName(name);

			return 1;
		}
		else
		{
			cout << "Department not found.\n";
			return 0;
		}
	}
	void Display()
	{
		cout << "University Name: " << name << endl << endl;

		for (int i = 0; i < size; ++i)
		{
			if (department[i].getDeptID() > 0)
			{
				cout << "Department " << i + 1 << ": " << department[i].getName() << endl
					<< "Department ID: " << department[i].getDeptID() << endl
					<<"Total No. of Professors: "<< total << endl;
			}
		}
	}
};