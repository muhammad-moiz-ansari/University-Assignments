#include <iostream>
using namespace std;

int findInsertPosition(int arr[], int n, int x)
{
	int start = 0, end = n - 1, ind = 0;

	if (x < arr[0])
		return 0;
	if (x > arr[n - 1])
		return n;

	while (start <= end)
	{
		ind = start + ((end - start) / 2);

		if (arr[ind] == x)
			return ind;
		else
		{
			if (x > arr[ind])
				start = ind;
			else
				end = ind;

			if (end - start <= 1)
			{
				return start + 1;
			}
		}
	}
}
//
//int main()
//{
//	const int size = 6;
//	int arr1[size] = { 1, 3, 5, 7, 9, 11 };
//
//	cout << "In Middle: "<< findInsertPosition(arr1, size, 6)<<endl;
//
//	cout<<"In start: "<< findInsertPosition(arr1, size, 0) << endl;
//
//	cout << "In last: " << findInsertPosition(arr1, size, 12) << endl;
//
//	cout << "Already there: " << findInsertPosition(arr1, size, 9) << endl;
//
//
//	return 0;
//}