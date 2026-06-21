#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main()
{
    char buffer[256];
    char request[256];
    int sockfd;

    // create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr;
    socklen_t addr_size = sizeof(server_addr);

    // server address setup
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    while (1)
    {
        // send message
        printf("Enter student ID(20xx-CS-xxx): ");
        scanf("%s", request);
        sendto(sockfd, request, strlen(request) + 1, 0, (struct sockaddr *)&server_addr, addr_size);

        // if (request[0] == 'e', request[1] == 'x', request[2] == 'i', request[3] == 't')
        if (strcmp(request, "exit") == 0)
            break;

        // receive reply
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_size);
        printf("Result: %s\n\n", buffer);
    }

    close(sockfd);
    return 0;
}