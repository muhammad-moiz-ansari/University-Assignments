#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080

struct Student
{
    char id[100], name[100], grade[100];
};

int main()
{
    char buffer[256];
    char message[900];

    struct Student students[5] = {
        {"2023-CS-001", "Dani Jani", "A+"},
        {"2023-CS-002", "Ali Sherian", "D"},
        {"2023-CS-003", "Shahmee Kabab", "A++"},
        {"2023-CS-004", "Abdullah Shadeeqi", "B"},
        {"2023-CS-005", "Ahmad Kamaria", "C"}};

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
        int n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                         (struct sockaddr *)&client_addr, &addr_size);
        buffer[n] = '\0'; // null-terminate

        if (buffer[0] == 'e', buffer[1] == 'x', buffer[2] == 'i', buffer[3] == 't')
            break;

        printf("Student ID query: %s\n", buffer);

        int ind = -1;
        for (int i = 0; i < 5; ++i)
        {
            if (strcmp(buffer, students[i].id) == 0)
                ind = i;
        }

        // send reply
        printf("Result: Name: %s, Grade: %s\n\n", students[ind].name, students[ind].grade);
        sprintf(message, "Name: %s, Grade: %s", students[ind].name, students[ind].grade);
        if (ind < 0)
            sprintf(message, "Result not found!");

        sendto(sockfd, message, strlen(message) + 1, 0, (struct sockaddr *)&client_addr, addr_size);
    }

    close(sockfd);
    return 0;
}
