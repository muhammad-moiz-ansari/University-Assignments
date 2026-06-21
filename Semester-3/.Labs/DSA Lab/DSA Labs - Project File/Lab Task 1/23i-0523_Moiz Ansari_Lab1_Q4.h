#pragma once
#include <iostream>
using namespace std;

template <typename T>
class Container
{
private:
	T* values;
	int capacity;
	int counter;

public:
	Container(int cap = 5)
	{
		values = new T[cap];
		capacity = cap;
		counter = 0;
	}

	bool isFull()
	{
		if (counter >= capacity)
			return true;
		else
			return false;
	}

	void insert(T val)
	{
		if (!isFull())
			values[counter++] = val;
		else
			cout << "Container is full!\n";
	}

	bool search(T val)
	{
		for (int i = 0; i < counter; ++i)
		{
			if (values[i] == val)
				return true;
		}
		return false;
	}

	void remove(T val)
	{
		for (int i = 0; i < counter; ++i)
		{
			if (values[i] == val)
			{
				for (int k = i; k < counter - 1; ++k)
					values[k] = values[k + 1];
				--counter;
			}
		}
	}

	void print()
	{
		cout << "Capacity: " << capacity << endl
			<< "Counter: " << counter << endl
			<< "Values:\n";
		for (int i = 0; i < counter; ++i)
		{
			cout << i + 1 << ": " << values[i] << endl;
		}
		cout << endl << endl;
	}
};