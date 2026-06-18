#include <iostream>
using namespace std;



int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	const int size = 5;
	int arr[size];
	int *p = arr;
	int sum=0;
	int *sumptr = &sum;
	
	cout<<"Enter elements of array: \n";
	for(int i=0; i<size; ++i)
	{
		cin>>arr[i];
	}
	cout<<endl;
	
	for(int i=0; i<size; ++i)
		*(sumptr) += *(p+i);
	
	cout<<"Sum of array elements = "<<*sumptr<<endl;
	
	
	
	
	return 0;
}
