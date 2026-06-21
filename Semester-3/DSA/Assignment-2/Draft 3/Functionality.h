#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

int startx = 2, starty = 3;
int miny = 3, maxy = 5,//22,
	minx = 2, maxx = 23;//96;
int minindex = 0, maxindex = maxx - 3; //20		///////////chect it

void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

class Node
{
public:
	char data;
	int x;
	int y;
	Node* up;
	Node* down;
	Node* left;
	Node* right;

	Node(char c = '\0', Node* u = NULL, Node* d = NULL, Node* l = NULL, Node* r = NULL, int xx = 0, int yy = 0)
	{
		data = c;
		up = u;
		down = d;
		left = l;
		right = r;
		x = xx;
		y = yy;
	}

	void movexy(int xx, int yy)
	{
		x = xx - 2;
		y = yy - 3;
	}
};


class Cursor
{
public:
	int index;
	int length;
	Node* next;

	Cursor(int ind = 0, int l = 0, Node* n = NULL)
	{
		index = ind;
		length = l;
		next = n;
	}
	void movexy(int x, int y)
	{
		next->x = x - 2;
		next->y = y - 3;
	}
};

Node* getCharacter(Node* head, int x, int y)
{
	int height = 0;
	if (!head)
		return NULL;

	Node* temp = head;
	while (temp)
	{
		temp = temp->down;
		++height;
	}

	temp = head;
	for (int i = 0; i < height && temp; ++i)
	{
		while (temp->right)	//Going right
		{
			if (temp->x == x && temp->y == y)
				return temp;
			temp = temp->right;
		}
		if (temp->x == x && temp->y == y)
			return temp;
		while (temp->left)	//Coming back to start col
			temp = temp->left;
		if (temp->down)
			temp = temp->down;
	}

	return NULL;
}





class List
{
public:
	Node* head;

	List()
	{
		head = NULL;
	}

	void setPointers(Node* temp)
	{
		Node* up = getCharacter(head, temp->x, temp->y - 1);
		Node* down = getCharacter(head, temp->x, temp->y + 1);
		Node* left = getCharacter(head, temp->x - 1, temp->y);
		Node* right = getCharacter(head, temp->x + 1, temp->y);

		temp->up = up;
		temp->down = down;
		temp->left = left;
		temp->right = right;

		if (up)
			up->down = temp;
		
		if (down)
			down->up = temp;

		if (left)
			left->right = temp;

		if (right)
			right->left = temp;
	}

	void setAllNodes()
	{
		int height = 0;
		if (!head)
			return;

		Node* temp = head, * temp2 = NULL, * temp3 = NULL;
		while (temp)
		{
			temp = temp->down;
			++height;
		}

		/*temp = head;
		for (int i = 0; i < height && temp; ++i)
		{

		}*/

		temp = head;
		for (int i = 0; i < height && temp; ++i)
		{
			if (getCharacter(head, maxx - 3, i) && getCharacter(head, 0, i + 1))
			{
				while (temp->right)	//Going right
				{
					temp2 = temp->right;
					if (head->down)		///////////// use tempv instead of head here
						temp3 = head->down->right;
					setPointers(temp);
					if (!(temp->right))
					{
						while (temp->left)
							temp = temp->left;
						
						temp->down = temp2;
						temp->down->up = temp;
						temp2->right = temp3;
						if (temp3)
							temp3->left = temp2;
						break;
					}
					temp = temp->right;
					//if (!temp)/////////////////////////////////////////////
					//	break;
				}
			}
			else
				while (temp->right)	//Going right
				{
					setPointers(temp);
					temp = temp->right;
					if (!temp)/////////////////////////////////////////////
						break;
				}
			setPointers(temp);
			while (temp->left)	//Coming back to start col
				temp = temp->left;
			if (temp->down)
				temp = temp->down;
		}
	}

	void forward(Node* curr, bool notstart)
	{
		if (notstart)
			--(curr->x);
		int height = 0;
		if (!curr)
			return;

		Node* temp = curr;
		while (temp->left)	//Coming back to start col
			temp = temp->left;
		while (temp)
		{
			temp = temp->down;
			++height;
		}

		temp = curr;
		for (int i = 0; i < height && temp; ++i)
		{
			while (temp->right)	//Going right
			{
				++temp->x;
				if (temp->x > maxindex)	//for char at end of line
				{
					temp->x = 0;
					++temp->y;
				}
				temp = temp->right;
			}
			++temp->x;

			if (temp->x <= maxindex)
				break;
			else
			{
				temp->x = 0;	//for char at end of line
				++temp->y;
			}
			while (temp->left)	//Coming back to start col
				temp = temp->left;
			if (temp->down)
				temp = temp->down;
		}

		setAllNodes();
	}

