#include <iostream>
using namespace std;

int* reverseArray(int *arr, int size);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int size;
	
	cout<<"Enter size of array: ";
	cin>>size;
	
	int *arr = new int [size];
	
	cout<<"Enter the elements of array:\n";
	for(int i=0; i<size; ++i)
		cin>>*(arr+i);
	
	int *result = reverseArray(arr, size);
	
	for(int i=0; i<size; ++i)
		cout<<*(result+i);
	
	cout<<endl;
	
	delete []result;
	
	
	return 0;
}
int *reverseArray(int *arr, int size)
{
	int *reverse = new int [size];
	
	int temp;
	
	for(int i=0, j=size-1; i<size; ++i, --j)
	{
		*(reverse+i) = *(arr+j);
	}
	
	
	return reverse;
}






