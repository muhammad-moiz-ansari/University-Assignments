#include <iostream>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <pthread.h>
using namespace std;

struct Calculator
{
    float a, b, r;
    char op;
    Calculator(float n1 = 0, float n2 = 0, char o = '+')
    {
        a = n1;
        b = n2;
        op = o;
    }
};

void *calculate(void *arg)
{
    Calculator *c = (Calculator *)arg;

    switch (c->op)
    {
    case '+':
        c->r = c->a + c->b;
        break;

    case '-':
        c->r = c->a - c->b;
        break;

    case '*':
        c->r = c->a * c->b;
        break;

    case '/':
        c->r = c->a / c->b;
        break;
    }
    cout << c->a << " " << c->op << " " << c->b << " = " << c->r << endl;
    pthread_exit(NULL);
}

int main()
{
    int n;
    cout << "Enter number of calculations: ";
    cin >> n;

    Calculator *c = new Calculator[n];
    pthread_t *tid = new pthread_t[n];
    for (int i = 0; i < n; ++i)
    {
        cout << "\nEnter two numbers: ";
        cin >> c[i].a >> c[i].b;
        cout << "Enter operator: ";
        cin >> c[i].op;

        pthread_create(&tid[i], NULL, calculate, &c[i]);
        pthread_join(tid[i], NULL);
    }
    cout << "\nAll calculations are completed!\n\n";

    return 0;
}