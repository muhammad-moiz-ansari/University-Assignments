#include <iostream>
#include <pthread.h>
#include <unistd.h>
using namespace std;

void *func1(void *arg)
{
	int *m = (int *)arg;
	char *grades = new char[3];

	cout << "Enter Marks:\n";
	for (int i = 0; i < 3; ++i)
	{
		cout << "Student " << i + 1 << ": ";
		cin >> m[i];
		if (m[i] < 0 || m[i] > 100)
		{
			cout << "Invalid marks!\n";
			--i;
		}
	}

	cout << "\nGrades Assigned:\n";
	for (int i = 0; i < 3; ++i)
	{
		if (m[i] >= 90)
			grades[i] = 'A';
		else if (m[i] >= 80)
			grades[i] = 'B';
		else if (m[i] >= 70)
			grades[i] = 'C';
		else if (m[i] >= 60)
			grades[i] = 'D';
		else if (m[i] >= 50)
			grades[i] = 'E';
		else
			grades[i] = 'F';
		cout << "Student " << i + 1 << ": " << grades[i] << endl;
	}

	delete[] grades;
	pthread_exit(NULL);
}

void *func2(void *arg)
{
	int *m = (int *)arg;

	int highind = 0, lowind = 0;
	for (int i = 0; i < 3; ++i)
	{
		if (m[i] > m[highind])
			highind = i;
		if (m[i] < m[lowind])
			lowind = i;
	}

	cout << "\nHighest Marks = " << m[highind] << "\nLowest Marks = " << m[lowind] << endl;

	pthread_exit(NULL);
}

void *func3(void *arg)
{
	int *m = (int *)arg;
	int per = 0;
	for (int i = 0; i < 3; ++i)
		per += m[i];

	per = (per / 3);
	cout << "\nClass Percentage: " << per <<"%"<< endl;

	pthread_exit(NULL);
}

int main()
{
	pthread_t thread1, thread2, thread3;

	int marks[3];

	pthread_create(&thread1, NULL, func1, marks);

	sleep(10);

	pthread_create(&thread2, NULL, func2, marks);

	sleep(2);

	pthread_create(&thread3, NULL, func3, marks);

	sleep(2);

	return 0;
}
