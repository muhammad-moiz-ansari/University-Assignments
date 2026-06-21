#include <iostream>
using namespace std;

template <typename T>
void rearrangeArray(T arr[], int size)
{
	T* arr1 = new T[size];
	for (int i = 0; i < size; ++i)
		arr1[i] = arr[i];
	cout << "\narr1:\n";
		for (int i = 0; i < size; ++i)
			cout << arr1[i] << "  ";
	cout << "\n";


	T* arr2 = new T[size];
	for (int i = 0; i < size; ++i)
		arr2[size-1-i] = arr[i];
	cout << "\narr2:\n";
	for (int i = 0; i < size; ++i)
		cout << arr2[i] << "  ";
	cout << "\n";

	int c1 = 0, c2 = 0;
	for (int i = 0; i < size; ++i)
	{
		if (i % 2 == 0)
		{
			arr[i] = arr2[c2++];
		}
		if (i % 2 != 0)
		{
			arr[i] = arr1[c1++];
		}
	}


}

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int size = sizeof(arr) / sizeof(arr[0]);
	//int expected[] = { 10, 1, 9, 2, 8, 3, 7, 4, 6, 5 }; // Manually computed expected output

	rearrangeArray(arr, size);

	cout<<"\nArr:\n";
	for (int i = 0; i < size; ++i)
	{
		cout << arr[i] << "  ";
	}


	return 0;
}