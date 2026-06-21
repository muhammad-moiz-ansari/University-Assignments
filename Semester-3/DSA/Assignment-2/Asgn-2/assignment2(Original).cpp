#include <iostream>
#include <Windows.h>
#include <fstream>
#include <filesystem>
//#include "Functionality.h"
using namespace std;

#pragma once
#include <iostream>
#include <Windows.h>
using namespace std;

char enter = '\0';
const int startx = 2, starty = 3;
const int miny = 3, maxy = 8;	//22,
const int minx = 2, maxx = 24;	//96;
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
	while (tempv)
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

		while (tempv)
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

	void insert(char c, Cursor& cur, int x, int y)
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

	void remove(Cursor& cur, int& x, int& y)
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
		while (temp)
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

	while (tempv)	//Printing text
	{
		gotoxy(startx, ty++);
		while (temp)
		{
			cout << temp->data;
			temp = temp->right;
		}
		tempv = tempv->down;
		temp = tempv;
	}

	gotoxy(x, y);
}


filesystem::path createdfile;
Cursor cur;
List notepad;
Node* check = NULL, * tempv = notepad.head, * endcheck = NULL;

void printchar(int n, char ch)
{
	for (int i = 0; i < n; ++i)
		cout << ch;
}

int extrasen = 0;
int extraexit = 0;
void printMainWindow()
{
	system("cls");
	cout << "| (Press \'Esc\' to Exit the program)";	extraexit = 21;
	printchar(maxx - 1 - 13 - extraexit, ' ');
	cout << "| Search:\n"
		<< "| Welcome to Notepad! You can write in this specified area."; extrasen = 38;
	printchar(maxx - 1 - 20 - extrasen, ' ');
	cout << "| \n"
		<< "| Start:";
	printchar(maxx - 1 - 7, ' ');
	cout << "|\n";
	for (int i = 0; i < maxy - 2; ++i)	//Printing empty writable space:
	{
		cout << "|";
		printchar(maxx - 1, ' ');
		cout << "|\n";
	}
	cout << "|";
	printchar(maxx - 1, '_');
	cout << "| \n"
		<< "Word Suggestions:\n";
}

void printStartingWindow(int& ch)
{
	cout << "\t\t\t------------------ Welcome to Ansari Notepad ------------------\n\n"
		<< "Which option would you like to choose?\n"
		<< "1. Create new file\n"
		<< "2. Load an existing file\n\n";
	while (1)
	{
		cout << "Choice: ";
		cin >> ch;
		if (ch == 1 || ch == 2)
			break;
		else
			cout << "Invalid choice (Choose only 1 or 2)\n\n";
	}
}

void printSavingWindow(bool& save)
{
	int choice = 0;
	system("cls");
	cout << "\n\n\n\n\n";
	cout << "\t\t\t\t\t _______________________________\n"
		<< "\t\t\t\t\t|                                |\n"
		<< "\t\t\t\t\t|  Do you want to save the file? |\n"
		<< "\t\t\t\t\t|  1. Yes                        |\n"
		<< "\t\t\t\t\t|  2. No                         |\n"
		<< "\t\t\t\t\t|                                |\n"
		<< "\t\t\t\t\t --------------------------------\n";

	while (1)
	{
		cout << "Choice: ";
		cin >> choice;
		if (choice == 1 || choice == 2)
			break;
		else
			cout << "Invalid choice (Choose only 1 or 2)\n";
	}
	if (choice == 1)
	{
		save = 1;
	}
	else
	{
		cout << "\nYour file has not been saved.\n";
		save = 0;
	}
}

void createFile()
{
	cout << "Enter the file name to create (No spaces allowed): ";
	cin >> createdfile;

	//For making .txt file:
	createdfile += '.';
	createdfile += 't';
	createdfile += 'x';
	createdfile += 't';
	createdfile += '\0';

	ofstream newFile(createdfile, ios::out);
	if (!newFile)
		cout << "\nFile not created.\n";
	else
	{
		cout << "\nFile created: " << createdfile << "\n";
		newFile.close();
	}
}

//
//
///////////////////////////////////// INSERT ////////////////////////////////////
//
//

bool checkisenter(Cursor& cur)
{
	bool yesenter = 0;
	if (cur.index == 0)
	{
		if (cur.next)
			if (cur.next->isenter)
			{
				cur.next->isenter = 0;
				yesenter = 1;
			}
	}
	else
	{
		if (cur.next)
			if (cur.next->right)
				if (cur.next->right->isenter)
				{
					cur.next->right->isenter = 0;
					yesenter = 1;
				}
	}
	return yesenter;
}

