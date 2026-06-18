#pragma once
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Polynomial
{
	int a;
	int b;
	double c;

public:
	Polynomial()
	{
		a = 0;
		b = 0;
		c = 0;
	}
	Polynomial(int a, int b, int c)
	{
		this->a = a;
		this->b = b;
		this->c = c;
	}
	void set_a(int a)
	{
		this->a = a;
	}
	void set_b(int b)
	{
		this->b = b;
	}
	void set_c(int c)
	{
		this->c = c;
	}
	int get_a()
	{
		return this->a;
	}
	int get_b()
	{
		return this->b;
	}
	double get_c()
	{
		return this->c;
	}
	Polynomial(Polynomial& Copy)
	{
		this->set_a(Copy.a);
		this->set_b(Copy.b);
		this->set_c(Copy.c);
	}
	Polynomial& operator=(Polynomial& Copy)
	{
		this->set_a(Copy.a);
		this->set_b(Copy.b);
		this->set_c(Copy.c);

		return *this;
	}
	bool operator==(Polynomial& Copy)
	{
		if (this->a == Copy.a && this->b == Copy.b && this->c == Copy.c)
			return true;
		else
			return false;
	}
	Polynomial operator+(Polynomial& P)
	{
		Polynomial obj;

		obj.set_a(this->a + P.a);
		obj.set_b(this->b + P.b);
		obj.set_c(this->c + P.c);

		return obj;
	}
	Polynomial operator-(const Polynomial& P)
	{
		Polynomial obj;

		obj.set_a(this->a - P.a);
		obj.set_b(this->b - P.b);
		obj.set_c(this->c - P.c);

		return obj;
	}
	Polynomial operator*(int s)
	{
		Polynomial obj;

		obj.set_a(this->a * s);
		obj.set_b(this->b * s);
		obj.set_c(this->c * s);

		return obj;
	}
	operator string()
	{
		string str;

		str = (to_string(a) + "X^2 + " + to_string(b) + "X ");

		if (c > 0)
			str += ("+ " + to_string(c));
		else
			str += ("- " + to_string(abs(c)));

		return str;
	}
};