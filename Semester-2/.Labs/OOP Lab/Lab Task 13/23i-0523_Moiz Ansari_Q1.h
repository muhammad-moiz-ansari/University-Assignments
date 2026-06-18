#pragma once
#include <iostream>
#include <string>
using namespace std;
class Drink
{
protected:
	string Flavor;
	float Temperature; // for best serve;
	float Price;
	string Expiry_date;

public:
	Drink()
	{
		Flavor = "";
		Temperature = 0;
		Price = 0;
		Expiry_date = "";
	}
	Drink(string f, float temp, float p, string exp)
	{
		Flavor = f;
		Temperature = temp;
		Price = p;
		Expiry_date = exp;
	}

	//Getters:
	string getFlavor()
	{
		return Flavor;
	}
	float getTemperature()
	{
		return Temperature;
	}
	float getPrice()
	{
		return Price;
	}
	string getExpiryDate()
	{
		return Expiry_date;
	}

	//Setters:
	void setFlavor(string f)
	{
		Flavor = f;
	}
	void setTemperature(float temp)
	{
		Temperature = temp;
	}
	void setPrice(float p)
	{
		Price = p;
	}
	void setExpiryDate(string exp)
	{
		Expiry_date = exp;
	}

	//Functions:
	virtual void Display() = 0;
};

class Water:public Drink
{
protected:
	string supplier;

public:
	Water()
	{
		Flavor = "";
		Temperature = 0;
		Price = 0;
		Expiry_date = "";
		supplier = "";
	}
	Water(string f, float temp, float p, string exp, string sup)
	{
		Flavor = f;
		Temperature = temp;
		Price = p;
		Expiry_date = exp;
		supplier = sup;
	}

	virtual void Display()
	{
		cout << "Flavor: " << Flavor << endl
			<< "Temperatur: " << Temperature << endl
			<< "Price: " << Price << endl
			<< "Expiry Date: " << Expiry_date << endl
			<< "Supplier: " << supplier << endl << endl;
	}

};

class Carbonated:public Water
{
private:
	string type;

public:
	Carbonated()
	{
		Flavor = "";
		Temperature = 0;
		Price = 0;
		Expiry_date = "";
		supplier = "";
		type = "";
	}
	Carbonated(string f, float temp, float p, string exp, string sup, string t)
	{
		Flavor = f;
		Temperature = temp;
		Price = p;
		Expiry_date = exp;
		supplier = sup;
		type = t;
	}

	//Getters:
	string getType()
	{
		return type;
	}

	//Setter:
	void setType(string t)
	{
		type = t;
	}

	//Functions:
	virtual void Display()
	{
		cout << "Flavor: " << Flavor << endl
			<< "Temperatur: " << Temperature << endl
			<< "Price: " << Price << endl
			<< "Expiry Date: " << Expiry_date << endl
			<< "Supplier: " << supplier << endl
			<< "Type: " << type << endl << endl;
	}
};