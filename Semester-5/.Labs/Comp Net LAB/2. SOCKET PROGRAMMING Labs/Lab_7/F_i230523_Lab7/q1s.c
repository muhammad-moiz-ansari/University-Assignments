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

// Password strength function
int passwordStrength(char *pass, bool *length, bool *upper, bool *lower, bool *digit, bool *special)
{
    int strength = 0;
    if (strlen(pass) >= 8)
        *length = true;

    for (int i = 0; i < strlen(pass); ++i)
    {
        if (pass[i] >= 'a' && pass[i] <= 'z')
            *lower = true;
        if (pass[i] >= 'A' && pass[i] <= 'Z')
            *upper = true;
        if (pass[i] >= '0' && pass[i] <= '9')
            *digit = true;
        if (pass[i] == '!' || pass[i] == '@' || pass[i] == '#' || pass[i] == '$' || pass[i] == '%' || pass[i] == '^' || pass[i] == '&' || pass[i] == '*' || pass[i] == '(' || pass[i] == ')')
            *special = true;
    }

    if (*length)
        ++strength;
    if (*lower)
        ++strength;
    if (*upper)
        ++strength;
    if (*digit)
        ++strength;
    if (*special)
        ++strength;

    return strength;
}

// Thread function to handle each client
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

        printf("Client %d: Checking password...(Wait 5 sec)\n", client_fd);
        sleep(5);

        bool length = false, upper = false, lower = false, digit = false, special = false;
        int strength = passwordStrength(buffer, &length, &upper, &lower, &digit, &special);

        //✅❌
        sprintf(buffer, "Length(%d) Uppercase(%d) Lowercase(%d) Digit(%d) Special(%d)", length, upper, lower, digit, special);

        if (strength <= 2)
            strcpy(strengthstr, "Weak password...PATHETIC!!");
        else if (strength == 3)
            strcpy(strengthstr, "Medium password...LEARN SOMETHING FROM OTHERS!!");
        else
            strcpy(strengthstr, "Strong password...OK (-_-)");

        printf("Cleint %d: Result sent - %s  (%d/5)\n\n", client_fd, strengthstr, strength);
        //printf("Strength: %d\n\n", strength);

        send(client_fd, buffer, strlen(buffer), 0); // Echo back
    }

    return NULL;
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size;
    pthread_t tid;

    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }
    printf("Server socket created.\n");

    // Configure server address
    server_addr.sin_family = AF_INET;

    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    memset(server_addr.sin_zero, '\0', sizeof(server_addr.sin_zero));

    // Bind
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Bind to port %d successful.\n", PORT);

    // Listen
    if (listen(server_fd, 10) == 0)
    {
        printf("Listening...\n");
    }
    else
    {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    // Accept connections in a loop
    while (1)
    {
        addr_size = sizeof(client_addr);
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_size);
        if (client_fd < 0)
        {
            perror("Accept failed");
            continue;
        }

        printf("Connection accepted from %s:%d\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

        // Create a thread for each client
        int *pclient = malloc(sizeof(int));
        *pclient = client_fd;
        pthread_create(&tid, NULL, handle_client, pclient);

        // Detach thread so its resources are freed automatically
        pthread_detach(tid);
    }

    close(server_fd);
    return 0;
}