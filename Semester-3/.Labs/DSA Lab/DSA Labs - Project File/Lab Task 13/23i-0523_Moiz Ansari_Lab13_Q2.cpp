#include <iostream>
using namespace std;

template <typename T>
class BTreeNode
{
public:
    T* keys;
    int m;      //Min Degree
    BTreeNode<T>** Children;
    int n;      //Current No of keys
    bool leaf;
    T* min, * max;

    BTreeNode(int M = 2, bool l = 0, int N = 1, T* minn = NULL, T* maxx = NULL)
    {
        m = M;
        keys = new T[m - 1];
        for (int i = 0; i < m - 1; ++i)
        {
            keys[i] = 0;
        }
        Children = new BTreeNode * [m];
        for (int i = 0; i < m; ++i)
        {
            Children[i] = NULL;
        }
        n = N;
        leaf = l;
        if (!minn)
            min = &keys[0];
        else
            min = minn;
        if (!maxx)
            max = &keys[0];
        else
            max = maxx;
    }
};

template<typename T>
class BTree
{
public:
    BTreeNode <T>* root;
    int m;

    BTree(int M = 2, BTreeNode <T>* r = NULL)
    {
        root = NULL;
        m = M;
    }
};


template <typename T>
void createBtree(BTree<T>& tree)
{
    tree.root = new BTreeNode<int>(4, 0, 1);
    tree.root->keys[0] = 9;

    tree.root->Children[0] = new BTreeNode<int>(4, 0, 2);
    tree.root->Children[0]->keys[0] = 3;
    tree.root->Children[0]->keys[1] = 6;
    tree.root->Children[0]->max = &tree.root->Children[0]->keys[1];

    tree.root->Children[1] = new BTreeNode<int>(4, 0, 2);
    tree.root->Children[1]->keys[0] = 14;
    tree.root->Children[1]->keys[1] = 17;
    tree.root->Children[1]->max = &tree.root->Children[1]->keys[1];

    BTreeNode<int>* temp1 = tree.root->Children[0];
    BTreeNode<int>* temp2 = tree.root->Children[1];

    temp1->Children[0] = new BTreeNode<int>(4, 1, 2);
    temp1->Children[0]->keys[0] = 1;
    temp1->Children[0]->keys[1] = 2;
    temp1->Children[0]->max = &temp1->Children[0]->keys[1];

    temp1->Children[1] = new BTreeNode<int>(4, 1, 2);
    temp1->Children[1]->keys[0] = 4;
    temp1->Children[1]->keys[1] = 5;
    temp1->Children[1]->max = &temp1->Children[1]->keys[1];

    temp1->Children[2] = new BTreeNode<int>(4, 1, 2);
    temp1->Children[2]->keys[0] = 7;
    temp1->Children[2]->keys[1] = 8;
    temp1->Children[2]->max = &temp1->Children[2]->keys[1];




    temp2->Children[0] = new BTreeNode<int>(4, 3, 1);
    temp2->Children[0]->keys[0] = 10;
    temp2->Children[0]->keys[1] = 11;
    temp2->Children[0]->keys[2] = 12;
    temp2->Children[0]->max = &temp2->Children[0]->keys[2];

    temp2->Children[1] = new BTreeNode<int>(4, 1, 1);
    temp2->Children[1]->keys[0] = 16;
    temp2->Children[1]->max = &temp2->Children[1]->keys[0];

    temp2->Children[2] = new BTreeNode<int>(4, 1, 2);
    temp2->Children[2]->keys[0] = 18;
    temp2->Children[2]->keys[1] = 19;
    temp2->Children[2]->max = &temp2->Children[2]->keys[1];
}

template <typename T>
void rightImage(BTreeNode<T>* root)
{
    BTreeNode<T>* temp = root;

    cout << "Right Image: [ ";
    while (!temp->leaf)
    {
        //cout << temp->keys[temp->n - 1] << ", ";
        cout << *temp->max << ", ";

        int i = 0;
        while (i < temp->m && temp->Children[i])
            ++i;
        --i;
        temp = temp->Children[i];
    }
    //cout << temp->keys[temp->n - 1] << " ]\n";
    cout << *temp->max << " ]\n";
}

int main()
{
    BTree<int> tree(4);

    createBtree(tree);

    rightImage(tree.root);
}