#include <iostream>
using namespace std;

const int SIZE = 3;
template <typename T>
T** rotateMatrix90DegreesClockwise(T(&matrix)[SIZE][SIZE])
{
	T** arr = new T*[SIZE];
	for (int i = 0; i < SIZE; ++i)
		arr[i] = new T[SIZE];


	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			arr[j][SIZE-1-i] = matrix[i][j];
		}
	}

	for (int i = 0; i < SIZE; ++i)
	{
		for (int j = 0; j < SIZE; ++j)
		{
			matrix[i][j]=arr[i][j];
		}
	}

	return arr;
}

//int main()
//{
//	int arr[][3] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//
//	int** arr2 = new int*[SIZE];
//	for (int i = 0; i < SIZE; ++i)
//		arr2[i] = new int[SIZE];
//
//	arr2 = rotateMatrix90DegreesClockwise(arr);
//
//	for (int i = 0; i < SIZE; ++i)
//	{
//		for (int j = 0; j < SIZE; ++j)
//		{
//			cout << arr2[i][j] << "  ";
//		}
//		cout << endl;
//	}
//
//	for (int i = 0; i < SIZE; ++i)
//		delete[] arr2[i];
//	delete[] arr;
//
//	return 0;
//}