#include <iostream>
#include <string>
#include <cstring>      // for memset, strlen
#include <cstdlib>      // for exit()
#include <unistd.h>     // for close()
#include <sys/types.h>  // for socket types
#include <sys/socket.h> // for socket functions
#include <netinet/in.h> // for sockaddr_in
#include <arpa/inet.h>  // for inet_pton
#include <sstream>
#include <iomanip> // for std::setprecision
#define PORT 9000
using namespace std;

int main()
{
    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    string request = "";
    int n, sent;

    int sockfd;
    struct sockaddr_in server_addr{};
    socklen_t addr_size = sizeof(server_addr);

    // Input variables
    string move;

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        cout << "Error: Socket creation failed!\n";
        return 1;
    }
    else
    {
        cout << "------ RPS Server Joined successfully ------\n\n";
    }

    // Server address setup
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        cout << "Connection to the server failed!\n";
        close(sockfd);
        return 1;
    }

    bool skip = false, starting = true;
    while (true && !skip)
    {
        skip = false;

        if (starting)
        {
            cout << "Joining server...\n";
            request = "Joining server...";
            starting = false;
        }
        else
        {
            // Take input
            cout << "\nSelect you move: \n"
                 << "Rock [r]\n"
                 << "Paper [p]\n"
                 << "Scissor [s]\n"
                 << "Exit [exit]\n"
                 << "Enter your choice: ";
            if (cin.peek() == '\n')
                cin.ignore();
            getline(cin, move);
            if (move == "exit")
                skip = true;
            else if (move != "r" && move != "p" && move != "s")
            {
                cout << "Invalid input! Please enter r, p, s or exit.\n";
                continue;
            }

            if (!skip)
            {
            }

            // Send message
            if (skip)
                request = "exit";
            else
            {
                request = move;
            }
        }
        sent = send(sockfd, request.c_str(), request.size() + 1, 0);
        if (sent < 0)
        {
            cout << "Error: send() failed\n";
            close(sockfd);
            return 1;
        }
        if (skip)
        {
            cout << "Exiting...\n";
            break;
        }

        // Receive reply
        n = recv(sockfd, buffer, BUFFER_SIZE, 0);
        if (n < 0)
        {
            cout << "Error: recv() failed\n";
            close(sockfd);
            return 1;
        }

        buffer[n] = '\0';
        cout << "Message from server: " << buffer << "\n\n-------------------------------------\n";

        if (strncmp(buffer, "Server full", strlen("Server full")) == 0)
            break;
    }

    close(sockfd);
    return 0;
}