#include <iostream>
#include "D:\Documents\Semester-3\.Labs\.DSA Lab\Lab Task 10\Lab-10 Project File\23i-0523_Moiz Ansari_Q1.cpp"
using namespace std;

void FindPathSum(Node* root, int sum, int targetSumm, bool& b)
{
    if (!b)
    {
        if (root == NULL)
        {
            if (sum == targetSumm)
            {
                b = 1;
                FindPathSum(root, sum, targetSumm, b);
                return;
            }
            else
                return;
        }

        sum += root->val;
        if (!(!root->left && root->right))
        {
            FindPathSum(root->left, sum, targetSumm, b);
            if (!root->right)
                return;
        }
        if (!(!root->right && root->left))
        {
            FindPathSum(root->right, sum, targetSumm, b);
            if (!root->left)
                return;
        }
    }
}

bool hasPathSum(Node* root, int targetSumm)
{
    if (!root)
        return 0;
    bool b = 0;
    FindPathSum(root, 0, targetSumm, b);
    return b;
}

/*  /

int main()
{
	BinaryTree shajar;

	int num, ch = 1, targetSum;

	while (ch)
	{
		cout << "\nDo you want to insert a node?\n"
			<< "If you want to exit, press 0, else anything: ";
		cin >> ch;
		if (ch == 0)
			break;

		cout << "Enter the value: ";
		cin >> num;

		shajar.insert(num);
	}

	cout << "\nEnter target sum: ";
	cin >> targetSum;

	cout << endl;
	cout << "The path to target sum exists? " << hasPathSum(shajar.root, targetSum);
	cout << "\n";

	return 0;
}

//
*/