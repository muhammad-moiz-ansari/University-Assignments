#include <iostream>
#include <cmath>
using namespace std;
int main()
{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

int N, a, b, c, d, n1, n2, n3, n4, n5, n6, sum1, sum2, sum3;
cout<<"Enter Four Digit Integer : ";
cin>>N;
cout<<endl;

a=N%10;
n1=N/10;
b=n1%10;
n2=n1/10;
c=n2%10;
d=n2/10;

sum1=a+b+c+d;

n3=sum1%10;
n4=sum1/10;

sum2=n3+n4;

n5=sum2%10;
n6=sum2/10;

sum3=n5+n6;

cout<<"First Sum : "<<sum1<<endl;
cout<<"Second Sum : "<<sum2<<endl;
cout<<"Third Sum : "<<sum3<<endl;

return 0;
}

