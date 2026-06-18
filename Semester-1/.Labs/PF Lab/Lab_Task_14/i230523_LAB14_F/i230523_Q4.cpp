#include <iostream>
using namespace std;

void C_to_K(float &C);
void K_to_F(float &C);
void F_to_C(float &C);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	float C, F, K;
	
	cout<<"Enter temperature in Centigrade: ";
	cin>>C;
	
	cout<<endl;
	
	C_to_K(C);
	cout<<"\nCentigrade to Kelvin: "<<C;
	
	K_to_F(C);
	cout<<"\nKelvin to Fahrenhiet: "<<C;
	
	F_to_C(C);
	cout<<"\nFahrenhiet to Centigrade: "<<C<<endl;
	
	
	return 0;
	
	
}
void C_to_K(float &C)
{
	C=C+273.15;
}

void K_to_F(float &C)
{
	C = ((C - 273.15) * 1.8) + 32;
}
void F_to_C(float &C)
{
	C=(C-32) * 5.0/9;
}


