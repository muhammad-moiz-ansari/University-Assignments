/*    Problem 2(a)

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 2

*/

#include <iostream>
using namespace std;
int main()

{
	int h=1, a=1, S=1, s=1;
	int n=1, n1=25, n2=0, n3=5;
	
	while(n<=5)
		{
	
		 h=1;
		 while(h<=2)
		 {
		 	  S=1;
		 	  while(S<=n1)
		 	  {
		 	  		cout<<" ";
		 	  		S+=1;
		 	  }
		 	  if(h==1)
		 	  {
		   	  a=1;
		   	  while(a<=6)
		   	  {
		   	 	   cout<<"*";
		   	 	   a+=1;
		   	  }
		   	  s=1;
		   	  while(s<=n2)
		   	  {
		   	 	   cout<<" ";
		   	 	   s+=1;
		   	  }
		   	  cout<<"*";
		 	  }
		 	  cout<<endl;
		 	  h+=1;
		 
		 	  S=1;
	 	 	  while(S<=n1)
		 	  {
		 	  	   cout<<" ";
		 	  	   S+=1;
		 	  }
	 	 	  cout<<"*";
		 
		 	  s=1;
		 	  while(s<=n3)
		 	  {
		 	  	   cout<<" ";
		 	  	   s+=1;
		 	  }
		 	  cout<<"*";
		  }
		  cout<<endl;
	
		  n+=1;
		  n1-=5;
		  n2+=5;
		  n3+=5;
		  }
	
	n=1;
	while(n<=32)
	{
		 cout<<"*";
		 n+=1;
	}
	
	cout<<endl;
	
	return 0;
}
