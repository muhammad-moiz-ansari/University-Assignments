#include <iostream>
using namespace std;

int computeMax(int num1, int num2, int num3);

int main()
{
 cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int num1, num2, num3;
	cout<<"Enter the value of num 1: ";
	cin>>num1;
	cout<<"Enter the value of num 2: ";
	cin>>num2;
	cout<<"Enter the value of num 3: ";
	cin>>num3;
	
	cout<<"The maximum number is: "<<computeMax(num1, num2, num3)<<endl;
	
	return 0;
}

int computeMax(int num1, int num2, int num3)
{
	int max;
	if(num1>num2 && num1>num3)
	  max=num1;
	if(num2>num1 && num2>num3)
	  max=num2;
	if(num3>num1 && num3>num2)
	  max=num3;
	return max;
}