void CompleteInsert(char ch, int& x, int& y)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == ' ')
	{
		//// Check last character
		bool canIinsert = 0, inserted = 1, lastlineempty = 1;
		if (getCharacter(notepad.head, maxx - 3, maxy - starty) == NULL)
			canIinsert = 1;
		else if (cur.next->y < maxy - starty)
		{
			Node* temp = cur.next;
			while (temp->right)
				temp = temp->right;

			tempv = notepad.head;
			for (int i = 0; tempv; ++i, tempv = tempv->down)
			{
				if (getCharacter(notepad.head, maxx - 3, i) == NULL && cur.next->y <= i)
				{
					canIinsert = 1;
					break;
				}
			}
		}

		if (canIinsert)
		{
			if (y <= maxy)	//Checking if above last line
			{
				if (cur.next)
				{
					Node* temp = cur.next;
					while (temp->right)
						temp = temp->right;

					if (temp->x >= maxindex)
					{
						int i = 1;
						Node* tempen = notepad.head;
						while (tempen->y != cur.next->y)
						{
							tempen = tempen->down;
							++i;
						}
						if (tempen->down)					//Vertical temp ptr
							for (; tempen->down->isenter == 0 && tempen->down->data != enter; ++i)
							{
								if (getCharacter(notepad.head, maxindex, i) == NULL)
								{
									while (tempen->down)
										tempen = tempen->down;
									break;
								}
								tempen = tempen->down;
								if (!tempen->down)
									break;
							}

						if (tempen->down)
						{
							if (tempen->down->isenter || tempen->down->data == enter)
							{
								Node* tempcur = tempen;
								while (tempcur->right)
									tempcur = tempcur->right;

								tempv = notepad.head;				//Vertical temp ptr
								while (tempv->down)
									tempv = tempv->down;

								if (tempv->y + starty < maxy)	//Checking if last line is empty
								{
									if (tempcur->right == NULL)	//Cursor is at end of line and no text onwards on right
									{
										temp = notepad.head;
										while (temp->y != cur.next->y)
											temp = temp->down;
										if (temp->down)		//If some text is present in below line
											tempcur = temp->down;

										temp = tempcur->up;
										temp->down = new Node(enter, temp, tempcur, NULL, NULL, 0, tempcur->y);
										tempcur->up = temp->down;
										notepad.down_forward(tempcur);
									}
								}
								else
									lastlineempty = 0;
							}
						}
					}
				}

				if (lastlineempty)
				{
					if (x < maxx)
					{
						if (cur.next)
						{
							if (cur.next->data == enter)
							{
								cur.next->data = ch;
								if (cur.index != 0)
									inserted = 0;
								if (cur.next->y != 0)
									cur.next->isenter = 1;
							}
							else
							{
								bool yesenter = checkisenter(cur);
								notepad.insert(ch, cur, x, y);
								if (yesenter)
									cur.next->isenter = 1;
							}
						}
						else
						{
							bool yesenter = checkisenter(cur);
							notepad.insert(ch, cur, x, y);
							if (yesenter)
								cur.next->isenter = 1;
						}

						printText(notepad.head, x, y);
						if (inserted)
						{
							if (x < maxx)
								cur.index++;
							x++;
						}
					}
					else// if (x >= maxx)
					{
						x = startx;
						y++;
						cur.index = 0;
						gotoxy(x, y);

						if (cur.next)
						{
							if (cur.next->data == enter)
							{
								cur.next->data = ch;
								if (cur.index != 0)
									inserted = 0;
								cur.next->isenter = 1;
							}
							else
							{
								bool yesenter = checkisenter(cur);
								notepad.insert(ch, cur, x, y);
								if (yesenter)
									cur.next->isenter = 1;
							}
						}
						else
						{
							bool yesenter = checkisenter(cur);
							notepad.insert(ch, cur, x, y);
							if (yesenter)
								cur.next->isenter = 1;
						}
						printText(notepad.head, x, y);
						if (inserted)
						{
							x = startx + 1;
							cur.index = 1;
						}
					}
				}
			}
		}

		gotoxy(x, y);
	}
}

//
//
///////////////////////// ENTER //////////////////////////
//
//

