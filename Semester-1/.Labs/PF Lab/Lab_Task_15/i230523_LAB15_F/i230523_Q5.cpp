#include <iostream>
using namespace std;

void count(char* arr, int size, int *p1, int *p2);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int size, vow=0, con=0;
	int *p1=&vow, *p2=&con;
	
	cout<<"Enter size of string array: ";
	cin>>size;
	
	char *arr = new char[size];
	
	cout<<"Enter string array: ";
	for(int i=0; i<size; ++i)
		cin>>*(arr+i);
	
	
	count(arr, size, p1, p2);
	
	cout<<"Number of vowels:"<<*p1<<endl
		<<"Number of consonants:"<<*p2<<endl;
	
	
	
	
	
	return 0;
}
void count(char* arr, int size, int *p1, int *p2)
{
	for(int i=0; i<size; ++i)
	{
		if(*(arr+i)=='a' || *(arr+i)=='e' || *(arr+i)=='i' || *(arr+i)=='o' || *(arr+i)=='u' || *(arr+i)=='A' || *(arr+i)=='E' || *(arr+i)=='I' || *(arr+i)=='O' || *(arr+i)=='U')
		{
			++*p1;
		}
		else
		{
			++*p2;
		}
	}
}

