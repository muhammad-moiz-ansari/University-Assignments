#include <iostream>
#include "23i-0523_Moiz Ansari_Q2.h"
using namespace std;


template<typename T>
List<T>::List(int s)
{
	capacity = s;
	values = new T[s];
	index = 0;
}

template<typename T>
bool List<T>::insert(T item)
{
	if (values != NULL)
	{
		if (index < capacity)
		{
			values[index++] = item;
			return true;
		}
		else
			return false;
	}
}

template<typename T>
bool List<T>::insertAt(T item, int index)
{
	if (values != NULL)
	{
		if (this->index < capacity)
		{
			for (int i = capacity - 1; i >= index; --i)
			{
				values[i] = values[i - 1];
			}
			values[index] = item;

			++(this->index);

			return true;
		}
		else
			return false;
	}
}

template<typename T>
bool List<T>::insertAfter(T itemTobeInserted, T item)
{
	if (values != NULL)
	{
		if (this->index < capacity)
		{
			int ind = 0;
			for (int i = 0; i < capacity; ++i)
			{
				ind = i;
				if (values[i] == item)
					break;
			}
			for (int i = capacity - 1; i >= ind; --i)
			{
				values[i] = values[i - 1];
			}
			values[index] = itemTobeInserted;

			++(this->index);

			return true;
		}
		else
			return false;
	}
}

template<typename T>
bool List<T>::insertBefore(T itemTobeInserted, int item)
{
	if (values != NULL)
	{
		if (this->index < capacity)
		{
			int ind = 0;
			for (int i = 0; i < capacity; ++i)
			{
				ind = i;
				if (values[i] == item)
					break;
			}
			insertAt(itemTobeInserted, ind);

			return true;
		}
		else
			return false;
	}
}

template<typename T>
bool List<T>::isEmpty()
{
	return !index;
}

template<typename T>
bool List<T>::isFull()
{
	if (index < capacity)
		return false;
	else
		return true;
}

template<typename T>
bool List<T>::remove(T item)
{
	if (values != NULL)
	{
		int ind = search(item);
		for (int i = ind; i < capacity; ++i)
		{
			values[i] = values[i + 1];
		}
		--index;

		return true;
	}
	return false;
}

template<typename T>
bool List<T>::removeBefore(T item)
{
	if (values != NULL)
	{
		int ind = search(item) - 1;
		for (int i = ind; i < capacity; ++i)
		{
			values[i] = values[i+1];
		}
		--index;

		return true;
	}
	return false;
}

template<typename T>
bool List<T>::removeAfter(T item)
{
	if (values != NULL)
	{
		int ind = search(item) + 1;
		for (int i = ind; i < capacity; ++i)
		{
			values[i] = values[i+1];
		}
		--index;

		return true;
	}
	return false;
}

template<typename T>
bool List<T>::operator==(List& L)
{
	if (values != NULL)
	{
		if (this->capacity != L.capacity)
			return false;

		for (int i = 0; i < capacity; ++i)
			if (this->values[i] != L.values[i])
				return false;

		return true;
	}
}

template<typename T>
void List<T>::reverse()
{
	if (values != NULL)
	{
		for (int i = 0; i < index/2; ++i)
		{
			T temp = values[index - 1 - i];
			values[index - 1 - i] = values[i];
			values[i] = temp;
		}
	}
}

template<typename T>
int List<T>::search(T item)
{
	if (values != NULL)
	{
		int ind = 0;
		for (int i = 0; i < capacity; ++i)
		{
			ind = i;
			if (values[i] == item)
				break;
		}
		return ind;
	}
	else
		return -1;
}

template<typename T>
void List<T>::print()
{
	if (values != NULL)
	{
		cout << "\nArr: ";
		for (int i = 0; i < index; ++i)
			cout << values[i] << "  ";
		cout << "\n";
	}
	else
		cout << "List is empty\n";
}


//int main()
//{
//	cout << "--- Welcome to MA LIst System ---\n\n\n";
//
//	int size = 0, val;
//	cout << "Enter the capacity of list: ";
//	cin >> size;
//
//	List<int> obj(size);
//
//	for (int i = 0; i < size; ++i)
//	{
//		cout << "Arr[" << i << "]: ";
//		cin >> val;
//		obj.insert(val);
//	}
//
//	int op = 1;
//	int pos;
//	while (op != 14)
//	{
//		cout << "\n\nWhich operation would you like to perform: \n";
//		cout << "1. Insert element\n"
//			<< "2. Insert element At given position\n"
//			<< "3. Insert element after\n"
//			<< "4. Insert element before\n"
//			<< "5. Remove element\n"
//			<< "6. Remove element before\n"
//			<< "7. Remove element after\n"
//			<< "8. Compare equality\n"
//			<< "9. Is empty\n"
//			<< "10. Is full\n"
//			<< "11. Reverse\n"
//			<< "12. Search\n"
//			<< "13. Print\n"
//			<< "14. Exit\n\n";
//
//		cout << "Choose: ";
//		cin >> op;
//
//
//		if (op == 1)
//		{
//			cout << "Enter value: ";
//			cin >> val;
//			obj.insert(val);
//			obj.print();
//		}
//		else if (op == 2)
//		{
//			cout << "Enter value: ";
//			cin >> val;
//			cout << "Enter position: ";
//			cin >> pos;
//			obj.insertAt(val, pos);
//			obj.print();
//		}
//		else if (op == 3)
//		{
//			cout << "Enter value: ";
//			cin >> val;
//			cout << "Enter position: ";
//			cin >> pos;
//			obj.insertAfter(val, pos);
//			obj.print();
//		}
//		else if (op == 4)
//		{
//			cout << "Enter value: ";
//			cin >> val;
//			cout << "Enter position: ";
//			cin >> pos;
//			obj.insertBefore(val, pos);
//			obj.print();
//		}
//		else if (op == 5)
//		{
//			cout << "Enter value: ";
//			cin >> val;
//			obj.remove(val);
//			obj.print();
//		}
//		else if (op == 6)
//		{
//			cout << "Enter value: ";
//			cin >> val;
//			obj.removeBefore(val);
//			obj.print();
//		}
//		else if (op == 7)
//		{
//			cout << "Enter value: ";
//			cin >> val;
//			obj.removeAfter(val);
//			obj.print();
//		}
//		else if (op == 8)
//		{
//			cout << "Equal? " << (obj == obj) << endl;
//		}
//		else if (op == 9)
//		{
//			cout << "Is empty: " << obj.isEmpty() << endl;
//		}
//		else if (op == 10)
//		{
//			cout << "Is full: " << obj.isFull() << endl;
//		}
//		else if (op == 11)
//		{
//			obj.reverse();
//			obj.print();
//		}
//		else if (op == 12)
//		{
//			cout << "Enter value: ";
//			cin >> val;
//			cout << "Value at index: " << obj.search(val) << endl;
//		}
//		else if (op == 13)
//		{
//			obj.print();
//		}
//	}
//
//	return 0;
//}


