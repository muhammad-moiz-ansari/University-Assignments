#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void *func1(void *arg)
{
	cout << "\nEven Numbers: ";
	for (int i = 0; i < 10; i += 2)
	{
		cout << i << "  ";
	}

	pthread_exit(NULL);
}

void *func2(void *arg)
{
	int n = 0;
	for (int i = 0; i < 10; i += 1)
	{
		n += i;
	}
	cout << "\nSum: " << n << endl;

	pthread_exit(NULL);
}

void *func3(void *arg)
{
	int n = 1;
	for (int i = 1; i <= 5; i += 1)
	{
		n *= i;
	}
	cout << "Product: " << n << endl;

	pthread_exit(NULL);
}

int main()
{
	pthread_t thread1, thread2, thread3;

	pthread_create(&thread1, NULL, func1, NULL);
	sleep(1);

	pthread_create(&thread2, NULL, func2, NULL);
	sleep(1);

	pthread_create(&thread2, NULL, func3, NULL);
	sleep(1);

	return 0;
}
