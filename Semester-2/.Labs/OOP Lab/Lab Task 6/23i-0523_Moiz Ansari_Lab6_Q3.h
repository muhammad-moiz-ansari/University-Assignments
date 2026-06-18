#pragma once
#include <iostream>
using namespace std;

class Point
{
	int x;
	int y;

public:
	Point()
	{
		x = 0;
		y = 0;
	}
	Point(int a, int b)
	{
		x = a;
		y = b;
	}
	int getx()
	{
		return x;
	}
	int gety()
	{
		return y;
	}
	void setx(int a)
	{
		x = a;
	}
	void sety(int b)
	{
		y = b;
	}
	void display()
	{
		cout << "(" << x << ", " << y << ")" << endl;
	}
};

class Line
{
private:
	Point P1;
	Point P2;

public:
	Line(Point& p1, Point& p2)
	{
		p1 = P1;
		p2 = P2;
	}
	Line(int x1, int y1, int x2, int y2)
	{
		P1.setx(x1);
		P1.sety(y1);

		P2.setx(x2);
		P2.sety(y2);
	}
	Point getP1()
	{
		return P1;
	}
	Point getP2()
	{
		return P2;
	}
	double getSlope()
	{
		return ((P2.gety() - P1.gety()) / (double)(P2.getx() - P1.getx()));
	}
	void displayLine()
	{
		cout << "P1 = ";
		P1.display();

		cout << "P2 = ";
		P2.display();
	}
};
