#include <iostream>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
using namespace std;

struct Order
{
    int id1, id2;
    string name1, name2;

    Order(int i1 = 0, int i2 = 0, string n1 = "", string n2 = "")
    {
        id1 = i1;
        id2 = i2;
        name1 = n1;
        name2 = n2;
    }
};

void *takeorder(void *arg)
{
    Order *o = (Order *)arg;

    cout << "Orders " << o->id1 << " & " << o->id2 << " delivered successfully!\n";
    pthread_exit(NULL);
}

int main()
{
    int n;
    cout << "Enter the number of orders: ";
    cin >> n;

    Order *orders = new Order[n / 2];
    pthread_t *tid = new pthread_t[n / 2];
    string name = "abc";
    for (int i = 0, j = 100; i < n / 2; ++i)
    {
        orders[i].id1 = j++;
        orders[i].id2 = j++;
        orders[i].name1 = name;
        name[2] = name[2] + 1;
        orders[i].name2 = name;

        pthread_create(&tid[i], NULL, takeorder, &orders[i]);
        pthread_join(tid[i], NULL);
    }
    cout << "All deliveries are completed!\n\n";

    return 0;
}