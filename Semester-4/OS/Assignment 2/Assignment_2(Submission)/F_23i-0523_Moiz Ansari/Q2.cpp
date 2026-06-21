#include <iostream>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>
#include <cstring>
#include <pthread.h>
#include <vector>
using namespace std;

class Student
{
public:
	int id, arrtime, duration, t;
	bool done;

	Student(int ID = 0, int at = 0, int dur = 0, int time = 0)
	{
		id = ID;
		arrtime = at;
		duration = dur;
		t = time;
		done = 0;
	}

	Student(const Student &st)
	{
		id = st.id;
		arrtime = st.arrtime;
		duration = st.duration;
		t = st.t;
		done = st.done;
	}
};

void *QuestionStart(void *arg)
{
	Student *s = (Student *)arg;

	cout << "\nStudent " << s->id << " starts asking question at time " << s->t << endl;
	s->t += s->duration;

	return NULL;
}

void QuestionDone(void *arg, pthread_t &tid)
{
	Student *s = (Student *)arg;

	cout << "Student " << s->id << " finishes question at time " << s->t << endl;

	pthread_cancel(tid);
}

void *AnswerStart(void *arg)
{
	Student *s = (Student *)arg;

	cout << "\nProfessor starts responding to the student " << s->id << " at time " << s->t << endl;
	s->t += (s->duration * 2);

	return NULL;
}

void AnswerDone(void *arg, pthread_t &tid)
{
	Student *s = (Student *)arg;

	cout << "Professor finishes responding to the student " << s->id << " at time " << s->t << endl;

	pthread_cancel(tid);
}

void sort(vector<Student> &vec, vector<pthread_t> &vect)
{
	bool swap;
	int n = vec.size();
	for (int i = 0; i < n; ++i)
	{
		swap = 0;
		for (int j = 0; j < n - i - 1; ++j)
		{
			if (vec[j].arrtime > vec[j + 1].arrtime)
			{
				Student temp = vec[j];
				pthread_t tempt = vect[j];
				vec[j] = vec[j + 1];
				vect[j] = vect[j + 1];
				vec[j + 1] = temp;
				vect[j + 1] = tempt;
				swap = 1;
			}
		}
		if (!swap)
			break;
	}
}

int main()
{
	int n;
	cout << "Enter the number of students: ";
	cin >> n;

	vector<Student> student_info;
	vector<int> id(n), arrtime(n), duration(n);
	vector<pthread_t> students(n);
	pthread_t prof;

	// Taking Inputs:
	cout << "\nEnter Student IDs:\n";
	for (int i = 0; i < n; ++i)
	{
		cout << "Student " << i + 1 << ": ";
		cin >> id[i];
	}

	cout << "\nEnter Arrival Times:\n";
	for (int i = 0; i < n; ++i)
	{
		cout << "Student " << i + 1 << ": ";
		cin >> arrtime[i];
	}

	cout << "\nEnter Time Duration:\n";
	for (int i = 0; i < n; ++i)
	{
		cout << "Student " << i + 1 << ": ";
		cin >> duration[i];
		student_info.emplace_back(id[i], arrtime[i], duration[i]);
	}

	sort(student_info, students);

	cout << "\n----- University Starts -----\n";
	int t = 0;
	for (int i = 0; i < n; ++i)
	{
		if (student_info[i].arrtime > t)
		{
			cout << "\nProfessor sleeps for " << student_info[i].arrtime - t << " minutes!\n";
			t = student_info[i].arrtime;
		}

		student_info[i].t = t;
		pthread_create(&students[i], NULL, QuestionStart, &student_info[i]);
		t = student_info[i].t;

		pthread_join(students[i], NULL);
		QuestionDone(&student_info[i], students[i]);

		pthread_create(&prof, NULL, AnswerStart, &student_info[i]);
		t = student_info[i].t;

		pthread_join(prof, NULL);
		AnswerDone(&student_info[i], prof);
	}
	cout<<"\n\n----- Students Finished -----\n";

	return 0;
}
