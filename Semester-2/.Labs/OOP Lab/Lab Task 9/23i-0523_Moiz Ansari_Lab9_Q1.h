#pragma once
#include <iostream>
using namespace std;

class Item
{
	string itemName;
	int quantity;
	int Price_per_unit;

public:
	Item()
	{
		itemName = "";
		quantity = 0;
		Price_per_unit = 0;
	}
	Item(string str, int q, int p)
	{
		itemName = str;
		quantity = q;
		Price_per_unit = p;
	}
	Item& operator++()
	{
		++quantity;
		return *this;
	}
	Item& operator--()
	{
		if (quantity > 0)
			--quantity;
		return *this;
	}
	Item operator++(int)
	{
		Item obj = *this;
		quantity += 5;
		return obj;
	}
	Item operator--(int)
	{
		Item obj = *this;
		if (quantity > 5)
			quantity -= 5;
		return obj;
	}
	Item& operator+=(int n)
	{
		quantity += n;
		return *this;
	}
	Item& operator-=(int n)
	{
		if (quantity > n)
			quantity -= n;
		return *this;
	}
	Item& operator+(Item& obj)
	{
		if (itemName == obj.itemName)
			quantity += obj.quantity;
		return *this;
	}
	/*Item& operator-(Item& obj)
	{
		if (itemName == obj.itemName && (quantity-obj.quantity)>0)
			quantity -= obj.quantity;
		return *this;
	}*/
	int operator~()
	{
		return (quantity * Price_per_unit);
	}
	void operator!()
	{
		cout << "Item Name: " << itemName << endl
			<< "Quantity: " << quantity << endl
			<< "Price per Unit: " << Price_per_unit << endl << endl;
	}
};