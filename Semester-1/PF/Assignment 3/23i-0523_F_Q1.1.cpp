/*    Problem 1.1

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 3

*/

#include <iostream>
using namespace std;

int   FindSum(int, int, int);
void  ShowSum(int);
float FindAvg(int, int, int);
void  ShowAvg(float);
int   FindMax(int, int, int);
void  ShowMax(int);
int   FindMin(int, int, int);
void  ShowMin(int);

int main()

{
	int x, y, z;
	cout<<"Enter 3 integer numbers: \n";
	cout<<"n1: ";
	cin>>x;
	cout<<"n2: ";
	cin>>y;
	cout<<"n3: ";
	cin>>z;
	cout<<endl;
	
	int Sum;
	float Average;
	Sum=FindSum(x, y, z);
	ShowSum(Sum);
	
	Average=FindAvg(x, y, z);
	ShowAvg(Average);
	
	cout<<endl;
	
	int Max, Min;
	Max=FindMax(x, y, z);
	ShowMax(Max);
	Min=FindMin(x, y, z);
	ShowMin(Min);
	
	return 0;
}

int FindSum(int x, int y, int z)
{
	return(x+y+z);
}
void ShowSum(int Sum)
{
	cout<<"Sum = "<<Sum<<endl;
}

float FindAvg(int x, int y, int z)
{
	return((float)FindSum(x, y, z)/3);
}
void ShowAvg(float Average)
{
	cout<<"Average = "<<Average<<endl;
}

int FindMax(int x, int y, int z)
{
	int max;
	if(x>y && x>z)
	  max=x;
	else if(y>x && y>z)
		   max=y;
	else
		max=z;
	return(max);
}
void ShowMax(int Max)
{
	cout<<"Maximum = "<<Max<<endl;
}

int FindMin(int x, int y, int z)
{
	int min;
	if(x<y && x<z)
	  min=x;
	else if(y<x && y<z)
		   min=y;
	else
		min=z;
	return(min);
}
void ShowMin(int Min)
{
	cout<<"Minimum = "<<Min<<endl;
}

