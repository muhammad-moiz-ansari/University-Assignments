#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <string>
using namespace std;

int main()
{
    pid_t pid=fork();

    if(pid>0)
    {
        wait(NULL);

        cout<<"\nProgram Executed Successfully!\n";
    }
    else if(pid==0)
    {
        char* arr=new char[30], *arg1=new char[30];
        cout<<"Enter comand name: ";
        cin>>arr;
        cout<<"Enter arguments: ";
        cin>>arg1;
        char* args[]={arr, arg1, NULL};
        cout<<endl;
        execvp(arr, args);
    }

    return 0;
}