#include <iostream>
using namespace std;
int main()

{
 cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n[5], max, min;
	
	cout<<"Enter 5 integers, one at a time: "<<endl;
	for(int i=0; i<=4; ++i)
	{
		cout<<"Enter number "<<(i+1)<<": ";
		cin>>n[i];
	}
	
	for(int j=0; j<=4; ++j)
	{
	if(n[j]>n[1] && n[j]>n[2] && n[j]>n[3] && n[j]>n[4])
	  max=n[j];
	}
	
	for(int j=0; j<=4; ++j)
	{
	if(n[j]<n[1] && n[j]<n[2] && n[j]<n[3] && n[j]<n[4])
	  min=n[j];
	} 
	
	cout<<"\nThe largest number in the array is: "<<max<<endl;
	cout<<"The smallest number in the array is: "<<min<<endl;
	
	return 0;
}
