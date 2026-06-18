#include <iostream>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	{
	int n, a=0;
	cout<<"Enter the rows of the upside-down triangle: ";
	cin>>n;
	
	int b=n+n-1;
	for(int i=0; i<n; ++i)
	{
	   for(int j=0; j<a; ++j)
	   {
	   	  cout<<" ";
	   }
	   for(int k=0; k<b; ++k)
	   {
	   	  cout<<"*";
	   }
	   cout<<endl;
	   a+=1;
	   b-=2;
	}
	cout<<endl;
	}
	
	int N;
	cout<<"Enter the number of rows (odd number): ";
	cin>>N;
	int n=(N-1)/2;
	
	{
	int a, b=1;
	
	a=n;
	for(int i=0; i<n; ++i)
	{
	   
	   for(int j=0; j<a; ++j)
	   {
	   	  cout<<" ";
	   }
	   for(int k=0; k<b; ++k)
	   {
	   	  cout<<"*";
	   }
	   cout<<endl;
	   b+=2;
	   a-=1;
	}
	}
	int mid=n+n+1;
	for(int o=0; o<mid; ++o)
	   cout<<"*";
	cout<<endl;
	
	{int b=n+n-1, a=1;
	for(int i=0; i<n; ++i)
	{
	   for(int j=0; j<a; ++j)
	   {
	   	  cout<<" ";
	   	  
	   }
	   for(int k=0; k<b; ++k)
	   {
	   	  cout<<"*";
	   }
	   cout<<endl;
	   a+=1;
	   b-=2;
	}
	cout<<endl;
	}
	
	return 0;
}
