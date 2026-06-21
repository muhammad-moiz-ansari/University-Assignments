












































// TCP thread
// Server

#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdbool.h>

#define PORT 7000
#define BUFFER_SIZE 1024

void *handle_client(void *arg)
{
    int client_fd = *((int *)arg);
    free(arg);

    char buffer[BUFFER_SIZE];
    char strengthstr[BUFFER_SIZE];
    int bytes_received;

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received <= 0)
        {
            printf("Client %d disconnected.\n", client_fd);
            close(client_fd);
            break;
        }

        sprintf(buffer, "response from server");
        printf("Cleint %d\n", client_fd);

        send(client_fd, buffer, strlen(buffer), 0);
    }
    return NULL;
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    pthread_t tid;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    listen(server_fd, 10);
    printf("Listening...\n");

    while (1)
    {
        addr_size = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_size);
        if (client_fd < 0)
        {
            perror("Accept failed");
            continue;
        }

        printf("Connection accepted from %s:%d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        int *pclient = malloc(sizeof(int));
        *pclient = client_fd;
        pthread_create(&tid, NULL, handle_client, pclient);
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}

// Client
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 7000
#define BUFFER_SIZE 1024

int main()
{
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Connection failed");
        exit(EXIT_FAILURE);
    }
    printf("Connected to server.\n");

    while (1)
    {
        printf("\nEnter password: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0';

        if (strcmp(buffer, "exit") == 0)
        {
            send(client_fd, buffer, strlen(buffer), 0);
            break;
        }

        send(client_fd, buffer, strlen(buffer), 0);

        memset(buffer, 0, BUFFER_SIZE);
        int bytes_received = recv(client_fd, buffer, BUFFER_SIZE, 0);
        if (bytes_received > 0)
        {
            printf("Details: %s\n", buffer);
        }
    }

    close(client_fd);
    return 0;
}




///// TCP Simple
// Server
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

// Client
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 9000
#define BUFFER_SIZE 1024

int main()
{
    char request[256];
    char buffer[256];

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in server_address;
    server_address.sin_addr.s_addr = INADDR_ANY;
    //server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);

    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        printf("Connection failed");
        exit(1);
    }
    printf("Connected to server.\n");

    while (1)
    {
        printf("\nEnter the word to be scanned: ");
        scanf("%s", request);

        if (strcmp(request, "quit") == 0)
            break;

        send(sock, request, sizeof(request), 0);
        printf("Message sent from client.\n");

        memset(buffer, 0, BUFFER_SIZE);
        recv(sock, &buffer, sizeof(buffer), 0);
        printf("Message from server: %s\n", buffer);
    }
    close(sock);
    return 0;
}



//// UDP Simple
// Server
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
    char message[900] = "Hi from UDP server!";
    int counter = 0;

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while (1)
    {
        // receive message from client
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0, (struct sockaddr *)&client_addr, &addr_size);
        buffer[n] = '\0';

        if (strcmp(buffer, "exit") == 0)
            break;

        printf("Recieved message: %s\n", buffer);
        printf("Total messages: %d\n", counter);

        // send reply
        sprintf(message, "Echo # %d: %s", counter++, buffer);
        sendto(sockfd, message, strlen(message) + 1, 0, (struct sockaddr *)&client_addr, addr_size);
    }

    close(sockfd);
    return 0;
}


// Client
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