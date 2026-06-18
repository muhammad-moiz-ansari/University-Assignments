/*
Name : Moiz ansari
Roll no : 23i=0523
*/

#include <iostream>
#include <cmath>

using namespace std;

int main()
{
	int x, y;
	cout<<"Enter x: ";
	cin>>x;
	
	y=((double)(pow(x,3)+5*pow(x,2)-4*x+3)/(2*pow(x,4)+7*pow(x,3)-3*pow(x,2)+6))-pow(((double)(pow(x,2)-3*x+2)/(4*pow(x,3)-5*pow(x,2)+8)),1.0/3);
	
	cout<<"Output= "y<<endl;
	return 0;
}
