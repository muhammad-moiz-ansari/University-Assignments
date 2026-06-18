#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Point
{
	int X_Coordinate;
	int Y_Coordinate;

public:
	Point()
	{
		X_Coordinate = 0;
		Y_Coordinate = 0;
	}
	Point(int x, int y)
	{
		X_Coordinate = x;
		Y_Coordinate = y;
	}
	Point(const Point& p)
	{
		this->X_Coordinate = p.X_Coordinate;
		this->Y_Coordinate = p.Y_Coordinate;
	}
	int getX_Coordinate() const
	{
		return X_Coordinate;
	}
	int getY_Coordinate() const
	{
		return Y_Coordinate;
	}

};


class Line
{
	Point P1;
	Point P2;

public:
	Line():P1(1,5), P2(10,15)
	{}
	Line(int x1, int y1, int x2, int y2):P1(x1,y1), P2(x2,y2)
	{}
	Line(const Point& p1, const Point& p2):P1(p1), P2(p2)
	{}

	float findSlope()
	{
		float s = 0;

		s = (double)(P2.getY_Coordinate() - P1.getY_Coordinate()) / (P2.getX_Coordinate() - P1.getX_Coordinate());
		return s;
	}

	float findLength()
	{
		float d = 0;

		d = sqrt(pow((P2.getX_Coordinate() - P1.getX_Coordinate()), 2) + pow((P2.getY_Coordinate() - P1.getY_Coordinate()), 2));
		return d;
	}

	Point& findMidPoint()
	{
		Point M((double)(P1.getX_Coordinate() + P2.getX_Coordinate())/2 , (double)(P1.getY_Coordinate() + P2.getY_Coordinate()) / 2);

		return M;
	}

	friend ostream& operator<<(ostream& out, Point P);

};
ostream& operator<<(ostream& out, Point P)
{
	out << "(" << P.getX_Coordinate() << ", " << P.getY_Coordinate() << ")";
	return out;
}