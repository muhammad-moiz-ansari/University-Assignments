#include <iostream>
using namespace std;

int perfect(int);

int main()
{
 cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n=1, p;
	for(n; n<=1000; ++n)
	{
		p=perfect(n);
		if(n==1)
		  cout<<n<<" is a perfect number."<<endl;
		if(p!=0)
		  cout<<p<<" is a perfect number."<<endl;
	}
		
	return 0;
}
int perfect(int n)
{
	int sum=0, p=0;
	for(int i=1; i<n; ++i)
	{
		if(n%i==0)
		  sum+=i;	
	}
	if(sum==n)
	  p=n;
	return p;
}








