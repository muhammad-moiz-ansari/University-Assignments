#include <iostream>
using namespace std;
int main()

{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	int age, price;
	
	cout<<"Enter age : ";
	cin>>age;
	
	if(age>=0 && age<=12)
	price=10;
	else if(age>=13 && age<=64)
	price=20;
	else if(age>65)
	price=15;
	else
	cout<<"Invalid age\n";
	
	cout<<"Ticket Price : $"<<price<<endl;
	
	return 0;
}
