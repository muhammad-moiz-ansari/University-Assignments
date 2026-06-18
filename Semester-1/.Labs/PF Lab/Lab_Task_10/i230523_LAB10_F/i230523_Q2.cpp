#include <iostream>
using namespace std;
int main()

{
 cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n;
	cout<<"Enter the size: ";
	cin>>n;
	
	int jl=n, jr=n;
	for(int i=1; i<=n; ++i)
	{
		for(int j=1;j<=(2*n)-1; ++j)
		{
			if(j==jl || j==jr)
			  cout<<"*";
			else
				cout<<" ";
		}
		jl-=1;
		jr+=1;
		cout<<endl;
	}
	
	jl=2; jr=(2*n)-2;
	for(int i=1; i<=n-1; ++i)
	{
		for(int j=1;j<=(2*n)-1; ++j)
		{
			if(j==jl || j==jr)
			  cout<<"*";
			else
				cout<<" ";
		}
		jl+=1;
		jr-=1;
		cout<<endl;
	}
	
	return 0;
}
