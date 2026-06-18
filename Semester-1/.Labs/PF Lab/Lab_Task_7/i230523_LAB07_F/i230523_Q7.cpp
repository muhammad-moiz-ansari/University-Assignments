#include <iostream>
using namespace std;
int main()

{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	float N;
	char c;
	
	cout<<"Enter unit type : ";
	cin>>c;
	cout<<"Enter value : ";
	cin>>N;
	
	switch(c)
	{
	case 'I':
	cout<<"Converted value = "<<N*2.54<<"cm";
	break;
	
	case 'P':
	cout<<"Converted value = "<<N*0.453592<<"kg";
	break;
	
	default:
	cout<<"Invalid character\nEnter I or P\n";
	}
	cout<<endl;
	return 0;
}
