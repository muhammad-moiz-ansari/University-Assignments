#include <iostream>
//#include <queue>
using namespace std;




template <typename T>
class BTreeNode
{
public:
    T* keys;               // Array of keys
    int t;                 // Minimum degree
    int m;                 // Maximum keys (2 * t - 1)
    BTreeNode<T>** Children; // Array of child pointers
    int n;                 // Current number of keys
    bool leaf;             // True if leaf node
    T* min;                // Pointer to minimum key
    T* max;                // Pointer to maximum key

    BTreeNode(int M = 2, bool l = 0, int N = 1, T* minn = NULL, T* maxx = NULL)
    {
        t = M;
        m = 2 * t - 1; // Max keys in a node
        keys = new T[m];
        for (int i = 0; i < m; ++i)
            keys[i] = 0;

        Children = new BTreeNode * [m + 1];
        for (int i = 0; i < m + 1; ++i)
            Children[i] = NULL;

        n = 0;
        leaf = l;

        min = &keys[0];
        max = &keys[0];
    }

    void insertNonFull(T k);
    void splitChild(int i, BTreeNode<T>* y);
    bool search(T val)
    {
        int i = 0;
        while (i < n && val > keys[i])
            i++;

        if (keys[i] == val)
            return true;
        if (leaf)
            return false;
        return Children[i]->search(val);
    }
};

//template <typename T>
class Qnode
{
public:
    BTreeNode<int>* val;
    Qnode* next;
    Qnode(BTreeNode<int>* v = NULL, Qnode* n = NULL)
    {
        val = v;
        next = n;
    }
};

//template <typename T>
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

    void enqueue(BTreeNode<int>* data)
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

    BTreeNode<int>* getNode()
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


template <typename T>
class BTree
{
public:
    BTreeNode<T>* root; 
    int t;              // Minimum degree

    // Constructor
    BTree(int tt)
    {
        root = nullptr;
        t = tt;
    }

    void insert(T k)
    {
        if (root == nullptr)
        {
            root = new BTreeNode<T>(t, true);
            root->keys[0] = k; 
            root->n = 1;      
            root->min = &root->keys[0];
            root->max = &root->keys[0];
        }
        else
        {
            if (root->n == 2 * t - 1)
            {
                BTreeNode<T>* s = new BTreeNode<T>(t, false);
                s->Children[0] = root; 

                s->splitChild(0, root);

                int i = 0;
                if (s->keys[0] < k)
                    i++;
                s->Children[i]->insertNonFull(k);

                root = s;
            }
            else
            {
                root->insertNonFull(k);
            }
        }
    }

    void levelorder(BTreeNode<int>* btnode)
    {
        if (root == nullptr)
            return;

        Que q;
        q.enqueue(btnode);

        while (!q.isEmpty()) 
        {
            BTreeNode<int>* node = q.getNode();         //q.front();
            q.dequeue();

            for (int i = 0; i < node->n; i++)
                cout << node->keys[i] << " ";

            cout << endl;

            if (!node->leaf) 
            {
                for (int i = 0; i <= node->n; i++) 
                {
                    q.enqueue(node->Children[i]);
                }
            }
        }
    }
};

template <typename T>
void BTreeNode<T>::insertNonFull(T k)
{
    int i = n - 1;

    if (leaf)
    {
        // Find position and shift keys
        while (i >= 0 && keys[i] > k)
        {
            keys[i + 1] = keys[i];
            i--;
        }

        keys[i + 1] = k;
        n++; 

        // Update min and max pointers
        min = &keys[0];
        max = &keys[n - 1];
    }
    else
    {
        while (i >= 0 && keys[i] > k)
            i--;

        if (Children[i + 1]->n == 2 * t - 1)
        {
            splitChild(i + 1, Children[i + 1]);

            if (keys[i + 1] < k)
                i++;
        }
        Children[i + 1]->insertNonFull(k);

        // Update min and max
        min = &keys[0];
        max = &keys[n - 1];
    }
}

template <typename T>
void BTreeNode<T>::splitChild(int i, BTreeNode<T>* y)
{
    BTreeNode<T>* z = new BTreeNode<T>(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t - 1; j++)
        z->keys[j] = y->keys[j + t];

    if (!y->leaf)
    {
        for (int j = 0; j < t; j++)
            z->Children[j] = y->Children[j + t];
    }

    y->n = t - 1;

    for (int j = n; j >= i + 1; j--)
        Children[j + 1] = Children[j];

    Children[i + 1] = z;

    for (int j = n - 1; j >= i; j--)
        keys[j + 1] = keys[j];

    keys[i] = y->keys[t - 1];

    n++;

    // Update min and max
    min = &keys[0];
    max = &keys[n - 1];
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
            temp->keys[0];
            temp->keys[1];
            temp->keys[2];
            temp->keys[3];
            temp->keys[4];

            int i = 0;
            while (i < temp->m && temp->Children[i])
                ++i;
            --i;
            temp = temp->Children[i];
        }
        //cout << temp->keys[temp->n - 1] << " ]\n";
        cout << *temp->max << " ]\n";
    }

    int computePascal(int row, int col)
    {
        if (col == 0 || col == row)
            return 1;
        return computePascal(row - 1, col - 1) + computePascal(row - 1, col);
    }

    void makepascaltriangle(BTree<int>& tree, int rows)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j <= i; j++)
            {
                tree.insert(computePascal(i, j));
            }
        }
    }

    int main()
    {
        BTree<int> tree(2);

        tree.insert(1);
        tree.insert(2);
        tree.insert(3);
        tree.insert(4);
        tree.insert(5);
        tree.insert(6);
        tree.insert(7);
        tree.insert(8);
        tree.insert(9);
        tree.insert(10);
        tree.insert(18);
        tree.insert(16);
        tree.insert(17);
        tree.insert(14);
        tree.insert(12);
        tree.insert(11);
        tree.insert(19);

        rightImage(tree.root);




        int n, value;
        cout << "Enter the number of rows for Pascal's Triangle: ";
        cin >> n;
        BTree<int> tree2(n);

        makepascaltriangle(tree2, n);

        tree2.levelorder(tree2.root);

        cout << "\nEnter a value to search in Pascal's Triangle: ";
        cin >> value;

        if (tree2.root->search(value))
            cout << "The value " << value << " exists in pascal triangle.\n";
        else
            cout << "The value " << value << " does not exist in pascal triangle.\n";

        return 0;
    }