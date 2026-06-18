#include <iostream>
using namespace std;
int main()

{
 cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n, a=0, b=-1, c=1, k=1;
	cout<<"Enter the limit: ";
	cin>>n;
	
	for(int i=1; i<=n; ++i)
	{
		a=1, b=0, c=1;
		for(int j=1; j<=n; ++j)
		{
			a=b+c;
			b=c;
			c=a;
			
			if(j==1)
			  a=1, b=0, c=1;
			
			cout<<a<<"  ";
			
			if(j==k)
			{
			  break;
			}
		}
		++k;
		cout<<endl;
	}
	
	return 0;
}
