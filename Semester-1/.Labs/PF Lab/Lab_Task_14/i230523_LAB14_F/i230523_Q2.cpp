#include <iostream>
using namespace std;

const int ROWS = 5, COLS = 5;
void csort(int arr[][COLS], int ROWS);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int arr[ROWS][COLS];
	
	cout<<"Enter values of array:\n";
	for(int i=0; i<ROWS; ++i)
	{
		for(int j=0; j<COLS; ++j)
		{
			cin>>arr[i][j];
		}
	}
	
	cout<<"\nArray before sorting:\n";
	for(int i=0; i<ROWS; ++i)
	{
		for(int j=0; j<COLS; ++j)
		{
			cout<<arr[i][j]<<"\t";
		}
		cout<<endl;
	}
	
	csort(arr, ROWS);
	
	cout<<"\nArray after sorting:\n";
	for(int i=0; i<ROWS; ++i)
	{
		for(int j=0; j<COLS; ++j)
		{
			cout<<arr[i][j]<<"\t";
		}
		cout<<endl;
	}
		
	return 0;
}
void csort(int arr[][COLS], int ROWS)
{
	for(int k=0; k<COLS; ++k)
	{
		for(int i=0; i<(ROWS-1); ++i)
		{
			for(int j=0; j<(ROWS-1-i); ++j)
			{
				if(arr[j+1][k]<arr[j][k])
				{
					int temp=arr[j][k];
					arr[j][k]=arr[j+1][k];
					arr[j+1][k]=temp;
					
				}
			}
		}
	}
}











