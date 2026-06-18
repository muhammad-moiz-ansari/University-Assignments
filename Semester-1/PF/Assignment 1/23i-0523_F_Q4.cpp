/*    Problem 4

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 1

*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{

	int N1, N2, N3, N4, N5;

	cout<<"Enter 5 Numbers:"<<endl;

	// Taking input
	
	cout<<"N1:";
	cin>>N1;
	cout<<"N2:";
	cin>>N2;
	cout<<"N3:";
	cin>>N3;
	cout<<"N4:";
	cin>>N4;
	cout<<"N5:";
	cin>>N5;

	cout<<endl;

	// Printing stars

	cout<<"N1:"<<setw(N1+1)<<setfill('*')<<" "<<endl;
	cout<<"N2:"<<setw(N2+1)<<setfill('*')<<" "<<endl;
	cout<<"N3:"<<setw(N3+1)<<setfill('*')<<" "<<endl;
	cout<<"N4:"<<setw(N4+1)<<setfill('*')<<" "<<endl;
	cout<<"N5:"<<setw(N5+1)<<setfill('*')<<" "<<endl;

	return 0;
}
