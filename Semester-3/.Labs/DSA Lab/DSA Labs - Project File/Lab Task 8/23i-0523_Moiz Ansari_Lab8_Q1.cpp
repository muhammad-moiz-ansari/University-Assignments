#include <iostream>
using namespace std;

class Process
{
public:
	int process_id,
		priority;
	float burst_time;
	Process* next;

	Process(int id = 0, int pr = 0, float bt = 0, Process* n = NULL)
	{
		process_id = id;
		if (pr < 0 || pr>2)
			pr = 0;
		priority = pr;
		burst_time = bt;
		next = n;
	}

	~Process()
	{
		//delete next;
	}
};

class CustomQueue
{
public:
	Process* head, * tail;

	CustomQueue(Process* h = NULL, Process* t = NULL)
	{
		head = h;
		tail = t;
	}
	bool isEmpty()
	{
		if (!head && !tail)
			return true;
		else
			return false;
	}
	void enqueue(Process* process)
	{
		if (isEmpty())
		{
			head = new Process(process->process_id, process->priority, process->burst_time);
			tail = head;
			head->next = NULL;
		}
		else
		{
			Process* temp = head;
			head = new Process(process->process_id, process->priority, process->burst_time);
			head->next = temp;
		}
	}
	Process* dequeue()
	{
		if (isEmpty())
			return NULL;
		else if (head == tail)
		{
			Process* temp = tail;
			head = tail = NULL;
			return temp;
		}
		else
		{
			Process* rem = tail, * temp = head;
			while (temp->next->next)
				temp = temp->next;
			tail = temp;
			temp = NULL;
			return rem;
		}
	}

	~CustomQueue()
	{
		/*if (head || tail)
		{
			while (head || tail)
			{
				if (head == tail)
				{
					Process* temp = tail;
					head = tail = NULL;
					delete temp;
				}
				else
				{
					Process* rem = tail, * temp = head;
					while (temp->next->next)
						temp = temp->next;
					tail = temp;
					temp = NULL;
					delete rem;
				}
			}
		}*/
		//head = tail = NULL;
	}
};

class MultiLevelFeedbackQueueScheduler
{
public:
	CustomQueue List[3];

	MultiLevelFeedbackQueueScheduler()
	{
		CustomQueue Q1, Q2, Q3;

		List[0] = Q1;
		List[1] = Q2;
		List[2] = Q3;
	}

	void addProcess(Process* process)
	{
		if (process->priority == 0)
			List[0].enqueue(process);
		else if (process->priority == 1)
			List[1].enqueue(process);
		else if (process->priority == 2)
			List[2].enqueue(process);
	}

	void executeProcesses()
	{
		cout << "\nBurst times: \n";
		for (int i = 0; i < 3; ++i)
		{
			if (i == 0)
				cout << "High priority: ";
			else if(i==1)
				cout << "Medium priority: ";
			else
				cout << "Low priority: ";

			while (!(List[i].isEmpty()))
			{
				Process* temp = List[i].dequeue();
				if (temp)
				{
					cout << temp->burst_time << "  ";
					delete temp;
				}
			}
			cout << "\n";
		}
		cout << "\nAll processes executed!\n";
	}

	~MultiLevelFeedbackQueueScheduler()
	{
		//if (List)
		//	delete[] List;
	}
};

int main()
{
	int num = 0;
	cout << "How many process do you want to enter: ";
	cin >> num;

	MultiLevelFeedbackQueueScheduler scheduler;

	int process_id = 0, priority = 0;
	float btime = 0;
	for (int i = 0; i < num; ++i)
	{
		cout << "\nProcess " << i + 1 << ":\n";
		cout << "Enter Process ID: "
			<< i + 1 << endl;
		//cin >> process_id;
		process_id = i + 1;
		cout << "Enter Priority: ";
		cin >> priority;
		cout << "Enter Burst Time: ";
		cin >> btime;

		scheduler.addProcess(new Process(process_id, priority, btime));
	}

	scheduler.executeProcesses();


	return 0;
}