#include <iostream>
using namespace std;

template <typename T>
T* sumOfArrays(const T arr1[], const T arr2[], int size)
{
	T* res = new T[size];

	for (int i = 0; i < size; ++i)
	{
		res[i] = arr1[i] + arr2[i];
	}

	return res;
}

int main()
{
	int arr1[] = { 1, 2, 3, 4 };
	int arr2[] = { 1, 2, 3, 4 };
	int size = sizeof(arr1) / sizeof(arr1[0]);
	//int expected[] = { 2, 4, 6, 8 };

	int* result = sumOfArrays(arr1, arr2, size);

	cout << "Arr:\n";
	for (int i = 0; i < size; ++i) 
	{
		cout << result[i] << "  ";
	}
	cout << endl;

	return 0;
}