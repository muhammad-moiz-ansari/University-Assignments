#include <iostream>
using namespace std;

class Process
{
public:
	int task_id;
	float cpu_time;
	Process* next;

	Process(int id = 0, float bt = 0, Process* n = NULL)
	{
		task_id = id;
		cpu_time = bt;
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
	float quantumtime = 30;

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
			head = new Process(process->task_id, process->cpu_time);
			tail = head;
			head->next = NULL;
		}
		else
		{
			Process* temp = head;
			head = new Process(process->task_id, process->cpu_time);
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
			tail->next = NULL;
			temp = NULL;
			return rem;
		}
	}

	void execute()
	{
		cout << "\nExecution: ";
		while (!isEmpty())
		{
			Process* temp = dequeue();
			if (temp)
			{
				if (temp->cpu_time - quantumtime <= 0)
				{
					cout << temp->cpu_time << "  ";
					delete temp;
				}
				else
				{
					cout << temp->cpu_time << "  ";
					temp->cpu_time = temp->cpu_time - quantumtime;
					enqueue(temp);
				}
			}
		}
	}
};


int main()
{
	int num = 0;
	cout << "How many process do you want to enter: ";
	cin >> num;

	CustomQueue list;
	cout << "\nQuantum Time: " << list.quantumtime << "\n";

	int task_id = 0;
	float cputime = 0;
	for (int i = 0; i < num; ++i)
	{
		cout << "\nProcess " << i + 1 << ":\n";
		cout << "Enter Task ID: "
			<< i + 1 << endl;
		task_id = i + 1;
		cout << "Enter CPU Time: ";
		cin >> cputime;

		list.enqueue(new Process(task_id, cputime));
	}

	list.execute();

	cout << endl;
	return 0;
}