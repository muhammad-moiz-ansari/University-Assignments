#include <iostream>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	int N, n=2, p;
	
	cout<<"Enter the number: ";
	cin>>N;
		 
	while(N>=0)
	{
		 n=2;
		 
		 while(n<N)
		 {
			  if(N%n==0)
			  { p=0;
			    break;
			  }
			  else
			      p=1;
			      
			  n+=1;
		 }
		 if(N==2)
		   p=1;
		 if(N==0)
		   p=1;
		   
		 if(N>=0)
		 {
		 if(p==1)
		   cout<<"The entered number is prime."<<endl;
		 else if(p==0)
		 	 cout<<"The entered number is not prime."<<endl;
		 }
		 cout<<"Enter the number: ";
		 cin>>N;
	}
	
	
	
	
	return 0;
}
