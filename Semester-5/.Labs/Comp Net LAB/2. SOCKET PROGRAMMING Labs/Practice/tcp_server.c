#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 9000

int main()
{
    char message[256];
    char buffer[256];

    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    listen(server_socket, 5);

    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);

    while (1)
    {
        recv(client_socket, &buffer, sizeof(buffer), 0);
        printf("Message from client: %s\n", buffer);

        if (strcmp(buffer, "quit") == 0)
            break;

        else if (isPalindrome(buffer) == 1)
        {
            strcpy(message, "Palindrome");
        }
        else
        {
            strcpy(message, "Not palindrome");
        }

        send(client_socket, message, sizeof(message), 0);
        printf("Message sent from server.\n");
    }
    close(client_socket);
    close(server_socket);
    return 0;
}