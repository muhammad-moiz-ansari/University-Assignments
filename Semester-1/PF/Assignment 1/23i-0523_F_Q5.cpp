/*    Problem 5

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 1

*/

#include<iostream>
using namespace std;
int main()
{

	int d,m,y;
	
	//Taking Data

	cout<<endl<<"Enter Date(In digits):";
	cin>>d;
	cout<<"Enter Month(In digits):";
	cin>>m;
	cout<<"Enter Year(Only the last two digits):";
	cin>>y;
	cout<<endl;

	//Taking condition
	
	string exp = d>31? "Invalid date" : m>12? "Invalid month" : y>99? "Enter only last two digits of year" : (d*m==y)?"The date is magic.":"The date is not magic.";
	cout<<exp<<endl;

	return 0;
}

