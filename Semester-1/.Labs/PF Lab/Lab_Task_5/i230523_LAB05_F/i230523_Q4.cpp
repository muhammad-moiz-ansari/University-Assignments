#include <iostream>
using namespace std;
int main()
{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

int x, y;

cout<<"x = ";
cin>>x;
cout<<"y = ";
cin>>y;

cout<<-((x>>31)^(y>>31))<<endl;

return 0;
}
