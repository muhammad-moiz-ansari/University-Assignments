#include <iostream>
using namespace std;

const int ROWS = 4, COLS = 4;
bool IsMatrixUpperTriangular(int [][COLS], int ROWS, int COLS);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int matrix[ROWS][COLS];
	
	cout<<"Enter values of Matrix A:\n";
	for(int i=0; i<ROWS; ++i)
	{
		for(int j=0; j<COLS; ++j)
		{
			cin>>matrix[i][j];
		}
	}
	
	cout<<"\nMatrix A:\n";
	for(int i=0; i<ROWS; ++i)
	{
		for(int j=0; j<COLS; ++j)
		{
			cout<<matrix[i][j]<<"\t";
		}
		cout<<endl;
	}
	
	cout<<"Is the matrix upper triangular? "<<boolalpha<<(IsMatrixUpperTriangular(matrix, ROWS, COLS))<<endl;
		
	return 0;
}

bool IsMatrixUpperTriangular(int matrix[][COLS], int ROWS, int COLS)
{
	bool check=0;
	for(int i=0; i<ROWS; ++i)
	{
		for(int j=0; j<COLS; ++j)
		{
			if(i>j)
			{
				if(matrix[i][j]==0)
					check=1;
				else
				{
					check=0;
					break;
				}
			}
		}
	}
	return check;
}







