#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main()
{
	int n, n1, n2;
	int pd1[2], pd2[2];
	pipe(pd1);
	pipe(pd2);
	
	pid_t pid1 = fork();
	if(pid1 == 0)	//Child 1
	{
		close(pd1[1]);

		read(pd1[0], &n, sizeof(n));
		n1 = n * 2;
		write(pd2[1], &n1, sizeof(n1));
		
		exit(0);
	}
	pid_t pid2 = fork();
	if(pid2 == 0)	//Child 2
	{
		close(pd2[1]);

		read(pd2[0], &n, sizeof(n));
		n2 = n + 10;
		write(pd1[1], &n2, sizeof(n2));

		exit(0);
	}
	
	cout<<"Enter the number: ";
	cin >> n;

	write(pd1[1], &n, sizeof(n));
	write(pd2[1], &n, sizeof(n));
	wait(NULL);
	wait(NULL);

	read(pd1[0], &n2, sizeof(n2));
	read(pd2[0], &n1, sizeof(n1));
		
	cout << "Child 1: Computed "<< n1 << endl;
	cout << "Child 2: Computed "<< n2 << endl;
		
	
	return 0;
}