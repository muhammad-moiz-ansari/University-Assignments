#include <iostream>
using namespace std;

void decreaseSort(int arr[], int s);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	const int s=6;
	int arr[s];
	
	cout<<"Enter array: \n";
	for(int i=0; i<s; ++i)
		cin>>arr[i];
	
	cout<<"\nOriginal Array: ";
	for(int i=0; i<s; ++i)
		cout<<arr[i]<<" ";
	cout<<endl;
	
	decreaseSort(arr, s);
	
	cout<<"Sorted Array: ";
	for(int i=0; i<s; ++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	
		
	return 0;
}
void decreaseSort(int arr[], int s)
{
	int temp;
	for(int i=0; i<=s-1; ++i)
	{
		for(int j=0; j<s-i-1; ++j)
		{
			if(arr[j]<arr[j+1])
			{
				temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}
		}
	}
}









