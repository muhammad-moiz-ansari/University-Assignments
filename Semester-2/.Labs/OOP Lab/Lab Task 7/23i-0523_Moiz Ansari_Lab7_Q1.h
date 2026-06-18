#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Distance
{
	int feet;
	int inch;

public:
	Distance()
	{
		feet = 0;
		inch = 0;
	}
	Distance(int f, int i) // parameterized constructor
	{
		feet = f;
		inch = i;
	}
	Distance(Distance& copy) // copy constructor
	{
		feet = copy.feet;
		inch = copy.inch;
	}
	void setInch(int i)
	{
		inch = i;
	}
	int getInch()
	{
		return inch;
	}
	void setFeet(int f)
	{
		feet = f;
	}
	int getFeet()
	{
		return feet;
	}
	Distance addDistance(Distance& d2)
	{
		Distance d3;
		feet = feet + d2.feet;
		inch = inch + d2.inch;

		if (inch >= 12)
		{
			++feet;
			inch -= 12;
		}
		d3.feet = feet;
		d3.inch = inch;
		return d3;
	}
	Distance subDistance(Distance& d2)
	{
		d2.feet = abs(feet - d2.feet);
		d2.inch = abs(inch - d2.inch);
		if (d2.inch >= 12)
		{
			++d2.feet;
			d2.inch -= 12;
		}
		return d2;
	}
	void Display()
	{
		cout << feet << "ft, " << inch << "in\n";
	}
};