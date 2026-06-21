#include <iostream>
# include <string>
using namespace std;

//template <typename T>
//void bubbleSort(T* arr, int size)
//{
//	T temp;
//	for (int i = 0; i < size; ++i)
//	{
//		for (int j = 0; j < size - i - 1; ++j)
//		{
//			if (arr[j] > arr[j + 1])
//			{
//				temp = arr[j];
//				arr[j] = arr[j + 1];
//				arr[j + 1] = temp;
//			}
//		}
//	}
//}

void vowelFreq(char text[])
{
	int size = 0;
	//Size of string:
	for (; text[size] != '\0'; ++size);
	++size;

	cout << "Size: " << size << endl;

	//Removing consonants:
	for (int i = 0; i < size; ++i)
	{
		if (!(text[i] == 'a' || text[i] == 'e' || text[i] == 'i' || text[i] == 'o' || text[i] == 'u' || text[i] == '\0'))
		{
			for (int j = i; j < size; ++j)
				text[j] = text[j + 1];
			--i;
			--size;
		}
	}
	text[size - 1] = 'z';
	text[size++] = '\0';

	bubbleSort(text, size - 1);

	cout << endl << text << endl;

	//Binary sort:
	int start = 0, end = size - 2, ind = 0, count;
	char arr[] = "aeiou";

	//Selecting vowels:
	int select[5];
	bool q = 0;
	cout << "Choose which vowels to count frequency (Press 0 or 1):\n";
	for (int i = 0; i < 5; ++i)
	{
		cout << "Select " << arr[i] << "? ";
		cin >> q;
		select[i] = q;
	}

	for (int i = 0; i < 5; ++i)
	{
		count = 0;
		end = size - 2;
		ind = 0;

		while (start <= end)
		{
			ind = start + ((end - start) / 2);

			if (start == end)
				--end;

			if (text[ind] == arr[i])
			{
				count++;
				text[ind] = text[ind] + 1;
			}
			if (end - start == 1)
			{
				if (text[start] == arr[i])
				{
					count++;
					text[start] = text[start] + 1;
				}
				if (text[end] == arr[i])
				{
					count++;
					text[end] = text[end] + 1;
				}
				break;
			}

			if (start > end)
				break;
			else if (arr[i] > text[ind])
				start = ind;
			else
				end = ind;
		}
		start += count;
		if (select[i])
			cout << arr[i] << " appears " << count << " times\n";
	}

}

int main()
{	
	const int size = 100;
	char text[size];

	cout << "Enter text: ";
	cin.getline(text, size);
	//cout << text << endl;
	
	vowelFreq(text);
	
	return 0;
}