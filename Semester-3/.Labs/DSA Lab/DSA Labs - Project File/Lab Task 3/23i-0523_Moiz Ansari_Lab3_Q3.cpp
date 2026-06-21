#include <iostream>
using namespace std;

const int SIZE_M = 2, SIZE_N = 2;
template <typename T>
bool calculateInverse(T matrix[SIZE_M][SIZE_N], T inverse[SIZE_M][SIZE_N])
{
	//New arr
	/*T** res = new T * [SIZE_M];
	for (int i = 0; i < SIZE_M; ++i)
		res[i] = new T[SIZE_N];*/

	T** inv = new T * [SIZE_M];
	for (int i = 0; i < SIZE_M; ++i)
		inv[i] = new T[SIZE_N];

	//Inverse
	inv[0][0] = matrix[1][1];
	inv[1][1] = matrix[0][0];

	inv[0][1] = matrix[0][1] * -1;
	inv[1][0] = matrix[1][0] * -1;

	T det = (matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]);
	if (det == 0)
		return 0;

	for (int i = 0; i < SIZE_M; ++i)
		for (int j = 0; j < SIZE_N; ++j)
			inverse[i][j] = inv[i][j] * (1 / det);

	//Delete
	for (int i = 0; i < SIZE_M; ++i)
		delete[] inv[i];
	delete[] inv;

	return 1;
}

template <typename T>
bool matricesAreEqual(T A[SIZE_M][SIZE_N], T B[SIZE_M][SIZE_N])
{
	for (int i = 0; i < SIZE_M; ++i)
		for (int j = 0; j < SIZE_N; ++j)
			if (A[i][j] != B[i][j])
				return 0;

	return 1;
}

const int row = 3, col = 3;
template <typename T>
T calculateDeterminant(T arr[row][col])
{
	T det = 0, d = 0;
	int k = 0;

	d = arr[1][1] * arr[2][2] - arr[1][2] * arr[2][1];
	det += arr[0][k++] * d;

	d = arr[1][0] * arr[2][2] - arr[1][2] * arr[2][0];
	det += (-1 * arr[0][k++]) * d;

	d = arr[1][0] * arr[2][1] - arr[2][0] * arr[1][1];
	det += arr[0][k++] * d;

	return det;
}

//int main()
//{
//	float arr[][2] = { 1, 2, 3, 4 };
//
//	New arr
//	float** res = new float* [SIZE_M];
//	for (int i = 0; i < SIZE_M; ++i)
//		res[i] = new float[SIZE_N];
//
//	res = calculateInverse(arr);
//
//	for (int i = 0; i < SIZE_M; ++i)
//	{
//		for (int j = 0; j < SIZE_N; ++j)
//		{
//			cout << res[i][j] << "  ";
//		}
//		cout << endl;
//	}
//
//	Delete
//	for (int i = 0; i < SIZE_M; ++i)
//		delete[] res[i];
//	delete[] res;
//
//	return 0;
//}