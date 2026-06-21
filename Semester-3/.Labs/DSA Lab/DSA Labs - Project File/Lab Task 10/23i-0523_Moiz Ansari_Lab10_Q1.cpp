#include <iostream>
using namespace std;

class Node
{
public:
	int val;
	Node* left, * right;

	Node(int v = 0, Node* l = NULL, Node* r = NULL)
	{
		val = v;
		left = l;
		right = r;
	}
};

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

	void inorder(Node* root)
	{
		if (root == NULL)
			return;
		inorder(root->left);
		cout << root->val << " ";
		inorder(root->right);
	}

	void preorder(Node* root)
	{
		if (root == NULL)
			return;

		cout << root->val << " ";
		preorder(root->left);
		preorder(root->right);
	}

	void postorder(Node* root)
	{
		if (root == NULL)
			return;
		postorder(root->left);
		postorder(root->right);
		cout << root->val << " ";
	}

	void Display()
	{
		cout << "Inorder Traversal: ";
		inorder(root);

		cout << "Preorder Traversal: ";
		preorder(root);

		cout << "Postorder Traversal: ";
		postorder(root);
	}	
};
//
//int main()
//{
//	BinaryTree shajar;
//
//	int num, ch = 1;
//
//	while (ch)
//	{
//		cout << "\nDo you want to insert a node?\n"
//			<< "If you want to exit, press 0, else anything: ";
//		cin >> ch;
//		if (ch == 0)
//			break;
//
//		cout << "Enter the value: ";
//		cin >> num;
//
//		shajar.insert(num);
//	}
//
//	cout << endl;
//	shajar.Display();
//	cout << "\n";
//
//	return 0;
//}