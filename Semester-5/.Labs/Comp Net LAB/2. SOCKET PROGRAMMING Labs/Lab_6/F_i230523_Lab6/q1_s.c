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
    char message[900] = "Hello from UDP server!";
    int counter = 0;

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    // create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // setup server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // bind socket
    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while (1)
    {
        // receive message from client
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client_addr, &addr_size);
        buffer[n] = '\0'; // null-terminate
        printf("Recieved message: %s\n", buffer);
        printf("Total messages: %d\n", counter);

        // send reply
        sprintf(message, "Echo # %d: %s", counter++, buffer);
        sendto(sockfd, message, strlen(message) + 1, 0, (struct sockaddr *)&client_addr, addr_size);
    }

    close(sockfd);
    return 0;
}
