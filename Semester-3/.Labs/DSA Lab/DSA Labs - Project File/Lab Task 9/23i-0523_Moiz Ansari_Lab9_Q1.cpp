#include <iostream>
using namespace std;

class Cell
{
public:
	int x, y;
	string dir;
	bool l, r, u, d;

	int data;

	Cell(int xx = 0, int yy = 0, string dirr = "")
	{
		x = xx;
		y = yy;
		dir = dirr;

		data = 0;

		l = r = u = d = 1;
	}

	void initialize()
	{
		l = r = u = d = 1;
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

	void push(int val)
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
			top--;
	}

	T getval()
	{
		if (isEmpty())
			return -1;
		else
			return arr[top];
	}

};





Cell* visited;
Cell* ptr;
Cell** maze;

void createmaze(int** arr, int n, int m)
{
	maze = new Cell * [n];
	for (int i = 0; i < n; ++i)
		maze[i] = new Cell[m];

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
		{
			maze[i][j].x = j;
			maze[i][j].y = i;
			maze[i][j].data = arr[i][j];
		}

	visited = new Cell[n * m];
}

bool moveup(Cell cell, int **arr, int n, int m, int x, int y)
{
	if (y > 0 && cell.u && arr[y - 1][x] == 1)
		return true;
	else
		return false;
}

bool movedown(Cell cell, int** arr, int n, int m, int x, int y)
{
	if (y < n - 1 && cell.d && arr[y + 1][x] == 1)
		return true;
	else
		return false;
}

bool moveleft(Cell cell, int** arr, int n, int m, int x, int y)
{
	if (x > 0 && cell.l && arr[y][x - 1] == 1)
		return true;
	else
		return false;
}

bool moveright(Cell cell, int** arr, int n, int m, int x, int y)
{
	if (x < m - 1 && cell.r && arr[y][x + 1] == 1)
		return true;
	else
		return false;
}

bool isReachable(int **arr, int n, int m, int x, int y)
{
	createmaze(arr, n, m);

	Stack<Cell> st(n * m);

	ptr = &maze[0][0];

	
	return 1;
}

int main()
{
	char ch = '\0';

	int n = 4, m = 4;
	int** mazearr = new int* [n];
	for (int i = 0; i < n; ++i)
		mazearr[i] = new int[m];

	int mazeData[4][4] = {
		{1, 0, 0, 0},
		{1, 1, 0, 1},
		{0, 1, 0, 0},
		{1, 1, 1, 1}
	};

	for (int i = 0; i < n; ++i)
		for (int j = 0; j < m; ++j)
			mazearr[i][j] = mazeData[i][j];

	createmaze(mazearr, n, m);

	ptr = &maze[0][0];

	int xx = 0, yy = 0, exit = 0;
	cout << "Enter coordinates of food: ";
	cout << "x, y: ";
	cin >> xx >> yy;
	--xx;
	--yy;
	maze[yy][xx].data = 1;
	mazearr[yy][xx] = 1;



	while ((ptr->x != xx || ptr->y != yy) || exit == 1)
	{
		bool b = 0;
		//print:
		cout << "\n\n\n";
		for (int i = 0; i < n; ++i) 
		{
			for (int j = 0; j < m; ++j) 
			{
				if (i == yy && j == xx)
					cout << "F  ";
				else if (i == ptr->y && j == ptr->x)
					cout << "C  ";
				else
					cout << mazearr[i][j] << "  ";
			}
			cout << endl;
		}

		cout << "Where move: \n";
		cout << "W. Up\nS. Down\nA. Left\nD. Right\nQ. Exit\n";
		while (1)
		{
			cout << "Choose: ";
			cin >> ch;
			if (ch == 'a' || ch == 's' || ch == 'd' || ch == 'w' || ch == 'q')
				break;
			else
			{
				if (ch == 'q')
				{
					exit = 1;
					break;
				}
				cout << "Invalid Input\n";
			}
		}
		if (exit)
			break;

		if (ch == 'w')
		{
			if (moveup(*ptr, mazearr, n, m, ptr->x, ptr->y))
				ptr = &maze[ptr->y - 1][ptr->x];
			else
				cout << "\nCant move up\n";
		}
		else if (ch == 's')
		{
			if (movedown(*ptr, mazearr, n, m, ptr->x, ptr->y))
				ptr = &maze[ptr->y + 1][ptr->x];
			else
				cout << "\nCant move down\n";
		}
		else if (ch == 'a')
		{
			if (moveleft(*ptr, mazearr, n, m, ptr->x, ptr->y))
				ptr = &maze[ptr->y][ptr->x - 1];
			else
				cout << "\nCant move left\n";
		}
		else if (ch == 'd')
		{
			if (moveright(*ptr, mazearr, n, m, ptr->x, ptr->y))
				ptr = &maze[ptr->y][ptr->x + 1];
			else
				cout << "\nCant move right\n";
		}
	}
	if (exit)
		cout << "\nGame exited\n";
	else
		cout << "\nMouse ate food!\n";

	return 0;
}