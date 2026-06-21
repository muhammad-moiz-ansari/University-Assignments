#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h> // For pid_t type
#include <unistd.h>    // For fork(), close()
#define PORT 4444
#define BUFFER_SIZE 1024

int main()
{
    int sockfd, ret;
    struct sockaddr_in serverAddr;
    int clientSocket;
    struct sockaddr_in cliAddr;
    socklen_t addr_size;
    pid_t childpid;
    int opt = 1;
    char buffer[BUFFER_SIZE];

    // Creates a TCP socket id from IPV4 family
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Server Socket is created.\n");

    // Allow address reuse
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Initializing address structure with NULL
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Binding the socket id with the socket structure
    ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        printf("Error in binding.\n");
        exit(1);
    }

    if (listen(sockfd, 10) == 0)
    {
        printf("Listening...\n\n");
    }

    addr_size = sizeof(cliAddr);

    while (1)
    {
        // Accept client connection
        clientSocket = accept(sockfd, (struct sockaddr *)&cliAddr, &addr_size);
        if (clientSocket < 0)
        {
            exit(1);
        }
        // Displaying information of connected client
        printf("Connection accepted from %s:%d\n", inet_ntoa(cliAddr.sin_addr),
               ntohs(cliAddr.sin_port));

        // Create a child process for the connected client
        if ((childpid = fork()) == 0)
        {
            // Close the listening socket in the child process
            close(sockfd);
            while (1)
            {
                // Clear the buffer
                memset(buffer, 0, BUFFER_SIZE);

                // Receive message from the client
                int recv_bytes = recv(clientSocket, buffer, BUFFER_SIZE, 0);
                if (recv_bytes <= 0)
                {
                    printf("Client disconnected.\n");
                    break;
                }

                // Print the client's message
                printf("Expression: %s\n", buffer);

                // Parse expression
                char num1[BUFFER_SIZE], num2[BUFFER_SIZE], result[BUFFER_SIZE], op;
                float a, b, res;
                int ind = 0;

                // Num1
                for (int i = 0; i < strlen(buffer); ++i)
                {
                    if (buffer[i] == ' ')
                    {
                        ind = i;
                        break;
                    }
                    num1[i] = buffer[i];
                }
                num1[ind++] = '\0';

                //printf("%c\n", buffer[ind]);
                op = buffer[ind++];
                //printf("%c\n", buffer[ind]);
                ind++;
                //printf("%c\n", buffer[ind]);

                // Num2
                for (int i = ind, j=0; i < strlen(buffer); ++i, ++j)
                {
                    num2[j] = buffer[i];
                }
                num2[++ind] = '\0';

                // Conversion
                a = (float)atoi(num1);
                b = (float)atoi(num2);

                

                // Calculation
                switch (op)
                {
                case '+':
                    res = a + b;
                    break;

                case '-':
                    res = a - b;
                    break;

                case '*':
                    res = a * b;
                    break;

                case '/':
                    if (b != 0)
                        res = a / b;
                    break;
                }

                //printf("a=%f\nb=%f\nres=%f\n", a, b, res);

                if (op == '/' && b == 0)
                    sprintf(result, "ERROR -> Cant divide by zero");
                else
                    sprintf(result, "%f", res);

                printf("Result = %f\n\n", res);

                // Respond back to the client
                send(clientSocket, result, strlen(result), 0);
            }

            // Close the client socket and exit child process
            close(clientSocket);
            exit(0);
        }

        // Close the client socket in the parent process
        close(clientSocket);
    }

    // Close the listening socket
    close(sockfd);
    return 0;
}