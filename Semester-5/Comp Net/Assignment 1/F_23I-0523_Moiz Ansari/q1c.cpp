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

bool checkTimeFormat(string t)
{
    bool b = false;
    if ((t[0] >= '0' && t[0] <= '2') && (t[1] >= '0' && t[1] <= '9') && t[2] == ':' && (t[3] >= '0' && t[3] <= '5') && (t[4] >= '0' && t[4] <= '9'))
        b = true;
    if (t[0] == '2' && (t[1] < '0' || t[1] > '3'))
        b = false;
    if (t.length() != 5)
        b = false;
    return b;
}

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
    string name, atime, loc, service;
    float temp;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        cout << "Error: Socket creation failed!\n";
        return 1;
    }

    // Server address setup
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bool skip = false;
    while (true && !skip)
    {
        skip = false;
        // Take input
        cout << "\nEnter name (Write 'exit' to quit): ";
        if (cin.peek() == '\n')
            cin.ignore(); // To ignore any leftover newline character in the input buffer
        getline(cin, name);
        if (name == "exit")
            skip = true;
        if (!skip)
        {
            cout << "Enter arrival time (HH:MM): ";
            do
            {
                cin >> atime;
            } while (!checkTimeFormat(atime) && cout << "Invalid time format! Please enter in HH:MM format: ");
            cout << "Enter location: ";
            if (cin.peek() == '\n')
                cin.ignore();
            getline(cin, loc);
            cout << "Enter temperature (in Celsius): ";
            cin >> temp;
            cout << "Enter service required: ";
            if (cin.peek() == '\n')
                cin.ignore();
            getline(cin, service);
        }

        // Send message
        if (skip)
            request = "exit";
        else
        {
            stringstream ss;
            ss << fixed << setprecision(1) << temp;
            string tempStr = ss.str();
            request = name + ";" + atime + ";" + loc + ";" + tempStr + ";" + service;
        }
        sent = sendto(sockfd, request.c_str(), request.size() + 1, 0, (struct sockaddr *)&server_addr, addr_size);
        if (sent < 0)
        {
            cout << "Error: sendto() failed\n";
            close(sockfd);
            return 1;
        }
        if (skip)
        {
            cout << "Exiting...\n";
            break;
        }

        // Receive reply
        n = recvfrom(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, &addr_size);
        if (n < 0)
        {
            cout << "Error: recvfrom() failed\n";
            close(sockfd);
            return 1;
        }

        buffer[n] = '\0';
        cout << "Message from server: " << buffer << "\n\n-------------------------------------\n";
    }

    close(sockfd);
    return 0;
}