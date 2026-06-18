#include <iostream>
#include <cmath>
using namespace std;

double calculateVolume(double, double , double);
double calculateVolume(double, double);
double calculateVolume(double sideLength);

int main()
{
 	cout<<endl<<"Name : Muhammad Moiz Ansari"<<endl;
 	cout<<"Roll No : 23i-0523"<<endl<<endl;
	
	int n, s, l, w, h, r, ch;
	cout<<"Which shape you want to calculate volume: \n";
	cout<<"1. Cube\n2. Cuboid\n3. Cylinder\n";
	cout<<"Enter choice: ";
	cin>>ch;
	
	switch(ch)
	{
	case 1:
	cout<<"Enter sidelength for volume of cube: \n";
	cin>>s;
	cout<<"Volume of a cube with side length"<<s<<"is: "<<calculateVolume(s)<<endl;
	break;
	
	case 2:
	cout<<"Enter length, width and height for volume of cuboid: \n";
	cin>>l>>w>>h;
	cout<<"Volume of a cuboid with dimensions "<<l<<"x"<<w<<"x"<<h<<" is: "<<calculateVolume(l, w, h)<<endl;
	break;
	
	case 3:
	cout<<"Enter radius and height for volume of cylinder: \n";
	cin>>r>>h;
	cout<<"Volume of a cylinder with radius "<<r<<" and height"<<h<<" is: "<<calculateVolume(r, h)<<endl;
	break;
	
	default:
	cout<<"Choose only 1, 2 or 3\n";
	}
	return 0;
}
double calculateVolume(double sideLength)
{
	double V;
	V=pow(sideLength, 3);
	return V;
}
double calculateVolume(double length, double width, double height)
{
	double V;
	V=length*width*height;
	return V;
}
double calculateVolume(double radius, double height)
{
	double V;
	const double pi=3.14;
	V=pi*pow(radius, 2)*height;
	return V;
}





