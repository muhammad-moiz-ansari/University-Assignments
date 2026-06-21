#include <iostream>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstdlib>
#include <unistd.h>
using namespace std;

int main()
{
	int n, m, n1, n2, n3;
	int pd1[2], pd2[2], pd3[2];
	pipe(pd1);
	pipe(pd2);
	pipe(pd3);

	cout<<"Enter two number:\nn: ";
	cin>>n;
	cout<<"m: ";
	cin>>m;
	
	pid_t pid1 = fork();
	if(pid1 == 0)	//Child 1
	{
		close(pd2[1]);
		close(pd3[1]);

		n1 = n * n;
		write(pd1[1], &n1, sizeof(n1));
		
		exit(0);
	}
	pid_t pid2 = fork();
	if(pid2 == 0)	//Child 2
	{
		close(pd1[1]);
		close(pd3[1]);

		//Sum of Squares upto n
		n2 = 0;
		for(int i=0; i<=n; ++i)
		{
			n2 += i * i;
		}
		write(pd2[1], &n2, sizeof(n2));

		exit(0);
	}
	pid_t pid3 = fork();
	if(pid3 == 0)	//Child 3
	{
		close(pd1[1]);
		close(pd2[1]);

		//GCD of n & m
		int r;
		while(m != 0)
		{
			r = n % m;
			n = m;
			m = r;
		}
		n3 = n;
		write(pd3[1], &n3, sizeof(n2));

		exit(0);
	}

	wait(NULL);
	wait(NULL);
	wait(NULL);

	read(pd1[0], &n1, sizeof(n1));
	read(pd2[0], &n2, sizeof(n2));
	read(pd3[0], &n3, sizeof(n3));
		
	cout << "Child 1: Computed "<< n1 << endl;
	cout << "Child 2: Computed "<< n2 << endl;
	cout << "Child 3: Computed "<< n3 << endl;
	
	return 0;
}