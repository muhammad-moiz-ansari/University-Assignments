#pragma once
#include <iostream>
using namespace std;

class Shape
{
protected:
	string type;
	float A;

public:
	Shape()
	{
		type = "";
		A = 0;
	}
	Shape(string t, float a)
	{
		type = t;
		A = a;
	}

	void setType(string t)
	{
		type = t;
	}
	void setArea(float a)
	{
		A = a;
	}

	string getType()
	{
		return type;
	}
	float getArea()
	{
		return A;
	}

	virtual void area()
	{
		A = 0;
	}
	virtual void Display()
	{
		cout << "Area = " << A << endl;
	}
};

class Rectangle: public Shape
{
private:
	string type;
	float height;
	float width;
	
public:
	Rectangle()
	{
		type = "";
		height = 0;
		width = 0;
	}
	Rectangle(string t, float h, float w)
	{
		type = t;
		height = h;
		width = w;
	}

	void area()
	{
		setArea(height * width);
	}

	virtual void Display()
	{
		cout << "Area = " << getArea() << endl;
		cout << "Type : " << type << endl;
		cout << "Width:" << width << endl;
		cout << "Height :" << height << endl;
	}
	
};

class Triangle : public Shape
{
private:
	string type;
	float base;
	float height;
	
public:
	Triangle()
	{
		type = "";
		base = 0;
		height = 0;
	}
	Triangle(string t, float b, float h)
	{
		type = t;
		base = b;
		height = h;
	}

	virtual void area()
	{
		setArea((1 / 2) * base * height);
	}
	virtual void Display()
	{
		cout << "Area = " << getArea() << endl;
		cout << "Type : " << type << endl;
		cout << "Base:" << base << endl;
		cout << "Height :" << height << endl;
	}

};

class Circle : public Shape
{
private:
	string type;
	float radius;
	

public:
	Circle()
	{
		type = "";
		radius = 0;
	}
	Circle(string t, float r)
	{
		type = t;
		radius = r;
	}

	virtual void area()
	{
		setArea(3.14 * radius * radius);
	}
	virtual void Display()
	{
		cout << "Area = " << getArea() << endl;
		cout << "Type : " << type << endl;
		cout << "Radius:" << radius << endl;
	}
};