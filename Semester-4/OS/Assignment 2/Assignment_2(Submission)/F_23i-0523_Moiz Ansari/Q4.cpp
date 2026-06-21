#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
using namespace std;

int main()
{
	string loga = "log_A.txt", logb = "log_B.txt", logc = "log_C.txt", logd = "log_D.txt";

	int fd1[2], fd2[2], fd3[2], fd4[2];
	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);

	const int size1 = 255, extra = 8, size2 = size1 + extra, size3 = size1 + 2 * extra, size4 = size1 + 3 * extra;
	char mess[size4];

	pid_t pid1, pid2, pid3, pid4;
	
	pid1 = fork();
	if (pid1 > 0)	//Parent
	{
		close(fd1[0]);	close(fd1[1]);
		close(fd2[0]);	close(fd2[1]);
		close(fd3[0]);	close(fd3[1]);
		close(fd4[0]);	close(fd4[1]);

		wait(NULL);
	}
	else		//Process A
	{
		cout << "Enter the message: ";
		cin.getline(mess, size1);
		
		close(fd2[0]);	close(fd2[1]);
		close(fd3[0]);	close(fd3[1]);

		write(fd1[1], mess, size1);
		close(fd1[1]);

		int fd = open(loga.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd != -1)
		{
			write(fd, mess, strlen(mess));
			close(fd);
		}

		pid2 = fork();
		if(pid2 > 0)
		{
			wait(NULL);
		}
		else		//Process B
		{
			close(fd1[1]);
			close(fd3[0]);	close(fd3[1]);
			close(fd4[0]);

			read(fd1[0], mess, size1);
			
			char str[size2] = "B says, ";
			strcpy(str + extra, mess);
			strcpy(mess, str);
			mess[size1 + extra] = '\0';
			
			write(fd2[1], mess, size2);
			close(fd2[1]);

			int fd = open(logb.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd != -1)
			{
				write(fd, " - Processed by B\n", 18);
				write(fd, mess, strlen(mess));
				close(fd);
			}

			pid3 = fork();
			if(pid3 > 0)
			{
				wait(NULL);
			}
			else		//Process C
			{
				close(fd1[0]);	close(fd1[1]);
				close(fd2[1]);
				close(fd4[0]);

				read(fd2[0], mess, size2);
				char str[size3] = "C says, ";
				strcpy(str + extra, mess);
				strcpy(mess, str);
				mess[size2 + extra] = '\0';

				write(fd3[1], mess, size3);
				close(fd3[1]);

				int fd = open(logc.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if(fd != -1)
				{
					write(fd, " - Processed by C\n", 18);
					write(fd, mess, strlen(mess));
					close(fd);
				}

				pid4 = fork();
				if(pid4 > 0)
				{
					wait(NULL);
				}
				else		//Process D
				{
					close(fd1[0]);	close(fd1[1]);
					close(fd2[0]);	close(fd2[1]);
					close(fd3[1]);

					read(fd3[0], mess, size3);

					char str[size4] = "D says, ";
					strcpy(str + extra, mess);
					strcpy(mess, str);
					mess[size3 + extra] = '\0';

					write(fd4[1], mess, size4);
					
					int fd = open(logd.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
					if(fd != -1)
					{
						write(fd, " - Processed by D\n", 18);
						write(fd, mess, strlen(mess));
						close(fd);
					}
					exit(0);
				}
				exit(0);
			}
			exit(0);
		}

		// Recieve message from D
		close(fd4[1]);
		read(fd4[0], mess, size4);
		close(fd4[0]);

		fd = open(loga.c_str(), O_WRONLY | O_CREAT | O_APPEND, 0644);
		if(fd != -1)
		{
			write(fd, "\n", 1);
			write(fd, mess, strlen(mess));
			close(fd);
		}

		cout << "Fully Modified Message: " << mess << endl;
	}
	
	
	
	return 0;
}
