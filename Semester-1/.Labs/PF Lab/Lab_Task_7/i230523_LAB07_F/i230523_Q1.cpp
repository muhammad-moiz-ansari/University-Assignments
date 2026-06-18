#include <iostream>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	float per;
	char grade;
	cout<<"Enter the percentage : ";
	cin>>per;
	
	if(per>=90 && per<=100)
	grade='A';
	else if(per>=80 && per<=89)
	grade='B';
	else if(per>=70 && per<=79)
	grade='C';
	else if(per>=0 && per<=69)
	grade='D';
	else
	cout<<"Invalid percentage\nEnter percentage between 0 and 100\n";
	
	cout<<"Grade = Grade "<<grade<<endl;
	
	
	return 0;
}
