#include <iostream>
#include<string>
using namespace std;

int main()
/* {
	char arr[]={};
	cout<<"enter ";
	
	int size=1;
		
	for(int i=0; arr[i]!='\0'; ++i)
	{
		cin.get(arr[i]);
	}
	cout<<arr<<endl;
	cout<<size;
} */
{
	int arr[]={9,3,2,1,5,6,10};
	bool b=1;
	int temp;
	int size=sizeof(arr)/sizeof(arr[0]);
	
	for(int i=1; i<(size-1); ++i)
	{
		if(arr[size-i]<arr[size-1-i])
		{
		  temp=arr[size-1-i];
		  arr[size-i]=arr[size-1-i];
		  arr[size-1-i]=temp;
		}
	}
	for(int i=0; i<size; ++i)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}







