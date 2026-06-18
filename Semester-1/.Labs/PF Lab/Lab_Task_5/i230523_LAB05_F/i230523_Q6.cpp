#include <iostream>
using namespace std;
int main()
{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

int a, b;

cout<<"Enter Two Numbers : "<<endl;
cout<<"Number 1 : ";
cin>>a;
cout<<"Number 2 : ";
cin>>b;
cout<<endl;

a=(a&b)|b;

cout<<"Before swapping : num1 = "<<a<<", num2 = "<<b<<endl;

cout<<"After swapping :  num1 = "<<a<<", num2 = "<<b<<endl;

return 0;
}
