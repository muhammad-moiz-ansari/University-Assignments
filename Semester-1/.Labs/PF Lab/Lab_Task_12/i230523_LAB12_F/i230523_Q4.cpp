#include <iostream>
using namespace std;


int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	const int r=3;
	const int c=4;
	int arr[r][c];
	int search, s=0, yes;
	bool b=0;
	
	cout<<"Enter the matrix elements: \n";
	
	for(int i=0; i<r; ++i)
	{
		for(int j=0; j<c; ++j)
		{
			cin>>arr[i][j];
			cout<<arr[i][j]<<"\t";
			++s;
		}
		cout<<endl;
	}
	
	cout<<"Enter the value to search for: ";
	cin>>search;
	
	int I;
	int J;
	
		for(int i=0; i<r; ++i)
		{
			for(int j=0; j<c; ++j)
			{
				if(search==arr[i][j])
				{
					yes=arr[i][j];
					I=i;
					J=j;
					b=1;
					break;
				}
			}
			if(search==arr[I][J])
			{
				break;
			}
		}
	
	if(b)
	  cout<<"The value "<<search<<" is found at position ("<<I<<", "<<J<<").\n";
	else
		cout<<"Not found.\n";
		
	return 0;
}
