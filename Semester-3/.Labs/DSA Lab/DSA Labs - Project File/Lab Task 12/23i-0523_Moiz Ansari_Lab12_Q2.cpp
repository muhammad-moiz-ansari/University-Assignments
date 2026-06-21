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

class AVL
{
public:
	Node* root;
	AVL(Node* r = NULL)
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

		if (height(root->right) - height(root->left) == 2)
		{
			if (height(root->right->right) - height(root->right->left) == 1)
				RotateLeft(root);
			else
				RotateRightLeft(root);
		}
		else if (height(root->left) - height(root->right) == 2)
		{
			if (height(root->left->left) - height(root->left->right) == 1)
				RotateRight(root);
			else
				RotateLeftRight(root);
		}
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
		///////////
		if (height(root->right) - height(root->left) == 2)
		{
			if (height(root->right->right) - height(root->right->left) == 1)
				RotateLeft(root);
			else
				RotateRightLeft(root);
		}
		else if (height(root->left) - height(root->right) == 2)
		{
			if (height(root->left->left) - height(root->left->right) == 1)
				RotateRight(root);
			else
				RotateLeftRight(root);
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

void balancetree(Node*& root)
{
	if (!root)
		return;

	balancetree(root->left);
	balancetree(root->right);

	if (height(root->right) - height(root->left) >= 2)
	{
		if (height(root->right->right) - height(root->right->left) == 1)
			RotateLeft(root);
		else
			RotateRightLeft(root);
	}
	else if (height(root->left) - height(root->right) >= 2)
	{
		if (height(root->left->left) - height(root->left->right) == 1)
			RotateRight(root);
		else
			RotateLeftRight(root);
	}
}

void splittree(Node*& root, Node*& root1, Node*& root2)
{
	root1 = root;
	root2 = root->right;
	root1->right = NULL;

	balancetree(root1);
	balancetree(root2);
}
//
//int main()
//{
//	AVL tree;
//	int n = 0, val = 0, * arr = NULL;
//	bool hardcode = 1;
//
//	cout << "Do hardcode? ";
//	cin >> hardcode;
//
//	if (hardcode)
//	{
//		tree.insert(tree.root, 15);
//		tree.insert(tree.root, 10);
//		tree.insert(tree.root, 12);
//		tree.insert(tree.root, 3);
//		tree.insert(tree.root, 7);
//		tree.insert(tree.root, 69);
//		tree.insert(tree.root, 2);
//		tree.insert(tree.root, 4);
//	}
//	else
//	{
//		cout << "How many elements you want to enter? ";
//		cin >> n;
//
//		arr = new int[n];
//
//		cout << "\nEnter the elements:\n";
//		for (int i = 0; i < n; ++i)
//		{
//			cout << "Node " << i + 1 << ": ";
//			cin >> val;
//			arr[i] = val;
//
//			/*for (int j = 0; j <= i; ++j)
//			{
//				if (arr[j] == val && j != i)
//				{
//					cout << "Barahe meherbani, Same value mat daliye!\n";
//					cout << "Node " << i + 1 << ": ";
//					cin >> val;
//					j = 0;
//				}
//			}
//			arr[i] = val;*/
//		}
//
//		for (int i = 0; i < n; ++i)
//			tree.insert(tree.root, arr[i]);
//	}
//
//	//Original:
//	cout << "\nOriginal tree: [";
//	tree.preorder(tree.root);
//	cout << "\b\b]\n";
//
//	Node* root1, * root2;
//	splittree(tree.root, root1, root2);
//
//	//Output:
//	cout << "\nAfter splitting: \n\n";
//
//	cout << "\nRoot 1: [";
//	tree.preorder(root1);
//	cout << "\b\b]\n";
//
//	cout << "\nRoot 2: [";
//	tree.preorder(root2);
//	cout << "\b\b]\n\n";
//}