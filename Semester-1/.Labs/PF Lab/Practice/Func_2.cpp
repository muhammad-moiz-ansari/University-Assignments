// C++ program to demonstrate
// the use of static Static
// variables in a Function
#include <iostream>
#include <string>
using namespace std;

void demo(0)
{
	// static variable
	static int c = 0;
	cout << c << " ";

	// value is updated and
	// will be carried to next
	// function calls
	c++;
}

int main()
{   
	int n;
	for (int i = 0; i < 8; i++)
		demo(0);
	return 0;
}

