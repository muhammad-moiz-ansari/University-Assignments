#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
using namespace std;

int main()
{
    const int size = 200;
    char message1[size]="", message2[size]="";
    string pipe1="pipe1", pipe2="pipe2";

    //mkfifo(pipe1, 0666);
    //mkfifo(pipe2, 0666);

    int fd1, fd2;

    fd1=open("pipe1", O_RDONLY);
    

    while(true)
    {
        read(fd1, message1, size);
        cout<<"\nReceived: "<<message1;

        sleep(1);
        fd2=open("pipe2", O_WRONLY);
        write(fd2, message2, size);
        cout<<"\nEnter response: ";
        cin.getline(message2, 200);

        if(strcmp(message2, "exit")==0)
            break;
    }

    close("pipe1");
    close("pipe2");
    //unlink(pipe1);
    //unlink(pipe2);

    return 0;
}