void CompleteEnter(int& x, int& y)
{
	bool a = 0;
	tempv = notepad.head;
	if (tempv)					//Vertical temp ptr
		while (tempv->down)
			tempv = tempv->down;

	if (!tempv)		//If head is empty
	{
		notepad.insert(enter, cur, x, y);
		cur.next->down = new Node(enter, cur.next, NULL, NULL, NULL, 0, 1);
		cur.next = cur.next->down;
		y++;
		x = startx;
	}
	else if (tempv->y + starty < maxy)	//Checking if last line is empty
	{
		/////////   Handle enter
		Node* temp = notepad.head;
		bool b = 1;
		while (temp->y != cur.next->y && temp->down)
			temp = temp->down;

		if (cur.index == 0 || cur.next->right == NULL)	//Cursor is at start of line OR at end of line and no text onwards on right
		{
			if (cur.next->right == NULL)	//If no text on right
			{
				if (temp->down)		//If some text is present in below line
				{
					cur.next = temp->down;
					cur.index = 0;			//Brings cursor to start
					a = 1;
				}
				else	//If line below is empty
				{
					temp->down = new Node(enter, temp, NULL, NULL, NULL, 0, cur.next->y + 1);
					cur.next = temp->down;
					cur.index = 0;
					b = 0;			//Enter is done here
				}
			}
			if (b)	//If cursor is at start
			{
				if (cur.next->up == NULL)	//Cursor is at start of para
				{
					cur.next->up = new Node(enter, NULL, cur.next, NULL, NULL, 0, 0);
					notepad.head = cur.next->up;
					notepad.down_forward(cur.next);
				}
				else	//Cursor is at start of any other line
				{
					temp = cur.next->up;
					temp->down = new Node(enter, temp, cur.next, NULL, NULL, 0, cur.next->y);
					cur.next->up = temp->down;
					cur.next->isenter = 1;
					notepad.down_forward(cur.next);
					if (a)
						cur.next = cur.next->up;
				}
			}
		}
		else	//Cursor is in middle of text
		{
			Node* temp2 = cur.next->right, * temp3 = temp2;
			cur.next->right = NULL;
			while (temp3->left)
				temp3 = temp3->left;
			temp3 = temp3->down;

			temp->down = temp2;
			temp2->up = temp;

			temp2->down = temp3;
			if (temp3)
				temp3->up = temp2;
			temp2->left = NULL;
			temp2->isenter = 1;

			notepad.right_forward(temp2);
			notepad.down_forward(temp2);

			cur.next = temp2;
			cur.index = 0;
		}
		y++;
		x = startx;
	}
	if (cur.next->data == enter && cur.index == 1)
	{
		cur.index = 0;
		x = minx;
	}
	gotoxy(x, y);
}

void loadFile(List& notepad, Cursor& cur, int& x, int& y)
{
	filesystem::path name;
	cout << "Enter the file to load (No spaces allowed): ";
	cin >> name;

	//For searching for .txt file
	name += '.';
	name += 't';
	name += 'x';
	name += 't';
	name += '\0';

	ifstream loadFile(name, ios::in);
	if (!loadFile)
	{
		cout << "\nFile not found\nCreate a new file now\n\n";
		createFile();
	}
	else
	{
		cout << "File found!\n";

		printMainWindow();

		Node* temp = notepad.head, * tempv = notepad.head;

		gotoxy(startx, starty);
		char ch;
		while (loadFile.get(ch))
		{
			if (ch == enter)
				CompleteEnter(x, y);
			else if (ch == '\n')
			{
				CompleteEnter(x, y);
				loadFile.get(ch);
				if (ch != enter)
				{
					CompleteInsert(ch, x, y);
					cur.next->isenter = 0;
				}
				else
				{
					//CompleteInsert(ch, x, y);
				}
			}
			else
				CompleteInsert(ch, x, y);

			printText(notepad.head, x, y);
		}

		loadFile.close();
		//cout << "\nYour file has been loaded successfully.\n";
	}
}


