#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <cstdlib>
#include <fstream>
using namespace std;

string logp = "/home/moiz129/Assignment1/q4log.txt";
ofstream file(logp);

// Functions for Child to perform
int length(string str)
{
    int size = 0;
    for(; str[size] != '\0'; ++size);
    return size;
}
string reverse(string str)
{
    int l = length(str);
    for(int i = 0; i < l/2; ++i)
    {
        char a = str[i];
        str[i] = str[l - i - 1];
        str[l - i - 1] = a;
    }
    return str;
}
string addtwo(string str)
{
    for(int i = 0; i < length(str); ++i)
        str[i] = str[i] + 2;
    return str;
}
string sort(string str)
{
    int l = length(str);
    bool b = 0;
    for(int i = 0; i < l - 1; ++i)
    {
        b = 0;
        for(int j = 0; j < l - 1 - i; ++j)
        {
            if(str[j] > str[j + 1])
            {
                int t = str[j];
                str[j] = str[j + 1];
                str[j + 1] = t;
                b = 1;
            }
        }
        if (!b)
            break;
    }
    return str;
}
string capitalize(string str)
{
    for(int i = 0; i < length(str); ++i)
    {
        if(str[i]>='a' && str[i]<='z')
            str[i] -= 32;
    }
    return str;
}

void select(int& ch)
{
    cout<<"\nWhich task would you like to perform?\n"
        <<"1. Reverse\n"
        <<"2. Find Length\n"
        <<"3. Add 2 in the ASCII of each character\n"
        <<"4. Sort\n"
        <<"5. Capitalize\n";
    while(true)
    {
        cout<<"Choose: ";
        cin>>ch;
        if(ch>=1 && ch<=5)
            break;
        else
            cout<<"Invalid input...Enter only 1-5\n";
    }
    cout << endl;
}

void perform(int ch, string& str, pid_t pid)
{
    string a, b = to_string(getpid()), c;
    if(ch == 1)
    {
        a = "Reverse", c = reverse(str);
        cout << "Reversed string: " << c << endl;
    }
    else if(ch == 2)
    {
        a = "Find Length", c = to_string(length(str));
        cout << "Length of string: " << c << endl;
    }
    else if(ch == 3)
    {
        a = "Add 2 in ASCII", c = addtwo(str);
        cout << "String after adding 2 in ASCII:" << c << endl;
    }
    else if(ch == 4)
    {
        a = "Sort", c = sort(str);
        cout << "Sorted string: " << c << endl;
    }
    else    //if(ch == 5)
    {
        a = "Capitalize", c = capitalize(str);
        cout << "Capitalized string: " << c << endl;
    }
    file.open(logp, ios::app);
    if(file.is_open())
    {
        file << "Task: " << a << endl;
        file << "Process ID: " << b << endl;
        file << "Result: " << c << "\n\n";
        file.close();
    }
}

void performtask(string& str, pid_t pid)
{
    int ch;
    select(ch);
    perform(ch, str, pid);
}

int main()
{
    string str;
    cout << "Enter a string: ";
    getline(cin, str);

    file.open(logp);
    if(file.is_open())
    {
        file << "";
        file.close();
    }
    else
        "File not opened!\n";

    pid_t pid = fork();
    if(pid > 0)     //Main parent
    {
        wait(NULL);

        cout << "\nAll tasks executed!\n"
            <<"Exiting terminal...\n";
    }
    else if (pid == 0)      //Child 1
    {
        performtask(str, pid);
        pid_t cpid1 = fork();
        if(cpid1 > 0)
            wait(NULL);
        else if(cpid1 == 0)      //Child 2
        {
            performtask(str, cpid1);
            pid_t cpid2 = fork();
            if(cpid2 > 0)
                wait(NULL);
            else if(cpid2 == 0)      //Child 3
            {
                performtask(str, cpid2);
                pid_t cpid3 = fork();
                if(cpid3 > 0)
                    wait(NULL);
                else if(cpid3 == 0)      //Child 4
                {
                    performtask(str, cpid3);
                    pid_t cpid4 = fork();
                    if(cpid4 > 0)
                        wait(NULL);
                    else if(cpid4 == 0)      //Child 5
                    {
                        performtask(str, cpid4);
                    }
                }
            }
        }
    }

    cout<<"\n\n---------- Log File ----------\n\n";
    ifstream file(logp);
    if(file.is_open())
    {
        string line;
        while(getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }

    return 0;
}