#include <iostream>
using namespace std;

int removeDuplicates(int arr[], int s);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	const int s=8;
	int arr[s], count=0;
	
	cout<<"Enter array: \n";
	for(int i=0; i<s; ++i)
		cin>>arr[i];
	
	cout<<"\nOriginal Array: ";
	for(int i=0; i<s; ++i)
		cout<<arr[i]<<" ";
	cout<<endl;
	
	count=s-removeDuplicates(arr, s);
	
	cout<<"Sorted Array: ";
	for(int i=0; i<(count); ++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	
	
		
	return 0;
}
int removeDuplicates(int arr[], int s)
{
	int count=0, temp;
	for(int i=0; i<s; ++i)
	{
		for(int j=i+1; j<s; ++j)
		{
			//cout<<arr[i]<<" "<<arr[j]<<endl;
			if(arr[i]==arr[j])
			{
				++count;
				for(int k=i; k<s; ++k)
				{
					arr[k]=arr[k+1];
				}
			}
		}
	}
	//--count;
	return count;
}








