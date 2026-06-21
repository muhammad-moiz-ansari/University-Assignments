#include <iostream>
#include <signal.h>
using namespace std;

void func1(int sigma)
{
    cout << "\nSIGINT recieved!🥳\nIgnoring Ctrl+C.\n";
}

void func2(int sigma)
{
    cout << "\nSIGTERM received!🔪\nExiting program.\n";
    exit(0);
}

void func3(int sigma)
{
    cout << "\nSIGALRM received!⏰\nTimer expired.\n";
}

int main()
{
    signal(SIGINT, func1);
    signal(SIGTERM, func2);
    signal(SIGALRM, func3);

    cout << "PID: " << getpid();
    alarm(3);
    
    while(1)
    {
        pause();
    }

    

    return 0;
}