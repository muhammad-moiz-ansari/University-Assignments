/*    Problem 3

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 1

*/

#include <iostream>
#include <cmath>
using namespace std;
int main()
{
	int const c=30; int b, p, years, months, days;
	float N, i_rate, i, y, M, m1;

	cout<<"Input Monthly Payment(Should be less then Loan Amount):";
	cin>>p;
	cout<<"Input Balance(Loan Amount):";
	cin>>b;
	cout<<"Input Yearly Interest Rate:";
	cin>>i_rate;

	i=i_rate/365;

	N=(-1/(float)c)*(log(1+((float)b/p)*(1-pow((1+i),c))))/log(1+i);  //Formula
	
	years=N;	//Seperating years
	
	y=N-years;
	M=y*12;		//Seperating months
	
	months=M;
	m1=M-months;
	days=m1*31;	//Seperating days
	
	cout<<endl<<"How long will it take to pay off a credit loan:"<<years<<" years, "<<months<<" months, "<<days<<"days"<<endl;
	
	return 0;
}

