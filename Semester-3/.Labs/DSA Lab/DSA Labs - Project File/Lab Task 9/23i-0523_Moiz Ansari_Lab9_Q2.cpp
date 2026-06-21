#include <iostream>
#include <string>
using namespace std;

class Node
{
public:
	int data;
	Node* next;

	Node(int d = 0, Node* n = NULL)
	{
		data = d;
		next = n;
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

	/*Node* top;

	Stack(Node* t = NULL)
	{
		top = t;
	}

	bool isEmpty()
	{
		return !top;
	}

	void push(int val)
	{
		Node* temp = new Node(val);
		temp->next = top;
		top = temp;
	}

	Node* pop()
	{
		if (isEmpty())
			return NULL;
		else
		{

		}
	}*/

};

bool isValid(string str)
{
	if (str == "")
		return 1;
	bool b = 0;

	int size = 0;
	for (; str[size] != '\0'; ++size);
	++size;

	Stack<char> st(size);

	for (int i = 0; i < size; ++i)
	{
		if (str[i] == '(')
			st.push('(');
		else if (str[i] == '{')
			st.push('{');
		else if (str[i] == '[')
			st.push('[');
		else if (str[i] == ')' && st.getval() == '(')
		{
			if (st.isEmpty())
				return 0;
			else
				st.pop();
			b = 1;
		}
		else if (str[i] == '}' && st.getval() == '{')
		{
			if (st.isEmpty())
				return 0;
			else
				st.pop();
			b = 1;
		}
		else if (str[i] == ']' && st.getval() == '[')
		{
			if (st.isEmpty())
				return 0;
			else
				st.pop();
			b = 1;
		}
	}
	if (b)
		return st.isEmpty();
	else
		return 0;
}
//
//int main()
//{
//	string str;
//	cout << "Enter the string: ";
//	getline(cin, str);
//
//	cout << "\nIs the string valid: " << isValid(str) << endl;
//
//	return 0;
//}