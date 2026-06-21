#include <iostream>
using namespace std;

template <typename T>
void selectionSort(T* arr, int size)
{
	int ind = 0;
	T min = 0, temp = 0;

	for (int i = 0; i < size; ++i)
	{
		ind = i;
		min = arr[i];
		for (int j = i; j < size; ++j)
		{
			if (arr[j]< min)
			{
				min = arr[j];
				ind = j;
			}
		}
		temp = arr[ind];
		arr[ind] = arr[i];
		arr[i] = temp;
	}
}

template <typename T>
void bubbleSort(T* arr, int size)
{
	T temp;
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size - i - 1; ++j)
		{
			if (arr[j] > arr[j + 1])
			{
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

//int main()
//{
//	int arr1[] = { 6, 4, 5, 1, 3, 2 };
//	int arr2[] = { 7, 5, 3, 1, 2, 4, 6 };
//
//
//	// Sort the first row using insertion sort
//	selectionSort(arr1, 6);
//
//	cout << "Arr1:\n";
//	for (int i = 0; i < 6; i++) {
//		cout << arr1[i] << "  ";
//	}
//	cout << endl;
//
//	// Sort the third row using bubble sort
//	bubbleSort(arr2, 7);
//
//	cout << "Arr2:\n";
//	for (int i = 0; i < 7; i++) {
//		cout << arr2[i] << "  ";
//	}
//	cout << endl;
//
//	return 0;
//}