#include <iostream>
#include <cmath>
using namespace std;

class Node
{
public:
	int data;
	bool isFull = 0;
	Node(int d = 0, bool b = 0)
	{
		data = d;
		isFull = b;
	}
};


class HashTable
{
public:
	int capacity;
	int currkeys;
	Node* arr;
	HashTable(int c = 50, Node** l = NULL)
	{
		capacity = c;
		arr = new Node[capacity];
		currkeys = 0;
	}
	int Hash_Function(int key) // You can use the division hash function
	{
		return key % capacity;
	}
	void insert(int key, int value)
	{
		if (currkeys >= capacity)		//extending size
		{
			int c = capacity;
			capacity += capacity;
			Node* temp = new Node[capacity];
			for (int i = 0; i < c; ++i)
			{
				temp[i].data = arr[i].data;
				temp[i].isFull = arr[i].isFull;
			}
			delete[] arr;
			arr = temp;
			temp = NULL;
		}
		int ind = Hash_Function(key);
		int i = 1;
		if (currkeys + 2 < capacity)
			while (1)
			{
				if (arr[ind].isFull == 0)
					break;
				ind = Hash_Function(key + pow(i++, 2));
			}
		else
			while (1)
			{
				if (arr[ind].isFull == 0)
					break;
				ind = Hash_Function(key + i++);
			}
		arr[ind].data = value;
		arr[ind].isFull = 1;
		++currkeys;
	}
	void find(int value)
	{
		int ind = Hash_Function(key);
		int i = 1;
		if (currkeys + 2 < capacity)
			while (1)
			{
				if (arr[ind].isFull == 0)
					break;
				ind = Hash_Function(key + pow(i++, 2));
			}
		else
			while (1)
			{
				if (arr[ind].isFull == 0)
					break;
				ind = Hash_Function(key + i++);
			}
		arr[ind].isFull = 0;
		--currkeys;
	}
	void remove(int key)
	{
		if (currkeys == 0)
		{
			cout << "Hashtable is empty!\n";
			return;
		}
		int ind = Hash_Function(key);
		int i = 1;
		while (1)
		{
			if (arr[ind].isFull == 0)
				break;
			ind = Hash_Function(ind + pow(i++, 2));
		}
		arr[ind].isFull = 0;
		--currkeys;
	}
	/*
	int search(int value)
	{
		for (int i = 0; i < capacity; ++i)
		{
			Node* temp = list[i];
			while (temp)
			{
				if (temp->data == value)
					return temp->key;
				temp = temp->next;
			}
		}
		return -1;
	}*/
	void display()
	{
		cout << "\nHash Table:\n";
		for (int i = 0; i < capacity; ++i)
		{	
			if (arr[i].isFull)
				cout << "Key " << i << ": " << arr[i].data << endl;
		}
	}
	~HashTable()
	{
		delete arr;
	}
};
//
//int main()
//{
//	int cap = 0;
//	cout << "Enter the capacity for hash-table: ";
//	while (1)
//	{
//		cin >> cap;
//		if (cap > 0)
//			break;
//		cout << "Invalid input...Enter again(Greater than 0): ";
//	}
//	HashTable hash(cap);
//
//	int ch = 1, val = 0, key = 0;
//
//	while (1)
//	{
//		cout << "\n\nChoose on of following:\n"
//			<< "1. Insert\n2. Remove\n3. Display\n0. Exit\n\n";
//		cout << "Choice: ";
//		cin >> ch;
//
//		if (ch == 1)
//		{
//			cout << "Enter value: ";
//			cin >> val;
//			cout << "Enter key: ";
//			cin >> key;
//			hash.insert(key, val);
//		}
//		else if (ch == 2)
//		{
//			cout << "Enter key: ";
//			cin >> key;
//			hash.remove(key);
//		}
//		else if (ch == 3)
//		{
//			hash.display();
//		}
//		else if (ch == 0)
//			break;
//		else
//			cout << "Wrong input\n";
//	}
//
//
//	return 0;
//}