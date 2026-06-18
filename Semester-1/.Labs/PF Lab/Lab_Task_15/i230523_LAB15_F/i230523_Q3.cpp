#include <iostream>
using namespace std;



int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int s;
	
	cout<<"Enter the size of string array: ";
	cin>>s;
	
	char *arr = new char[s];
	
	cout<<"Enter string: ";
	cin>>arr;
	
	for(int i=0, j=0; i<2; ++i)
	{
		char temp;
		temp = *(arr+j);
		*(arr+j) = *(arr+j+1);
		*(arr+j+1) = temp;
		
		cout<<i+1<<"st combination: "<<arr<<endl;
		
		j+=2;
	}
	cout<<endl;
	
	delete []arr;
	
	
	
	
	
	return 0;
}
