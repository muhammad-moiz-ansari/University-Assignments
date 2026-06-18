#pragma once
#include <iostream>
#include <cmath>
using namespace std;

class Fraction
{
	int numerator;
	int denominator;

public:
	Fraction()
	{
		numerator = 0;
		denominator = 1;
	}
	Fraction(int n, int d)
	{
		numerator = n;
		denominator = d;
	}
	bool operator==(Fraction& obj)
	{
		if (numerator == obj.numerator && denominator == obj.denominator)
			return true;
		else
			return false;
	}
	bool operator>(Fraction& obj)
	{
		if((double)numerator/denominator > (double)obj.numerator / obj.denominator)	//(numerator > obj.numerator && denominator > obj.denominator)
			return true;
		else
			return false;
	}
	bool operator<(Fraction& obj)
	{
		if ((double)numerator / denominator < (double)obj.numerator / obj.denominator)
			return true;
		else
			return false;
	}

	void simplify(Fraction& obj)
	{
		int a = 0;
		if (obj.numerator < obj.denominator)
			a = obj.numerator;
		else
			a = obj.denominator;

		for (int i = 2; i < a; ++i)
		{
			if (obj.numerator % i == 0 && obj.denominator % i == 0)
			{
				obj.numerator /= i;
				obj.denominator /= i;
				i = 1;
				if (obj.numerator < obj.denominator)
					a = obj.numerator;
				else
					a = obj.denominator;
			}
		}
	}

	Fraction& operator+(Fraction obj)
	{
		int lcm = 0,
			a = 0,
			b = 0;
		bool done = 0;

		if (denominator != obj.denominator)
		{
			if (denominator < obj.denominator)
			{
				for (int i = 0, l = denominator; (denominator * i) <= obj.denominator; ++i)
				{
					if (l * i == obj.denominator)
					{
						lcm = l;
						a = i;
						b = 1;
						done = 1;
						break;
					}
				}
			}
			else if (obj.denominator < denominator)
			{
				for (int i = 0, l = obj.denominator; (obj.denominator * i) <= denominator; ++i)
				{
					if (l * i == denominator)
					{
						lcm = l;
						b = i;
						a = 1;
						done = 1;
						break;
					}
				}
			}
			if(!done)
			{
				lcm = denominator * obj.denominator;
				a = obj.denominator;
				b = denominator;
			}
			numerator *= a;
			denominator *= a;
			obj.numerator *= b;
			obj.denominator *= b;
		}
		numerator += obj.numerator;

		simplify(*this);

		return *this;
	}
	Fraction& operator-(Fraction obj)
	{
		int lcm = 0,
			a = 0,
			b = 0;
		bool done = 0;

		if (denominator != obj.denominator)
		{
			if (denominator < obj.denominator)
			{
				for (int i = 0, l = denominator; (denominator * i) <= obj.denominator; ++i)
				{
					if (l * i == obj.denominator)
					{
						lcm = l;
						a = i;
						b = 1;
						done = 1;
						break;
					}
				}
			}
			else if (obj.denominator < denominator)
			{
				for (int i = 0, l = obj.denominator; (obj.denominator * i) <= denominator; ++i)
				{
					if (l * i == denominator)
					{
						lcm = l;
						b = i;
						a = 1;
						done = 1;
						break;
					}
				}
			}
			if (!done)
			{
				lcm = denominator * obj.denominator;
				a = obj.denominator;
				b = denominator;
			}
			numerator *= a;
			denominator *= a;
			obj.numerator *= b;
			obj.denominator *= b;
		}
		numerator -= obj.numerator;

		simplify(*this);

		return *this;
	}
	Fraction& operator*(Fraction& obj)
	{
		numerator *= obj.numerator;
		denominator *= obj.denominator;
		simplify(*this);

		return *this;
	}

	friend istream& operator>>(istream& in, Fraction& obj);
	friend ostream& operator<<(ostream& out, Fraction& obj);
};
istream& operator>>(istream& in, Fraction& obj)
{
	cout << "Enter Numerator: ";
	in >> obj.numerator;
	cout << "Enter Denominator: ";
	in >> obj.denominator;

	return in;
}
ostream& operator<<(ostream& out, Fraction& obj)
{
	out << obj.numerator << "/" << obj.denominator << endl << endl;
	return out;
}