int main(int argc, char* argv[])
{
	system("cls");
	system("color 0D");


	HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console

	DWORD Events = 0;     // Event count
	DWORD EventsRead = 0; // Events read from console

	bool Running = true,
		SaveWindow = true,
		save = 0;

	int x = startx, y = starty;
	int choice = 0;
	//Node* check = NULL, * tempv = notepad.head, * endcheck = NULL;

	//Starting window:
	printStartingWindow(choice);

	//File creating/loading:
	if (choice == 1)	//create new file
		createFile();
	else		// if(choice==2)	//load existing file
		loadFile(notepad, cur, x, y);

	//Printing whole static window:
	if (choice == 1)
		printMainWindow();
	gotoxy(x, y);

	//Program's main loop
	while (Running)
	{
		// gets the systems current "event" count
		GetNumberOfConsoleInputEvents(rhnd, &Events);

		if (Events != 0) { // if something happened we will handle the events we want

			// create event buffer the size of how many Events
			INPUT_RECORD eventBuffer[200];

			// fills the event buffer with the events and saves count in EventsRead
			ReadConsoleInput(rhnd, eventBuffer, Events, &EventsRead);

			// loop through the event buffer using the saved count
			for (DWORD i = 0; i < EventsRead; ++i) {

				// check if event[i] is a key event && if so is a press not a release
				if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown) {


					// check if the key press was an arrow key
					switch (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode) {

					case VK_UP: //up
						if (y > miny && cur.next)
							if (cur.next->up)
							{
								y--;
								cur.next = cur.next->up;
							}
							else
							{
								tempv = notepad.head;
								while (tempv->y != cur.next->y)
									tempv = tempv->down;

								if (tempv->up)
								{
									Node* temp = tempv->up;
									while (temp->right)
										temp = temp->right;
									cur.next = temp;
									cur.index = cur.next->x + 1;
									x = cur.next->x + 3;
									y = cur.next->y + 3;
								}
							}
						if (cur.next)
						{
							if (cur.next->data == enter && cur.index == 1)
							{
								cur.index = 0;
								x = minx;
							}
						}
						gotoxy(x, y);
						break;
					case VK_DOWN: //down
						if (y < maxy && cur.next)
							if (cur.next->down)
							{
								y++;
								cur.next = cur.next->down;
							}
							else
							{
								tempv = notepad.head;
								while (tempv->y != cur.next->y)
									tempv = tempv->down;

								if (tempv->down)
								{
									Node* temp = tempv->down;
									while (temp->right)
										temp = temp->right;
									cur.next = temp;
									cur.index = cur.next->x + 1;
									x = cur.next->x + 3;
									y = cur.next->y + 3;
								}
							}
						if (cur.next)
						{
							if (cur.next->data == enter && cur.index == 1)
							{
								cur.index = 0;
								x = minx;
							}
						}
						gotoxy(x, y);
						break;
					case VK_RIGHT: //right
						if (x == startx && cur.index == maxx - 2 && getCharacter(notepad.head, x - 2, y - 3))
						{
							x++;
							//y++;
							cur.index = x - 2;
							cur.next = getCharacter(notepad.head, x - 1 - 2, y - 3);
						}
						else if (x < maxx && cur.next)
						{
							if (cur.index == 0)
							{
								x++;
								cur.index++;
							}
							else if (cur.next->right)
							{
								x++;
								cur.next = cur.next->right;
								cur.index++;
							}
							else
							{
								check = getCharacter(notepad.head, 0, y + 1 - 3);
								if (check)
								{
									x = startx;
									y++;
									cur.next = check;
									cur.index = 0;
								}
							}
						}
						else if (x >= maxx && !(x == maxx && y == maxy))//////////////////
						{
							check = getCharacter(notepad.head, 0, y + 1 - 3);
							if (check)
							{
								x = startx;
								y++;
								cur.next = check;
								cur.index = 0;
							}
						}
						if (cur.next)
						{
							if (cur.next->data == enter && cur.index == 1)
							{
								cur.index = 0;
								x = minx;
							}
						}
						gotoxy(x, y);
						break;
					case VK_LEFT: //left
						if (x > minx && cur.next)
						{
							if (cur.next->left)
							{
								x--;
								cur.next = cur.next->left;
								cur.index--;
							}
							else if (cur.next->left == NULL && cur.index == 1)
							{
								x--;
								cur.index--;
							}
						}
						else if (x <= minx && !(x == startx && y == starty))//////////////////////////
						{
							Node* temp = getCharacter(notepad.head, 0, y - 1 - 3);
							while (temp->right)
								temp = temp->right;

							x = temp->x + 3;
							//x = maxx;
							y--;
							cur.index = x - 2;
							//if (x == maxx)
							cur.next = getCharacter(notepad.head, x - 3, y - 3);
							//else
							//	cur.next = getCharacter(notepad.head, x - 2, y - 3);
						}
						if (cur.next)
						{
							if (cur.next->data == enter && cur.index == 1)
							{
								cur.index = 0;
								x = minx;
							}
						}
						gotoxy(x, y);
						break;
					case VK_ESCAPE:	//escape to exit
						Running = 0;
						break;
					case VK_RETURN:	//enter

						CompleteEnter(x, y);
						printText(notepad.head, x, y);
						break;
					case VK_BACK:
						notepad.remove(cur, x, y);

						gotoxy(x, y);
						printText(notepad.head, x, y);
						break;
					default:
						CompleteInsert(eventBuffer->Event.KeyEvent.uChar.AsciiChar, x, y);
						gotoxy(x, y);
						break;
					}
				}

			} // end EventsRead loop

		}

	} // end program loop

	// Window for saving
	printSavingWindow(save);

	/////////////////////
	//				   //
	//   File Saving   //
	//				   //
	/////////////////////

	if (save)
	{
		ofstream saveFile(createdfile, ios::out);

		Node* temp = notepad.head, * tempv = notepad.head;

		while (tempv)
		{
			while (temp)
			{
				if (temp->isenter)
				{
					saveFile.put(enter);
					saveFile.put(temp->data);
				}
				else
					saveFile.put(temp->data);
				temp = temp->right;
			}
			if (tempv->down)
				saveFile.put('\n');
			tempv = tempv->down;
			temp = tempv;
		}
		saveFile.close();
		cout << "\nYour file has been saved successfully.\n";
	}

	return 0;
}