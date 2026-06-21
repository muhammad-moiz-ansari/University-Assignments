#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

char enter = '_';
const int startx = 2, starty = 3;
const int miny = 3, maxy = 6;	//22,
const int minx = 2, maxx = 15;	//96;
const int minindex = 0, maxindex = maxx - 3; //12		///////////chect it

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
	bool isenter = 0;

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

	Node* temp = head, * tempv = head;
	while(tempv)
	{
		while (temp)	//Going right
		{
			if (temp->x == x && temp->y == y)
				return temp;
			temp = temp->right;
		}
		tempv = tempv->down;
		temp = tempv;
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

	void setAllNodes(int fwd, int bwd = 0)
	{
		int height = 0;
		if (!head)
			return;

		Node* temp = head, * temp2 = NULL, * temp3 = NULL, * temp4 = NULL, * tempv = head, * check = head;
		while (temp)
		{
			temp = temp->down;
			++height;
		}

		if (fwd)
		{
			temp = getCharacter(head, maxindex - 2, 0);
			for (int i = 0; i < height; ++i)
			{
				temp3 = NULL;
				if (getCharacter(head, maxindex, i) && getCharacter(head, 0, i + 1))
				{
					check = getCharacter(head, maxindex, i);
					if (check->right != NULL)
					{
						while (temp)	//Going right
						{
							if (tempv->down)
								temp3 = tempv->down;
							if (!(temp->right))
							{
								temp = tempv;

								temp->down = temp2;
								if (temp->down)
									temp->down->up = temp;
								if (temp2)
									temp2->right = temp3;
								if (temp3)
								{
									temp3->left = temp2;
									if (temp3->down)
									{
										temp2->down = temp3->down;
										temp2->down->up = temp2;
									}
									else
										temp2->down = NULL;
								}
								break;
							}
							temp2 = temp->right;
							temp = temp->right;
						}
					}
				}

				temp = tempv;		//Coming back to start col
				if (temp->down)
					temp = temp->down;
				if (tempv->down)
					tempv = tempv->down;
			}
		}

		if (bwd)
		{
			temp = getCharacter(head, maxindex - 2, 0);
			for (int i = 0; i < height; ++i)
			{
				temp3 = NULL;
				if (getCharacter(head, maxindex - 1, i) && getCharacter(head, maxindex, i))
				{
					check = getCharacter(head, maxindex, i);
					if (check->right != NULL)
					{
						while (temp)	//Going right
						{
							if (tempv->down)
								temp3 = tempv->down;	//temp3 = getCharacter(head, maxindex, i)
							if (!(temp->right))
							{
								//temp = tempv;
								if (temp3)
									temp4 = temp3->down;

								temp->right = temp3;
								if (temp->right)
								{
									temp->right->left = temp;
									temp3->right = temp3->down = NULL;	///////
								}
								
								if (temp2)
								{
									tempv->down = temp2;
									temp2->up = tempv;
									temp2->left = NULL;

									temp2->down = temp4;
									if (temp4)
										temp4->up = temp2;
								}
								break;
							}
							temp2 = temp3->right;
							temp = temp->right;
						}
					}
				}

				temp = tempv;		//Coming back to start col
				if (temp->down)
					temp = temp->down;
				if (tempv->down)
					tempv = tempv->down;
			}
		}

		temp = head;
		for (int i = 0; i < height && temp; ++i)
		{
			while (temp->right)	//Going right
			{
				setPointers(temp);
				if (!temp->right)
					break;
				temp = temp->right;
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
		if (!curr)
			return;

		Node* temp = curr, * tempv = head;
		while (tempv->y != temp->y)	//Coming to start col
			tempv = tempv->down;

		while(tempv)
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
			tempv = tempv->down;
			temp = tempv;			//Coming to start col
		}

		setAllNodes(1);
	}

	void down_forward(Node* curr)
	{
		if (!curr)
			return;

		Node* temp = curr, * tempv = curr;
		while (tempv->left)
			tempv = tempv->left;

		while (tempv)
		{
			while (temp)	//Going right
			{
				++temp->y;
				temp = temp->right;
			}
			tempv = tempv->down;
			temp = tempv;
		}

		setAllNodes(0);
	}

	void right_forward(Node* curr)
	{
		if (!curr)
			return;

		int ind = 0;
		while (curr)
		{
			curr->x = ind++;
			curr = curr->right;
		}
	}

	void up_forward(Node* curr)
	{
		if (!curr)
			return;

		Node* temp = curr, * tempv = curr;
		while (tempv->left)
			tempv = tempv->left;

		while (tempv)
		{
			while (temp)	//Going right
			{
				--temp->y;
				temp = temp->right;
			}
			tempv = tempv->down;
			temp = tempv;
		}

		setAllNodes(0);
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
				Node* temp = cur.next->down;
				if (temp)
				{
					temp->up = cur.next->left;
					temp->up->down = temp;
				}

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
					setAllNodes(0);
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
				{
					if (temp2)
						forward(getCharacter(head, cur.next->x + 2, cur.next->y), 1);
					else
						forward(cur.next->right, 1);
				}
				else
					setAllNodes(0);
				
				if (cur.next->right)
					cur.next = cur.next->right;
			}
			else
			{

			}
		}
	}

	void backward(Node* curr, bool bwd = 1)
	{
		if (!curr)
			return;

		bool isalone = 0;
		Node* temp = curr, * tempv = head;
		while (tempv->y != temp->y)	//Coming to start col
			tempv = tempv->down;

		if ((temp->data == enter || temp->isenter) && temp->x == 0)
		{
			up_forward(temp);
			return;
		}

		while (tempv)
		{
			if (tempv->x == 0 && tempv->right == NULL)
				isalone = 1;
			while (temp)	//Going right
			{
				--temp->x;
				if (temp->x < 0)	//for char at end of line
				{
					temp->x = maxindex;
					--temp->y;
				}
				temp = temp->right;
			}

			if (tempv->down)
				if (tempv->down->isenter || tempv->down->data == enter)
				{
					if (isalone)
					{
						if (tempv->up)
							tempv->up->down = tempv->down;
						if (tempv->down)
							tempv->down->up = tempv->up;
						up_forward(tempv->down);
					}
					break;
				}

			tempv = tempv->down;
			temp = tempv;			//Coming to start col
		}

		setAllNodes(0, bwd);
	}

	void delete_node(Node* curr, bool up = 1, bool down = 1, bool left = 1, bool right = 1)
	{
		if (!curr)
			return;
		
		if (curr->up && up)
			curr->up->down = curr->down;
		if (curr->down && down)
			curr->down->up = curr->up;
		if (curr->left && left)
			curr->left->right = curr->right;
		if (curr->right && right)
			curr->right->left = curr->left;

		delete curr;
	}

	void remove(Cursor& cur, int &x, int &y)
	{
		bool lastcase = 0, seclastchar = 0, goon = 1;

		if (!head)	//Empty notepad
			return;
		else if (cur.next == head && cur.index == 0 && cur.next->data != enter)	//At start of notepad
			return;
		else if (cur.next == head && !cur.next->right && !cur.next->down)	//Just one letter left in the start of whole notepad
		{//done
			delete cur.next;
			cur.index = 0;
			cur.next = NULL;
			head = NULL;
			x = minx;
			goon = 0;
		}
		else if (cur.next->isenter)
		{
			//cur.next->isenter = 0;
			if (cur.index == 0)		//Just shift the text up ---->  |abcd
			{
				//cur.next->isenter = 0;
			}
			else	//Delete char and shift the text back ---->  a|bcd
			{
				if (cur.next->right)
				{
					cur.next->right->isenter = 1;
					seclastchar = 1;
				}
				else
				{
					cur.next->data = enter;
					cur.next->isenter = 0;
					cur.index = 0;
					x = minx;
					goon = 0;
				}
			}
		}
		else if (cur.next->data == enter && cur.index == 0)		//Empty line
		{//done
			Node* temp = cur.next->up, * temp2 = cur.next->down;

			if (temp)
				temp->down = temp2;
			if (temp2)
				temp2->up = temp;

			if (cur.next->up)
			{
				while (temp->right)
					temp = temp->right;
				delete_node(cur.next);
				cur.next = temp;
				if (cur.next->data == enter)
					cur.index = 0;
				else
					cur.index = cur.next->x + 1;
				--y;
				x = cur.index + startx;
				if (temp2)
					up_forward(temp2);
				else
					setAllNodes(0);
			}
			goon = 0;
		}
		else if (cur.index == 1)	//Cursor to delete char at start of line	--->  a|bcd 	& isenter == 0
			seclastchar = 1;

		if (goon)
		{
			if (seclastchar)
			{//
				bool ishead = 0, putenter = 0;
				Node* temp = cur.next, * tempv = head;

				if (cur.next == head)
					ishead = 1;

				if (cur.next->right)
				{
					Node* tempu = cur.next->up, * tempd = cur.next->down;
					cur.next = cur.next->right;
					if (tempu)
					{
						tempu->down = cur.next;
						cur.next->up = tempu;
					}
					if (tempd)
					{
						tempd->up = cur.next;
						cur.next->down = tempd;
					}
				}
				else
				{
					while (tempv->y != cur.next->y)
						tempv = tempv->down;
					tempv = tempv->down;

					if (tempv)
						cur.next = tempv;
					if (cur.next->isenter)
						putenter = 1;
				}

				if (putenter)
				{
					temp->data = enter;
					cur.next = temp;
				}
				else
				{
					if (temp->right)
						delete_node(temp, 0, 0);
					else
						delete_node(temp);
				}

				if (ishead)
					head = cur.next;
				if (!putenter)
					backward(cur.next);
				else
					up_forward(cur.next);
				cur.index = 0;
				--x;
			}
			else if (cur.index == 0)	//	--->  |abcd		&& isenter == 0 && cur.next.y > 0
			{//
				////// We will add restriction a/c to word length later

				Node* temp = head;
				while (temp->y != cur.next->y - 1)
					temp = temp->down;
				while (temp->right)
					temp = temp->right;

				cur.next = temp;
				y = cur.next->y + starty;	//--y;
				x = cur.next->x + 3;		//x = maxx;
				cur.index = x - 2;
				gotoxy(x, y);

				lastcase = 1;
			}
			else	//Rest of cases
				lastcase = 1;

			if (lastcase)
			{//
				Node* tempdel = cur.next, * temp2 = cur.next->right, * tempv = head, * temp = cur.next->left;

				while (tempv->y != cur.next->y)
					tempv = tempv->down;

				if (cur.next->left)
					cur.next = cur.next->left;

				delete_node(tempdel);
				if (temp2)
					backward(temp2);
				else if (tempv->down)
				{
					if (tempv->down->isenter == 0 && tempv->down->data != enter)
					{
						cur.next->right = tempv->down;
						backward(tempv->down);
					}
					else
						setAllNodes(0);
				}

				--cur.index;
				--x;
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
	int ty = starty;
	gotoxy(startx, ty);

	for (int i = 0; i < maxy - starty + 1; ++i)	//Clearing screen
	{
		gotoxy(startx, ty++);
		for (int j = 0; j < maxx - startx; ++j)
		{
			cout << " ";
		}
	}
	ty = starty;
	gotoxy(startx, ty);

	if (!head)
		return;

	Node* temp = head, * tempv = head;
	
	while(tempv)	//Printing text
	{	
		gotoxy(startx, ty++);
		while(temp)
		{
			cout << temp->data;
			temp = temp->right;
		}
		tempv = tempv->down;
		temp = tempv;
	}

	gotoxy(x, y);
}
