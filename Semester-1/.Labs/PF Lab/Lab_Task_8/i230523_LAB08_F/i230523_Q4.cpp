#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int main()

{
	
cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	int x, n=1, N;
	srand(time(0));
	x = (rand() % 100) + 1;
	
	cout<<"Hi! I\'m thinking of a random number between 1 and 100."<<endl;
	
	while(n<=10)
	{
		 cout<<"---Attempt "<<n<<":"<<endl;
		 cout<<"Guess what number I am thinking of: ";
		 cin>>N;
		 if(N>x)
		   cout<<"Too high"<<endl;
		 if(N<x)
		   cout<<"Too low"<<endl;
		 if(N==x)
		 {
		   cout<<endl<<"Congratulations! You have guessed the right number."<<endl;
		   break;
		 }
		 n+=1;
	}
	if(N!=x)
	  cout<<endl<<"Aww, you ran out of tries. The number was "<<x<<"."<<endl;
	
	return 0;
}
