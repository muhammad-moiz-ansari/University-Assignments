#pragma once
#include <iostream>
#include <string>
using namespace std;

//Problem 1
string assignAndDisplayValues(int a, int b)
{
	int* ptrA = &a;
	int* ptrB = &b;

	string str = "Value of 'a' through pointer ptrA: " + to_string(*ptrA) + "\n" + "Value of 'b' through pointer ptrB: " + to_string(*ptrB) + "\n";

	return str;
}

//Problem 2
string printAndUpdatePointer(string inputStr, int pointerPosition)
{
	string* ptr2;
	ptr2 = &inputStr;

	string str = "Index 0: " + *ptr2 + ", Pointer Position : " + to_string(pointerPosition) + ", Letter 't' : t\n";
	++ptr2;
	++pointerPosition;
	return str;
}

string printPointerAndLetters(string inputStr, int pointerPosition)
{
	string* ptr2;
	ptr2 = &inputStr;

	string r = *(ptr2 + 2), g = *(ptr2 + 5);

	string str = "Pointer: " + to_string(pointerPosition) + ", Letters 'r' and 'g': " + r + " " + g + "\n";


	return str;
}

//Problem 3
char* calculateGrades(int arr[], int size)
{
	char* grades = new char[size];

	for (int i = 0; i < size; ++i)
	{
		if (*(arr+i) >= 91 && *(arr + i) <= 100)
			*(grades + i) = 'A';
		else if (*(arr + i) >= 76 && *(arr + i) <= 90)
			*(grades + i) = 'B';
		else if (*(arr + i) >= 60 && *(arr + i) <= 75)
			*(grades + i) = 'C';
		else if (*(arr + i) >= 51 && *(arr + i) <= 59)
			*(grades + i) = 'D';
		else
			*(grades + i) = 'F';
	}
	return grades;
}

//Problem 4
int* rotateArray(int* arr, int sizeofArray, int n, int m)		//int arr[] = { 1,2,3,4,5,6 };
																//		{ 1,2,3,4,5,6 };
																//int a[] = { 2,3,1,5,6,4 };
{
	int size = sizeofArray / m, temp;
	for (int i = 0; i < sizeofArray; i += size)
	{
		for (int k = 0; k < n; ++k)
		{
			temp = arr[size + i - 1];
			for (int j = size + i - 1; j > i; --j)
			{

				arr[j] = arr[j - 1];
			}
			arr[i] = temp;
		}
	}

	return arr;
}