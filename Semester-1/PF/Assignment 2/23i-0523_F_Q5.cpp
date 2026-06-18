/*    Problem 5

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 2

*/

//Indentation is according to TAB WIDTH = 4

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
int main()

{
	string n1, n2;
	int r1, r2;
	char r;
	cout<<"\nPlayer 1: \n"
		<<"Enter Full Name: ";
	getline(cin, n1);
	cout<<"Enter Roll No(Last four digits): ";
	cin>>r1;
	
	while(r1<=0 || r1>9999)
	{	 cout<<endl<<"Invalid Roll No."<<endl;
	   	 cout<<"Enter positive four digits only: ";
	   	 cin>>r1;
	}
	cin.ignore(1,'\n');
	
	cout<<endl<<"Player 2: "<<endl
		<<"Enter Full Name: ";
	getline(cin, n2);
	cout<<"Enter Roll No(Last four digits): ";
	cin>>r2;
	
	while(r2<=0 || r2>9999)
	{	 cout<<endl<<"Invalid Roll No."<<endl;
	   	 cout<<"Enter positive four digits only: ";
	   	 cin>>r2;
	}
	cin.ignore(1,'\n');
	cout<<endl;
	
	int min=1, max=6, a=1;
	int p1d1, p1d2, pt1=0, rn1p1, rn2p1, a1;
	int p2d1, p2d2, pt2=0, rn1p2, rn2p2, a2;
	char np1, np2;
	
	while(a<=5)
	{
		 cout<<"Press Enter to roll the dice for player 1 & 2:";
		 cin.get(r);
		 
		 unsigned seed=time(0);
		 srand(seed);
		 p1d1=(rand() % (max-min+1)) + min;
		 p1d2=(rand() % (max-min+1)) + min;
		 
		 p2d1=(rand() % (max-min+1)) + min;
		 p2d2=(rand() % (max-min+1)) + min;
		 
		 cout<<"Player 1:"<<endl;
		 cout<<"Die 1: "<<p1d1<<endl;
		 cout<<"Die 2: "<<p1d2<<endl<<endl;
		 
		 cout<<"Player 2:"<<endl;
		 cout<<"Die 1: "<<p2d1<<endl;
		 cout<<"Die 2: "<<p2d2<<endl<<endl;
		 
		 pt1 += p1d1 + p1d2;
		 pt2 += p2d1 + p2d2;
		 
		 rn1p1=r1%10;		//Last digit of roll no. of player 1
		 rn2p1=(r1/10)%10;	//Second last digit of roll no. of player 1
		 
		 if((p1d1+p1d2)==(rn1p1+rn2p1))	//For player 1
		   pt1 += rn1p1;
		   
		 rn1p2=r2%10;		//Last digit of roll no. of player 2
		 rn2p2=(r2/10)%10;	//Second last digit of roll no. of player 2
		   
		 if((p2d1+p2d2)==(rn1p2+rn2p2))	//For player 2
		   pt2 += rn1p2;
		 
		 int l1=n1.length();		//Last letter of player 1 name
		 np1=n1.at(l1-1);
		 
		 if(np1<='A' && np1<='Z')	//For player 1
		   if((p1d1+p1d2)==(np1-64))
		     pt1 += pt1 + 5;
		     
		 else if(np1<='a' && np1<='z')
		 		if((p1d1+p1d2)==(np1-96))
		 		  pt1 += pt1 + 5;
		 
		 int l2=n2.length();		//Last letter of player 2 name
		 np2=n2.at(l2-1);
		 
		 if(np2<='A' && np2<='Z')	//For player 2
		   if((p2d1+p2d2)==(np2-64))
		     pt2 += pt2 + 5;
		     
		 else if(np2<='a' && np2<='z')
		 		if((p2d1+p2d2)==(np2-96))
		 		  pt2 += pt2 + 5;
		
		a1=p1d1+p1d2;		//For player 1
		
		if(p1d1==p1d2)		
		  if(a1==0 || a1==4)   
		  { cout<<"Player 1 gets an extra roll."<<endl;
		 	cout<<"Press Enter to roll dice for player 1:"<<endl;
		 	cin.get(r);
		 
		 	unsigned seed=time(0);
		 	srand(seed);
		 	p1d1=(rand() % (max-min+1)) + min;
			p1d2=(rand() % (max-min+1)) + min;
		 
		 	cout<<"Player 1:"<<endl;
		 	cout<<"Extra Die 1: "<<p1d1<<endl;
		 	cout<<"Extra Die 2: "<<p1d2<<endl<<endl;
		 	
		 	pt1 += p1d1 + p1d2;
		  }
		  
		a2=p2d1+p2d2;		//For player 2
		
		if(p2d1==p2d2)		
		  if(a2==0 || a2==4)   
		  { cout<<"Player 2 gets an extra roll."<<endl;
		 	cout<<"Press Enter to roll dice for player 2:"<<endl<<endl;
		 	cin.get(r);
		  
		    p2d1=(rand() % (max-min+1)) + min;
		 	p2d2=(rand() % (max-min+1)) + min;
		 
		 	cout<<"Player 2:"<<endl;
		 	cout<<"Extra Die 1: "<<p2d1<<endl;
		 	cout<<"Extra Die 2: "<<p2d2<<endl<<endl;
		 	
		 	pt2 += p2d1 + p2d2;
		  }
		  
		 a+=1;
	}


	cout<<"Score:"<<endl;
	cout<<"Player 1= "<<pt1<<endl;
	cout<<"Player 2= "<<pt2<<endl;
	
	if(pt1==pt2)
	{ 
	  p1d1=p2d1;
	  cout<<endl<<"Both player\'s scores are equal, so it\'s a sudden death!"<<endl;
	  
	  while(p1d1==p2d1)
	  {
	  	   cout<<endl<<"Press Enter to roll the dice for player 1 & 2:"<<endl;
		   cin.get(r);
		 
		   unsigned seed=time(0);
		   srand(seed);
		   p1d1=(rand() % (max-min+1)) + min;
		   p2d1=(rand() % (max-min+1)) + min;
		   
		   cout<<"Die Number:"<<endl;
		   cout<<"Player 1: "<<p1d1<<endl;
		   cout<<"Player 2: "<<p2d1<<endl;
	  }
	  if(p1d1>p2d1)
	    cout<<endl<<"Player 1 Wins!"<<endl;
	  else if(p2d1>p1d1)
	  		 cout<<endl<<"Player 2 Wins!"<<endl;  
	 }
	 
	 if(pt1>pt2)
	   cout<<endl<<"Player 1 Wins!"<<endl;
	 else if(pt2>pt1)
	 		cout<<endl<<"Player 2 Wins!"<<endl;
	 
	return 0;
}
