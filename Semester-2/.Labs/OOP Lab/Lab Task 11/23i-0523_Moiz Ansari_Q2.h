#pragma once
#include <iostream>
using namespace std;

class Staff
{
protected:
	string name;
	string cnic;
	int dob;
	int age;
	unsigned int contact;

public:
	Staff(string n = "", string c = "", int d = 0, unsigned int cont = 0)
	{
		name = n;
		cnic = c;
		dob = d;
		age = 2024 - dob;
		contact = cont;
	}
	//Setters:
	void setName(string n)
	{
		name = n;
	}
	void setCnic(string c)
	{
		cnic = c;
	}
	void setDob(int d)
	{
		dob = d;
	}
	void setAge(int a)
	{
		age = a;
	}
	void setContact(unsigned int cont = 0)
	{
		contact = cont;
	}

	//Getters:
	string getName()
	{
		return name;
	}
	string getCnic()
	{
		return cnic;
	}
	int getDob()
	{
		return dob;
	}
	int getAge()
	{
		return age;
	}
	unsigned int getContact()
	{
		return contact;
	}

};

class Faculty: protected Staff
{
protected:
	int payScale;
	int roomNumber;
		string subject;
		string rank;

public:
	Faculty(int p=0, int rn=0, string s="", string r="")
	{
		payScale = p;
		roomNumber = rn;
		subject = s;
		rank = r;
	}

	//Setters:
	void setPayScale(int p)
	{
		payScale = p;
	}
	void setRoomNumber(int rn)
	{
		roomNumber = rn;
	}
	void setSubject(string s)
	{
		subject = s;
	}
	void setRank(string r)
	{
		rank = r;
	}

	//Getters:
	int getPayScale()
	{
		return payScale;
	}
	int getRoomNumber()
	{
		return roomNumber;
	}
	string getSubject()
	{
		return subject;
	}
	string getRank()
	{
		return rank;
	}
};

class NonFaculty: public Staff
{
protected:
	string duty;
	string startTiming;
	string endTiming;

public:
	NonFaculty(string d = "", string st = "", string et = "")
	{
		duty = d;
		startTiming = st;
		endTiming = et;
	}
	//Setters:
	void setDuty(string d)
	{
		duty = d;
	}
	void setStartTiming(string st)
	{
		startTiming = st;
	}
	void setEndTiming(string et)
	{
		endTiming = et;
	}

	//Getters:
	string getDuty()
	{
		return duty;
	}
	string getStartTiming()
	{
		return startTiming;
	}
	string getEndTiming()
	{
		return endTiming;
	}
};

class HOD: public Faculty
{
protected:
	int DeptID;
	string Department;

public:
	HOD(int id=0, string dept="")
	{
		DeptID = id;
		Department = dept;
	}
	//Setters:
	void setDeptID(int id)
	{
		DeptID = id;
	}
	void setDepartment(string dept)
	{
		Department = dept;
	}
	//Getters:
	int getDeptID()
	{
		return DeptID;
	}
	string getDepartment()
	{
		return Department;
	}

	void print_detail()
	{
		cout << "\nHOD Details:\n"
			<< "Name: " << name << endl
			<< "CNIC: " << cnic << endl
			<< "DOB: " << dob << endl
			<< "Age: " << age << endl
			<< "Contact: " << contact << endl
			<< "Pay Scale: " << payScale << endl
			<< "Room Number: " << roomNumber << endl
			<< "Subject: " << subject << endl
			<< "Rank: " << rank << endl
			<< "Department ID: " << DeptID << endl
			<< "Department: " << Department << endl;
	}
	void input()
	{
		cout << "\nEnter HOD Details:\n";
		cout << "Name: ";
		cin >> name;
		cout << "CNIC: ";
		cin >> cnic;
		cout << "DOB: ";
		cin >> dob;
		cout << "Contact: ";
		cin >> contact;
		cout << "Pay Scale: ";
		cin >> payScale;
		cout << "Room Number: ";
		cin >> roomNumber;
		cout << "Subject: ";
		cin >> subject;
		cout << "Rank: ";
		cin >> rank;
		cout << "Department ID: ";
		cin >> DeptID;
		cout << "Department: ";
		cin >> Department;
	}
};

class Teacher: public Faculty
{
protected:
	string TeachProgram;

public:
	Teacher(string tp = "")
	{
		TeachProgram = tp;
	}
	//Setter:
	void setProgram(string tp)
	{
		TeachProgram = tp;
	}
	//Getter:
	string getProgram()
	{
		return TeachProgram;
	}

