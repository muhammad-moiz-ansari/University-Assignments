#include <iostream>
#include "23i-0523_Moiz Ansari_Q1.h"
using namespace std;

int main()
{
	Drink* bottle;

	string flavor, expiry_date, supplier, type;
	float temperature, price;

	cout << "Enter Flavor: ";
	cin >> flavor;
	cout << "Enter Temperature: ";
	cin >> temperature;
	cout << "Enter Expiry Date: ";
	cin >> expiry_date;
	cout << "Enter Price: ";
	cin >> price;
	cout << "Enter Supplier: ";
	cin >> supplier;

	cout << "\nWater:\n";

	bottle = new Water(flavor, temperature, price, expiry_date, supplier);
	bottle->Display();
	delete bottle;

	cout << "Enter Type: ";
	cin >> type;

	cout << "\n\nCarbonated Water:\n";

	bottle = new Carbonated(flavor, temperature, price, expiry_date, supplier, type);
	bottle->Display();
	delete bottle;

	bottle = NULL;



	return 0;
}