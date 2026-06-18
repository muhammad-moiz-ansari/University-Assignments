#include <iostream>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n, a, b, i=0, j, k;
	float sum;
	for(n=1; n>=0; )
	{
	i=0;
	   sum=0;
	   cout<<"Enter a positive integer (or a negative number to exit): ";
	   cin>>n;
	   j=n;
	   
	   for(k=0; k<n; ++k)
	   {
	   
	   i+=1;
	   a=i;
	   
	   b=j;
	   j-=1;
	   cout<<a<<"/"<<b<<"+";
	   if(k==n-1)
	   cout<<"\b";
	   sum=sum+(float)a/b;
	   }
	   if(n>=0)
	   cout<<endl<<"Sum = "<<sum<<endl;
	}
	
	
	
	return 0;
}
