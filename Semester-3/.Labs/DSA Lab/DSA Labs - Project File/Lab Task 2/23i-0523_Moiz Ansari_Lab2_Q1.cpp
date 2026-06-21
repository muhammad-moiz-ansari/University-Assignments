#include <iostream>
using namespace std;

template<typename T>
T findMostFrequentElement(T arr[], int size)
{
	int ccount = 0, mcount = 0;
	T n = 0, num = 0;
	for (int i = 0; i < size; ++i)
	{
		n = arr[i];
		ccount = 0;
		for (int j = 0; j < size; ++j)
		{
			if (arr[j] == n)
				++ccount;
		}
		if (ccount > mcount)
		{
			mcount = ccount;
			num = n;
		}
	}

	return num;
}

int main()
{
	int arr1[] = { 2, 3, 5, 7, 3, 2, 1, 5, 3 };
	int size = sizeof(arr1) / sizeof(arr1[0]);
	cout << "Arr1: " << findMostFrequentElement(arr1, size) << endl;

	double arr2[] = { 2.1, 3.2, 5.1, 7.1, 3.2, 2.1, 1.1, 3.2, 5.1, 3.1 };
	int size1 = sizeof(arr2) / sizeof(arr2[0]);

	cout << "Arr2: " << findMostFrequentElement(arr2, size) << endl;


	return 0;
}