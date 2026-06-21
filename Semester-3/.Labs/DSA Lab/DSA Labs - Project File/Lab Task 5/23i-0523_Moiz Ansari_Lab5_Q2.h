#pragma once
#include <iostream>
using namespace std;

template <typename T>
class List
{
private:
	int capacity;
	int index;

public:
	T* values;

	List(int s = 0);

	bool insert(T item);

	bool insertAt(T item, int index);

	bool insertAfter(T itemTobeInserted, T item);

	bool insertBefore(T itemTobeInserted, int item);

	bool isEmpty();

	bool isFull();

	bool remove(T item);

	bool removeBefore(T item);

	bool removeAfter(T item);

	bool operator==(List& L);

	void reverse();

	int search(T item);

	void print();

};

