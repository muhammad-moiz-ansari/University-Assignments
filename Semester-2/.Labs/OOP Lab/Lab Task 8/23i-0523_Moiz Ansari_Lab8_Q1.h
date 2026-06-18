#pragma once
#include <iostream>
using namespace std;

class Money
{
	int dollars;
	int cents;

public:
	Money()
	{
		dollars = 0;
		cents = 0;
	}
	Money(int dollar, int cents)
	{
		this->dollars = dollar;
		this->cents = cents;
	}
	void set_dollar(int d)
	{
		dollars = d;
	}
	void set_cents(int c)
	{
		cents = c;
	}

	Money operator+(const Money& obj)
	{
		Money objt;
		
		objt.set_dollar(this->dollars + obj.dollars);
		objt.set_cents(this->cents + obj.cents);

		if (objt.cents >= 100)
		{
			++objt.dollars;
			objt.cents -= 100;
		}

		return objt;
	}
	Money operator-(const Money& obj)
	{
		Money objt;

		objt.set_dollar(this->dollars - obj.dollars);
		objt.set_cents(this->cents - obj.cents);

		if (objt.dollars > 0 && objt.cents<0)
		{
			--objt.dollars;
			objt.cents += 100;
		}
		return objt;
	}
	const Money operator=(const Money& obj)
	{
		this->set_dollar(obj.dollars);
		this->set_cents(obj.cents);

		return *this;
	}
	Money& operator++ ()
	{
		++(this->dollars);
		++(this->cents);

		if (this->cents >= 100)
		{
			++this->dollars;
			this->cents -= 100;
		}

		return *this;
	}
	Money operator++ (int x)
	{
		Money objt(*this);
		
		 ++(this->cents);

		return objt;
	}
	Money& operator-- ()
	{
		--(this->dollars);
		--(this->cents);

		return *this;
	}
	Money operator-- (int x)
	{
		(this->dollars) -= x;
		(this->cents) -= x;

		return *this;
	}
	bool operator!= (const Money& right)
	{
		if (this->dollars != right.dollars && this->cents != right.cents)
			return true;
		else
			return false;
	}

	friend istream& operator >>(istream&, Money&);
	friend ostream& operator <<(ostream&, Money&);
};
istream& operator >>(istream& in, Money& obj)
{
	cout << "Enter dollars: ";
	in >> obj.dollars;

	cout << "Enter cents: ";
	in >> obj.cents;

	return in;
}
ostream& operator <<(ostream& out, Money& obj)
{
	out << "$" << obj.dollars << ", " << obj.cents << " cents\n\n";
	return out;
}