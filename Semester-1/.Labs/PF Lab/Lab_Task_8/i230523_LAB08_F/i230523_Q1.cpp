#include <iostream>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	int N, n=1, p=1;
	cout<<"Enter a positive integer: ";
	cin>>N;
	cout<<endl;
	
	if(N<0)
	  cout<<"Invalid Output (Enter a positive integer)"<<endl;
	
	else
	{
	while(n<=N)
	{
		 p = p * n;
		 n+=1;
	}
	
	cout<<"Factorial of "<<N<<" = "<<p<<endl;
	}
	
	return 0;
}
