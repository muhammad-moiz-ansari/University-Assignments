#include <iostream>
using namespace std;

const int r=2, c=3;
void transpose(int arr[][c], int r, int c);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	
	int arr[r][c], Tarr[r][c];
	
	cout<<"Enter 2x3 matrix: \n";
	for(int i=0; i<r; ++i)
		for(int j=0; j<c; ++j)
			cin>>arr[i][j];
	
	cout<<"\nOriginal Matrix: \n";
	for(int i=0; i<r; ++i)
	{
		for(int j=0; j<c; ++j)
			cout<<arr[i][j]<<"\t";
		cout<<endl;
	}
	
	transpose(arr, r, c);
	
	
	
		
	return 0;
}
void transpose(int arr[][c], int r, int c)
{
	int Tarr[c][r];
	for(int i=0; i<c; ++i)
		for(int j=0; j<r; ++j)
			Tarr[i][j]=arr[j][i];
	
	cout<<endl;
	
	cout<<"Transpose: \n";
	for(int i=0; i<c; ++i)
	{
		for(int j=0; j<r; ++j)
			cout<<Tarr[i][j]<<"\t";
		cout<<endl;
	}
	
}










