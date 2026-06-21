#include <iostream>
using namespace std;

class Node
{
public:
	int data;
	Node* left, * right;
	Node(int d = 0, Node* l = NULL, Node* r = NULL)
	{
		data = d;
		left = l;
		right = r;
	}
};

class BST
{
public:
	Node* root;
	BST(Node* r = NULL)
	{
		root = r;
	}

	void insert(Node*& root, int val)
	{
		if (root == NULL)
			root = new Node(val);
		else if (val > root->data)
			insert(root->right, val);
		else
			insert(root->left, val);
	}

	Node* find(Node* root, int val)
	{
		if (root == NULL || root->data == val)
			return root;
		else if (val > root->data)
			find(root->right, val);
		else
			find(root->left, val);
	}

	void preorder(Node*& root)
	{
		if (root == NULL)
			return;
		cout << root->data << ", ";
		preorder(root->left);
		preorder(root->right);
	}

};




int main()
{
	BST tree;
	int n = 0, val = 0, * arr = NULL;

	cout << "How many elements you want to enter? ";
	cin >> n;

	arr = new int[n];

	cout << "\nEnter the elements:\n";
	for (int i = 0; i < n; ++i)
	{
		cout << "Node " << i + 1 << ": ";
		cin >> val;
		arr[i] = val;
		
		for (int j = 0; j <= i; ++j)
		{
			if (arr[j] == val && j != i)
			{
				cout << "Barahe meherbani, Same value mat daliye!\n";
				cout << "Node " << i + 1 << ": ";
				cin >> val;
				j = 0;
			}
		}
		arr[i] = val;
	}

	for(int i=0; i<n; ++i)
	tree.insert(tree.root, arr[i]);

	cout << "\nEnter the value to find and then print its output of sub-tree: ";
	cin >> val;

	//Output:
	cout << "\nOutput: [";
	Node* temp = tree.find(tree.root, val);
	tree.preorder(temp);
	cout << "\b\b]";
}