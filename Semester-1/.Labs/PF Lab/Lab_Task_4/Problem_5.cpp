#include <iostream>
#include <cmath>
using namespace std;
int main()
{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

int N, a, b, n1, n2, sum;
cout<<"Enter Four Digit Integer : ";
cin>>N;
cout<<endl;

a=N%10;
n1=N/10;
n2=n1/10;
b=n2/10;
sum=a+b;

cout<<"Sum = "<<sum<<endl;

return 0;
}

