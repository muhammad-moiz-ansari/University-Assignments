#include <iostream>
using namespace std;

int* mergeArrays(int *arr1, int size1, int *arr2, int size2);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int size1, size2, size;
	
	cout<<"Enter the size of array 1: ";
	cin>>size1;
	
	cout<<"Enter the size of array 2: ";
	cin>>size2;
	
	size = size1 + size2;
	
	int *arr1 = new int[size1];
	int *arr2 = new int[size2];
	int *arr  = new int[size];
	
	cout<<"Enter array 1:\n";
	for(int i=0; i<size1; ++i)
		cin>>*(arr1+i);
	
	cout<<"Enter array 2:\n";
	for(int i=0; i<size2; ++i)
		cin>>*(arr2+i);
	
	int* result = mergeArrays(arr1, size1, arr2, size2);
	
	for(int i=0; i<size; ++i)
		cout<<result[i];
	
	cout<<endl;
	
	delete []result;
	
	
	return 0;
}
int* mergeArrays(int *arr1, int size1, int *arr2, int size2)
{
	int size = size1 + size2;
	int *merged = new int[size];
	
	int j=0;
	for(int i=0; i<size1; ++i, ++j)
	{
		merged[j] = arr1[i];
	}
	for(int i=0; i<size2; ++i, ++j)
	{
		merged[j] = arr2[i];
	}
	
	return merged;
}










