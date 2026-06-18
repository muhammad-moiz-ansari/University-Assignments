#pragma once
#include <iostream>
using namespace std;

static int Slot=1;
int maxcars = 5;

struct Car
{
	int entertime;
	int reg_no;
	int slot_no = Slot;
};

class ParkingGarage
{
	public:
	Car* car = new Car[maxcars];

	ParkingGarage()
	{
	}


	void initialize()
	{
		for (int i = 0; i < maxcars; ++i)
		{
			car[i].entertime = 0;
			car[i].reg_no = 0;
			car[i].slot_no = 0;
		}
	}
	void print()
	{
		int slots = 0;
		for (int i = 0; i < maxcars; ++i)
		{
			cout << "Car " << i + 1 << ":\n";
			cout << "Entry Time: " << car[i].entertime << endl;
			cout << "Registration Number: " << car[i].reg_no << endl;
			slots = maxcars - Slot + 1;
			if (slots < 0)
				slots = 0;

			cout << "Empty slots: " << slots << endl << endl;
		}
	}
	bool IsFull()
	{
		if (Slot >= 1 && Slot <= maxcars)
			return false;
		else
			return true;
	}
	void ParkCar()
	{
		int index = 0;
		if (Slot >= 1 && Slot <= maxcars)
		{
			for (; car[index].slot_no != 0; ++index);

			cout << "Enter entry time: ";
			cin >> car[index].entertime;
			while(!(car[index].entertime>=0 && car[index].entertime<=24))
				cin >> car[index].entertime;

			cout << "Enter registration number: ";
			cin >> car[index].reg_no;
			
			car[index].slot_no = index + 1;
			cout << endl;

			++Slot;
		}
	}
	void RemoveCar(int index, int rem_t)
	{
		int charge = 0;
		int time = rem_t - car[index].entertime;

		car[index-1].entertime = 0;
		car[index-1].reg_no = 0;
		car[index-1].slot_no = 0;

		--Slot;

		charge = 20 * time;

		cout << "You have been charged Rs. " << charge << " for parking. Enjoy your day :)\n\n";
	}
};