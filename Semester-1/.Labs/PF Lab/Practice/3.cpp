#include <iostream>
#include <cmath>
#include <unistd.h>

using namespace std;
int main()

{
	char r;			
	int a=0, b=0;	
	double S,		
		   s=0,		
		   s_ins=0,	
		   v0,		
		   v=50,	
		   v_ins,	
		   T,		
		   s_ex;	
	double t=0;		
	const float g=9.8;
	const double dt=0.01;
	const double dv=-g*dt;
	
	cout<<"Enter Initial Velocity in range [50,150]: ";
	cin>>v0;
	
	while(v0<0)		//Input validation
	{
		 cout<<"Invalid input"<<endl;
		 cout<<"Enter positive value): ";
		 cin>>v0;
	}
	
	while(v0<50 || v0>150)		//Range validation
	{
		 cout<<"Out of Range"<<endl;
		 cout<<"Enter value in range [50,150]: ";
		 cin>>v0;
	}
	cin.ignore(1,'\n');
	cout<<endl;
	
	T=v0/g;		//Time for maximum height
	S = v0*T - 0.5*g*(double)(T*T);	//Maximum vertical distance
	int y=0, oop=1;

cout<<"T="<<2*T<<endl;
cout<<"S="<<S<<endl;

	for(int i=2*T; i>=0; i-=1)		//Full program loop
	{
	   cout<<"Press Enter to print graph: ";
	   cin.get(r);
	   cout<<endl;
	   system("clear");
	   cout<<endl;
	   
	   for(int yaxis=s_ins; yaxis>=0; yaxis-=1)	//Full y-axis loop
	   {
	 	  if(a==b)
	   	  {
	   		for(int top=S; top>s_ins; top-=1)	//Loop for y-axis above printing value
	   		{
	   		   cout.flush();
			   usleep(1000);
	   		   cout<<top<<"\t|";		//Printing y-axis
	   		   cout<<endl;
	   		}
	   	  }
	   		   
	   	  if(yaxis==(int)s_ins)		//Printing ball condition
	   	  {
	   		cout<<yaxis<<"\t|\tO"<<endl;
	   		++b;
	   	  }
	   	  else						//Printing y-axis below printing value
	   	  {
	   		  cout.flush();
			  usleep(1000);
	   		  cout<<yaxis<<"\t|";		//Printing y-axis
	   		  cout<<endl;
	   	  }
	   }
	   
	   s_ex = v0*t - 0.5*g*(double)(t*t);	//Exact formula value of position of ball
	   
	   cout<<endl<<"Exact formula value:\t\t\b\b\b\b"<<s_ex<<endl;
	   cout<<"Position value from graph:\t\b\b\b\b"<<s_ins<<endl<<endl;
	   
	   for(int j=1; j<=100; ++j)	//Loop for calculating values for every second with 0.01 secong change
	   {
	      v=v-(g*dt);
	   	  s=s+(v*dt);
	   	  t=t+dt;
	   }
	   
	   v_ins=v;
	   s_ins=s;
	   
	   a+=1;	//Incrementing checking value
	   
	}
	
	cout<<endl;
	
	return 0;
}
