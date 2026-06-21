#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <set>
#include <sstream>
#include <fstream>
#define PORT 9000
#define MAX_CLIENTS 5

using namespace std;

int main()
{
    string filename = "attendance_log.txt";

    const int BUFFER_SIZE = 256;
    char buffer[BUFFER_SIZE];
    string message = "";
    int n, sent;

    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_size = sizeof(client_addr);

    set<string> connectedClients;
    string clientKey;

    // Client variables
    string name, atime, loc, temp, service;

    // Creating socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        cout << "Error: Socket creation failed!\n";
        return 1;
    }

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Binding socket
    if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
    {
        cout << "Error: Binding failed!\n";
        close(sockfd);
        return 1;
    }

    cout << "UDP server is running on port " << PORT << "...\n\n";

    // Continuous loop
    while (true)
    {
        // Receive message
        n = recvfrom(sockfd, buffer, sizeof(buffer) - 1, 0,
                     (struct sockaddr *)&client_addr, &addr_size);

        if (n < 0)
        {
            cout << "recvfrom() failed!\n";
            continue;
        }
        buffer[n] = '\0';

        clientKey = string(inet_ntoa(client_addr.sin_addr)) + ":" + to_string(ntohs(client_addr.sin_port));

        if (connectedClients.find(clientKey) == connectedClients.end()) // If client is not found
        {
            if (connectedClients.size() >= MAX_CLIENTS)
            {
                message = "Server Full! Plz try again later.";
                sendto(sockfd, message.c_str(), message.size() + 1, 0,
                       (struct sockaddr *)&client_addr, addr_size);
                cout << "Client [" << clientKey << "] rejected!\n";
                continue;
            }
            else
            {
                connectedClients.insert(clientKey);
                cout << "New client(" << connectedClients.size() << ") added --> " << clientKey << endl << endl;
            }
        }

        if (strcmp(buffer, "exit") == 0)
        {
            connectedClients.erase(clientKey);
            cout << "Client disconnected: " << clientKey << endl << endl;
            message = "Thanks for contacting us. Goodbye!";
            sendto(sockfd, message.c_str(), message.size() + 1, 0,
                   (struct sockaddr *)&client_addr, addr_size);
            continue;
        }

        //cout << "Message from client: " << buffer << endl;

        // Extract Information
        string data(buffer);
        stringstream ss(data);
        getline(ss, name, ';');
        getline(ss, atime, ';');
        getline(ss, loc, ';');
        getline(ss, temp, ';');
        getline(ss, service, ';');

        // Log file entry
        ofstream logfile(filename, ios::app);
        if (!logfile)
        {
            cout << "Error opening log file!\n";
            //continue;
        }
        logfile << "Name: " << name
                << "\nArrival Time: " << atime
                << "\nLocation: " << loc 
                << "\nTemperature: " << temp
                << "C\nService Required: " << service << "\n\n--------------------------------------\n\n";
        logfile.close();

        // Send reply
        message = "details noted: " + service + ", temp " + temp + "C from " + name + " on " + loc;

        sent = sendto(sockfd, message.c_str(), message.size() + 1, 0,
                      (struct sockaddr *)&client_addr, addr_size);
        if (sent < 0)
            cout << "sendto() failed!\n";
        else
            cout << "Reply sent to client: " << message << "\n\n";
    }

    close(sockfd);
    return 0;
}