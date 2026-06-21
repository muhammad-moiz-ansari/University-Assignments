#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

int main(int argc, char *argv[])
{
    char buffer[256];
    char request[256];
    strcpy(request, argv[1]);
    int sockfd;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in server_addr;
    socklen_t addr_size = sizeof(server_addr);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    while (1)
    {
        printf("Enter .....: ");
        scanf("%s", request);
        printf("Sending: %s", request);
        sendto(sockfd, request, strlen(request) + 1, 0, (struct sockaddr *)&server_addr, addr_size);

        if (strcmp(request, "exit") == 0)
            break;

        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_size);
        printf("Message from server: %s\n", buffer);
    }

    close(sockfd);
    return 0;
}