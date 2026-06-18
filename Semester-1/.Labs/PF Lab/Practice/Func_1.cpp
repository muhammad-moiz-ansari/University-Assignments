#include <iostream>
using namespace std;

int power(int, int);

int main()
{
	int x, n;
	cout<<"x: ";
	cin>>x;
	cout<<"n: ";
	cin>>n;
	int p=power(x,n);
	
	cout<<p;
	cout<<endl;
	
	return 0;
}

int power(int x, int n)
{
	int p=1;
	for(int i=1; i<=n; ++i)
	{
	   p=p*x;
	}
	return p;
}
