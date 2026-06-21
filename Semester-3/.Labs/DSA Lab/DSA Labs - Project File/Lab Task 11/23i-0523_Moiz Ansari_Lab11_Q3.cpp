#include <iostream>
#include <cmath>
using namespace std;

class Node
{
public:
	int val;
	Node* left, * right;
	Node(int d = 0, Node* l = NULL, Node* r = NULL)
	{
		val = d;
		left = l;
		right = r;
	}
};

/////// Queue ///////
class Qnode
{
public:
	Node* val;
	Qnode* next;
	Qnode(Node* v = NULL, Qnode* n = NULL)
	{
		val = v;
		next = n;
	}
};

class Que
{
public:
	Qnode* head, * tail;

	Que(Qnode* h = NULL, Qnode* t = NULL)
	{
		head = h;
		tail = t;
	}

	bool isEmpty()
	{
		if (!head && !tail)
			return true;
		else
			return false;
	}

	void enqueue(Node* data)
	{
		if (isEmpty())
		{
			head = new Qnode(data);
			tail = head;
			head->next = NULL;
		}
		else
		{
			Qnode* temp = head;
			head = new Qnode(data);
			head->next = temp;
		}
	}

	void dequeue()
	{
		if (isEmpty())
			return;
		else if (head == tail)
		{
			Qnode* temp = tail;
			head = tail = NULL;
			delete temp;
		}
		else
		{
			Qnode* rem = tail, * temp = head;
			while (temp->next != tail)
				temp = temp->next;
			tail = temp;
			tail->next = NULL;
			temp = NULL;
			delete rem;
		}
	}

	Node* retdequeue()
	{
		if (isEmpty())
			return NULL;
		else if (head == tail)
		{
			Qnode* temp = tail;
			head = tail = NULL;
			return temp->val;
		}
		else
		{
			Qnode* rem = tail, * temp = head;
			while (temp->next != tail)
				temp = temp->next;
			tail = temp;
			tail->next = NULL;
			temp = NULL;
			return rem->val;
		}
	}

	Node* getNode()
	{
		return tail->val;
	}

	void printQue()
	{
		Qnode* curr = head;
		cout << endl;
		while (curr)
		{
			cout << curr->val << "  ";
			curr = curr->next;
		}
		cout << "\n";
	}
};

template<typename T>
class Stack
{
public:
	T* arr;
	int size;
	int top;

	Stack(int s = 30)
	{
		size = s;
		arr = new T[size];
		top = -1;
	}

	bool isEmpty()
	{
		return top == -1;
	}

	bool isFull()
	{
		return top == size - 1;
	}

	void push(T val)
	{
		if (isFull())
			return;
		else
			arr[++top] = val;
	}

	T pop()
	{
		if (isEmpty())
			return -1;
		else
			return arr[top--];
	}

	T getval()
	{
		if (isEmpty())
			return -1;
		else
			return arr[top];
	}

};

class BinaryTree
{
public:
	Node* root;
	Que Q;

	BinaryTree(Node* r = NULL)
	{
		root = r;
	}

	void insert(int data)
	{
		Node* newnode = new Node(data);
		Node* curr = root;

		if (root == NULL)
		{
			root = newnode;
			Q.enqueue(root);
		}
		else
		{
			if (Q.getNode()->left == NULL)
			{
				Q.getNode()->left = newnode;
				Q.enqueue(newnode);
			}
			else if (Q.getNode()->right == NULL)
			{
				Q.getNode()->right = newnode;
				Q.enqueue(newnode);

				Q.dequeue();
			}
		}
	}

	void preorder(Node* root)
	{
		if (root == NULL)
			return;

		cout << root->val << " ";
		preorder(root->left);
		preorder(root->right);
	}

	void spiral()
	{
		int n = 0, i = 1;
		Que qb;
		Stack <int>st(40);
		Node* temp = NULL;
		qb.enqueue(root);
		cout << "Spiral Order: [ ";
		while (!qb.isEmpty())
		{
			temp = qb.retdequeue();

			if (temp->left)
				qb.enqueue(temp->left);
			if (temp->right)
				qb.enqueue(temp->right);


			if (n % 2 != 0)
			{
				st.push(temp->val);
			}
			else
				cout << temp->val << ", ";

			if (i == pow(2, n))
			{
				while (!st.isEmpty())
				{
					cout << st.pop() << ", ";
				}
				i = 0;
				++n;
			}
			++i;
		}
		while (!st.isEmpty())
		{
			cout << st.pop() << ", ";
		}
		cout << "\b\b ]\n";
	}
};


int main()
{
	BinaryTree darakht;

	int num, ch = 1;

	while (ch)
	{
		cout << "\nDo you want to insert a node?\n"
			<< "If you want to exit, press 0, else anything: ";
		cin >> ch;
		if (ch == 0)
			break;

		cout << "Enter the value: ";
		cin >> num;

		darakht.insert(num);
	}

	cout << "\n";
	darakht.spiral();

	return 0;
}