#include <iostream>
using namespace std;



int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int s;
	
	cout<<"Enter the size of integer array: ";
	cin>>s;
	
	int *arr = new int[s];
	
	cout<<"Enter the integer array:\n";
	for(int i=0; i<s; ++i)
		cin>>*(arr+i);
	
	int pos=0, neg=0, odd=0, even=0;
	for(int i=0; i<s; ++i)
	{
		if(*(arr+i)>0)
			++pos;
		if(*(arr+i)<0)
			++neg;
		if((*(arr+i))%2==0)
			++even;
		if((*(arr+i))%2!=0)
			++odd;
	}
	
	cout<<endl;
	cout<<"Number of positive integers= "<<pos<<endl
		<<"Number of negative integers= "<<neg<<endl
		<<"Number of odd integers= "<<odd<<endl
		<<"Number of even integers= "<<even<<endl;
		
	
	
	
	
	return 0;
}
