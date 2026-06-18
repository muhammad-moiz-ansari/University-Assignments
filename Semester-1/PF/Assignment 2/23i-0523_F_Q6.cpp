/*    Problem 6

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 2

*/

#include <iostream>
#include <cmath>
/*For dry run:
#include <bitset>*/
using namespace std;
int main()

{
	int r, n, x, m1, m2, k;
	long long l;
	cout<<"Enter the number of rounds: ";
	cin>>r;
	while(r<=0)		//Input validation
	{
		 cout<<"Invalid input."<<endl;
		 cout<<"Enter a positive integer: ";
		 cin>>r;
	}
	
	n=r;
	
	l=pow(2, n)-1;
	x=l;
	m1=l;
	
	for(int i=1; i<=r; ++i)
	{
	   if(i==1)
	   {
	     k=-1;
	     for(int j=0; j<(n/3); ++j)	//Turns off every third lamp
	     {
	        k+=3;
	        l=l-pow(2,k);		//Subtracts 2^2, 2^5, 2^9, ... from the number to null the every third bit
	         					
	     }
	   }
	   
	   	 m1=x;
	     k=-1;
	     
	     for(int j=0; j<(n/i); ++j)	//Making mask
	     {
	     	if(i==1)
	     	  break;
	     	k+=i;
	     	m1=m1-pow(2,k);
	     }
	     
	     l=l^(~m1 & x);	//l=l^m3;
	     				//m2=~m1;
	     				//m3=~m1 & x;
	     
	   if(i==1 && i==n)				//For nth Round
	   {
	      m1=x;
	     k=-1;
	     for(int j=0; j<(n/i); ++j)	//Making mask
	     {
	     	k+=i;
	     	m1=m1-pow(2,k);
	     }
	     
	     l=l^(~m1 & x);	//l=l^m3;
	     				//m2=~m1;
	     				//m3=~m1 & x;
	     				
	   }
	/* For dry run:
	cout<<endl;
	cout<<"Round="<<i<<endl;
	cout<<"m1="<<bitset<64>(~m1 & x)<<endl;
	cout<<"l ="<<bitset<64>(l)<<endl;
	*/	   
	}
	
	int bits=0;
	m2=1;
	
	/* For dry run:
	cout<<endl;
	cout<<"m2="<<bitset<64>(m2)<<endl;
	*/
	for(int p=1; p<=r; ++p)
	{
	   if((m2 & l) == 1)
	     bits+=1;
	   l=l>>1;

	/* For dry run:
	cout<<"l ="<<bitset<64>(l)<<endl;
	*/
	}
	
	cout<<"Number of lamps that are on: "<<bits<<endl;	
	
	return 0;
}
