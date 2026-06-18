#include <iostream>

using namespace std;
int main()

{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	int N;
	string n1, n2;
	cout<<"Enter a number : ";
	cin>>N;
	
	if(N%2==0)
	n1="even";
	else
	n1="odd";
	
	if(N>0)
	n2="positive";
	else if(N<0)
	n2="negative";
	else
	n2="zero";
		
	cout<<"Number is "<<n2<<" and "<<n1<<endl;
	
	return 0;
}
