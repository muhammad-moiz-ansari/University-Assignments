#pragma once
#include <iostream>
#include <string>
using namespace std;

///////////////////////////////
//                           //
//          Battery          //
//                           //
///////////////////////////////

class Battery
{
private:
    int Capacity;
    double price;

public:
    //Constructors:
    Battery();
    Battery(int cap, double p);

    //Setters:
    void setCapacity(int cap);
    void setPrice(double p);

    //Getters:
    int getCapacity();
    double getPrice();
};

//////////////////////////////
//                          //
//         Battery          //
//                          //
//////////////////////////////

//Constructors:
Battery::Battery()
{
    Capacity = 0;
    price = 0;
}
Battery::Battery(int cap, double p = 0)
{
    Capacity = cap;
    price = p;
}

//Setters:
void Battery::setCapacity(int cap)
{
    Capacity = cap;
}
void Battery::setPrice(double p)
{
    price = p;
}

//Getters:
int Battery::getCapacity()
{
    return Capacity;
}
double Battery::getPrice()
{
    return price;
}