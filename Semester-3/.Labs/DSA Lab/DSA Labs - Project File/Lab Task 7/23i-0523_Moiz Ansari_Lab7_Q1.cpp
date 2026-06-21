#include <iostream>
using namespace std;

class Node
{
public:
	int data;
	Node* next;
	Node* prev;

	Node(int d = 0, Node* n = NULL, Node* p = NULL)
	{
		data = d;
		next = n;
		prev = p;
	}
};

class DoublyCircular
{
public:
	Node* head;

	DoublyCircular(Node* h = NULL)
	{
		head = h;
	}

	void insert(int val)
	{
		if (head == NULL)
		{
			head = new Node(val);
			head->next = head;
			head->prev = head;
		}
		else
		{
			Node* temp = head->prev;
			temp->next = new Node(val, head, temp);
			head->prev = temp->next;
		}
	}

	void remove(int val)
	{
		if (!head)
			return;

		Node* temp = head;

		while (temp->data != val)
			temp = temp->next;

		if (temp == head)
		{
			if (temp->prev == temp->next)
				head = NULL;
			else
				head = head->next;
		}

		temp->next->prev = temp->prev;
		temp->prev->next = temp->next;
		delete temp;
	}

	int squidegame(int M, int N)
	{
		if (!head)
			return -1;

		Node* ptr = head, * temp = ptr;

		int m;
		if (M > 0)
			m = M;
		else
			m = M * -1;

		while (ptr != ptr->next)
		{
			if (M > 0)
				for (int i = 0; i < m; ++i)
					ptr = ptr->next;
			else	// if (M < 0)
				for (int i = 0; i < m; ++i)
					ptr = ptr->prev;

			if (M > 0)
				temp = ptr->next;
			else
				temp = ptr->prev;

			remove(ptr->data);
			ptr = temp;
		}
		return ptr->data;
	}

	void print()
	{
		cout << "\nList: ";
		if (!head)
			return;
		Node* temp = head;
		do {
			cout << temp->data << "  ";
			temp = temp->next;
		} while (temp != head);
		cout << "\n\n";
	}
};


int main()
{
	int N = 0, M = 0;
	DoublyCircular list;
	cout << "----- Welcome to Squid Game -----\n\n";

	cout << "Enter size of people (N): ";
	cin >> N;
	cout << "Enter number of jumps (M): ";
	cin >> M;

	for (int i = 0; i < N; ++i)
		list.insert(i + 1);
	
	list.print();

	cout << "\nThe only survivor: " << list.squidegame(M, N) << endl;

	return 0;
}