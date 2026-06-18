/*    Problem 8

Made By : Muhammad Moiz Ansari
Student ID : 23i-0523
Assignment # 1

*/

#include <iostream>
#include <iomanip>
using namespace std;
int main()
{
    float g, b1, b2, b3, b4, bill, a1, a2, a3, a4;
    cout<<"Enter Number of Gallons Consumed : ";	//Taking input
    cin>>g;
    cout<<endl;
    
    //Calculating bills for specific conditions
    
    bool a=g<=100;
    a1=0.45*g;
    b1=(a1+a1*0.14)*a;
    
    bool b=(g<=350 && g>100);
    a2=(100*0.45)+(0.85*g);
    b2=(a2+a2*0.14)*b;
    
    bool c=(g<=600 && g>350);
    a3=(100*0.45)+(250*0.85)+(1.45*g);
    b3=(a3+a3*0.14)*c;
    
    bool d=(g>600);
    a4=(100*0.45)+(250*0.85)+(250*1.45)+(2.60*g);
    b4=(a4+a4*0.14)*d;
    
    bill=b1+b2+b3+b4;
    
    cout<<"Bill : "<<fixed<<setprecision(2)<<bill<<" $"<<endl;	//Printing bill

    return 0;
}


