#include <iostream>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int N=100, n=2, a, b;
	bool p=1;
	
	while(N<=999)
	{
		 a=N%10;
		 b=(N/100);
		 n=2;
		 
		 while(n<N)
		 {
			  if(N%n==0)
			  { p=0;
			    break;
			  }
			  
			  n+=1;
		 }
		 
		 if(p==1)
		   if(a==b)
		   	 cout<<N<<" ";
		 N+=1;
		 p=1;
	 }
	 
	 cout<<endl;
	 
	return 0;
}