	void print_detail()
	{
		cout << "\nTeacher Details:\n"
			<< "Name: " << name << endl
			<< "CNIC: " << cnic << endl
			<< "DOB: " << dob << endl
			<< "Age: " << age << endl
			<< "Contact: " << contact << endl
			<< "Pay Scale: " << payScale << endl
			<< "Room Number: " << roomNumber << endl
			<< "Subject: " << subject << endl
			<< "Rank: " << rank << endl
			<< "Teaching Program" << TeachProgram << endl;
	}
	void input()
	{
		cout << "\nEnter HOD Details:\n";
		cout << "Name: ";
		cin >> name;
		cout << "CNIC: ";
		cin >> cnic;
		cout << "DOB: ";
		cin >> dob;
		cout << "Contact: ";
		cin >> contact;
		cout << "Pay Scale: ";
		cin >> payScale;
		cout << "Room Number: ";
		cin >> roomNumber;
		cout << "Subject: ";
		cin >> subject;
		cout << "Rank: ";
		cin >> rank;
		cout << "Teaching Program: ";
		cin >> TeachProgram;
	}
};

class Security : public NonFaculty
{
protected:
	string GunMade;
	string LisenceNumber;

public:
	Security(string gm = "", string ln = "")
	{
		GunMade = gm;
		LisenceNumber = ln;
	}
	//Setters:
	void setGunMade(string gm)
	{
		GunMade = gm;
	}
	void setLisenceNumber(string ln)
	{
		LisenceNumber = ln;
	}

	//Getters:
	string getGunMade()
	{
		return GunMade;
	}
	string getLisenceNumber()
	{
		return LisenceNumber;
	}

	void print_detail()
	{
		cout << "\nSecurity Details:\n"
			<< "Name: " << name << endl
			<< "CNIC: " << cnic << endl
			<< "DOB: " << dob << endl
			<< "Age: " << age << endl
			<< "Contact: " << contact << endl
			<< "Duty: " << duty << endl
			<< "Start Timing: " << startTiming <<":00:00" << endl
			<< "End Timing: " << endTiming <<":00:00" << endl
			<< "Gun Made: " << GunMade << endl
			<< "Lisence Number: " << LisenceNumber << endl;
	}
	void input()
	{
		cout << "\nEnter HOD Details:\n";
		cout << "Name: ";
		cin >> name;
		cout << "CNIC: ";
		cin >> cnic;
		cout << "DOB: ";
		cin >> dob;
		cout << "Contact: ";
		cin >> contact;
		cout << "Duty: ";
		cin >> duty;
		cout << "Start Timing: ";
		cin >> startTiming;
		cout << "End Timing: ";
		cin >> endTiming;
		cout << "Gun Made: ";
		cin >> GunMade;
		cout << "Lisence Number: ";
		cin >> LisenceNumber;
	}
};

class GateKeeper : public NonFaculty
{
protected:
	int GateNumber;

public:
	GateKeeper(int gn = 0)
	{
		GateNumber = gn;
	}
	//Setters:
	void setGateNumber(int gn)
	{
		GateNumber = gn;
	}
	//Getters:
	int getGateNumber()
	{
		return GateNumber;
	}

	void print_detail()
	{
		cout << "\nSecurity Details:\n"
			<< "Name: " << name << endl
			<< "CNIC: " << cnic << endl
			<< "DOB: " << dob << endl
			<< "Age: " << age << endl
			<< "Contact: " << contact << endl
			<< "Duty: " << duty << endl
			<< "Start Timing: " << startTiming << ":00:00" << endl
			<< "End Timing: " << endTiming << ":00:00" << endl
			<< "Gate Number: "<<GateNumber <<endl;
	}
	void input()
	{
		cout << "\nEnter HOD Details:\n";
		cout << "Name: ";
		cin >> name;
		cout << "CNIC: ";
		cin >> cnic;
		cout << "DOB: ";
		cin >> dob;
		cout << "Contact: ";
		cin >> contact;
		cout << "Duty: ";
		cin >> duty;
		cout << "Start Timing: ";
		cin >> startTiming;
		cout << "End Timing: ";
		cin >> endTiming;
		cout << "Gate Number: ";
		cin >> GateNumber;
	}
};