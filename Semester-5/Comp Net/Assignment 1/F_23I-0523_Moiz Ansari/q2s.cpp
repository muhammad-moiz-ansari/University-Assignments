#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
using namespace std;

#define PORT 9000
#define BUFFER_SIZE 512
#define THREAD_POOL_SIZE 2
#define QUEUE_SIZE 10

// Structure representing a task (TCP message)
struct Task
{
    sockaddr_in clientAddr;
    int client_socket;
    Task(sockaddr_in addr, int sock)
    {
        clientAddr = addr;
        client_socket = sock;
    }
    Task() = default;
};

// Shared task queue
Task queue[QUEUE_SIZE];
int front = 0, rear = 0, count = 0;

// Synchronization variables
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t client_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t player_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t cout_mutex = PTHREAD_MUTEX_INITIALIZER;
int connected_clients = 0;
int last_id = 2;
char move1 = '\0', move2 = '\0';
string result1, result2, move1str, move2str, movestr;
int winner;
bool resultCalculated1 = false, resultCalculated2 = false;
pthread_cond_t move_cv = PTHREAD_COND_INITIALIZER;
bool computed = false;
int replies_sent = 0;

int server_socket;

// Worker thread function
void *worker_thread(void *arg)
{
    while (true)
    {
        Task current_task;
        int playerId;

        pthread_mutex_lock(&player_mutex);
        if (last_id == 2)
        {
            playerId = 1;
            last_id = 1;
        }
        else
        {
            playerId = 2;
            last_id = 2;
        }
        pthread_mutex_unlock(&player_mutex);

        pthread_mutex_lock(&mutex);
        while (count == 0)
            pthread_cond_wait(&cond, &mutex);
        current_task = queue[front];
        front = (front + 1) % QUEUE_SIZE;
        count--;
        pthread_mutex_unlock(&mutex);

        cout << "Player " << to_string(playerId) << " joined server: "
             << inet_ntoa(current_task.clientAddr.sin_addr)
             << ":" << ntohs(current_task.clientAddr.sin_port) << endl
             << endl;

        // Handle client persistently
        while (true)
        {
            char buffer[BUFFER_SIZE];
            string reply;
            int n = recv(current_task.client_socket, buffer, BUFFER_SIZE - 1, 0);
            if (n <= 0)
            {
                cerr << "Player " << to_string(playerId) << " disconnected: "
                     << inet_ntoa(current_task.clientAddr.sin_addr)
                     << ":" << ntohs(current_task.clientAddr.sin_port) << endl;
                close(current_task.client_socket);
                pthread_mutex_lock(&client_mutex);
                connected_clients--;
                pthread_mutex_unlock(&client_mutex);
                break;
            }
            buffer[n] = '\0';
            if (strncmp(buffer, "Joining server...", strlen("Joining server...")) == 0)
            {
                buffer[0] = '\0';
                reply = "Welcome Player " + to_string(playerId) + "! You are connected to the RPS server.";
                send(current_task.client_socket, reply.c_str(), reply.size() + 1, 0);
                continue;
            }

            // Check for exit command
            if (strcmp(buffer, "exit") == 0)
            {
                cout << "\nPlayer " << to_string(playerId) << " exited: "
                     << inet_ntoa(current_task.clientAddr.sin_addr)
                     << ":" << ntohs(current_task.clientAddr.sin_port) << "\n\n";
                close(current_task.client_socket);
                pthread_mutex_lock(&client_mutex);
                connected_clients--;
                if (playerId == 1)
                    last_id = 2;
                else
                    last_id = 1;
                pthread_mutex_unlock(&client_mutex);
                break;
            }

            // Making strings from moves
            if (buffer[0] == 'r')
                movestr = "rock";
            else if (buffer[0] == 'p')
                movestr = "paper";
            else if (buffer[0] == 's')
                movestr = "scissor";

            if (playerId == 1)
            {
                move1 = buffer[0];
                move1str = movestr;
            }
            else
            {
                move2 = buffer[0];
                move2str = movestr;
            }

            movestr[0] = toupper(movestr[0]);
            pthread_mutex_lock(&cout_mutex);
            cout << "Player " << to_string(playerId) << ": " << movestr << endl;
            pthread_mutex_unlock(&cout_mutex);

            // Checking moves
            // signal that this player has provided a move
            pthread_mutex_lock(&player_mutex);

            // notify other thread that a move arrived
            pthread_cond_signal(&move_cv);

            // wait until both moves are present or computation done
            while (!(move1 != '\0' && move2 != '\0' && computed))
            {
                // If both moves are present and nobody computed yet, compute now
                if (move1 != '\0' && move2 != '\0' && !computed)
                {
                    // compute winner and results (only one thread will do this)
                    if (move1 == move2)
                        winner = 0;
                    else if ((move1 == 'r' && move2 == 's') || (move1 == 's' && move2 == 'p') || (move1 == 'p' && move2 == 'r'))
                        winner = 1;
                    else
                        winner = 2;

                    if (winner == 0)
                    {
                        result1 = result2 = "It's a tie! Both chose " + move1str;
                        pthread_mutex_lock(&cout_mutex);
                        cout << result1 << endl
                             << endl;
                        pthread_mutex_unlock(&cout_mutex);
                    }
                    else if (winner == 1)
                    {
                        pthread_mutex_lock(&cout_mutex);
                        cout << "Player 1 wins! " << move1str << " beats " << move2str << endl
                             << endl;
                        pthread_mutex_unlock(&cout_mutex);
                        result1 = "You win! " + move1str + " beats " + move2str;
                        result2 = "You lose! " + move1str + " beats " + move2str;
                    }
                    else
                    {
                        pthread_mutex_lock(&cout_mutex);
                        cout << "Player 2 wins! " << move2str << " beats " << move1str << endl
                             << endl;
                        pthread_mutex_unlock(&cout_mutex);
                        result1 = "You lose! " + move2str + " beats " + move1str;
                        result2 = "You win! " + move2str + " beats " + move1str;
                    }

                    computed = true;
                    // wake up both threads to send results
                    pthread_cond_broadcast(&move_cv);
                    break;
                }
                // Wait for condition: someone computed results or other move arrived
                pthread_cond_wait(&move_cv, &player_mutex);
            }

            // Now results are ready, send to client
            replies_sent++;
            if (replies_sent == 2)
            {
                move1 = move2 = '\0';
                move1str.clear();
                move2str.clear();
                computed = false;
                replies_sent = 0;
                // optionally notify waiting threads (if any)
                pthread_cond_broadcast(&move_cv);
            }
            pthread_mutex_unlock(&player_mutex);

            if (playerId == 1)
                reply = result1;
            else
                reply = result2;

            send(current_task.client_socket, reply.c_str(), reply.size() + 1, 0);
        }
    }
    return nullptr;
}

