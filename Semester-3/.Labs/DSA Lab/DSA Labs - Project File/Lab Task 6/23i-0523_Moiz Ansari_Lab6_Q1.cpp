#include <iostream>
using namespace std;

class Employee
{
public:
	string name;
	string cnic;
	string dateofjoining;
	string gender;
	string maritalStatus;
	float salary;
	string designation;
	int employeeScale;
	string department;

	Employee(string n = "", string nic = "", string doj = "", string gen = "", string ms = "", float sal = 0, string des = "", int emps = 0, string dep = "")
	{
		name = n;
		cnic = nic;
		dateofjoining = doj;
		gender = gen;
		maritalStatus = ms;
		salary = sal;
		designation = des;
		employeeScale = emps;
		department = dep;
	}
};

template <typename T>
class Node
{
public:
	T data;
	Node* next;

	Node()
	{
		next = NULL;
	}
};

class EmployeeList
{
public:
	Node<Employee>* head;

	EmployeeList()
	{
		head = NULL;
	}

	Node<Employee>* addEmployee(Employee emp)
	{
		Node<Employee>* temp = head;

		if (temp != NULL)
			while (temp->next)
				temp = temp->next;

		Node<Employee>* temp2 = new Node<Employee>;
		temp2->data = emp;
		if (temp != NULL)
		{
			temp2->next = temp->next;
			temp->next = temp2;
		}
		else
		{
			temp2->next = temp;
			temp = temp2;
		}
		if (head == NULL)
			head = temp;
		temp = NULL;
		temp2 = NULL;

		return head;
	}

	Employee* searchEmployeeByNIC(string str)
	{
		Node<Employee>* temp = head;

		while (temp && temp->data.cnic != str)
			temp = temp->next;
		
		if (temp)
			return &(temp->data);
		else
			return NULL;
	}

	void listEmployeesByJoiningDate(string edoj)
	{
		if (!head)
			return;

		Node<Employee>* temp = head;

		while (temp)
		{
			if (temp->data.dateofjoining == edoj)
			{
				cout << temp->data.name << endl;
			}
			temp = temp->next;
		}
	}

	void sortEmployeesBySalary()
	{
		if (!head)
			return;

		Node<Employee>* temp = head;
		int size = 0;

		while (temp)
		{
			temp = temp->next;
			++size;
		}

		bool b = 1;
		for (int i = 0; i < size; ++i)
		{
			temp = head;
			b = 1;
			for (int j = 0; j < size - i - 1; ++j)
			{
				if (temp->data.salary > temp->next->data.salary)
				{
					//sal
					float t = temp->data.salary;
					temp->data.salary = temp->next->data.salary;
					temp->next->data.salary = t;

					//Name
					string s1 = temp->data.name;
					temp->data.name = temp->next->data.name;
					temp->next->data.name = s1;

					//Department
					string s2 = temp->data.department;
					temp->data.department = temp->next->data.department;
					temp->next->data.department = s2;

					b = 0;
				}
				temp = temp->next;
			}
			if (b)
				break;
		}
	}

	void listEmployeesByDepartment(string edep)
	{
		if (!head)
			return;

		Node<Employee>* temp = head;

		while (temp)
		{
			if (temp->data.department == edep)
			{
				cout << temp->data.name << endl;
			}
			temp = temp->next;
		}
	}

	void listEmployeesWithDepartmentDesignation(string edep, string edes)
	{
		if (!head)
			return;

		Node<Employee>* temp = head;

		while (temp)
		{
			if (temp->data.department == edep && temp->data.designation == edes)
			{
				cout << temp->data.name << endl;
			}
			temp = temp->next;
		}
	}

	void editEmployeeRecord(string nic, string ms, float sal, string des, int emps, string dep)
	{
		if (!head)
			return;

		Node<Employee>* temp = head;

		while (temp)
		{
			if (temp->data.cnic == nic)
			{
				break;
			}
			temp = temp->next;
		}

		if (temp)
		{
			temp->data.maritalStatus = ms;
			temp->data.salary = sal;
			temp->data.designation = des;
			temp->data.employeeScale = emps;
			temp->data.department = dep;
		}
	}

};


