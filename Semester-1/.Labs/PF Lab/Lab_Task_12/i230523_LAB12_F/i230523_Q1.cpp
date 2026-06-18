#include <iostream>
using namespace std;


int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	const int size=20;
	int s=0;
	char ch[size];
	
	cout<<"Enter a character array: ";
	cin>>ch;
	
	for(; ch[s]!='\0'; ++s);
	
	int p=1, a=0, b=s-1;
	
	{
	  for(int i=s; i>(s/2); --i)
	  {
	  	 if(ch[a]!=ch[b])
	  	 { 
	  	   p=0;
	  	 }
	  	 
	  	   ++a;
	  	   --b;
	  	 	
	  }
	}
	
	
	
	if(p==1)
	  cout<<"The entered character array is a palindrome.\n";
	
	if(p==0)
	  cout<<"The entered character array is not a palindrome.\n";
	
		
	return 0;
}
