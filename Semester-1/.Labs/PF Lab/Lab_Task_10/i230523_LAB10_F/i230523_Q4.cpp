#include <iostream>
using namespace std;

int add(int, int);
int subtract(int, int);
int multiply(int, int);
float divide(int, int);

int main()
{
 cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int a, b, ch;
	float r;
	cout<<"Welcome to My Calculator: \n\n";
	cout<<"Enter the 1st Number: ";
	cin>>a;
	cout<<"Enter the 2nd Number: ";
	cin>>b;
	
	cout<<"\nSelect an operation: \n";
	cout<<"1. Addition\n"
		<<"2. Subtraction\n"
		<<"3. Multiplication\n"
		<<"4. Division\n";
	
	cout<<"\nEnter the number corresponding to your choice: ";
	cin>>ch;
	
	switch(ch)
	{
	case 1:
			r=add(a, b);
			break;
			
	case 2:
			r=subtract(a, b);
			break;
	
	case 3:
			r=multiply(a, b);
			break;
			
	case 4:
			r=divide(a, b);
			break;
	
	default:
			cout<<"Invalid choice\n";
	}
	if(ch>=1 && ch<=4)
	  cout<<"Result= "<<r<<endl;
	
	return 0;
}

int add(int a, int b)
{
	int result=a+b;
	return result;
}

int subtract(int a, int b)
{
	int result=a-b;
	return result;
}

int multiply(int a, int b)
{
	int result=a*b;
	return result;
}

float divide(int a, int b)
{
	float result=(float)a/b;
	return result;
}



