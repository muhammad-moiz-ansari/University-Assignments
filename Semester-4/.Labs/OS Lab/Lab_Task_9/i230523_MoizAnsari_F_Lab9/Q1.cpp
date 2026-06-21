#include <iostream>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
using namespace std;

void *pickup(void *arg)
{
    int c = *(int *)arg;

    cout << "Customer " << c << " picked up by taxi " << pthread_self() << "!\n";

    pthread_exit(NULL);
}

int main()
{
    int n;
    cout << "Enter the number of customers: ";
    cin >> n;

    int *customerID = new int[n];
    pthread_t *tid = new pthread_t[n];
    int j = 100;
    for (int i = 0; i < n; ++i)
    {
        customerID[i] = j++;

        pthread_create(&tid[i], NULL, pickup, &customerID[i]);
        pthread_join(tid[i], NULL);
    }

    cout << "All customers have been picked up!\n";

    return 0;
}