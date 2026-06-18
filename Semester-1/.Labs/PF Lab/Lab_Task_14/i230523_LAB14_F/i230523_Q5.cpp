#include <iostream>
using namespace std;

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n1, n2;
	
	cout<<"Enter the first integer: ";
	cin>>n1;
	cout<<"Enter the second integer: ";
	cin>>n2;
	
	cout<<"\nBefore swapping:\n"
		<<"First integer: "<<n1
		<<"\nSecond integer: "<<n2<<endl;
	
	int *p1 = &n1, *p2 = &n2, *p3;
	
	p3=p1;
	p1=p2;
	p2=p3;
	
	
	cout<<"\nAfter swapping:\n"
		<<"First integer: "<<*p1
		<<"\nSecond integer: "<<*p2<<endl;
	
		
	return 0;
}

