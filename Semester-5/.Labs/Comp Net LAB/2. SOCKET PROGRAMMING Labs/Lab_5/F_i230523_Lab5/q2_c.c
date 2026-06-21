#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>


#define PORT 9000


int main()
{
    char op;
    float a, b, result;
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

    while(1)
    {
        //take input
        printf("\nEnter two numbers: ");
        scanf("%f", &a);
        scanf("%f", &b);

        printf("Enter the operator (Enter '|' to exit): ");
        scanf(" %c", &op);
        
        if (op == '|')
            break;

        send(sock, &a, sizeof(a), 0);
        send(sock, &b, sizeof(b), 0);
        send(sock, &op, sizeof(op), 0);

        printf("Message sent from client.\n");
        int valread = recv(sock, &result, sizeof(result), 0);
        printf("Message from server: RESULT = %f\n", result);
    }  
    close(sock);
    return 0;
}
