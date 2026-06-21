#include <iostream>
using namespace std;

template <typename T>
class Container 
{
private:
	T* arr;
	int size;
public:
	Container(T* array, int s)
	{
		size = s;
		arr = new T[size];
		for (int i = 0; i < size; ++i)
		{
			arr[i] = array[i];
		}
	}
	T* sortInWaveForm()
	{
		bool b = 1;
		while (b == 1)
		{
			b = 0;
			for (int i = 0; i < size - 1; ++i)
			{
				if (i % 2 == 0)
				{
					if (arr[i] < arr[i + 1])
					{
						b = 1;
						T temp = arr[i + 1];
						arr[i + 1] = arr[i];
						arr[i] = temp;
					}
				}
				if (i % 2 != 0)
				{
					if (arr[i] > arr[i + 1])
					{
						b = 1;
						T temp = arr[i + 1];
						arr[i + 1] = arr[i];
						arr[i] = temp;
					}
				}
			}
		}

		return arr;
	}
};

int main()
{
	int nums1[] = { 4, 5, 2, 3, 1, 0, 45, 7 };

	int size1 = sizeof(nums1) / sizeof(nums1[0]);

	int expected1[] = { 5,  2,  4,  1,  3,  0,  45,  7 };
	
	Container<int> wave1(nums1, size1);

	int* p1 = wave1.sortInWaveForm();

	cout << "Arr2: \n";
	for (int i = 0; i < size1; ++i)
	{
		cout << p1[i] << "  ";
	}
	cout << endl;


	return 0;
}