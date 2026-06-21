#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
using namespace std;

int main()
{
    int a, b;
    cout << "Enter two numbers: \n";
    cin >> a >> b;

    pid_t pid1 = fork();

    if(pid1 > 0)
    {
        wait(NULL);
        pid_t pid2 = fork();
        if(pid2 > 0)
        {
            wait(NULL);
            pid_t pid3 = fork();
            if(pid3 > 0)
            {
                wait(NULL);
            }
            else if(pid3 == 0)
            {
                cout << "Child 3 (Product) = " << a * b << endl;
                exit(0);
            }
        }
        else if(pid2 == 0)
        {
            cout << "Child 2 (Difference) = " << a - b << endl;
            exit(0);
        }
    }
    else if(pid1 == 0)  
    {
        cout << "Child 1 (Sum) = " << a + b << endl;
        exit(0);
    }
    cout << "All Children Executed!" << endl;

    return 0;
}