int main()
{
    sockaddr_in serverAddr{}, clientAddr{};
    socklen_t addr_size = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];
    pthread_t pool[THREAD_POOL_SIZE];

    // 1. Create TCP socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0)
    {
        cerr << "Socket creation failed\n";
        close(server_socket);
        exit(1);
    }

    // 2. Configure server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // 3. Bind socket
    if (bind(server_socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cerr << "Bind failed\n";
        close(server_socket);
        exit(1);
    }

    // 3.5. Listen for incoming connections
    listen(server_socket, QUEUE_SIZE);

    cout << "TCP Server with Thread Pool running on port " << PORT << "..." << endl;

    // 4. Create worker threads
    for (int i = 0; i < THREAD_POOL_SIZE; i++)
        pthread_create(&pool[i], nullptr, worker_thread, nullptr);

    // 5. Main loop to receive and enqueue messages
    while (true)
    {
        int client_socket = accept(server_socket, (struct sockaddr *)&clientAddr, &addr_size);
        if (client_socket < 0)
        {
            cerr << "Accept failed!\n";
            continue;
        }

        pthread_mutex_lock(&client_mutex);
        if (connected_clients >= 2)
        {
            string msg = "Server full. Try again later.";
            send(client_socket, msg.c_str(), msg.size() + 1, 0);
            close(client_socket);
            cout << "Rejected connection from "
                 << inet_ntoa(clientAddr.sin_addr) << ":"
                 << ntohs(clientAddr.sin_port) << endl
                 << endl;
            pthread_mutex_unlock(&client_mutex);
            continue;
        }
        connected_clients++;
        pthread_mutex_unlock(&client_mutex);

        pthread_mutex_lock(&mutex);
        if (count < QUEUE_SIZE)
        {
            queue[rear].client_socket = client_socket;
            queue[rear].clientAddr = clientAddr;
            rear = (rear + 1) % QUEUE_SIZE;
            count++;
            pthread_cond_signal(&cond);
        }
        else
        {
            cout << "Queue full, rejecting client "
                 << inet_ntoa(clientAddr.sin_addr)
                 << ":" << ntohs(clientAddr.sin_port) << endl;
            close(client_socket);
        }
        pthread_mutex_unlock(&mutex);
    }

    for (int i = 0; i < THREAD_POOL_SIZE; i++)
        pthread_cancel(pool[i]);
    close(server_socket);
    return 0;
}
