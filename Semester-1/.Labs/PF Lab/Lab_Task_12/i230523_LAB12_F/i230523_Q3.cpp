#include <iostream>
using namespace std;


int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	const int n=5;
	int arr[n];
	int max, max2;
	
	cout<<"Enter array: \n";
	cin>>arr;
	
	for(int i=0; i<n; ++i)
	{
		for(int j=0; j<n; ++j)
		{
			if(arr[i]>arr[j])
				max=arr[i];
		}
	}
	
	cout<<max<<endl;
	
	
	cout<<"Before Split: ";
	
		
	return 0;
}
