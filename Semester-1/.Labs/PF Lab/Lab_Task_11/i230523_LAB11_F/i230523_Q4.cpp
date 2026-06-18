#include <iostream>
using namespace std;
int main()

{
	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n[10], sum=0;
	float avg;
	
	cout<<"Enter 10 floating-point numbers, one at a time: "<<endl;
	for(int i=0; i<=9; ++i)
	{
		cout<<"Enter number "<<(i+1)<<": ";
		cin>>n[i];
		sum+=n[i];
	}
	avg=(double)sum/10;
	cout<<"The average of the entered numbers is: "<<avg<<endl;
	
	return 0;
}
