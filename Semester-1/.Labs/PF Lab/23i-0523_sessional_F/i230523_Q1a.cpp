/*
Name : Moiz ansari
Roll no : 23i=0523
*/

#include <iostream>
#include <bitset>

using namespace std;

int main()
{
	int n, one=0, zero=0, m1=1;
	cout<<"Enter a number: ";
	cin>>n;
	
	for(int i=1; i<=n; ++i)
	{
		if(n & m1==1)
		  one+=1;
		else
			zero+=1;
		m1=m1<<1;
	}
	
	cout<<"Number of 1s= "<<one<<endl;
	cout<<"Number of 0s= "<<zero<<endl;
	
	
	return 0;
}
