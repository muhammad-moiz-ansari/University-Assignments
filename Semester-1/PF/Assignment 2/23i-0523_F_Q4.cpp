/*    Problem 4

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 2

*/

//Indentation is according to TAB WIDTH = 4

#include <iostream>
#include <cmath>
using namespace std;
int main()

{
	int x, n;
	cout<<"Enter Absolute Value of x: ";
	cin>>x;
	x=abs(x);
	
	cout<<"Enter positive integer n: ";
	cin>>n;
	while(n<0)
	{
		 cout<<"Invalid input(Enter positive integer): ";
		 cin>>n;
	}
	
	int X=x;
	int max=(pow(x,n)+pow(x,(n-1)));
	int y=max;
	for(int i=(pow(x,n)+pow(x,(n-1))); i>=0; i-=2)
	{  
	   //Printing y-axis...
	   if(max>999)
	   {
	   	 if(i>999)
	   	   cout<<i;
	   	 else if(i>99)
	   	 		cout<<"0"<<i;
	   	 else if(i>=10 && i<=99)
		 		cout<<"00"<<i;
	   	 else
			 cout<<"000"<<i;
	   }
	   if(max>99 && max<1000)
	   {
	   	 if(i>99)
	   	   cout<<i;
	   	 else if(i>=10 && i<=99)
		   cout<<"0"<<i;
	   	 else
			 cout<<"00"<<i;
	   }
	   if(max>=10 && max<100)
	   {
	     if(i>=10)
		   cout<<i;
	     else
	    	 cout<<"0"<<i;
	   }
	   if(max<10)
		 cout<<i;
	   
	   //...(printing y-axis) end
	   
	   for(int j=1; j<=3*(x+1); ++j)	//Printing space before star
	   {
	   	  cout<<" ";
	   }
	   
	   if(y==(pow(x,n)+pow(x,(n-1))))	//Printing star on the value
	   {
	   	 if(i==0 && x%2!=0 && n==1)
	   	   cout<<" *";
	   	 else
	   	 	 cout<<"*";
	   	 if(n>1)		//Decrementing variable for position before star
	   	   x-=1;
	   	 else
	   	 	 x-=2;
	   }
	   y-=2;		//Decrementing y-axis value used for checking
	   cout<<endl;
	}
	
	int ly=log10(max)+1;		//Length of Maximum range value
	for(int k=1; k<=ly+1; ++k)	//Space before x-axis
	   cout<<" ";
	   
	for(int i=0; i<X+1; ++i)	//Printing x-axis
	{
	   if(i==0 && x%2!=0 && n==1)
	     cout<<""<<i<<"  ";
	   else if(i<10)
			  cout<<"  "<<i;
	   else
	       cout<<" "<<i;
	}
	cout<<endl;
	
	return 0;
}
