#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
using namespace std;

int main()
{
    pid_t pid=fork();

    if(pid>0)
    {
        wait(NULL);

        cout<<"\nChild Process Executed Successfully!\n";
    }
    else if(pid==0)
    {
        cout<<"Current Date & Time:\n";
        execlp("date", "date", NULL);
    }

    return 0;
}