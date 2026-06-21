#include <iostream>
using namespace std;

class Node
{
public:
	int key;
	int data;
	Node* next;
	Node(int k = 0, int d = 0, Node* n = NULL)
	{
		key = k;
		data = d;
		next = n;
	}
};


class HashTable
{
public:
	int capacity;
	Node** list;
	HashTable(int c = 5, Node** l = NULL)
	{
		capacity = c;
		list = new Node * [capacity];
		for (int i = 0; i < capacity; ++i)
			list[i] = NULL;
	}
	int Hash_Function(int key) // You can use the division hash function
	{
		return key % capacity;
	}
	void insert(int key, int value)
	{
		int ind = Hash_Function(key);
		Node* temp = list[ind];
		list[ind] = new Node(key, value, temp);
		temp = NULL;
	}
	void remove_node(int key)
	{
		int ind = Hash_Function(key);
		if (list[ind] == NULL)
			return;
		else
		{
			Node* temp = list[ind];
			list[ind] = temp->next;
			delete temp;
			temp = NULL;
		}
	}
	void remove(int key)
	{
		int ind = Hash_Function(key);
		if (list[ind] == NULL)
			return;
		else
		{
			while (list[ind])
				remove_node(ind);
		}
	}
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
	}
	void display(int key)
	{
		int ind = Hash_Function(key);
		cout << "Key " << key << ": [  ";
		Node* temp = list[ind];
		while (temp)
		{
			cout << temp->data << ", ";
			temp = temp->next;
		}
		cout << "\b\b ]";
	}
	~HashTable()
	{
		for (int i = 0; i < capacity; ++i)
		{
			while (list[i])
				remove(i);
		}
		delete list;
	}
};

int main()
{
	int cap = 0;
	cout << "Enter the capacity for hash-table: ";
	while (1)
	{
		cin >> cap;
		if (cap > 0)
			break;
		cout << "Invalid input...Enter again(Greater than 0): ";
	}
	HashTable hash(cap);

	int ch = 1, val = 0, key = 0;
	
	while (1)
	{
		cout << "\n\nChoose on of following:\n"
			 << "1. Insert\n2. Remove\n3. Search\n4. Display\n0. Exit\n\n";
		cout << "Choice: ";
		cin >> ch;

		if (ch == 1)
		{
			cout << "Enter value: ";
			cin >> val;
			cout << "Enter key: ";
			cin >> key;
			hash.insert(key, val);
		}
		else if (ch == 2)
		{
			cout << "Enter key: ";
			cin >> key;
			hash.remove(key);
		}
		else if (ch == 3)
		{
			cout << "Enter value: ";
			cin >> val;
			int s = hash.search(val);
			cout << "Value is in key " << s << "\n";
		}
		else if (ch == 4)
		{
			cout << "Enter key: ";
			cin >> key;
			hash.display(key);
		}
		else if (ch == 0)
			break;
		else
			cout << "Wrong input\n";
	}


	return 0;
}