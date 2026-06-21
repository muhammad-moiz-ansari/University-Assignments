#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 9000


int main()
{
    char request[256] = "Yo server, pineapple on pizza?";
    char buffer[256];


    //create a socket


    int sock = socket(AF_INET, SOCK_STREAM, 0);
    
    //setup socket address
    struct sockaddr_in server_address;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_family= AF_INET;
    server_address.sin_port = htons(PORT);


    //connect to the server
    if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("Connection failed");
        exit(1);
    }
    printf("Connected to server.\n");
    send(sock, request, sizeof(request), 0);
    printf("Message sent from client.\n");
    int valread = recv(sock, &buffer, sizeof(buffer), 0);
    printf("Message from server: %s\n", buffer);    
    close(sock);
    return 0;
}
