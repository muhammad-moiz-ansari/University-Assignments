#include <iostream>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <string>
using namespace std;

void fib()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;

    int a = -1, b = 1, c = 0;
    cout << "Fibbonachi Seqence: ";
    for (int i = 0; i < n; ++i)
    {
        c = a + b;
        a = b;
        b = c;
        cout << c << "  ";
    }
    cout << "\n";
}

bool palin()
{
    string str;
    cout << "Enter a string: ";
    cin >> str;

    int l = str.length();
    for (int i = 0; i < l; ++i)
    {
        if (str[i] != str[l - i - 1])
        {
            cout << "The string is NOT a palindrome! :(\n";
            return 0;
        }
    }
    cout << "The string is a palindrome! :D\n";
    return 1;
}

void sumd()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;

    int sum = 0;
    while (n != 0)
    {
        sum += n % 10;
        n = n / 10;
    }
    cout << "Sum of Digits = " << sum << endl;
}

void numw()
{
    string s;
    cout << "Enter a string: ";
    cin.ignore();
    getline(cin, s);

    int count = 1;
    for (int i = 0; i < s.length(); ++i)
    {
        if (!((s[i] >= 'a' && s[i] <= 'z') || (s[i] >= 'A' && s[i] <= 'Z') || (s[i] >= '0' && s[i] <= '9')))
            ++count;
    }
    cout << "Number of words: " << count << endl;
}

int main()
{
    pid_t pid = fork();
    if (pid > 0) // Parent
    {
        wait(NULL);

        cout << "\nAll child processes executed!\n";
    }
    else if (pid == 0)
    {
        cout << "\nChild 1:\n";
        fib();

        pid_t cpid2 = fork();
        if (cpid2 > 0)
            wait(NULL);
        else if (cpid2 == 0)
        {
            cout << "\nChild 2:\n";
            palin();

            pid_t cpid2 = fork();
            if (cpid2 > 0)
                wait(NULL);
            else if (cpid2 == 0)
            {
                cout << "\nChild 3:\n";
                sumd();

                pid_t cpid3 = fork();
                if (cpid3 > 0)
                    wait(NULL);
                else if (cpid3 == 0)
                {
                    cout << "\nChild 4:\n";
                    numw();
                }
            }
        }
    }

    return 0;
}
