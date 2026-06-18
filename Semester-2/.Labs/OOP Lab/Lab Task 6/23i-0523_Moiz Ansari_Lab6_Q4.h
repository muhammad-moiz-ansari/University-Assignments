#pragma once
#include <iostream>
using namespace std;

class IntegerList
{
private:
	int* list = nullptr;
	int numElements = 0;
	int index = 0;

public:
	IntegerList(int size)
	{
		 list = new int[size];

		for (int i=0; i < size; ++i)
			list[i] = 0;

		numElements = size;
	}
	bool isValid(int in)
	{
		if (in >= 0 && in < numElements)
			return true;
		else
			return false;
	}
	bool addElement(int v)
	{
		if (isValid(index) == 0)
			return false;
		else
		{
			list[index++] = v;
			return true;
		}
	}
	int removeElement()
	{
			list[--index] = 0;
			return list[index];
	}
	int getElement(int in)
	{
		if (isValid(in) == 0)
			return -1;
		else
		{
			return list[in];
		}
	}
	void displayElements()
	{
		for (int i = 0; i < numElements; ++i)
		{
			if (list[i] != 0)
			{
				cout << list[i];
				if (i < numElements - 1)
					cout << ", ";
				else
					cout << endl;
			}
		}
	}
	~IntegerList()
	{
		delete[] list;
	}


};