int main()
{
	int num = 0;
	int ch = 0;
	string str, str2;

	string name;
	string cnic;
	string dateofjoining;
	string gender;
	string maritalStatus;
	float salary;
	string designation;
	int employeeScale;
	string department;

	EmployeeList list;

	cout << "How many employees you want to enter? ";
	cin >> num;

	for (int i = 0; i < num; ++i)
	{
		cout << "\n\nEmployee " << i + 1 << ":\n";
		cout << "Name: ";
		cin >> name;
		cout << "CNIC: ";
		cin >> cnic;
		cout << "Dat of Joining: ";
		cin >> dateofjoining;
		cout << "Gender: \n1. Male\n2. Female\n";
		cin >> ch;
		if (ch == 1)
			gender = "Male";
		else
			gender = "Female";
		cout << "Marital Status: ";
		cin >> maritalStatus;
		cout << "Salary: ";
		cin >> salary;
		cout << "Deisgnation: ";
		cin >> designation;
		cout << "Employee Scale: ";
		cin >> employeeScale;
		cout << "Department: ";
		cin >> department;

		Employee* emp = new Employee(name, cnic, dateofjoining, gender, maritalStatus, salary, designation, employeeScale, department);

		list.addEmployee(*emp);
		
		delete emp;
	}

	cout << "\n\nChoose the operation: \n"
		<< "1. Search Employee With NIC\n"
		<< "2. List of Employee Who have a certain joining date\n"
		<< "3. Employees in ascending sort order based on their salary\n"
		<< "4. Employees from a certain department\n"
		<< "5. Employees with a certain department and designation\n"
		<< "6. Edit the record of an Employee with a certain NIC\n"
		<< "7. Add Employee\n"
		<< "8. Exit\n\n";

	while (ch != 8)
	{
		cout << "Chosse: ";
		cin >> ch;
		if (ch == 1)
		{
			cout << "Enter CNIC: ";
			cin >> str;
			Employee* found = list.searchEmployeeByNIC(str);
			if (found)
			{
				cout << "Name: " << found->name << endl;
				cout << "Salary: " << found->salary << endl;
				cout << "Depeartment: " << found->department << endl;
			}
			else
				cout << "Employee got kidnapped :)";
		}
		else if (ch == 2)
		{
			cout << "Enter date of joining: ";
			cin >> str;
			cout << "List of Employee Who have the date " << str << ":\n";
			list.listEmployeesByJoiningDate(str);
		}
		else if (ch == 3)
		{
			cout << "Sort employees: \n";
			
			Employee* found = list.searchEmployeeByNIC("123");
			if (found)
			{
				cout << "Name: " << found->name << endl;
				cout << "Salary: " << found->salary << endl;
				cout << "Depeartment: " << found->department << endl;
			}
			found = list.searchEmployeeByNIC("234");
			if (found)
			{
				cout << "Name: " << found->name << endl;
				cout << "Salary: " << found->salary << endl;
				cout << "Depeartment: " << found->department << endl;
			}
		}
		else if (ch == 4)
		{
			cout << "Enter department: ";
			cin >> str;
			cout << "List of Employee Who have department " << str << ":\n";
			list.listEmployeesByDepartment(str);
		}
		else if (ch == 5)
		{
			cout << "Enter department: ";
			cin >> str;
			cout << "Enter designation: ";
			cin >> str2;
			cout << "List of Employee Who have department & designation " << str << ", " << str2 << ":\n";
			list.listEmployeesWithDepartmentDesignation(str, str2);
		}
		else if (ch == 6)
		{
			cout << "Enter CNIC to edit data:\n";
			cin >> str;
			list.editEmployeeRecord("NIC456", "Married", 45000, "Senior Engineer", 15, "IT");
			Employee* found = list.searchEmployeeByNIC(str);
			if (found)
			{
				cout << "Name: " << found->name << endl;
				cout << "Salary: " << found->salary << endl;
				cout << "Depeartment: " << found->department << endl;
			}
		}
		else if (ch == 7)
		{
			cout << "Name: ";
			cin >> name;
			cout << "CNIC: ";
			cin >> cnic;
			cout << "Dat of Joining: ";
			cin >> dateofjoining;
			cout << "Gender: \n1. Male\n2. Female\n";
			cin >> ch;
			if (ch == 1)
				gender = "Male";
			else
				gender = "Female";
			cout << "Marital Status: ";
			cin >> maritalStatus;
			cout << "Salary: ";
			cin >> salary;
			cout << "Deisgnation: ";
			cin >> designation;
			cout << "Employee Scale: ";
			cin >> employeeScale;
			cout << "Department: ";
			cin >> department;

			Employee* emp = new Employee(name, cnic, dateofjoining, gender, maritalStatus, salary, designation, employeeScale, department);

			list.addEmployee(*emp);

			delete emp;
		}
	}
}