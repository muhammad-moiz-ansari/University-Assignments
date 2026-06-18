#include <iostream>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	int N, n=1, r, ro, R=0, Ro=0, Re;
	float per;
	
	cout<<"Enter the number of floors: ";
	cin>>N;
	cout<<endl;
	
	if(N<=0)
	  cout<<"Invalid Input."<<endl;
	
	else
	{
		while(n<=N)
		{
			 cout<<"Enter the number of floors on the floor "<<n<<": ";
			 cin>>r;
			 
			 cout<<"How many rooms are occupied? ";
			 cin>>ro;
			 
			 R = R + r;
			 Ro = Ro + ro;
			 
			 n+=1;
		}
		Re = R - Ro;
		cout<<endl;
		
		cout<<"The hotel has total of "<<N<<" floors"<<endl;
		cout<<"The hotel has total of "<<R<<" rooms"<<endl;
		cout<<"There are "<<Ro<<" rooms occupied"<<endl;
		cout<<"There are "<<Re<<" empty rooms"<<endl;
		
		per = ((float)Ro / R) * 100;
		
		cout<<"Percentage of occupied rooms is "<<per<<"%"<<endl;
	}
	
	
	
	return 0;
}
