#include <iostream>
using namespace std;

class Node
{
public:
	int id;
	bool rotated = 0;
	Node* left, * right;
	Node(int d = 0, Node* l = NULL, Node* r = NULL)
	{
		id = d;
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
		else if (val > root->id)
			insert(root->right, val);
		else
			insert(root->left, val);
	}

	Node* find(Node* root, int val)
	{
		if (root == NULL || root->id == val)
			return root;
		else if (val > root->id)
			find(root->right, val);
		else
			find(root->left, val);
	}

	Node* deletion(Node*& root, int val)
	{
		if (root == NULL)
			return root;
		else if (val > root->id)
			deletion(root->right, val);
		else if (val < root->id)
			deletion(root->left, val);
		else	//Delete node
		{
			if (root->left == NULL)
			{
				Node* temp = root;
				root = root->right;
				delete temp;
			}
			else if (root->right == NULL)
			{
				Node* temp = root;
				root = root->left;
				delete temp;
			}
			else
			{
				Node* temp = root->right;
				while (temp->left)
				{
					temp = temp->left;
				}
				root->id = temp->id;
				deletion(root->right, root->id);
			}
		}
	}

	void preorder(Node* root)
	{
		if (root == NULL)
			return;
		cout << root->id << ", ";
		preorder(root->left);
		preorder(root->right);
	}

	void display()
	{
		cout << "\nBook List (Book ID's): [";
		preorder(root);
		cout << "\b\b]\n";
	}

};

void RotateRight(Node*& root)
{
	if (root->left)
	{
		Node* K = root->left;
		root->left = K->right;
		K->right = root;
		root = K;
	}
}

void RotateLeft(Node*& root)
{
	if (root->right)
	{
		Node* K = root->right;
		root->right = K->left;
		K->left = root;
		root = K;
	}
}

void RotateLeftRight(Node*& root)
{
	RotateLeft(root->left);
	RotateRight(root);
}

void RotateRightLeft(Node*& root)
{
	RotateRight(root->right);
	RotateLeft(root);
}

int height(Node* root)
{
	if (!root)
		return -1;

	int l = height(root->left);
	int r = height(root->right);

	if (r > l)
		return r + 1;
	else
		return l + 1;
}

bool isPrime(int num)
{
	if (num < 2)
		return 0;
	if (num == 2)
		return 1;

	for (int i = 2; i < num / 2; ++i)
	{
		if (num % i == 0)
			return 0;
	}
	return 1;
}

void specialrotation(Node*& root)
{
	if (!root)
		return;

	if (!root->rotated)
	{
		if (isPrime(root->id))
		{
			root->rotated = 1;
		}
		else if (root->id % 2 == 0)
		{
			root->rotated = 1;
			RotateLeft(root);
		}
		else
		{
			root->rotated = 1;
			RotateRight(root);
		}
	}
}

void inorderrotation(Node*& root, bool& b)
{
	if (!root)
		return;

	if (b)
		inorderrotation(root->left, b);
	if (!root->rotated && b)
	{
		b = 0;
		specialrotation(root);
		return;
	}
	if (b)
		inorderrotation(root->right, b);
}

void getNoOfNodes(Node*& root, int& size)
{
	if (!root)
		return;

	++size;
	getNoOfNodes(root->left, size);
	getNoOfNodes(root->right, size);
}

void balancefactor(Node*& root, int& index, int*& arr)
{
	if (!root)
		return;

	balancefactor(root->left, index, arr);
	balancefactor(root->right, index, arr);

	arr[index++] = height(root->right) - height(root->left);
}

int main()
{
	BST tree;
	int n = 0, val = 0, * arr = NULL;
	bool hardcode = 1;

	cout << "Do hardcode? ";
	cin >> hardcode;

	if (hardcode)
	{
		tree.insert(tree.root, 10);
		tree.insert(tree.root, 5);
		tree.insert(tree.root, 20);
		tree.insert(tree.root, 30);
		tree.insert(tree.root, 7);
		tree.insert(tree.root, 15);
		tree.insert(tree.root, 30);
	}
	else
	{
		cout << "How many elements you want to enter? ";
		cin >> n;

		arr = new int[n];

		cout << "\nEnter the elements:\n";
		for (int i = 0; i < n; ++i)
		{
			cout << "Node " << i + 1 << ": ";
			cin >> val;
			arr[i] = val;

			/*for (int j = 0; j <= i; ++j)
			{
				if (arr[j] == val && j != i)
				{
					cout << "Barahe meherbani, Same value mat daliye!\n";
					cout << "Node " << i + 1 << ": ";
					cin >> val;
					j = 0;
				}
			}
			arr[i] = val;*/
		}

		for (int i = 0; i < n; ++i)
			tree.insert(tree.root, arr[i]);
	}

	//Original:
	cout << "\nOriginal tree: [";
	tree.preorder(tree.root);
	cout << "\b\b]\n";

	bool b = 0, yes = 1;
	while (b == 0)
	{
		b = 1;
		inorderrotation(tree.root, b);
	}

	int size = 0;
	getNoOfNodes(tree.root, size);
	int* arrr = new int[size];

	int index = 0;
	balancefactor(tree.root, index, arrr);

	//Output:
	cout << "\nAfter special rotations: [";
	tree.preorder(tree.root);
	cout << "\b\b]\n\n";

	//Balanced Factor:
	cout << "\nBalanced Factors: [";
	for (int i = 0; i < index; ++i)
		cout << arrr[i] << ", ";
	cout << "\b\b]\n\n";
}