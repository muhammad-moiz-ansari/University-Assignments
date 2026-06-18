#include <iostream>
#include <ctime>
using namespace std;

void coin_tossing(int);
bool flip();

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n=1;
	coin_tossing(n);
	
		
	return 0;
}

void coin_tossing(int n)
{
	int h=0, t=0;
	srand(time(0));
	for(n; n<=100; ++n)
	{
	   if(flip())
	   {
	     cout<<"Heads\n";
	     ++h;
	   }
	   else
	   {
	   	   cout<<"Tails\n";
	   	   ++t;
	   }
	}
	cout<<"\nResults after 100 coin tosses:\n";
	cout<<"Heads: "<<h<<endl;
	cout<<"Tails: "<<t<<endl;
	
}

bool flip()
{
	return rand()%2;
}
