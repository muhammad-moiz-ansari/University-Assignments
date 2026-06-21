#include <iostream>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
using namespace std;

void func(int hehe)
{
	cout << "\nParent receives signal: " << hehe << endl;
}

int main()
{
	pid_t pid = fork();

	if(pid == 0) //Child
	{
		sleep(3);
		cout << "Child sends signal SIGUSR1 to parent!\n";
		kill(getppid(), SIGUSR1);
	}
	else	//Parent
	{
		signal(SIGUSR1, func);
		pause();
	}

	return 0;
}
