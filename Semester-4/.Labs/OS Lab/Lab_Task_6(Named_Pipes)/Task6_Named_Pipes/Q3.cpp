#include <iostream>
#include <fcntl.h>      // open()
#include <sys/wait.h>
#include <sys/types.h>
#include <cstdlib>
#include <unistd.h>     // dup(), dup2()
#include <cstring>
using namespace std;

int main()
{
    const int size = 200;
    char buffer[size];

    int fd = open("input.txt", O_RDONLY);
    int cfd = dup(fd);

    dup2(fd, STDIN_FILENO);

    cout << "\nContent read from file: " << endl;
    while(cin.getline(buffer, size))
        cout << buffer << endl;

    dup2(fd, cfd);
    close(fd);
}