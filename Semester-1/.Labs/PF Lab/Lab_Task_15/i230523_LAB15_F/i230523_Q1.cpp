#include <iostream>
using namespace std;



int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int s1, s2, s;
	
	cout<<"Enter size of array 1: ";
	cin>>s1;
	
	cout<<"Enter size of array 2: ";
	cin>>s2;
	
	s = s1 + s2;
	char *arr1 = new char[s1];
	char *arr2 = new char[s2];
	char *arr  = new char[s];
	
	cout<<"Enter string 1: ";
	for(int i=0; i<s1; ++i)
		cin>>*(arr1+i);
	
	cout<<"Enter string 2: ";
	for(int i=0; i<s2; ++i)
		cin>>*(arr2+i);
	
	int j=0;
	for(int i=0; i<s1; ++i, ++j)
	{
		arr[j]=arr1[i];
	}
	for(int i=0; i<s2; ++i, ++j)
	{
		arr[j]=arr2[i];
	}
	
	cout<<endl;
	for(int i=0; i<s; ++i)
		cout<<*(arr+i);
	
	cout<<endl;
	return 0;
}
