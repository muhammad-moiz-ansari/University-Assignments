#include <iostream>
using namespace std;
int main()

{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	int age, s, n;
	char c;
	
	cout<<"Enter age : ";
	cin>>age;
	
	cout<<"Enter exam score : ";
	cin>>s;
	
	cout<<"Does student have Parental Consent (Y/N) : ";
	cin>>c;
	
	if(age>=18 && age<=30)
	  if(s>=60 && s<=100)
	    if(c=='y' || c=='Y')
	      n=1;
	    else if(c=='n' || c=='N')
	      n=0;
	  else
	  n=0;
	else
	n=0;
	
	if(n==1)
	cout<<"Student is eligible to enroll in the course\n";
	else
	cout<<"Student is not eligible to enroll in the course\n";
	
	return 0;
}
