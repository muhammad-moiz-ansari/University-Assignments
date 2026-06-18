/*    Problem 2

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 1

*/

#include<iostream>
using namespace std;
int main()
{
	unsigned int n1,n2,n3,a,b,c;

	cout<<"Enter Three Non-Negative Integers:\n";	
	cin>>n1>>n2>>n3;				//Taking Input
	cout<<endl;

	a=n1%10;
	b=n2%10;
	c=n3%10;

	bool exp = (a==b || b==a || a==c || c==a || b==c || c==b);  //Comparing numbers

	cout<<boolalpha<<"The result is : "<<exp<<endl;  //Giving Output

	return 0;
}