	void insert(char c, Cursor &cur, int x, int y)
	{
		if (!head)
		{
			head = new Node(c);
			cur.next = head;
			cur.movexy(x, y);
			return;
		}
		else
		{
			if (cur.index == 0 && cur.next->x == 0 && cur.next->y == 0)	//Start of whole para case
			{
				cur.next->left = new Node(c, NULL, NULL, NULL, cur.next);
				cur.next->left->movexy(x, y);
				if (cur.next == head)
					head = cur.next->left;
				forward(cur.next, 0);
				cur.next = cur.next->left;
			}
			else if ((cur.index == 0 && cur.next->x != 0) || (cur.index == 0 && cur.next->x == 0 && cur.next->y != 0))	
			{
				int yy;
				if (cur.index == 0 && cur.next->x != 0)	//Cursor is at end of line and element is added in start in next line
					yy = cur.next->y;
				else									//Cursor is at start of line
					yy = cur.next->y - 1;

				Node* temp = getCharacter(head, 0, yy), * temp2 = NULL, * temp3 = NULL;
				temp2 = temp->down;
				if (temp->down)
					temp3 = temp2->down;
				temp->down = new Node(c, temp, NULL, NULL, NULL);
				temp->down->movexy(x, y);
				temp = temp->down;
				if (temp2)
				{
					temp->right = temp2;
					temp2->left = temp;
				}
				if (temp3)
				{
					temp->down = temp3;
					temp3->up = temp;
				}
				if (temp->right)
					forward(temp->right, 0);
				else if (temp->down)//////////////////////
					forward(temp->down, 0);///////////////
				else
					setAllNodes();
				cur.next = getCharacter(head, 0, yy + 1);
			}
			else if (cur.index <= maxindex)	//Not start and not end case
			{
				//
				Node* temp = head;
				while (temp->down)
					temp = temp->down;
				while (temp->right)
					temp = temp->right;
				
				Node* temp2 = NULL;
				if (cur.next->right)
				{
					cur.next->right->x++;
					temp2 = cur.next->right;
				}
				cur.next->right = new Node(c, NULL, NULL, cur.next, NULL);
				cur.next->right->movexy(x, y);

				if (temp2)
				{
					cur.next->right->right = temp2;
					cur.next->right->right->left = cur.next->right;
				}
				
				if (temp != cur.next)
					forward(getCharacter(head, cur.next->x + 2, cur.next->y), 1);
				else
					setAllNodes();
				
				if (cur.next->right)
					cur.next = cur.next->right;
			}
			else	//End of line case
			{
				////
				//Node* temp = head;
				//while (temp->down)
				//	temp = temp->down;
				//while (temp->right)
				//	temp = temp->right;
				////
				//Node* temp2 = NULL;
				//if (cur.next->right)
				//{
				//	cur.next->right->x++;
				//	temp2 = cur.next->right;
				//}
				//cur.next->right = new Node(c, NULL, NULL, cur.next, NULL);
				//cur.next->right->movexy(x, y);

				//if (temp2)
				//{
				//	cur.next->right->right = temp2;
				//	cur.next->right->right->left = cur.next->right;
				//}

				//if (temp != cur.next)
				//	forward(getCharacter(head, cur.next->x + 2, cur.next->y), 1);

				//if (cur.next->right)
				//	cur.next = cur.next->right;
			}
		}
	}

	~List()
	{
		if (!head)
			return;

		Node* temp = head, * temp2 = NULL;
		while(temp)
		{
			while (temp->right)	//Going right
			{
				temp = temp->right;
			}
			while (temp->left)	//Coming back to start col
			{
				temp2 = temp;
				temp = temp->left;
				delete temp2;
			}
			if (temp)
			{
				temp2 = temp;
				temp = temp->down;
				delete temp2;
			}
		}
		temp = NULL;
		temp2 = NULL;
	}
};

void printText(Node* head, int x, int y)
{
	int stx = 2, sty = 3;
	int ty = sty - 1;
	gotoxy(stx, ty);

	int h = 20,
		w = 94;
	int tsize = h * w,
		height = 0;
	if (!head)
		return;

	Node* temp = head;
	while (temp)
	{
		temp = temp->down;
		++height;
	}
	h -= height;

	temp = head;
	int k = w;
	for (int i = 0; i < height && temp; ++i)
	{	
		gotoxy(stx, ++ty);
		k = w;
		while(temp->right)	//Going right
		{
			cout << temp->data;
			--k;
			temp = temp->right;
		}
		cout << temp->data;
		--k;
		while (temp->left)	//Coming back to start col
			temp = temp->left;
		if (temp->down)
			temp = temp->down;
	}
	/*for (int i = 0; i < h; ++i)
	{
		if (i != 0)
			k = w;
		for (int j = 0; j < k; ++j)
		{
			cout << " ";
		}
		gotoxy(stx, ++ty);
	}*/
	temp = NULL;

	gotoxy(x, y);
}
