#include <iostream>
using namespace std;

class Node
{
public:
	int id;
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

	Node* search(Node* root, int val)
	{
		if (root == NULL)
		{
			cout << "Book not found! 😭\n";
			return root;
		}
		else if (root->id == val)
		{
			cout << "Book found! 🥳\n";
			cout << "Book ID: " << root->id << endl;
			return root;
		}
		else if (val > root->id)
			search(root->right, val);
		else
			search(root->left, val);
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

	Node* findmax()
	{
		Node* temp = root;
		if (temp == NULL)
		{
			cout << "No Maximum, book list is empty!\n";
			return temp;
		}
		else
		{
			while (temp->right)
				temp = temp->right;
			cout << "Maximum book ID: " << temp->id << endl;
			return temp;
		}
	}

	Node* findmin()
	{
		Node* temp = root;
		if (temp == NULL)
		{
			cout << "No Minimum, book list is empty!\n";
			return temp;
		}
		else
		{
			while (temp->left)
				temp = temp->left;
			cout << "Minimum book ID: " << temp->id << endl;
			return temp;
		}
	}

	void inorder(Node*& root)
	{
		if (root == NULL)
			return;
		inorder(root->left);
		cout << root->id << ", ";
		inorder(root->right);
	}

	void display()
	{
		cout << "\nBook List (Book ID's): [";
		inorder(root);
		cout << "\b\b]\n";
	}

};




int main()
{
	BST tree;
	int n = 0, val = 0, temp = 0, * arr = NULL, ch = 1;

	cout << "---- Welcome to Library Book Management System ----\n\n";

	while (ch != 0)
	{
		cout << "\nChoose one option of the following:\n";
		cout << "1. Insert a Book\n"
			<< "2. Search for a Book\n"
			<< "3. Delete a Book\n"
			<< "4. Display All Books.\n"
			<< "5. Find Minimum Book ID\n"
			<< "6. Find Maximum Book ID\n"
			<< "0 to Exit\n";
		cout << "\nChoice: ";
		cin >> ch;

		if (ch == 0)
		{
			break;
		}
		else if (ch == 1)
		{
			cout << "Enter the book ID to insert: ";
			cin >> val;
			//Node* t = tree.find(tree.root, val);
			//while (t->id == val)
			//{
			//	t = tree.find(tree.root, val);
			//	cout << "Book ID already exists! Enter again\n";
			//	cout << "Enter the value to insert: ";
			//	cin >> val;
			//}
			tree.insert(tree.root, val);
		}
		else if (ch == 2)
		{
			cout << "Enter the book ID to search: ";
			cin >> val;
			tree.search(tree.root, val);
		}
		else if (ch == 3)
		{
			cout << "Enter the book ID to delete: ";
			cin >> val;
			tree.deletion(tree.root, val);
		}
		else if (ch == 4)
		{
			tree.display();
		}
		else if (ch == 5)
		{
			tree.findmin();
		}
		else if (ch == 6)
		{
			tree.findmax();
		}
		else
		{
			cout << "Invalid choice input!\n";
		}
	}

	cout << "\n\n--- Exiting Library ---\n\n";

	return 0;
}