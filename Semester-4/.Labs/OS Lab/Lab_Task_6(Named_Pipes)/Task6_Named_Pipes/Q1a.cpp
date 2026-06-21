#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
using namespace std;

int main()
{
    const int size = 200;
    char message1[size]="", message2[size]="";
    char pipe1[]="pipe1", pipe2[]="pipe2";

    //int p1=mkfifo(pipe1, 0666);
    //int p2=mkfifo(pipe2, 0666);

    int fd1, fd2;

    fd1=open("pipe1", O_WRONLY);
   

    while(true)
    {
        cout<<"\nEnter message: ";
        cin.getline(message1, 200);

        write(fd1, message1, size);

        sleep(1);
        fd2=open("pipe2", O_RDONLY);
        read(fd2, message2, size);
        cout<<"\nProcess B Responded: "<<message2;

        if(strcmp(message1, "exit")==0)
            break;
    }

    close("pipe1");
    close("pipe2");
    //unlink(pipe1);
    //unlink(pipe2);

    return 0;
}