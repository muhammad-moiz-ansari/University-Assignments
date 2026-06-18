/*    Problem 1.2

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 3

*/

#include <iostream>
#include <ctime>
using namespace std;

int correct=0, wrong=0;

void Prints();
void DisplayMenu();
int  Select(int);
void PracticeAdd();
void PracticeSub();

int main()
{
	srand(time(0));
	
	DisplayMenu();
	
	char check='y';
	while(check == 'y' || check == 'Y')
	{
		int choice;
		choice=Select(choice);
		
		switch(choice)
		{
		case 1:
			PracticeAdd();
			break;
		case 2:
			PracticeSub();
			break;
		default:
			cout<<"Invalid choice.\n";
		}
		cout<<"Continue(y/n)? ";
		cin>>check;
	}
	cout<<"No. of Correct Answers = "<<correct<<endl;
	cout<<"No. of Wrong Answers = "<<wrong<<endl;
	
	
	return 0;
}

void Prints()
{
	for(int i=1; i<=10; ++i)
	   cout<<"-";
}

void DisplayMenu()
{
	Prints();
	cout<<"Practice Arithmetic";
	Prints();
	cout<<"\n1. Addition\n2. Subtraction\n\n";
}

int Select(int choice)
{
	cout<<"Enter your choice(1/2): ";
	cin>>choice;
	return choice;
}

void PracticeAdd()
{
	int a=(rand() % 100)-25,
		b=(rand() % 100)-25,
		c, n;
	if(a<0)
	  cout<<"("<<a<<")";
	else
		cout<<a;
	
	cout<<"+";
	
	if(b<0)
	  cout<<"("<<b<<")";
	else
		cout<<b;
	cout<<"=? ";
	
	cin>>n;
	if(n==(a+b))
	{
	  cout<<"CORRECT\n\n";
	  ++correct;
	}
	else
	{
		cout<<"WRONG\n\n";
		++wrong;
	}
}

void PracticeSub()
{
	int a=(rand() % 100)-25,
		b=(rand() % 100)-25,
		c, n;
	if(a<0)
	  cout<<"("<<a<<")";
	else
		cout<<a;
	
	cout<<"-";
	
	if(b<0)
	  cout<<"("<<b<<")";
	else
		cout<<b;
	cout<<"=? ";
	
	cin>>n;
	if(n==(a-b))
	{
	  cout<<"CORRECT\n";
	  ++correct;
	}
	else
	{
		cout<<"WRONG\n";
		++wrong;
	}
}

