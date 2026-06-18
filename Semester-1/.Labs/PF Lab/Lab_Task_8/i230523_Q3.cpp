#include <iostream>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	int N, n=1, a=0, b=-1, c=1;
	cout<<"Enter the number of elements: ";
	cin>>N;
	cout<<endl;
	
	while(n<=N)
	{
		 a=b+c;
		 b=c;
		 c=a;
		 
		 cout<<a<<" ";
		 n+=1;
	}
	cout<<endl;
	
	
	return 0;
}
