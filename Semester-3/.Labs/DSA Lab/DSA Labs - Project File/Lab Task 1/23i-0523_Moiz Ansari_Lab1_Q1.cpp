#include<iostream>
#include<utility>
using namespace std;

int k = 0;
//a:
template <typename T>
T* symmetricDifferenceSets(T* set1, int size1, T* set2, int size2)
{
	T* arr = new T[size1 + size2];
	//int k = 0;
	bool b = 0;
	for (int i = 0; i < size1; ++i)
	{
		b = 0;
		for (int j = 0; j < size2; ++j)
		{
			if (set1[i] == set2[j])
			{
				b = 1;
				break;
			}
		}
		if (b == 0)
			arr[k++] = set1[i];
	}

	for (int i = 0; i < size2; ++i)
	{
		b = 0;
		for (int j = 0; j < size1; ++j)
		{
			if (set2[i] == set1[j])
			{
				b = 1;
				break;
			}
		}
		if (b == 0)
			arr[k++] = set2[i];
	}

	T* final = new T[k + 1];
	for (int i = 0; i < k + 1; ++i)
		final[i] = arr[i];

	return final;
}

//c.
template<typename T>
bool isSubset(T* set1, int size1, T* set2, int size2)
{
	bool b = 0, check = 1;
	for (int i = 0; i < size1; ++i)
	{
		b = 0;
		for (int j = 0; j < size2; ++j)
		{
			if (set1[i] == set2[j])
			{
				b = 1;
				break;
			}
		}
		if (b == 0)
		{
			check = 0;
			break;
		}
	}
	return check;
}

//d.
template<typename T>
bool elementExists(T* set, int size, T element)
{
	bool check = 0;
	for (int i = 0; i < size; ++i)
	{
		if (set[i] == element)
		{
			check = 1;
			break;
		}
	}
	return check;
}

//b:
template <typename T>
pair<T, T>* cartesianProductSets(T* set1, int size1, T* set2, int size2)
{
	int size = size1 * size2, k=0;
	pair<T, T>* arr = new pair<T, T>[size];

	for (int i = 0; i < size1; ++i)
	{
		for (int j = 0; j < size2; ++j)
		{
			arr[k++]= make_pair(set1[i], set2[j]);
		}
	}

	return arr;
}

//int main()
//{
//	// a.
//
//	int s1 = 9, s2 = 13;
//	double* A = new double[s1] { 10.43, 4.3, 5.61, 6.90, 11.57, 12.11, 3.8, 2.4, 9.5 };
//	double* B = new double[s2] {11.01, 12.34, 16.5, 3.8, 8.1, 2.4, 9.11, 12.11, 6.75, 10.43, 20.2, 2.1, 4.3};
//	double* Tarr = new double[s1 + s2];
//
//	Tarr = symmetricDifferenceSets(A, s1, B, s2);
//
//	cout << "a:\n";
//	for (int i = 0; i < k; ++i)
//	{
//		cout << Tarr[i] << "  ";
//	}
//	cout << endl << endl;
//
//	// c.
//	s1 = 3;
//	s2 = 4;
//	int* C1 = new int [s1] {3, 5};
//	int* C2 = new int[s2] {2, 3, 5, 6};
//
//	cout << "c:\n";
//	cout << "IsSubset: " << isSubset(C1, s1, C2, s2) << endl << endl;
//
//	//d.
//	cout << "d:\n" << elementExists(C1, s1, 3) << endl << endl;
//
//	//b.
//	pair<int, int>* arr = new pair<int, int>[s1 * s2];
//	arr = cartesianProductSets(C1, s1, C2, s2);
//
//	cout << "b:\nPairs: {";
//	for (int i = 0; i < s1 * s2; ++i)
//	{
//		cout<<"(" << arr[i].first <<", " << arr[i].second << "), ";
//	}
//	cout << "\b\b}\n\n";
//
//	return 0;
//}