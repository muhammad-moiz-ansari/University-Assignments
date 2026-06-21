#include <iostream>
using namespace std;

int linearSearchString(string arr[], int n, string target)
{
	for (int i = 0; i < n; ++i)
	{
		if (arr[i] == target)
			return i;
	}
	return -1;
}

//int main()
//{
//	const int size = 5;
//
//	string strings1[size] = { "a", "b", "c", "d", "e" };
//	cout << "In array: " << linearSearchString(strings1, size, "c") << endl;
//
//	// If found in the array:
//	cout << "Not in array: " << linearSearchString(strings1, size, "z") << endl; // Expected result is -1 since "z" is not in the array
//
//
//
//	return 0;
//}