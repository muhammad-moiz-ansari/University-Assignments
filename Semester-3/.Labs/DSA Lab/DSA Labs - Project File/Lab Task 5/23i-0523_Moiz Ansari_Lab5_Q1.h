#pragma once
#include <iostream>
using namespace std;

class DynamicList
{
private:
	int size;

public:
	int index = 0;
	int* arr;

	DynamicList(int* arrr = NULL, int s = 0);

	void addEnd(int val);

	void addStart(int val);

	void addGivenP(int val, int pos);
		//Insert an Element at given position

	void delStart();
		//Remove an Element from the start of the list
		
	void delEnd();
		//Remove an Element from the end of the list

	void delGivenP(int pos);
		//Remove an Element from a given position

	int Next(int pos);
		//NEXT(p, L) : Return the position following p on list L.
		
	int Previous(int pos);
		//Return the position preceding position p on list L
		
	void print();
		//Printing the List

	bool Isempty();
		//Returns True if List is empty else returns False

	void replace(int ind, int val);
		//Replace(on the basis of index and value) Replace any element of the List

	void clear();
		//Deletes all the elements from the List

	bool checkDupli();
};