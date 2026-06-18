#include <iostream>
#include "Header.h"
using namespace std;


int main()
{
	//-----Problem 1-----
	int a, b;
	cout << "Enter a: ";
	cin >> a;
	cout << "Enter b: ";
	cin >> b;

	cout << assignAndDisplayValues(a, b) << endl;

	//-----Problem 2-----
	string inputStr = "A string";
	int pointerPosition = 0;
	cout << printAndUpdatePointer(inputStr, pointerPosition);
	cout << printPointerAndLetters(inputStr, pointerPosition) << endl;

	//-----Problem 3-----
	int size;
	cout << "Enter size of array: ";
	cin >> size;

	int* arr = new int[size];
	char* grr = new char[size];

	cout << "Enter values of array: \n";
	for (int i = 0; i < size; ++i)
	{
		cout << "arr[" << i << "]" << ": ";
		cin >> *(arr + i);
		if (arr[i] < 0 || arr[i] > 100)
		{
			--i;
			cout << "Enter value between 0 and 100\n";
		}
	}
	grr = calculateGrades(arr, size);
	for (int i = 0; i < size; ++i)
	{
		cout << *(grr + i);
	}
	//delete[] grades;
	delete[] grr;

	//----------Problem 4-----------
	int sizeofArray, m, n;
	cout << "Enter size of array: ";
	cin >> sizeofArray;
	cout << "Enter m: ";
	cin >> m;
	cout << "Enter n: ";
	cin >> n;

	int* brr = new int[sizeofArray];

	rotateArray(brr, sizeofArray, n, m);


	return 0;
}
