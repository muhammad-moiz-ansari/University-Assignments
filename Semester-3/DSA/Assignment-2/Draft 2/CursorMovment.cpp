#include <iostream>
#include <Windows.h>
#include <fstream>
#include "Functionality.h"
using namespace std;

//void gotoxy(int x, int y)
//{
//	COORD c = { x, y };
//	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
//}

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
	cout << "| (Press \'Esc\' to Exit";// the program)";	extraexit = 13;
	printchar(maxx - 1 - 21 - extraexit, ' ');
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
		cout << "\nYour file has been saved.\n";
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
	char name[80];
	cout << "Enter the file name to create (No spaces allowed): ";
	cin >> name;

	//For making .txt file:
	int size = 0;
	for (; name[size] != '\0'; ++size);
	name[size++] = '.';
	name[size++] = 't';
	name[size++] = 'x';
	name[size++] = 't';
	name[size++] = '\0';

	ofstream newFile(name);
	if (!newFile)
		cout << "\nFile not created.\n";
	else
		newFile.close();
}

void loadFile()
{
	char name[100];
	cout << "Enter the file to load (No spaces allowed): ";
	cin >> name;

	//For searching for .txt file
	int size = 0;
	for (; name[size] != '\0'; ++size);
	name[size++] = '.';
	name[size++] = 't';
	name[size++] = 'x';
	name[size++] = 't';
	name[size++] = '\0';

	ifstream loadfile(name);
	if (!loadfile)
	{
		cout << "\nFile not found\nCreate a new file now\n\n";
		createFile();
	}
	else
	{
		char i;
		cout << "File found!\nPress enter:";
		cin >> i;
		//
		//
		//
		//      Loading file functionality
		//
		//
		//
		//
	}
}
Cursor cur;

int main(int argc, char* argv[])
{
	system("cls");
	HANDLE  rhnd = GetStdHandle(STD_INPUT_HANDLE);  // handle to read console

	DWORD Events = 0;     // Event count
	DWORD EventsRead = 0; // Events read from console

	List notepad;

	bool Running = true,
		SaveWindow = true,
		save = 0;

	//int startx = 2, starty = 3;
	int x = startx, y = starty;
	//int miny = 3, maxy = 22,
	//	minx = 2, maxx = 96;
	int choice = 0;

	//Starting window:
	printStartingWindow(choice);
	
	//File creating/loading:
	if (choice == 1)	//create new file
		createFile();
	else		// if(choice==2)	//load existing file
		loadFile();

	//Printing whole static window:
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
						gotoxy(x, y);
						break;
					case VK_DOWN: //down
						if (y < maxy && cur.next)
							if (cur.next->down)
							{
								y++;
								cur.next = cur.next->down;
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
						}
						else if(x >= maxx && !(x == maxx && y == maxy))//////////////////
						{
							x = startx;
							y++;
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
						gotoxy(x, y);
						break;
					case VK_ESCAPE:	//escape to exit
						Running = 0;
						break;
					case VK_RETURN:	//enter
						if (y < maxy)
						{
							/////////   Handle enter
							y++;
							x = startx;
						}
						gotoxy(x, y);
						break;
					default:
						if ((eventBuffer->Event.KeyEvent.uChar.AsciiChar >= 'a' && eventBuffer->Event.KeyEvent.uChar.AsciiChar <= 'z') || (eventBuffer->Event.KeyEvent.uChar.AsciiChar >= 'A' && eventBuffer->Event.KeyEvent.uChar.AsciiChar <= 'Z') || eventBuffer->Event.KeyEvent.uChar.AsciiChar == ' ' || eventBuffer->Event.KeyEvent.uChar.AsciiChar == '\n')
						{
							if (y <= maxy)
							{
								if (x < maxx)
								{
									notepad.insert(eventBuffer->Event.KeyEvent.uChar.AsciiChar, cur, x, y);

									printText(notepad.head, x, y);
									//cout << eventBuffer->Event.KeyEvent.uChar.AsciiChar;
									x++;
									if (x < maxx)
									{
										cur.index++;
									}
									else
									{
										if (!(y <= maxy && x < maxx))	////////////////////////////////set boundaries for last element putted
										{
											x = startx;
											cur.index = 0;
											y++;
										}
										
									}
								}
								else// if (x >= maxx)
								{
									x = startx;
									y++;
									cur.index = 0;
									gotoxy(x, y);
									notepad.insert(eventBuffer->Event.KeyEvent.uChar.AsciiChar, cur, x, y);
									printText(notepad.head, x, y);
								}
							}
						}
						//cur.next = getCharacter(notepad.head, x, y);
						//if (y > maxy)
						//	gotoxy(x, y - 1);
						//else
							gotoxy(x, y);
						break;
					}
				}

			} // end EventsRead loop

		}

	} // end program loop

	// Window for saving
	printSavingWindow(save);

	///////////////////
	//
	//   File Saving
	//
	///////////////////

	return 0;
}