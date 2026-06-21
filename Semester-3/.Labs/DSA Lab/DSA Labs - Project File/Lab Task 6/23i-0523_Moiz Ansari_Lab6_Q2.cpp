#include <iostream>
using namespace std;

template <typename T>
class Node
{
public:
	T data;
	Node<T>* next;

	Node(int d = 0, Node* n = NULL)
	{
		data = d;
		next = n;
	}

	T getData()
	{
		return data;
	}
	Node* getNext()
	{
		return next;
	}
	void setData(T d)
	{
		data = d;
	}
	void setNext(Node<T> n)
	{
		next = n;
	}
};

template <typename T>
class SLinkedList
{
public:
	Node<T>* head;

	SLinkedList()
	{
		head = NULL;
	}

	Node<T>* insert(T val)
	{
		Node<T>* temp = head;

		if (temp != NULL)
			while (temp->next)
				temp = temp->next;

		Node<T>* temp2 = new Node<T>;
		temp2->data = val;
		if (temp != NULL)
		{
			temp2->next = temp->next;
			temp->next = temp2;
		}
		else
		{
			temp2->next = temp;
			temp = temp2;
		}
		if (head == NULL)
			head = temp;
		temp = NULL;
		temp2 = NULL;

		return head;
	}

	Node<T>* insertAtHead(T val)
	{
		Node<T>* temp = head;

		Node<T>* temp2 = new Node<T>;
		temp2->data = val;
		if (temp != NULL)
		{
			temp2->next = temp;
			temp = temp2;
		}
		head = temp;
		temp = NULL;
		temp2 = NULL;

		return head;
	}

	Node<T>* InsertAtIndex(T val, int index)
	{
		if (index < 0)
			return NULL;

		Node<T>* temp = head;

		if (temp != NULL)
			for (int i = 0; temp->next && i < index; ++i, temp = temp->next);

		Node<T>* temp2 = new Node<T>;
		temp2->data = val;
		if (temp != NULL)
		{
			temp2->next = temp->next;
			temp->next = temp2;
		}
		else
		{
			temp2->next = temp;
			temp = temp2;
		}
		if (head == NULL)
			head = temp;
		temp = NULL;
		temp2 = NULL;

		return head;
	}

	int search(T val)
	{
		Node<T>* temp = head;
		int index = 0;

		if (temp != NULL)
			for (; temp && temp->data != val; temp = temp->next, index++);

		if (temp == NULL)
			return -1;
		return index;
	}

	Node<T>* remove(T val)
	{
		if (head == NULL)
			return NULL;

		Node<T>* t1 = NULL, * current = head;

		for (; current && current->data != val; t1 = current, current = current->next);

		if (current == NULL)
			return NULL;

		if (t1 != NULL)
		{
			t1->next = current->next;
		}
		else
		{
			head = current->next;
		}
		delete current;
		current = NULL;
		t1 = NULL;

		return head;
	}

	Node<T>* update(T des, T val)
	{
		//Node<T>* temp = search(des);
		Node<T>* temp = head;
		int index = 0;

		if (temp != NULL)
			for (; temp && temp->data != des; temp = temp->next, index++);

		temp->data = val;

		return temp;
	}

	void print()
	{
		Node<int>* temp = head;
		int i = 1;
		while (temp)
		{
			cout << "Node " << i << ": " << temp->data << endl;
			temp = temp->next;
			++i;
		}
	}

	bool isEmpty()
	{
		return !head;
	}

	//No isFull bcz linked list can be extended to size infinitely
};

int main()
{
	SLinkedList<int> List;
	int num = 0, val = 0, ch = 0;

	cout << "How many elements u want to enter? ";
	cin >> num;

	for (int i = 0; i < num; ++i)
	{
		cout << "Node " << i + 1 << ": ";
		cin >> val;
		List.insert(val);
	}

	while (ch != 9)
	{
		cout << "\nChoose any option: \n"
			<< "1. Insert\n"
			<< "2. Insert at head\n"
			<< "3. Insert at index\n"
			<< "4. IsEmpty\n"
			<< "5. Search\n"
			<< "6. Update\n"
			<< "7. Delete\n"
			<< "8. Print\n"
			<< "9. Exit\n\n";
		cout << "\nChoose: ";
		cin >> ch;
		if (ch == 1)
		{
			cout << "Enter value: ";
			cin >> val;
			List.insert(val);
			List.print();
		}
		else if (ch == 2)
		{
			cout << "Enter value: ";
			cin >> val;
			List.insertAtHead(val);
			List.print();
		}
		else if (ch == 3)
		{
			cout << "Enter index: ";
			cin >> num;
			cout << "Enter value: ";
			cin >> val;
			List.InsertAtIndex(val, num);
			List.print();
		}
		else if (ch == 4)
		{
			cout << "Is Empty? " << List.isEmpty() << endl;
		}
		else if (ch == 5)
		{
			cout << "Enter value: ";
			cin >> val;
			cout << val << " is at index " << List.search(val) << endl;
		}
		else if (ch == 6)
		{
			cout << "Enter value to change: ";
			cin >> num;
			cout << "Enter value to put: ";
			cin >> val;
			List.update(num, val);
			List.print();
		}
		else if (ch == 7)
		{
			cout << "Enter element to delete: ";
			cin >> val;
			List.remove(val);
			List.print();
		}
		else if (ch == 8)
		{
			List.print();
		}
		else
			if (ch != 9)
				cout << "Wrong input!\n";
	}


	return 0;
}