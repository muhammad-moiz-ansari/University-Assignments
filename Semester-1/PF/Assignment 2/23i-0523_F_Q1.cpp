/*    Problem 1

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 2

*/

#include <iostream>
#include <cmath>

using namespace std;
int main()

{
	long long a=0;
	int n, n_bit, sum=0,
		m, m1, m2, m3,
		g1, g2, g3, g4,
		b=0, c=0, power, p, j;
	
	cout<<"Enter the number: ";
	cin>>n;
	
	m=1023;
	
	for(int i=1; i<=4; ++i)
	{
	   if(i==1)
	     g1=n & m;
	   if(i==2)
	     g2=n & m;
	   if(i==3)
	     g3=n & m;
	   if(i==4)
	     g4=n & m;
	   m=m<<10;
	}
	
	a=g1;
	while(a>0)		//Converting gate 1 decimal to binary form
	{
	   g1=a%2;
	   b=b*10 + g1;
	   a=a/2;
	}
	cout<<"Gate 1: "<<b;
	cout<<endl;
	
	int choice = 0;
	int bin=b;		//Binary Number
	
	cout<<"Enter choice:"<<endl;
	cout<<"1. First operation"<<endl;
	cout<<"2. Second operation"<<endl;
	cout<<"3. Third operation"<<endl;
	cout<<"4. Fourth operation"<<endl;
	cin>>choice;
	
	switch(choice)
	{
	case 1:
	
	power=0;
	a=0;
	j=0;
	sum=0;
	while(b!=0)
	   {
	   	  a=b%10;
	   	  power=pow(2, j);
	   	  p=power*a;
	   	  sum=sum+p;
	   	  b/=10;
	   	  ++j;
	   }
	cout<<"Gate 1:"<<sum<<endl;
	break;
	
	case 2:
	/*power=0;
	a=0;
	j=0;
	string hex="";
	int counter=0;
	while(b!=0)
	   {
	   	  a=b%10;
	   	  power=pow(16, j);
	   	  p=power*a;
	   	  char z;
	   	  if(p>=10)
	   	  {
	   	  	z = 'O' + 
	   	  }
	   	  else
	   	  {
	   	  	
	   	  }
	   	  
	   	  b/=10;
	   	  ++j;
	   	  
	   	  if(counter == 4)
	   	  {
			counter = 0;
			j = 0;
			
		  }
	   }cout<<hex<<endl;
	   */
	
	break;
	
	case 3:
		  int o;
		  g3=o;
		  g4=g3^g4;
		  g3=g4^o;
	break;
	
	case 4:
	break;
	
	default:
	cout<<"Invalid Choice\n";
	}
	return 0;
}
