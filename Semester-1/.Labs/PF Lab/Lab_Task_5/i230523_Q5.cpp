#include <iostream>
#include <bitset>
using namespace std;
int main()
{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

int N, n, a, b, c, d, x, y;

cout<<"Enter an Integer : ";
cin>>N;

x=2863311530;
y=x>>1;

b=N&x;
a=N&y;

c=b>>1;
d=a<<1;

n=c|d;

cout<<"After swapping adjacent bits : "<<n<<endl;

return 0;
}
