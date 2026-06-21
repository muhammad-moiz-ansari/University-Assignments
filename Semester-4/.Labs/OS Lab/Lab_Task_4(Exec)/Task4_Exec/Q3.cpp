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

        cout<<"\nExecution Completed!\n";
    }
    else if(pid==0)
    {
        char* args[] = {(char*)"/home/moiz129/Documents/Semester_4/Lab_Task_4/i230523_MoizAnsari_F_Lab4/conv", NULL};
        execv("/home/moiz129/Documents/Semester_4/Lab_Task_4/i230523_MoizAnsari_F_Lab4/conv", args);
    }

    return 0;
}