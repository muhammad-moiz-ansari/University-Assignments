#include <iostream>
using namespace std;

void swap(int &a, int &b);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int a, b;
	
	cout<<"Enter a: ";
	cin>>a;
	cout<<"Enter b: ";
	cin>>b;
	
	swap(a, b);
	
	cout<<"\nAfter swaping:\n"<<"a = "<<a<<"\nb = "<<b<<endl;
	
		
	return 0;
}
void swap(int &a, int &b)
{
	int c=a;
	a=b;
	b=c;
}
