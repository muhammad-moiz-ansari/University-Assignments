#include<iostream>
using namespace std;


template<typename T>
T* RemoveDups(T* set, int size)
{
	int* num = new int[size];
	for (int i = 0; i < size; ++i)
		num[i] = 0;

	
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (set[i] == set[j] && i != j)
			{
				for (int k = i; k < size-1; ++k)
					set[k] = set[k + 1];
				--size;
				j = -1;
			}
		}
	}

	//Making result array
	T* final = new T[size];
	for (int i = 0; i < size; ++i)
	{
		final[i] = set[i];
	}

	return final;
}

int main()
{
	int No_of_Sections[] = {2, 3, 1 , 3, 4, 3};
	string Subject[] = { "Math", "OOP", "DataStructure", "OOP", "OOP" };
	string Name_data[] = { "sara", "mary", "larry", "sara", "sara" };

	int* nos = new int[4];
	string* subj = new string[3];
	string* nd = new string[3];

	nos = RemoveDups(No_of_Sections, 5);
	subj = RemoveDups(Subject, 4);
	nd = RemoveDups(Name_data, 4);

	for (int i = 0; i < 4; ++i)
	{
		cout << nos[i] << "  ";
	}
	cout << endl << endl;

	for (int i = 0; i < 3; ++i)
	{
		cout << subj[i] << "  ";
	}
	cout << endl << endl;

	for (int i = 0; i < 3; ++i)
	{
		cout << nd[i] << "  ";
	}
	cout << endl << endl;

	return 0;
}