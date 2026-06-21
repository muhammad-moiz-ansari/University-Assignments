#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#define PORT 4444
#define BUFFER_SIZE 1024

int main()
{
    int clientSocket, ret;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    // Creating socket id
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0)
    {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Client Socket is created.\n");

    // Initializing server address structure
    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connect to the server
    ret = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if (ret < 0)
    {
        printf("Error in connection.\n");
        exit(1);
    }
    printf("Connected to Server.\n");

    while (1)
    {
        // Clear the buffer
        memset(buffer, 0, BUFFER_SIZE);

        // Input message to send to the server
        printf("Enter expression: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline

        if (strcmp(buffer, "exit") == 0)
        {
            send(clientSocket, buffer, strlen(buffer), 0);
            break;
        }

        // Send message to the server
        send(clientSocket, buffer, strlen(buffer), 0);

        // Clear the buffer to receive the server's response
        memset(buffer, 0, BUFFER_SIZE);

        // Receive the response from the server
        if (recv(clientSocket, buffer, BUFFER_SIZE, 0) < 0)
        {
            printf("Error in receiving data.\n");
        }
        else
        {
            printf("Result: %s\n", buffer);
        }
    }

    // Close the client socket
    close(clientSocket);
    return 0;
}