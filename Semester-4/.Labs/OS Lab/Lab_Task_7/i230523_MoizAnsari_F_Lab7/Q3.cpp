#include <iostream>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
using namespace std;

void func(int no)
{
	cout << "SIGUSR1 Called!🥳\n";
}

int main()
{
	pid_t pid = fork();
	sigset_t newmask, oldmask;

	signal(SIGUSR1, func);

	if(pid > 0)	//Parent
	{
		sigemptyset(&newmask);
		sigaddset(&newmask, SIGUSR1);
		sigprocmask(SIG_BLOCK, &newmask, &oldmask);

		sigsuspend(&oldmask);

		cout << "Received SIGUSR1, resuming execution.\n";

		wait(NULL);
	}
	else	//Child
	{
		sleep(5);
		kill(getppid(), SIGUSR1);
		raise(SIGKILL);
	}

	return 0;
}
