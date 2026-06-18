/*    Problem 2(b)

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 2

*/

#include <iostream>
using namespace std;
int main()

{
	int a=8, b=1;
	string n1=" ", n2="*", n3, n4;
	
	//First two lines...
	for(int i=1; i<=2; ++i)			
	{
	   for(int j=1; j<=10; ++j)
	   {
	      if(i==1)
	   	  {
		    if(j==9)
	     	  cout<<"*";
	   	  	else
	   		    cout<<" ";
	   	  }
	      if(i==2)
	      {
	        if(j==8 || j==10)
	     	  cout<<"-";
	   	  	else
	   		    cout<<" ";
	   	  }
	   	  
	   }
	   cout<<endl;
	}
	//(1-2)end
	
	//Lines 3-7:
	int st1=7, st2=11, d1=9, d2=9;
	int s1=1, s2=6, s3=8, s4=10, s5=9, s6=9, s7=12, s8=17;
	
	for(int i=1; i<=5; ++i)
	{
	   for(int j=1; j<=17; ++j)
	   {
		  if(i%2!=0)
		  {
	 		if(j==st1 || j==st2)
	 		  cout<<"*";
	 		if(j==d1 || j==d2)
	 		  cout<<"-";
	 		if((j>=s1 && j<=s2) || j==s3 || (j>=s4 && j<=s5) || j==s6 || (j>=s7 && j<=s8))
	 			cout<<" ";
	 	  }
	 	  
	 	  if(i%2==0)
		  {
	 		if(j==d1 || j==d2)
	 		  cout<<"*";
	 		if(j==st1 || j==st2)
	 		  cout<<"-";
	 		if((j>=s1 && j<=s2) || j==s3 || (j>=s4 && j<=s5) || j==s6 || (j>=s7 && j<=s8))
	 			cout<<" ";
	 	  }


	    }
	/*For Dry Run:
	cout<<endl;
	cout<<"s="<<" "<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<" "<<s5<<" "<<s6<<" "<<s7<<" "<<s8<<endl;
	cout<<"i="<<i<<endl;

	cout<<"d1="<<d1<<endl;
	cout<<"d2="<<d2<<endl;
	cout<<"st1="<<st1<<endl;
	cout<<"st2="<<st2<<endl;
	*/
	    cout<<endl;
	 	  
	 	  --st1;
	 	  --d1;
	 	  ++st2;
	 	  ++d2;
	 	  
	 	  --s2;
	 	  --s3;
	 	  --s4;
	 	  ++s5;
	 	  ++s6;
	 	  ++s7;
	 	  
	      a+=1;
	}
	//(3-7)end
	
	//Lines 8-16:
	int n=5, o=13, k=8, l=0, m=18;
	for(int i=8; i<=16; ++i)
	{
	   if(i==8)						//Line 8
	   { for(int j=1; j<=16; ++j)
		 {
		    if(j==2 || j==16)
		      cout<<"-";
		    if(j==1 || j==3 || j==15)
		      cout<<" ";
		    if((j>=n && j<=k) || (j>=10 && j<=14) || j==4)
		      cout<<"*";
		    if(j==9)
		      cout<<"1";
		  }
	    }
	     
	   if(i==9)						//Line 9
	   { for(int j=1; j<=17; ++j)
		 {
		    if(j==3 || j==15)
		      cout<<"-";
		    if(j==2 || j==4 || j==14 || j==16)
		      cout<<" ";
		    if(j==1 || (j>=n && j<=k) || (j>=11 && j<=13) || j==17)
		      cout<<"*";
		    if(j==8 || j==10)
		      cout<<"1";
		    if(j==9)
		      cout<<"2";
		 }
	   }
	   
	   if(i==10)					//Line 10
	   { for(int j=1; j<=17; ++j)
		 {
		    if(j==1 || j==17)
		      cout<<"-";
		    if(j==2 || j==4 || j==14 || j==16)
		      cout<<" ";
		    if(j==3 || (j>=n && j<=k) || (j>=12 && j<=13) || j==15)
		      cout<<"*";
		    if(j==7 || j==11)
		      cout<<"1";
		    if((j==8 || j==10))
		      cout<<"2";
		    if(j==9)
		      cout<<"3";
		 }
	   }
	   
	   if(i==11)					//Line 11
	   { for(int j=1; j<=17; ++j)
		 {
		    if(j==3 || j==15)
		      cout<<"-";
		    if(j==2 || j==4 || j==14 || j==16)
		      cout<<" ";
		    if(j==1 || (j>=n && j<=k) || (j==13) || j==17)
		      cout<<"*";
		    if(j==6 || j==12)
		      cout<<"1";
		    if((j==7 || j==11))
		      cout<<"2";
		    if((j==8 || j==10))
		      cout<<"3";
		    if(j==9)
		      cout<<"4";
		 }
	   }
	   
	   if(i==12)					//Line 12
	   { for(int j=1; j<=17; ++j)
		 {
		    if(j==1 || j==17)
		      cout<<"-";
		    if(j==2 || j==4 || j==14 || j==16)
		      cout<<" ";
		    if(j==3 || j==15)
		      cout<<"*";
		    if((j==5 || j==13))
		      cout<<"1";
		    if(j==6 || j==12)
		      cout<<"2";
		    if((j==7 || j==11))
		      cout<<"3";
		    if((j==8 || j==10))
		      cout<<"4";
		    if(j==9)
		      cout<<"5";
		 }
	   }
	   
	   if(i==13)					//Line 13
	   { for(int j=1; j<=17; ++j)
		 {
		    if(j==3 || j==15)
		      cout<<"-";
		    if(j==2 || j==4 || j==14 || j==16 || (j>=10 && j<=m-1))
		      cout<<" ";
		    if(j==1 || (j>=n && j<=l) || (j>=m && j<=o) || j==17)
		      cout<<"*";
		    if(j==6)
		      cout<<"1";
		    if(j==7)
		      cout<<"2";
		    if(j==8)
		      cout<<"3";
		    if(j==9)
		      cout<<"4";
		 }
	   }
	   
	   if(i==14)					//Line 14
	   { for(int j=1; j<=17; ++j)
		 {
		    if(j==1 || j==17)
		      cout<<"-";
		    if(j==2 || j==4 || j==14 || j==16 || (j>=10 && j<=m-1))
		      cout<<" ";
		    if(j==3 || (j>=n && j<=l) || (j>=m && j<=o) || j==15)
		      cout<<"*";
		    if(j==7)
		      cout<<"1";
		    if(j==8)
		      cout<<"2";
		    if(j==9)
		      cout<<"3";
		 }
	   }
	   
	   if(i==15)					//Line 15
	   { for(int j=1; j<=17; ++j)
		 {
		    if(j==3 || j==15)
		      cout<<"-";
		    if(j==2 || j==4 || j==14 || j==16 || (j>=10 && j<=m-1))
		      cout<<" ";
		    if(j==1 || (j>=n && j<=l) || (j>=m && j<=o) || j==17)
		      cout<<"*";
		    if(j==8)
		      cout<<"1";
		    if(j==9)
		      cout<<"2";
		 }
	   }
	   
	   if(i==16)					//Line 16
	   { for(int j=1; j<=17; ++j)
		 {
		    if(j==1 || j==17)
		      cout<<"-";
		    if(j==2 || j==4 || j==14 || j==16 || (j>=10 && j<=m-1))
		      cout<<" ";
		    if(j==3 || (j>=n && j<=l) || (j>=m && j<=o) || j==15)
		      cout<<"*";
		    if(j==9)
		      cout<<"1";
		 }
	   }
	   
		 --k;
		 ++l;
		 --m;
		 cout<<endl; 
	}
	//(8-16)end	 
	
	//Lines 17-22:
	st1=2, st2=16, d1=4, d2=14;
	s1=1, s2=1, s3=3, s4=5, s5=13, s6=15, s7=17, s8=17;
	
	for(int i=1; i<=6; ++i)
	{
	   for(int j=1; j<=17; ++j)
	   {
		  if(i%2!=0)
		  {
	 		if(j==st1 || j==st2)
	 		  cout<<"*";
	 		if(j==d1 || j==d2)
	 		  cout<<"-";
	 		if((j>=s1 && j<=s2) || j==s3 || (j>=s4 && j<=s5) || j==s6 || (j>=s7 && j<=s8))
	 			cout<<" ";
	 	  }
	 	  
	 	  if(i%2==0)
		  {
	 		if(j==d1 || j==d2)
	 		  cout<<"*";
	 		if(j==st1 || j==st2)
	 		  cout<<"-";
	 		if((j>=s1 && j<=s2) || j==s3 || (j>=s4 && j<=s5) || j==s6 || (j>=s7 && j<=s8))
	 			cout<<" ";
	 	  }


	    }
	/*For Dry Run:
	cout<<endl;
	cout<<"s="<<" "<<s1<<" "<<s2<<" "<<s3<<" "<<s4<<" "<<s5<<" "<<s6<<" "<<s7<<" "<<s8<<endl;
	cout<<"i="<<i<<endl;

	cout<<"d1="<<d1<<endl;
	cout<<"d2="<<d2<<endl;
	cout<<"st1="<<st1<<endl;
	cout<<"st2="<<st2<<endl;
	*/
	    cout<<endl;
	 	  
	 	  st1+=1;
	 	  d1+=1;
	 	  st2-=1;
	 	  d2-=1;
	 	  
	 	  ++s2;
	 	  ++s3;
	 	  ++s4;
	 	  --s5;
	 	  --s6;
	 	  --s7;
	 	  
	      a+=1;
	}
	//(17-22)end
	
	//Lines 23-24:
	for(int i=1; i<=2; ++i)
	{
	   for(int j=1; j<=10; ++j)
	   {
	      if(i==1)
	      {
	        if(j==8 || j==10)
	     	  cout<<"*";
	   	  	else
	   		    cout<<" ";
	   	  }
	   	  if(i==2)
	   	  {
		    if(j==9)
	     	  cout<<"-";
	   	  	else
	   		    cout<<" ";
	   	  }
	   }
	   cout<<endl;
	}
	//(23-24)end
	
	cout<<endl;
	
	
	return 0;
}
