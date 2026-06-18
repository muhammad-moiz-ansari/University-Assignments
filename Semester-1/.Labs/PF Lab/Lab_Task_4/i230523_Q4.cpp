#include <iostream>
#include <cmath>
using namespace std;
int main()
{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

float a, b, c, x1, x2;

cout<<"Enter Coefficient a : ";
cin>>a;
cout<<"Enter Coefficient b : ";
cin>>b;
cout<<"Enter Coefficient c : ";
cin>>c;
cout<<endl;

x1=(-b+sqrt(pow(b,2)-4*a*c))/(2*a);
x2=(-b-sqrt(pow(b,2)-4*a*c))/(2*a);

cout<<"Roots are:"<<endl;
cout<<"x1 = "<<x1<<endl;
cout<<"x2 = "<<x2<<endl;

return 0;
}

