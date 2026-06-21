#include <iostream>
#include <Windows.h>
#include <fstream>
#include <filesystem>
#include "Functionality.h"
using namespace std;

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
	cout << "| (Press \'Esc\'";// to Exit the program)";	extraexit = 21;
	printchar(maxx - 1 - 13 - extraexit, ' ');
	cout << "| Search:\n"
		<< "| Welcome to Notepad!";// You can write in this specified area."; extrasen = 38;
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

void CompleteInsert(char ch, int&x, int&y)
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
						else if(x >= maxx && !(x == maxx && y == maxy))//////////////////
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