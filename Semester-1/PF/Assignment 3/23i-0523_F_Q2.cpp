/*    Problem 2

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 3

*/

#include <iostream>

using namespace std;

int main()
{
	int N, K, T, count;
	
	cout<<"Enter number of test cases T: ";
	cin>>T;
	
	for(int t=1; t<=T; ++t)
	{
		cout<<"\n-----Case "<<t<<"-----\n";
		
		cout<<"Enter the dimensions of matrices N: ";
		cin>>N;
		cout<<"Enter maximum value range for matrices K: ";
		cin>>K;
		
		int A[N][N], B[N][N];
		
		//Inputting arrays:
		
		cout<<"\nEnter elements of martix A: \n";
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
			{
				cin>>A[i][j];
				if(A[i][j]>K)
				{
					cout<<"Out of range...Enter value btw 1 & "<<K<<": ";
					cin>>A[i][j];
				}
			}
		
		cout<<"\nEnter elements of martix B: \n";
		for(int i=0; i<N; ++i)
			for(int j=0; j<N; ++j)
			{
				cin>>B[i][j];
				if(B[i][j]>K)
				{
					cout<<"Out of range...Enter value btw 1 & "<<K<<": ";
					cin>>B[i][j];
				}
			}
		//Printing arrays:
		
		cout<<"\nMatrix A: \n";
		for(int i=0; i<N; ++i)
		{
			for(int j=0; j<N; ++j)
				cout<<A[i][j]<<"\t";
			cout<<endl;
		}
		cout<<"\nMatrix B: \n";
		for(int i=0; i<N; ++i)
		{
			for(int j=0; j<N; ++j)
				cout<<B[i][j]<<"\t";
			cout<<endl;
		}
		//Calculations:
		count=0;
		for(int i=0; i<N; ++i)
		{
			for(int j=0; j<N; ++j)
			{
				if(A[i][j]!=B[i][j])
				{
					for(int k=0; A[i][j]!=B[i][j]; ++k)
					{
						if(A[i][j]>B[i][j])
						{
							--A[i][j];
						}
						else if(A[i][j]<B[i][j])
						{
							++A[i][j];
						}
					}
					++count;
				}
			}
		}
		
		cout<<"Number of steps required: "<<count<<endl;
		
		
		
		
		
		
		
		
		
	}
	
	return 0;
}
