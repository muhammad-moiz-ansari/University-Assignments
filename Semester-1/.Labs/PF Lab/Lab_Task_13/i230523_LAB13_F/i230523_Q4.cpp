#include <iostream>
using namespace std;

const int r=4, c=4;
void spiral(int arr[][c], int r, int c);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int arr[r][c];
	
	cout<<"Enter 4x4 matrix: \n";
	for(int i=0; i<r; ++i)
		for(int j=0; j<c; ++j)
			cin>>arr[i][j];
	
	cout<<"\nMatrix: \n";
	for(int i=0; i<r; ++i)
	{
		for(int j=0; j<c; ++j)
			cout<<arr[i][j]<<"\t";
		cout<<endl;
	}
	
	spiral(arr, r, c);
	
	
	
		
	return 0;
}
void spiral(int arr[][c], int r, int c)
{
	int pr[r][c], j=0;
	for(int i=0; i<r; ++i)
	{
		if(i==0)
			for(j=0; j<c; ++j)
			{
				pr[i][j]=arr[i][j];
			}
		if(i==1)
			for(j=0; j<c; ++j)
			{
				if(j<c-1)
				  pr[i][j+11]=arr[i][j];
				else
					pr[i][j]=arr[i][j];
			}
	}
	
	cout<<endl;
	for(int i=0; i<(r*c); ++i)
	{
		cout<<pr[i][j]<<" ";
	}
	cout<<endl;


}











