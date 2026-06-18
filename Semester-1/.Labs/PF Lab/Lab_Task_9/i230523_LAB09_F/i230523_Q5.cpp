#include <iostream>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int N, a, b, c, n, p, sum=0;
	cout<<"Enter a number: ";
	cin>>N;
	c=N;
	
	while(c!=0)
	{
		 a=c%10;
		 b=c/10;
		 n=1; p=1;
		 while(n<=a)
		 {
		 	  p*=a;
		 	  n+=1;
		 }
		 sum+=p;
		 c=b;
	}
	cout<<"Answer = "<<sum<<endl;
	
	
	return 0;
}
