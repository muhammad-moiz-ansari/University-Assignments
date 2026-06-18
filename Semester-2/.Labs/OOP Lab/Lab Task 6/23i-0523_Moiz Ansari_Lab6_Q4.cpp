#include <iostream>
#include "23i-0523_Moiz Ansari_Q4.h"
using namespace std;

int main()
{
	int size = 5;

	IntegerList List(size);

	cout << "Enter array values: ";
	int* arr = new int[size];
	for (int i = 0; i < size; ++i)
	{
		cin >> arr[i];
	}

	for (int i = 0; i < size; ++i)
	{
		List.addElement(arr[i]);
	}

	cout << "Display 1: ";
	List.displayElements();

	cout << "\nDisplay 2: ";
	List.addElement(11);
	List.displayElements();

	List.removeElement();
	List.removeElement();

	cout << "\nDisplay 3: ";
	List.displayElements();

	delete[] arr;


	return 0;
}