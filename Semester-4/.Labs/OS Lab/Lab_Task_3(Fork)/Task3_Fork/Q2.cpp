#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;

    pid_t pid = fork();

    if (pid == 0)   //Child process
    {
        cout << "The entered number is ";
        (n % 2 == 0) ? cout << "even\n" : cout << "odd\n";
    }
    else if (pid > 0)   //Parent process
    {
        wait(NULL);
        cout << "The square of entered number is " << n * n << endl;
    }

    return 0;
}