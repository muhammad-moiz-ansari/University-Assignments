#include <iostream>
using namespace std;
int main()

{

cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
cout<<"Roll No : 23i-0523"<<endl<<endl;

	int p1, p2;
	
	cout<<"Rock    : 1\nPaper   : 2\nScissor : 3\n";
	
	cout<<"First Player : ";
	cin>>p1;
	cout<<"Second Player : ";
	cin>>p2;
	
	switch(p1)
	{
	case 1:
		  switch(p2)
		  {
		  case 1:
		  cout<<"It\'s a tie";
		  break;
		  
		  case 2:
		  cout<<"2st Player Wins";
		  break;
		  
		  case 3:
		  cout<<"1st Player Wins";
		  break;
		  
		  default:
		  cout<<"Invalid Number\nEnter number 1, 2 or 3\n";
		  
		  }
		  break;
	case 2:
		  switch(p2)
		  {
		  case 1:
		  cout<<"1st Player Wins";
		  break;
		  
		  case 2:
		  cout<<"It\'s a tie";
		  break;
		  
		  case 3:
		  cout<<"2st Player Wins";
		  break;
		  
		  default:
		  cout<<"Invalid Number\nEnter number 1, 2 or 3\n";
		  
		  }
		  break;
	case 3:
		  switch(p2)
		  {
		  case 1:
		  cout<<"2st Player Wins";
		  break;
		  
		  case 2:
		  cout<<"1st Player Wins";
		  break;
		  
		  case 3:
		  cout<<"It\'s a tie";
		  break;
		  
		  default:
		  cout<<"Invalid Number\nEnter number 1, 2 or 3\n";
		  
		  }
		  break;
	default:
	cout<<"Invalid Number\nEnter number 1, 2 or 3\n";
	}
	
	
	return 0;
}
