#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#define PORT 9000

float calculator(float a, float b, char op)
{
    if(b == 0 && op == '/')
    {
        printf("Error: Number can divide by zero!");
    }

    switch (op)
    {
        case '+':
            return a + b;
            break;
        case '-':
            return a - b;
            break;
        case '*':
            return a * b;
            break;
        case '/':
            return a / b;
            break;
        default:
            printf("Invalid operator!");
            return 0;
            break;
    }
}


int main()
{
    char message[256];
    char op;
    float a;
    float b;
    float result;
    char result1[] = "Palindrome";
    char result2[] = "Not palindrome";


    //create a socket
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);


    //setup socket address
    struct sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(PORT);
    server_address.sin_addr.s_addr = INADDR_ANY;        


    //bind the socket to our specified IP and port
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));


    //listen for connections
    listen(server_socket, 5);


    //accept a connection from a client
    int client_socket;
    client_socket = accept(server_socket, NULL, NULL);


    while(1)
    {
        recv(client_socket, &a, sizeof(a), 0);
        recv(client_socket, &b, sizeof(b), 0);
        recv(client_socket, &op, sizeof(op), 0);
        

        printf("\nInput from client: %f %c %f\n", a, op, b);

        
        result = calculator(a, b, op);
        

        send(client_socket, &result, sizeof(result), 0);
        printf("Message sent from server.\n");
    }
    close(client_socket);
    close(server_socket);
    return 0;
}