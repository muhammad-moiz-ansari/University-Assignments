#include <iostream>
#include "23i-0523_Moiz Ansari_Q2.h"
using namespace std;

int main()
{
	ParkingGarage g;

	cout << "Is full? " << g.IsFull()<<endl;

	g.initialize();

	g.ParkCar();
	g.ParkCar();
	g.ParkCar();

	cout << "Is full? " << g.IsFull()<<endl;

	g.ParkCar();
	g.ParkCar();
	g.ParkCar();

	g.print();

	g.RemoveCar(3, 22);

	g.print();
}