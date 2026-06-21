#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main()
{
	int a, b;
	cout << "Enter first number: ";
	cin >> a;
	
	cout << "Enter second number: ";
	cin >> b;
	cout << endl;
	
	pid_t pid = fork();
	
	if (pid > 0)
	{
		wait(NULL);
		cout << "Parent result (Sum) = "<< a + b << endl;
	}
	else if (pid == 0)
		cout << "Child result (Difference) = "<< a - b << endl;
	
	return 0;
}
