/*    Problem 5

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 3

*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;


//const int tn=99; const int tm=149;

int n, m, s;

void draw(int num[][99], int n, int m);
void play(int num[][99], int s, int &score, int &jump);
void showOutput(int , int);

int main()
{
	//Inputting n:
	cout<<"Enter value of n: ";
	cin>>n;
	while(!(n>1 && n<100))
	{
		cout<<"Out of range.\nEnter value of n in range of (1,100): ";
		cin>>n;
	}
	
	//Inputting m:
	cout<<"Enter value of m: ";
	cin>>m;
	while(!(m>1 && m<100))
	{
		cout<<"Out of range.\nEnter value of m in range of (1,150): ";
		cin>>m;
	}
	

	
	//Inputting s:
	cout<<"Enter value of s: ";
	cin>>s;
	while(!(s>0 && s<n))
	{
		cout<<"Out of range.\nEnter value of s in range of (0,"<<n<<"): ";
		cin>>s;
	}
	
	int num[n][99];	//Initailizing array
	
	draw(num, n, m);	//draw()
	
	int score=0, jump=0;
	play(num, s, score, jump);
	
	showOutput(score, jump);
	
	return 0;
}

void draw(int num[][99], int n, int m)
{
	srand(time(0));
	
	cout<<endl;
	for(int i=0; i<n; ++i)
	{
		cout<<"  ";
		for(int j=0; j<m; ++j)
		{
			num[i][j]=(rand()%m)+1;
			if(num[i][j]<10)
			  cout<<" 0"<<num[i][j];
			else
				cout<<" "<<num[i][j];
		}
		cout<<endl;
	}
}

void play(int num[][99], int s, int &score, int &jump)
{
	int q;
	q=num[s][0];
	
	
	do
	{
		int k=0;
		score+=num[k][q];
		if(num[k][q]==0)
		  score=0;
		++k;
		if(k==n)
		  k=0;
		++jump;
		
	}while(score<100);
	
	
}

void showOutput(int score, int jump)
{
	cout<<"\nNumber of jumps = "<<jump<<endl;
	cout<<"Final score = "<<score<<endl;
}



