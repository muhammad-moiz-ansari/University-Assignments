#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void *func1(void *arg)
{
	cout << "Thread 1: Booking ticket for Customer 1, Thread ID: " << pthread_self() << endl;

	pthread_exit(NULL);
}

void *func2(void *arg)
{
	cout << "Thread 2: Booking ticket for Customer 2, exiting...\n";

	pthread_exit(NULL);
}

void *func3(void *arg)
{
	cout << "Thread 3: Booking ticket for Customer 3, Seat Confirmed!\n";

	pthread_exit(NULL);
}

int main()
{
	pthread_t thread1, thread2, thread3;

	pthread_create(&thread1, NULL, func1, NULL);
	sleep(1);

	pthread_create(&thread2, NULL, func2, NULL);
	sleep(1);

	pthread_create(&thread3, NULL, func3, NULL);
	sleep(1);

	cout << "All ticket booked!\n";

	return 0;
}
