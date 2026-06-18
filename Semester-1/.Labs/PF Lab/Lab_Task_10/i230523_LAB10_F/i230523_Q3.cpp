#include <iostream>
#include <ctime>
using namespace std;
int main()

{
 cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n1=1, n2, sc=0, sp=0;
	srand(time(0));
	
	for(int i=1; n1>=1 && n1<=10; ++i)
	{
		 cout<<"Enter a number in the range [1,10]: ";
		 cin>>n1;
		 
		 n2 = (rand() % 10) + 1;
		 
		 cout<<"\nRound "<<i<<":"<<endl;
		 
		 cout<<"User\'s Number: "<<n1<<endl;
		 cout<<"Computer\'s Number: "<<n2<<endl;
		 
		 if((n1+n2)%2==0)
		 {
		   cout<<"The computer wins this round! :(\n\n";
		   sc+=1;
		 }
		 else
		 {
		 	 cout<<"The user wins this round! :D\n\n";
		 	 sp+=1;
		 }
		 
	}
	cout<<"Computer\'s Score= "<<sc<<endl;
	cout<<"User\'s Score= "<<sp<<endl;
	
	if(sc>sp)
	  cout<<"The Compuer Wins the Game! :("<<endl;
	else if(sp>sc)
			cout<<"The User Wins the Game! :D"<<endl;
	else
		cout<<"It\'s a tie! :| "<<endl;
	
	return 0;
}
