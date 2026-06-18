#include <iostream>
using namespace std;

bool checkVowels(char a);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	const int size=25;
	char arr[size];
	char a;
	char v[size];
	
	
	cout<<"Character array is: ";
	cin>>arr;
	
	int s=0;
	for(; arr[s]!='\0'; ++s);
	
	int j=0;
	for(int i=0; i<size; ++i)
	{
		a=arr[i];
		if(checkVowels(a))
		{	v[j]=arr[i];
			++j;
		}
	}
	v[j]='\0';
	cout<<"Returned array has: "<<v<<endl<<endl;
	
	int count=0;
	char ch;
	cout<<"Enter the letter to check count for: ";
	cin>>ch;
	
	for(int i=0; i<s; ++i)
	{
		if(arr[i]==ch)
		  ++count;
	}
	
	cout<<"Count("<<ch<<") is: "<<count<<endl;
		
	return 0;
}


bool checkVowels(char a)
{
	bool x;
	
	if(a=='a' || a=='e' || a=='i' || a=='o' || a=='u' || a=='A' || a=='E' || a=='I' || a=='O' || a=='U')
		x= 1;
	else
		x= 0;
			
	
	return x;
}





