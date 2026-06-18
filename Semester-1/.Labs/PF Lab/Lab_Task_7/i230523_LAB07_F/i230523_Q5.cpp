#include <iostream>
#include <iomanip>
using namespace std;
int main()

{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	float n1, n2, R;
	char op;
	
	cout<<"Enter operand 1 : ";
	cin>>n1;
	cout<<"Enter operand 2 : ";
	cin>>n2;
	cout<<"Enter operator : ";
	cin>>op;
	
	switch(op)
	{
	case '+':
	cout<<"Result : "<<(R=n1+n2)<<endl;
	break;
	
	case '-':
	cout<<"Result : "<<(R=n1-n2)<<endl;
	break;
	
	case '*':
	cout<<"Result : "<<(R=n1*n2)<<endl;
	break;
	
	case '/':
	cout<<"Result : "<<(R=n1/n2)<<endl;
	break;
	
	default:
	cout<<"Invalid operator\n";
	}
	
	return 0;
}
