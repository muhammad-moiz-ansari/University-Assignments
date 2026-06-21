#include <iostream>
#include "23i-0523_Moiz Ansari_Q1.h"
using namespace std;

DynamicList::DynamicList(int* arrr, int s)
{
	size = s;
	arr = new int[size];
	for (int i = 0; i < size; ++i)
		arr[index++] = arrr[i];
}

void DynamicList::addEnd(int val)
{
	if (!(index < size))
	{
		int* temp = arr;
		arr = new int[++size];
		for (int i = 0; i < size; ++i)
			arr[i] = temp[i];
		delete[] temp;
	}
	arr[index++] = val;
}

void DynamicList::addStart(int val)
{
	if (arr != NULL)
	{
		if (!(index < size))
		{
			int* temp = arr;
			arr = new int[++size];
			for (int i = 0; i < size; ++i)
				arr[i + 1] = temp[i];
			delete[] temp;
		}
		arr[0] = val;
	}
}

void DynamicList::addGivenP(int val, int pos)
{
	if (pos >= 0 && pos < size)
	{
		arr[pos] = val;
	}
	else
	{
		cout << "Out of range\n";
		return;
	}
}

void DynamicList::delStart()
{
	if (arr != NULL)
	{
		int* temp = arr;
		arr = new int[--size];
		for (int i = 1; i < size + 1; ++i)
			arr[i - 1] = temp[i];
		delete[] temp;
	}
}

void DynamicList::delEnd()
{
	if (arr != NULL)
	{
		int* temp = arr;
		arr = new int[--size];
		for (int i = 0; i < size; ++i)
			arr[i] = temp[i];
		delete[] temp;
	}
}

void DynamicList::delGivenP(int pos)
{
	if (arr != NULL)
	{
		int* temp = arr;
		arr = new int[--size];
		int k = 0;
		for (int i = 0; i < size + 1; ++i)
		{
			if (k == pos)
				++k;
			arr[i] = temp[k++];
		}
		delete[] temp;
	}
}

int DynamicList::Next(int pos)
{
	if (pos > 0 && pos < size - 1)
		return arr[pos+1];
	else
		return -1;
}

int DynamicList::Previous(int pos)
{
	if (pos > 0 && pos < size - 1)
		return arr[pos-1];
	else
		return -1;
}

void DynamicList::print()
{
	if (arr != NULL)
	{
		cout << "\nArr: ";
		for (int i = 0; i < size; ++i)
			cout << arr[i] << "  ";
		cout << "\n";
	}
	else
		cout << "Array is empty\n";
}

bool DynamicList::Isempty()
{
	//if (current == 0)
	//	return true;
	return !index;
}

void DynamicList::replace(int ind, int val)
{
	if (ind >= 0 && ind < size)
	{
		arr[ind] = val;
	}
	else
	{
		cout << "Out of range\n";
		return;
	}
}

void DynamicList::clear()
{
	delete[] arr;
	arr = NULL;
}

bool DynamicList::checkDupli()
{
	if (arr != NULL)
	{
		int temp = 0, ind = 0;

		for (int i = 0; i < size; ++i, ++ind)
		{
			temp = arr[ind];

			for (int j = 0; j < size; ++j)
			{
				if (ind != j)
					if (temp == arr[j])
						return 1;
			}
		}
	}
	return 0;
}

int main()
{
	cout << "Welcome to MA LIst System\n\n\n";

	int size = 0;
	cout << "Enter the size of list: ";
	cin >> size;

	int* arr = new int[size];
	for (int i = 0; i < size; ++i)
	{
		cout << "Arr[" << i << "]: ";
		cin >> arr[i];
	}

	DynamicList obj(arr, size);

	delete[] arr;
	arr = NULL;

	int op = 1;
	int val, pos;
	while (op != 0)
	{
		cout << "\n\nWhich operation would you like to perform: \n";
		cout << "1. Add element in end\n"
			<< "2. Add element in start\n"
			<< "3. Add element at given position\n"
			<< "4. Delete start element\n"
			<< "5. Delete end element\n"
			<< "6. Show next element\n"
			<< "7. Show previous element\n"
			<< "8. Print list\n"
			<< "9. Is empty\n"
			<< "10. Replace element\n"
			<< "11. Clear list\n"
			<< "12. Delete given position\n"
			<< "13. Check duplicate\n\n";

		cout << "Choose: ";
		cin >> op;


		if (op == 1)
		{
			cout << "Enter value: ";
			cin >> val;
			obj.addEnd(val);
			obj.print();
		}
		else if (op == 2)
		{
			cout << "Enter value: ";
			cin >> val;
			obj.addStart(val);
			obj.print();
		}
		else if (op == 3)
		{
			cout << "Enter value: ";
			cin >> val;
			cout << "Enter position: ";
			cin >> pos;
			obj.addGivenP(val, pos);
			obj.print();
		}
		else if (op == 4)
		{
			obj.delStart();
			obj.print();
		}
		else if (op == 5)
		{
			obj.delStart();
			obj.print();
		}
		else if (op == 6)
		{
			cout << "Enter position: ";
			cin >> pos;
			obj.Next(pos);
			obj.print();
		}
		else if (op == 7)
		{
			cout << "Enter position: ";
			cin >> pos;
			obj.Previous(pos);
			obj.print();
		}
		else if (op == 8)
		{
			obj.print();
		}
		else if (op == 9)
		{
			cout << "Is empty: " << obj.Isempty();
		}
		else if (op == 10)
		{
			cout << "Enter value: ";
			cin >> val;
			cout << "Enter position: ";
			cin >> pos;
			obj.addGivenP(val, pos);
			obj.print();
		}
		else if (op == 11)
		{
			obj.clear();
		}
		else if (op == 12)
		{
			cout << "Enter position: ";
			obj.delGivenP(pos);
			obj.print();
		}
		else if (op == 13)
		{
			cout << "Check Duplicate: " << obj.Isempty();
		}
	}

	return 0;
}