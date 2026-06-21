#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

class Process
{
public:
	int pid;
	float arrtime,
		btime,
		completiont,
		tat,
		waitingt,
		pendingt,
		qtime;

	Process(int p = 0, float at = 0, float bt = 5)
	{
		pid = p;
		arrtime = at;
		btime = bt;
		pendingt = btime;
		qtime = 0;
		completiont = 0;
		tat = 0,
		waitingt = 0;
	}
};

int main()
{
	int n;

	// Taking input:
	cout << "Enter n: ";
	// cin >> n;
	n = 3;

	float* at = new float[n];
	float* bt = new float[n];

	// Inputing Arrival Times:
	at[0] = 0;
	at[1] = 16;
	at[2] = 20;
	cout << "Enter Arrival Times:\n";
	for (int i = 0; i < n; ++i)
	{
		cout << "Process " << i + 1 << ": ";
		cin >> at[i];
	}

	// Inputing Burst Times:
	bt[0] = 36;
	bt[1] = 20;
	bt[2] = 12;
	cout << "\nEnter Burst Times:\n";
	for (int i = 0; i < n; ++i)
	{
		cout << "Process " << i + 1 << ": ";
		cin >> bt[i];
	}

	// Setting up the Process values
	Process* processes = new Process[n];
	for (int i = 0; i < n; ++i)
	{
		processes[i].pid = i + 1;
		processes[i].arrtime = at[i];
		processes[i].btime = bt[i];
		processes[i].pendingt = bt[i];
	}

	cout << "\n\nPID\tArr Time\tB Time\n";
	for (int i = 0; i < n; ++i)
	{
		cout << processes[i].pid << "\t" << processes[i].arrtime << "\t\t" << processes[i].btime << endl;
	}

	// Queues:
	queue<Process*> q1, q2, q3;
	int t1 = 4, t2 = 8, // Quantum times
		t = 0;

	cout << "\n\n---------- Starting Execution ----------\n\n";
	bool start = 1;

	// Main Loop
	while (!(q1.empty() && q2.empty() && q3.empty()) || start)
	{
		start = 0;

		// Arrival of New Processes
		for (int i = 0; i < n; ++i)
		{
			if (processes[i].arrtime >= t && processes[i].arrtime == t)
			{
				q1.push(&processes[i]);
				processes[i].qtime = t1;
				cout << "Process-" << i + 1 << " arrived at " << t << endl;
			}
		}

		++t;
		if (!q1.empty()) // Queue 1
		{
			q1.front()->qtime--;
			q1.front()->pendingt--;
			cout << "t " << t << ": " << "P" << q1.front()->pid << " (" << q1.front()->qtime << ")   Q1" << endl;

			if (q1.front()->pendingt <= 0)
			{
				q1.front()->completiont = t;
				cout << "Process-" << q1.front()->pid << " completed at " << t << endl;
				q1.pop();
			}
			else if (q1.front()->qtime <= 0)
			{
				q1.front()->qtime = t2;
				q2.push(q1.front());
				q1.pop();
			}
		}
		else if (!q2.empty()) // Queue2
		{
			if (!q2.empty())
			{
				q2.front()->qtime--;
				q2.front()->pendingt--;
				cout << "t " << t << ": " << "P" << q2.front()->pid << " (" << q2.front()->qtime << ")   Q2" << endl;

				if (q2.front()->pendingt <= 0)
				{
					q2.front()->completiont = t;
					cout << "Process-" << q2.front()->pid << " completed at " << t << endl;
					q2.pop();
				}
				else if (q2.front()->qtime <= 0)
				{
					q2.front()->qtime = t2;
					q3.push(q2.front());
					q2.pop();
				}
			}
		}
		else // Queue 3
		{
			if (!q3.empty())
			{
				q3.front()->qtime--;
				q3.front()->pendingt--;
				cout << "t " << t << ": " << "P" << q3.front()->pid << " (" << q3.front()->qtime << ")   Q3" << endl;

				if (q3.front()->pendingt <= 0)
				{
					q3.front()->completiont = t;
					cout << "Process-" << q3.front()->pid << " completed at " << t << endl;
					q3.pop();
				}
			}
		}
	}

	cout << "\n\nAll Processes Executed!\n\n";

	cout << "Statistics:\n";
	for (int i = 0; i < n; ++i)
	{
		processes[i].tat = processes[i].completiont - processes[i].arrtime;
		processes[i].waitingt = processes[i].tat - processes[i].btime;

		cout << "Process " << processes[i].pid << " -> Turnaround Time: " << processes[i].tat << ", Waiting Time: " << processes[i].waitingt << endl;
	}

	return 0;
}
