#include <iostream>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n;
	cout<<"Enter the number of rows: ";
	cin>>n;
	cout<<"Butterfly pattern of "<<n<<" rows."<<endl;
	
	{int a=1, b=n*2;
	for(int i=0; i<n; ++i)
	{
	   for(int j=0; j<a; ++j)
	   {
	   	  cout<<"*";
	   }
	   for(int k=0; k<b; ++k)
	   {
	   	  cout<<" ";
	   }
	   for(int j=0; j<a; ++j)
	   {
	   	  cout<<"*";
	   }
	   cout<<endl;
	   b-=2;
	   a+=1;
	}}
	
	int o;
	for(o=0; o<(n*2+2); ++o)
	   cout<<"*";
	cout<<endl;
	
	{int a=n, b=2;
	for(int i=0; i<n; ++i)
	{
	   for(int j=0; j<a; ++j)
	   {
	   	  cout<<"*";
	   }
	   for(int k=0; k<b; ++k)
	   {
	   	  cout<<" ";
	   }
	   for(int j=0; j<a; ++j)
	   {
	   	  cout<<"*";
	   }
	   cout<<endl;
	   b+=2;
	   a-=1;
	}}
	
	
	
	return 0;
}
